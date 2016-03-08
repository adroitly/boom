//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLATEXTURECACHE_H__
#define __FLATEXTURECACHE_H__

#include "FlaConfig.h"
#include "FlaDefinition.h"
#include "FlaCollection.h"
#include "FlaGLProgram.h"
#include "./base/fla_RefDict.h"
#include "./src/fla_TextureFrame.h"
#include "./src/fla_TextureCache.h"

class FlaResourceCache
{
public:
    static FlaResourceCache& getInstance();

    uint64_t addTexture2d(const std::string& key, cocos2d_bridge::Texture2D* texture2d);
    cocos2d_bridge::Texture2D* getTexture2d(const std::string& key);
    cocos2d_bridge::Texture2D* getTexture2d(uint64_t Id);

    void setTextureFrame(fla::TextureFrame* frame, const std::string& key);
    fla::TextureFrame* getTextureFrame(const std::string& key);

    void setGLProgram(FlaGLProgram* program, const std::string& key);
    FlaGLProgram* programForKey(const std::string& key);

    void setCollection(const FlaCollection& collection, const std::string& key);
    FlaCollection collectionForKey(const std::string& key);

    void clear();

private:
    FlaResourceCache();
    ~FlaResourceCache();

    fla::TextureCache _textureCache;
    fla::RefDict<FlaGLProgram> _programs;
    fla::RefDict<fla::Collection> _collections;
};

#endif