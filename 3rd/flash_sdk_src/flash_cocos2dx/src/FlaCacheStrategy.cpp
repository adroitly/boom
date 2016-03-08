//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaCacheStrategy.h"
#include <map>
#include "./fla_TextureFrame.h"
#include "libra/libra_fsys.h"
#include "libra/libra_path.h"
#include "../FlaResourceCache.h"
#include "fla_TexturePackage.h"
#include "./fla_AsynManager.h"
#include "fla_cocos2d_Texture.h"
#include "fla_Settings.h"
#include "../../core/utility/fla_MD5.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "../../core/graphics/fla_transToImage.h"
using namespace cocos2d;

/////////////////////

FlaCacheInfo::FlaCacheInfo() : movieScale(1.0), morphRatio(0.0)
{
    contentScale = fla::settings::getTextureContentScale();
}

bool FlaCacheInfo::isOK() const
{
    return !node.isNull() && !root.isNull();
}

static fla::TextureFrame* createAndCacheSpriteFrame(cocos2d_bridge::Texture2D* texture2d, const std::string& key)
{
    auto textureId = FlaResourceCache::getInstance().addTexture2d(key, texture2d);

    cocos2d_bridge::Rect rectInPixels(0.0, 0.0, 0.0, 0.0);
    rectInPixels.size = texture2d->getContentSizeInPixels();
    auto rect = fla::pixels_to_points(rectInPixels);
    auto frame = fla::TextureFrame::create(textureId, rect, rectInPixels, false);
    FlaResourceCache::getInstance().setTextureFrame(frame, key);

    frame->setTexture(texture2d);
    return frame;
}

//////////////////////
static fla::TextureFrame* s_findCacheFrame(const FlaCacheInfo& info, std::string* key)
{
    assert(info.isOK());
    assert(key);

    FlaDefinition node = info.node;
    *key = fla::keyOfCache(node.getDataMd5(), node.getId(), 0, info.getWholeScale(), info.morphRatio);
    return FlaResourceCache::getInstance().getTextureFrame(*key);
}

static std::function<fla::BitmapData::Ptr()> s_makeTransToBitmap(const fla::Definition::Ptr& definition,
                                                                 float scale,
                                                                 float ratio,
                                                                 fla::PixelFormat format,
                                                                 const std::string& filePath)
{
    return [=]
    {
        auto bitmapData = fla::transToBitmapData(definition, scale, ratio, format);
        if (!filePath.empty())
        {
            fla::saveBitmapToPngFile(bitmapData, filePath);
        }
        return bitmapData;
    };
}

template <typename T>
static void s_bitmapCallback(const fla::BitmapData::Ptr& bitmapData,
                             fla::PixelFormat pixelFormat,
                             const std::string& keyOfCache,
                             const T& callback)
{
    if (bitmapData)
    {
        auto texture2D = fla::bitmap_transToTexture(bitmapData.get(), pixelFormat);
        if (texture2D)
        {
            auto spriteFrame = createAndCacheSpriteFrame(texture2D, keyOfCache);
            callback(spriteFrame);
        }
        else
        {
            callback(nullptr);
        }
    }
    else
    {
        callback(nullptr);
    }
}

#define CHECK_SPRITE_FRAME(spriteFrame) \
    if (spriteFrame)                    \
    {                                   \
        return spriteFrame;             \
    }

static inline fla::AsyncManager& s_aysncManager()
{
    return fla::AsyncManager::getInstance();
}

void FlaCacheStrategy::beginPreload()
{
    fla::AsyncManager::getInstance().suspendFuture();
}

void FlaCacheStrategy::endPreload()
{
    fla::AsyncManager::getInstance().resumeAll();
}

void FlaCacheStrategy::setPixelFormat(FlaPixelFormat format)
{
    _pixelFormat = format;
}

FlaPixelFormat FlaCacheStrategy::getPixelFormat() const
{
    return _pixelFormat;
}

