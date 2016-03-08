//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_TexturePackage.h"
#include "fla_Settings.h"
#include "fla_cocos2d_Texture.h"
#include "libra/libra_path.h"
#include "../../core/texture_pack/fla_TPTexturePacker.h"
#include "libra/libra_string.h"
#include "clover/ScopeGuard.h"
#include "fla_cocos2d_Texture.h"
#include "fla_Settings.h"
#include "libra/libra_strbuf.h"
#include "libra/libra_fsys.h"
#include "libra/libra_path.h"
#include "./fla_AsynManager.h"
#include "../../core/base/fla_utils.h"
#include "libra/libra_math.h"
#include "../FlaResourceCache.h"
#include "fla_Settings.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include <boost/algorithm/string.hpp>

namespace fla
{
    static rbp::RectSize s_computeTextureSize(const rbp::RectSize& size)
    {
        int maxTextureSize = cocos2d_bridge::Configuration_getInstance()->getMaxTextureSize();
        int binSize = libra::max3(size.width, size.height, maxTextureSize);
        binSize = static_cast<int>(libra_next_pot(binSize));
        return rbp::RectSizeMake(binSize, binSize);
    }

    template <typename PackFun>
    static std::vector<tp::TextureOuput> s_createTextureOut(PixelFormat format, PackFun&& packFun)
    {
        std::vector<tp::TextureOuput> result;
        tp::TexturePacker packer(s_computeTextureSize);
        if (packFun(packer))
        {
            if (cocos2d_bridge::Configuration_getInstance()->supportsNPOT())
            {
                packer.minimizeBinSize();
            }
            result = packer.outputBins(format);
        }
        return result;
    }

    static std::string s_assemblePath(const std::string& dir,
                                      const std::string& name,
                                      int index,
                                      const std::string& subfix)
    {
        strbuf_init_stack(result, 64);
        CLOVER_SCOPE_EXIT
        {
            strbuf_finish(result);
        };

        libra::strbuf_push_string(result, dir);
        libra_path_join(result, name.c_str());
        strbuf_push_char(result, '_');
        strbuf_push_uint32(result, index);
        strbuf_push_char(result, '.');
        libra::strbuf_push_string(result, subfix);
        return libra::strbuf_to_string(result);
    }

    struct TexturePath
    {
        std::string configPath;
        std::string pngPath;
    };

    static std::vector<TexturePath> s_getAllTexturePaths(const std::string& dir, const std::string& name)
    {
        std::vector<TexturePath> paths;
        for (int i = 0;; i++)
        {
            auto configPath = s_assemblePath(dir, name, i, "plist");
            if (!fsys_is_exists(configPath.c_str()))
            {
                configPath = s_assemblePath(dir, name, i, "lua");
                if (!fsys_is_exists(configPath.c_str()))
                {
                    break;
                }
            }

            auto pngPath = s_assemblePath(dir, name, i, "png");
            if (!fsys_is_exists(pngPath.c_str()))
            {
                break;
            }

            TexturePath path = { configPath, pngPath };
            paths.push_back(path);
        }
        return paths;
    }

    template <typename PackFun>
    static TexturePackage::Ptr s_createPackages(PixelFormat format, PackFun&& packFun)
    {
        auto outputs = s_createTextureOut(format, packFun);
        if (outputs.empty())
        {
            return TexturePackage::Ptr();
        }
        auto package = makeRef<TexturePackage>();
        package->setOutputs(outputs, format);
        return package;
    }

    bool TexturePackage::saveTextureOuputs(const std::string& dir, const std::string& name, bool isAsyn)
    {
        fsys_let_dir_exists(dir.c_str());
        for (size_t index = 0; index < _outputs.size(); index++)
        {
            auto& iter = _outputs[index];

#if 0
            auto configPath = s_assemblePath(dir, name, index, "plist");
            auto config = iter.frames->transToCocos2dPlist(name, index);

#else
            auto configPath = s_assemblePath(dir, name, (int)index, "lua");
            auto config = iter.frames->transToLuaConfig(name, (int)index);
#endif
            libra::str_writeToPath(config, configPath);
            auto pngPath = s_assemblePath(dir, name, (int)index, "png");
            if (isAsyn)
            {
                AsyncManager::getInstance().saveBitmapAsync(iter.bitmap, pngPath);
            }
            else
            {
                saveBitmapToPngFile(iter.bitmap, pngPath);
            }
        }
        return true;
    }

    bool TexturePackage::saveAsPng(const std::string& dir, const std::string& name)
    {
        return saveTextureOuputs(dir, name, false);
    }

