//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLATEXTUREPACKAGE_H__
#define __FLATEXTUREPACKAGE_H__

#include "FlaConfig.h"
#include "FlaEnum.h"
#include "FlaDefinition.h"
#include "./src/fla_TextureFrame.h"

namespace fla
{
    class TexturePackage;
}

// 这个类用于合并纹理
class FlaTexturePackage
{
public:
    FlaTexturePackage();
    ~FlaTexturePackage();

    FlaTexturePackage(const FlaTexturePackage& rhs);
    FlaTexturePackage& operator=(const FlaTexturePackage& rhs);

    explicit FlaTexturePackage(fla::TexturePackage* impl);

    static bool isExit(const std::string& dir, const std::string& name);
    static bool load(const std::string& dir, const std::string& name, FlaPixelFormat format);
    static bool loadAsync(const std::string& dir,
                          const std::string& name,
                          FlaPixelFormat format,
                          const std::function<void(void)>& callback);

    static fla::TextureFrame* getSpriteFrame(const FlaDefinition& definition, float scale);

    static FlaTexturePackage pack(const std::vector<FlaDefinition>& definitions, float scale, FlaPixelFormat format);
    static FlaTexturePackage packShapes(const FlaDefinition& root, float scale, FlaPixelFormat format);

    bool isNull() const;
    bool saveAsPng(const std::string& dir, const std::string& name);
    bool saveAsPngAsync(const std::string& dir, const std::string& name);
    bool transToSpriteFrames(const std::string& dir, const std::string& name);

private:
    fla::TexturePackage* _impl;
};

#endif