FlaCacheStrategy::~FlaCacheStrategy()
{
}

FlaCacheStrategy::FlaCacheStrategy() : _pixelFormat(FlaPixelFormat::RGBA8888)
{
}

void FlaTexturePackCacheStrategy::retain()
{
    _refCount.fetch_add(1);
}

void FlaTexturePackCacheStrategy::release()
{
    auto refCount = _refCount.fetch_sub(1);
    if (refCount == 1)
    {
        delete this;
    }
}

size_t FlaCacheStrategy::preload(const FlaDefinition& root,
                                 const FlaDefinition& state,
                                 float scale,
                                 const AsyncCallback& callback)
{
    std::map<int, FlaDefinition> nodes;
    state.walkChildren([&](const FlaDefinition& node, int level)
                       {
                           FLA_UNUSED(level);
                           if (node.getMovieType() == FlaMovieType::Shape)
                           {
                               nodes[node.getId()] = node;
                           }
                       });

    FlaCacheInfo cacheInfo;
    cacheInfo.morphRatio = 0;
    cacheInfo.movieScale = scale;
    cacheInfo.root = root;

    size_t totalSize = 0;
    for (auto& pair : nodes)
    {
        cacheInfo.node = pair.second;
        if (!cacheAsync(cacheInfo, callback))
        {
            totalSize++;
        }
    }
    return totalSize;
}

fla::TextureFrame* FlaCocos2dCacheStrategy::cache(const FlaCacheInfo& info)
{
    assert(info.isOK());

    std::string keyOfCache;
    auto spriteFrame = s_findCacheFrame(info, &keyOfCache);
    CHECK_SPRITE_FRAME(spriteFrame);

    auto texture2D = info.node.transToTexture(info.movieScale, info.morphRatio, getPixelFormat());
    spriteFrame = createAndCacheSpriteFrame(texture2D, keyOfCache);

    return spriteFrame;
}

fla::TextureFrame* FlaCocos2dCacheStrategy::cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback)
{
    assert(info.isOK());

    std::string keyOfCache;
    fla::TextureFrame* spriteFrame = s_findCacheFrame(info, &keyOfCache);
    CHECK_SPRITE_FRAME(spriteFrame);

    auto pixelformat = static_cast<fla::PixelFormat>(getPixelFormat());
    auto action = s_makeTransToBitmap(info.node.getRaw(), info.movieScale, info.morphRatio, pixelformat, std::string());

    s_aysncManager().async(action,
                           [=](const fla::BitmapData::Ptr& bitmapData)
                           {
                               s_bitmapCallback(bitmapData, pixelformat, keyOfCache, callback);
                           });

    return nullptr;
}

///////////////////////
void FlaFileCacheStrategy::removeAllDefaultCaches()
{
    FlaFileCacheStrategy().removeAllCaches();
}

FlaFileCacheStrategy::FlaFileCacheStrategy()
{
    auto directory = cocos2d_bridge::FileUtils_getInstance()->getWritablePath();
    directory = libra::path_join(directory, "TextureCache");
    setCacheDirectory(directory);
}

FlaFileCacheStrategy::FlaFileCacheStrategy(const std::string& cachePath)
{
    setCacheDirectory(cachePath);
}

void FlaFileCacheStrategy::removeAllCaches()
{
    fsys_rmdir_contents(_cacheDirectory.c_str());
}

void FlaFileCacheStrategy::letDirectoryExits()
{
    fsys_let_dir_exists(_cacheDirectory.c_str());
}

