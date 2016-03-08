//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLACACHESTRATEGY_H__
#define __FLACACHESTRATEGY_H__

#include <functional>
#include <atomic>
#include "FlaConfig.h"
#include "FlaDefinition.h"
#include "FlaTexturePackage.h"

namespace fla
{
    class TextureFrame;
}

class FlaCacheInfo
{
public:
    FlaCacheInfo();
    bool isOK() const;
    float getWholeScale() const
    {
        return contentScale * movieScale;
    }

    FlaDefinition node;
    FlaDefinition root;
    float contentScale;
    float movieScale;
    float morphRatio;
};

////////////////////////////////////////////////////////////
// 纹理缓存策略
class FlaCacheStrategy
{
public:
    static void beginPreload();
    static void endPreload();

    FlaCacheStrategy();
    virtual ~FlaCacheStrategy();

    typedef fla::TextureFrame TextureFrame;
    typedef std::function<void(TextureFrame* spriteFrame)> AsyncCallback;

    virtual size_t preload(const FlaDefinition& root,
                           const FlaDefinition& state,
                           float scale,
                           const AsyncCallback& callback);

    virtual TextureFrame* cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback) = 0;
    virtual TextureFrame* cache(const FlaCacheInfo& info) = 0;

    void setPixelFormat(FlaPixelFormat format);
    FlaPixelFormat getPixelFormat() const;

private:
    FlaPixelFormat _pixelFormat;
};

/////////////////////////////////////////////////////////////////
// 默认的纹理缓存, 直接使用Cocos2d的纹理缓存
class FlaCocos2dCacheStrategy : public FlaCacheStrategy
{
public:
    virtual TextureFrame* cache(const FlaCacheInfo& info) override;
    virtual TextureFrame* cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback) override;
};

/////////////////////////////////////////////////////////////////
// 文件缓存
class FlaFileCacheStrategy : public FlaCacheStrategy
{
public:
    static void removeAllDefaultCaches();

    FlaFileCacheStrategy();
    FlaFileCacheStrategy(const std::string& cachePath);

    virtual TextureFrame* cache(const FlaCacheInfo& info) override;
    virtual TextureFrame* cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback) override;

    void setCacheDirectory(const std::string& cachePath)
    {
        _cacheDirectory = cachePath;
    }

    const std::string& getCacheDirectory() const
    {
        return _cacheDirectory;
    }

protected:
    void letDirectoryExits();

private:
    void removeAllCaches();
    std::string _cacheDirectory;
};

//////////////////
// 碎图合并
class FlaTexturePackCacheStrategy : public FlaFileCacheStrategy
{
public:
    FlaTexturePackCacheStrategy(const std::string& filePath);
    FlaTexturePackCacheStrategy();

    virtual size_t preload(const FlaDefinition& root,
                           const FlaDefinition& state,
                           float scale,
                           const AsyncCallback& callback) override;

    virtual TextureFrame* cache(const FlaCacheInfo& info) override;
    virtual TextureFrame* cacheAsync(const FlaCacheInfo& info, const AsyncCallback& callback) override;

    void retain();
    void release();

protected:
    virtual bool isInTexturePackage(const FlaCacheInfo& info, int* packageId) const = 0;
    virtual FlaTexturePackage packTexturePackage(const FlaCacheInfo& info, int packageId) = 0;

private:
    std::atomic<uint16_t> _refCount;
};

//////////////////////////////////////////////////////////////////////
class FlaAllTexturePackCacheStrategy : public FlaTexturePackCacheStrategy
{
public:
    FlaAllTexturePackCacheStrategy();
    FlaAllTexturePackCacheStrategy(const std::string& cachePath);

protected:
    virtual bool isInTexturePackage(const FlaCacheInfo& info, int* packageId) const override;
    virtual FlaTexturePackage packTexturePackage(const FlaCacheInfo& info, int packageId) override;
};

#endif
