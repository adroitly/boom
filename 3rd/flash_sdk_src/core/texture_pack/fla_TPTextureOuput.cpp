//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_TPTextureOuput.h"
#include "../platform/fla_PlatformTraits.h"
#include "clover/ScopeGuard.h"
#include "libra/libra_strbuf.h"
#include "libra/libra_path.h"
#include <sstream>
#include "rbp/rbp_TextureBin.h"
#include "fla_TPPackItem.h"

namespace fla
{
    namespace tp
    {
        template <typename Graphics>
        static void bin_renderInGraphics(const rbp::TextureBin& bin, Graphics& graphics)
        {
            for (auto& item : bin.getItems())
            {
                graphics.saveGState();
                CLOVER_SCOPE_EXIT
                {
                    graphics.restoreGState();
                };
                static_cast<PackItem*>(item.get())->renderInGraphics(graphics);
            }
        }

        static BitmapData::Ptr s_transToBitmapData(const rbp::TextureBin& bin, PixelFormat format)
        {
            auto binSize = bin.getSize();
            PlatformTraits::BitmapGraphics graphics(binSize.width, binSize.height, format);

            graphics.flipAndScale(1);
            bin_renderInGraphics(bin, graphics);

            return graphics.getBitmapData();
        }

        static void strbuf_push_pair(libra_strbuf* result, int x, int y)
        {
            // {x,y}
            assert(x >= 0 && y >= 0);
            strbuf_push_char(result, '{');
            strbuf_push_uint32(result, x);
            strbuf_push_char(result, ',');
            strbuf_push_uint32(result, y);
            strbuf_push_char(result, '}');
        }

        static std::string sizeToString(const rbp::RectSize& size)
        {
            strbuf_init_stack(result, 32);
            CLOVER_SCOPE_EXIT
            {
                strbuf_finish(result);
            };
            strbuf_push_pair(result, size.width, size.height);
            return strbuf_cstr(result);
        }

        static std::string rectToString(const rbp::Rect& rt)
        {
            strbuf_init_stack(result, 32);
            CLOVER_SCOPE_EXIT
            {
                strbuf_finish(result);
            };
            strbuf_push_char(result, '{');
            strbuf_push_pair(result, rt.x, rt.y);
            strbuf_push_char(result, ',');
            strbuf_push_pair(result, rt.width, rt.height);
            strbuf_push_char(result, '}');
            return strbuf_cstr(result);
        }

        static clover::plist::Value s_transToPlistMetadata(const rbp::RectSize& size, const std::string& imageName)
        {
            clover::plist::Value metadata = clover::plist::Value::makeDict();

            metadata.dict()["format"] = clover::plist::Value(2);
            metadata.dict()["size"] = clover::plist::Value(sizeToString(size));
            metadata.dict()["realTextureFileName"] = clover::plist::Value(imageName);
            metadata.dict()["textureFileName"] = clover::plist::Value(imageName);

            return metadata;
        }

        inline static void s_pushWithSpaces(libra_strbuf* buf)
        {
            strbuf_push_lstring(buf, "    ", 4);
        }

        static void s_transToLuaMetadata(libra_strbuf* buf, const rbp::RectSize& size, const std::string& imageName)
        {
            strbuf_push_string(buf, "metadata {\n");
            strbuf_push_string(buf, "    format = 2,\n");
            strbuf_push_format(buf, "    size = {%d, %d},\n", size.width, size.height);
            strbuf_push_format(buf, "    realTextureFileName = \"%s\",\n", imageName.c_str());
            strbuf_push_format(buf, "    textureFileName = \"%s\",\n", imageName.c_str());
            strbuf_push_string(buf, "}\n\n");
        }