fla::TextureFrame* FlaFileCacheStrategy::cache(const FlaCacheInfo& info)
{
    assert(info.isOK());

    std::string keyOfCache;
    fla::TextureFrame* spriteFrame = s_findCacheFrame(info, &keyOfCache);
    CHECK_SPRITE_FRAME(spriteFrame);

    // 去查找文件
    cocos2d_bridge::Texture2D* texture2D = nullptr;
    auto path = libra::path_join(_cacheDirectory, keyOfCache);

    if (fsys_is_exists(path.c_str()))
    {
        texture2D = FlaBitmapData::loadPngTexture(path, getPixelFormat());
    }

    // 没有，重新生成
    if (texture2D == nullptr)
    {
        letDirectoryExits();
        auto bitmapData = info.node.transToBitmap(info.movieScale, info.morphRatio, getPixelFormat());
        texture2D = bitmapData.transToTexture(getPixelFormat());
        bitmapData.saveAsPngAsync(path);
    }

    assert(texture2D);
    spriteFrame = createAndCacheSpriteFrame(texture2D, keyOfCache);
    return spriteFrame;
}

fla::TextureFrame* FlaFileCacheStrategy::cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback)
{
    assert(info.isOK());

    std::string keyOfCache;
    fla::TextureFrame* spriteFrame = s_findCacheFrame(info, &keyOfCache);
    CHECK_SPRITE_FRAME(spriteFrame);

    auto pixelformat = static_cast<fla::PixelFormat>(getPixelFormat());
    auto path = libra::path_join(_cacheDirectory, keyOfCache);
    if (fsys_is_exists(path.c_str()))
    {
        auto action = [=]
        {
            return fla::loadBitmapFromPngFile(path, pixelformat);
        };
        s_aysncManager().async(action,
                               [=](const fla::BitmapData::Ptr& bitmapData)
                               {
                                   s_bitmapCallback(bitmapData, pixelformat, keyOfCache, callback);
                               });
    }
    else
    {
        letDirectoryExits();
        auto action = s_makeTransToBitmap(info.node.getRaw(), info.movieScale, info.morphRatio, pixelformat, path);
        s_aysncManager().async(action,
                               [=](const fla::BitmapData::Ptr& bitmapData)
                               {
                                   s_bitmapCallback(bitmapData, pixelformat, keyOfCache, callback);
                               });
    }
    return nullptr;
}

///////////////////////////////
inline static std::string s_getPackageName(const FlaCacheInfo& info, int packageId)
{
    return fla::keyOfCache(info.root.getDataMd5(), info.root.getId(), packageId, info.getWholeScale(), 0);
}

FlaTexturePackCacheStrategy::FlaTexturePackCacheStrategy(const std::string& filePath) : FlaFileCacheStrategy(filePath)
{
    _refCount = 1;
}

FlaTexturePackCacheStrategy::FlaTexturePackCacheStrategy()
{
    _refCount = 1;
}

fla::TextureFrame* FlaTexturePackCacheStrategy::cache(const FlaCacheInfo& info)
{
    int packageId = 0;
    if (info.node.getMovieType() != FlaMovieType::Shape || !isInTexturePackage(info, &packageId))
    {
        return FlaFileCacheStrategy::cache(info);
    }

    auto key = fla::keyOfCache(info.node.getRaw(), info.getWholeScale());
    auto packageName = s_getPackageName(info, packageId);

    // 检查是否已经载入内存
    auto spriteFrame = fla::TexturePackage::getSpriteFrame(key);
    CHECK_SPRITE_FRAME(spriteFrame);

    // 从文件中载入
    auto pixelFormat = getPixelFormat();
    if (FlaTexturePackage::load(getCacheDirectory(), packageName, pixelFormat))
    {
        spriteFrame = fla::TexturePackage::getSpriteFrame(key);
        CHECK_SPRITE_FRAME(spriteFrame);
    }
    // 动态生成
    auto package = packTexturePackage(info, packageId);
    if (!package.isNull())
    {
        letDirectoryExits();
        package.transToSpriteFrames(getCacheDirectory(), packageName);
        package.saveAsPngAsync(getCacheDirectory(), packageName);
        spriteFrame = fla::TexturePackage::getSpriteFrame(key);
        CHECK_SPRITE_FRAME(spriteFrame);
    }
    return FlaFileCacheStrategy::cache(info);
}

