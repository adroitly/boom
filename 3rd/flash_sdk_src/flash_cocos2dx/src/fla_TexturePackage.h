//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_TEXTUREPACKAGE_H__
#define __FLA_TEXTUREPACKAGE_H__

#include "cocos2d_bridge.h"
#include "./fla_TextureFrame.h"
#include "../../core/texture_pack/fla_TPTextureOuput.h"

namespace fla
{
    class TexturePackage : public Ref<TexturePackage>
    {
    public:
        static bool isExit(const std::string& dir, const std::string& name);
        static bool load(const std::string& dir, const std::string& name, PixelFormat format);
        static bool loadAsync(const std::string& dir,  const std::string& name, PixelFormat format, const std::function<void(void)>& callback);

        static fla::TextureFrame* getSpriteFrame(const std::string& key);
        static fla::TextureFrame* getSpriteFrame(const Definition* definition, float scale);

        static TexturePackage::Ptr pack(const std::vector<Definition::Ptr>& definitions, float scale, PixelFormat format);
        static TexturePackage::Ptr packShapes(const Definition::Ptr& root, float scale, PixelFormat format);
        
        bool saveAsPng(const std::string& dir, const std::string& name);
        bool saveAsPngAsync(const std::string& dir, const std::string& name);
        bool transToSpriteFrames(const std::string& dir, const std::string& name);

        void setOutputs(std::vector<tp::TextureOuput>& outputs, PixelFormat format)
        {
            _outputs.swap(outputs);
            _pixelFormat = format;
        }

    private:
        bool saveTextureOuputs(const std::string& dir, const std::string& name, bool isAsyn);

    private:
        std::vector<tp::TextureOuput> _outputs;
        PixelFormat _pixelFormat;
    };
}

#endif