    bool TexturePackage::saveAsPngAsync(const std::string& dir, const std::string& name)
    {
        return saveTextureOuputs(dir, name, false);
    }

    static TextureFrame* s_createSpriteFrame(const tp::TextureFrames::FrameInfo& frame, uint64_t Id)
    {
        cocos2d_bridge::Rect rectInPixels(frame.rect.x, frame.rect.y, frame.rect.width, frame.rect.height);
        if (frame.isRotation)
        {
            std::swap(rectInPixels.size.width, rectInPixels.size.height);
        }

        auto rect = pixels_to_points(rectInPixels);
        return TextureFrame::create(Id, rect, rectInPixels, frame.isRotation);
    }

    bool TexturePackage::transToSpriteFrames(const std::string& dir, const std::string& name)
    {
        size_t index = 0;
        for (auto& iter : _outputs)
        {
            auto texture2d = bitmap_transToTexture(iter.bitmap, _pixelFormat);
            auto pngPath = s_assemblePath(dir, name, (int)index, "png");
            auto textureId = FlaResourceCache::getInstance().addTexture2d(pngPath, texture2d);

            for (auto& frame : iter.frames->getFrames())
            {
                auto spriteFrame = s_createSpriteFrame(frame, textureId);
                FlaResourceCache::getInstance().setTextureFrame(spriteFrame, frame.key);
            }
            index++;
        }
        return true;
    }

    TexturePackage::Ptr TexturePackage::pack(const std::vector<Definition::Ptr>& definitions,
                                             float scale,
                                             PixelFormat format)
    {
        auto wholeScale = settings::getTextureContentScale() * scale;
        return s_createPackages(format,
                                [&](tp::TexturePacker& packer)
                                {
                                    return packer.pack(definitions, 2, wholeScale);
                                });
    }

    TexturePackage::Ptr TexturePackage::packShapes(const Definition::Ptr& root, float scale, PixelFormat format)
    {
        auto wholeScale = settings::getTextureContentScale() * scale;
        return s_createPackages(format,
                                [&](tp::TexturePacker& packer)
                                {
                                    return packer.packShapes(root, 2, wholeScale);
                                });
    }

    TextureFrame* TexturePackage::getSpriteFrame(const std::string& key)
    {
        return FlaResourceCache::getInstance().getTextureFrame(key);
    }

    TextureFrame* TexturePackage::getSpriteFrame(const Definition* definition, float scale)
    {
        auto key = keyOfCache(definition, scale * settings::getTextureContentScale());
        return getSpriteFrame(key);
    }
    
    static bool s_loadFramesWithFile(const std::string& path, uint64_t textureId)
    {
        if (boost::ends_with(path, ".lua"))
        {
            return cocos2d_bridge::loadFramesWithLuaFile(path, textureId);
        }
        return cocos2d_bridge::loadFramesWithPlistFile(path, textureId);
    }

    bool TexturePackage::isExit(const std::string& dir, const std::string& name)
    {
        auto paths = s_getAllTexturePaths(dir, name);
        return !paths.empty();
    }
    
    bool TexturePackage::load(const std::string& dir, const std::string& name, PixelFormat format)
    {
        auto paths = s_getAllTexturePaths(dir, name);
        for (auto& path : paths)
        {
            auto texture = texture_loadPngFromFile(path.pngPath, format);
            if (texture == nullptr)
            {
                return false;
            }

            auto textureId = FlaResourceCache::getInstance().addTexture2d(path.pngPath, texture);
            if (!s_loadFramesWithFile(path.configPath, textureId))
            {
                return false;
            }
        }
        return !paths.empty();
    }

    bool TexturePackage::loadAsync(const std::string& dir,
                                   const std::string& package,
                                   PixelFormat format,
                                   const std::function<void(void)>& callback)
    {
        auto paths = s_getAllTexturePaths(dir, package);
        if (paths.empty())
        {
            return false;
        }

        size_t totalSize = paths.size();
        size_t* count = new size_t(0);

        for (auto path : paths)
        {
            AsyncManager::getInstance().async(
                [=]
                {
                    return loadBitmapFromPngFile(path.pngPath, format);
                },
                [=](const BitmapData::Ptr& bitmapData)
                {
                    if (bitmapData)
                    {
                        auto texture = bitmap_transToTexture(bitmapData, format);
                        if (texture)
                        {
                            auto textureId = FlaResourceCache::getInstance().addTexture2d(path.pngPath, texture);
                            s_loadFramesWithFile(path.configPath, textureId);
                        }
                    }

                    (*count)++;

                    if (*count == totalSize)
                    {
                        delete count;
                        callback();
                    }
                });
        }
        return true;
    }
}