fla::TextureFrame* FlaTexturePackCacheStrategy::cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback)
{
    int packageId = 0;
    if (info.node.getMovieType() != FlaMovieType::Shape || !isInTexturePackage(info, &packageId))
    {
        return FlaFileCacheStrategy::cacheAsync(info, callback);
    }

    auto key = fla::keyOfCache(info.node.getRaw(), info.getWholeScale());
    auto packageName = s_getPackageName(info, packageId);
    // 检查是否已经载入内存
    auto spriteFrame = fla::TexturePackage::getSpriteFrame(key);
    CHECK_SPRITE_FRAME(spriteFrame);

    // 从文件载入
    auto pixelFormat = getPixelFormat();
    bool canFromFile = FlaTexturePackage::loadAsync(getCacheDirectory(),
                                                    packageName,
                                                    pixelFormat,
                                                    [=]
                                                    {
                                                        auto spriteFrame = fla::TexturePackage::getSpriteFrame(key);
                                                        callback(spriteFrame);
                                                    });

    if (canFromFile)
    {
        return nullptr;
    }

    // 动态生成
    this->retain();
    auto directory = getCacheDirectory();
    s_aysncManager().async(
        [=]
        {
            auto package = this->packTexturePackage(info, packageId);
            if (!package.isNull())
            {
                letDirectoryExits();
                package.saveAsPng(directory, packageName);
            }
            return package;
        },
        [=](FlaTexturePackage package)
        {
            this->release();
            package.transToSpriteFrames(directory, packageName);
            auto spriteFrame = fla::TexturePackage::getSpriteFrame(key);
            callback(spriteFrame);
        });
    return nullptr;
}

size_t FlaTexturePackCacheStrategy::preload(const FlaDefinition& root,
                                            const FlaDefinition& state,
                                            float scale,
                                            const AsyncCallback& callback)
{
    FlaCacheInfo cacheInfo;
    cacheInfo.morphRatio = 0;
    cacheInfo.movieScale = scale;
    cacheInfo.root = root;

    std::map<int, FlaDefinition> packages;
    std::map<int, FlaDefinition> nodes;
    state.walkChildren([&](const FlaDefinition& node, int level)
                       {
                           FLA_UNUSED(level);
                           if (node.getMovieType() == FlaMovieType::Shape)
                           {
                               cacheInfo.node = node;
                               int packageId = 0;
                               if (isInTexturePackage(cacheInfo, &packageId))
                               {
                                   if (packages.count(packageId) == 0)
                                   {
                                       packages[packageId] = node;
                                   }
                               }
                               else
                               {
                                   nodes[node.getId()] = node;
                               }
                           }
                       });

    for (auto& pair : packages)
    {
        nodes[pair.second.getId()] = pair.second;
    }
    size_t totalSize = 0;
    for (auto& pair : nodes)
    {
        cacheInfo.node = pair.second;
        if (!cacheAsync(cacheInfo, callback))
        {
            totalSize++;
        }
    }
    return totalSize;
}

////////////////////////
FlaAllTexturePackCacheStrategy::FlaAllTexturePackCacheStrategy()
{
}

FlaAllTexturePackCacheStrategy::FlaAllTexturePackCacheStrategy(const std::string& cachePath)
    : FlaTexturePackCacheStrategy(cachePath)
{
}

bool FlaAllTexturePackCacheStrategy::isInTexturePackage(const FlaCacheInfo& info, int* packageId) const
{
    FLA_UNUSED(info);
    if (packageId)
    {
        *packageId = 0;
    }
    return true;
}

FlaTexturePackage FlaAllTexturePackCacheStrategy::packTexturePackage(const FlaCacheInfo& info, int packageId)
{
    FLA_UNUSED(packageId);
    return FlaTexturePackage::packShapes(info.root, info.movieScale, getPixelFormat());
}