        static clover::plist::Value s_transToPlistFrame(const rbp::Rect packRect, bool isRotation)
        {
            clover::plist::Value frame = clover::plist::Value::makeDict();

            auto rect = packRect;
            if (isRotation)
            {
                std::swap(rect.width, rect.height);
            }

            frame.dict()["frame"] = clover::plist::Value(rectToString(rect));
            frame.dict()["offset"] = clover::plist::Value("{0,0}");
            frame.dict()["rotated"] = clover::plist::Value(isRotation);

            rect.x = 0;
            rect.y = 0;
            frame.dict()["sourceColorRect"] = clover::plist::Value(rectToString(rect));

            rbp::RectSize sourceSize = { rect.width, rect.height };
            frame.dict()["sourceSize"] = clover::plist::Value(sizeToString(sourceSize));

            return frame;
        }

        static void s_transToLuaFrame(libra_strbuf* buf, const TextureFrames::FrameInfo& frame)
        {
            auto rt = frame.rect;
            if (frame.isRotation)
            {
                std::swap(rt.width, rt.height);
            }

            strbuf_push_string(buf, "frame {\n");
            strbuf_push_format(buf, "    key = \"%s\",\n", frame.key.c_str());
            strbuf_push_format(buf, "    frame = {%d, %d, %d, %d},\n", rt.x, rt.y, rt.width, rt.height);
            strbuf_push_format(buf, "    sourceSize = {%d, %d},\n", rt.width, rt.height);
            strbuf_push_format(buf, "    rotated = %s,\n", frame.isRotation ? "true" : "false");
            strbuf_push_string(buf, "    offset = {0, 0},\n");
            strbuf_push_string(buf, "}\n\n");
        }

        static std::string s_getImageName(const std::string& name, int index)
        {
            strbuf_init_stack(imageName, 64);
            CLOVER_SCOPE_EXIT
            {
                strbuf_finish(imageName);
            };

            strbuf_push_lstring(imageName, name.c_str(), name.size());
            libra_path_remove_ext(imageName);

            strbuf_push_char(imageName, '_');
            strbuf_push_uint32(imageName, index);
            strbuf_push_string(imageName, ".png");
            return strbuf_cstr(imageName);
        }

        std::string TextureFrames::transToLuaConfig(const std::string& name, int index)
        {
            strbuf_init_stack(result, 64);
            CLOVER_SCOPE_EXIT
            {
                strbuf_finish(result);
            };

            auto imageName = s_getImageName(name, index);
            s_transToLuaMetadata(result, _size, imageName);

            for (auto& frame : _frames)
            {
                s_transToLuaFrame(result, frame);
            }

            auto cstr = strbuf_cstr(result);
            return std::string(cstr, cstr + strbuf_length(result));
        }

        std::string TextureFrames::transToCocos2dPlist(const std::string& name, int index)
        {
            auto imageName = s_getImageName(name, index);

            clover::plist::Value rootValue = clover::plist::Value::makeDict();
            rootValue.dict()["metadata"] = s_transToPlistMetadata(_size, imageName);

            clover::plist::Value frames = clover::plist::Value::makeDict();
            rootValue.dict()["frames"] = frames;

            for (auto& frame : _frames)
            {
                auto itemName = frame.key;
                frames.dict()[itemName] = s_transToPlistFrame(frame.rect, frame.isRotation);
            }

            return clover::plist::valueToPlistString(rootValue);
        }

        void TextureFrames::addFrame(const rbp::Rect& rect, const std::string& key, bool isRotation)
        {
            _frames.resize(_frames.size() + 1);
            auto& info = _frames.back();
            info.rect = rect;
            info.key = key;
            info.isRotation = isRotation;
        }

        TextureOuput textureBinOutput(const rbp::TextureBin& bin, PixelFormat pixelFormat)
        {
            TextureOuput result;
            result.bitmap = s_transToBitmapData(bin, pixelFormat);
            result.frames = TextureFrames::create(bin.getSize());
            for (auto& item : bin.getItems())
            {
                auto* tmpItem = static_cast<PackItem*>(item.get());
                result.frames->addFrame(tmpItem->getOutpuPackRect(),
                                        tmpItem->computeItemCacheKey(),
                                        tmpItem->isRotation());
            }
            return result;
        }
    }
}
