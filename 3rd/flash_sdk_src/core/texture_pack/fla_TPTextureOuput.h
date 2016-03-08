//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_TPTEXTUREOUPUT_H__
#define __FLA_TPTEXTUREOUPUT_H__

#include "rbp/rbp_TextureBin.h"
#include "../base/fla_BitmapData.h"
#include "core/utility/fla_plist.h"
#include "clover/IntrusiveObject.h"
#include "../definition/fla_Definition.h"

namespace fla
{
    namespace tp
    {
        class TextureFrames : public clover::IntrusiveObject<TextureFrames>
        {
        public:
            struct FrameInfo
            {
                rbp::Rect rect;
                std::string key;
                bool isRotation;
            };

            static Ptr create(const rbp::RectSize& size)
            {
                return Ptr(new TextureFrames(size), false);
            }

            void addFrame(const rbp::Rect& rect, const std::string& key, bool isRotation);

            std::string transToCocos2dPlist(const std::string& name, int index);
            std::string transToLuaConfig(const std::string& name, int index);

            const std::vector<FrameInfo> getFrames() const
            {
                return _frames;
            }

        private:
            TextureFrames(const rbp::RectSize& size) : _size(size)
            {
            }
            clover::plist::Value transToRootValue(const std::string& name, int index) const;

        private:
            std::vector<FrameInfo> _frames;
            rbp::RectSize _size;
        };

        struct TextureOuput
        {
            BitmapData::Ptr bitmap;
            TextureFrames::Ptr frames;
        };

        TextureOuput textureBinOutput(const rbp::TextureBin& bin, PixelFormat pixelFormat);
    }
}

#endif
