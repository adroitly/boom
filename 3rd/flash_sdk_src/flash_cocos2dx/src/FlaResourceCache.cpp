//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaResourceCache.h"
#include "../../core/definition/fla_Collection.h"
#include "cocos2d_bridge.h"
using namespace cocos2d;

FlaResourceCache& FlaResourceCache::getInstance()
{
    static FlaResourceCache caches;
    return caches;
}

FlaResourceCache::FlaResourceCache()
{
}

FlaResourceCache::~FlaResourceCache()
{
}

uint64_t FlaResourceCache::addTexture2d(const std::string& key, cocos2d_bridge::Texture2D* texture2d)
{
    return _textureCache.addTexture2d(key, texture2d);
}

cocos2d_bridge::Texture2D* FlaResourceCache::getTexture2d(const std::string& key)
{
    return _textureCache.getTexture2d(key);
}

cocos2d_bridge::Texture2D* FlaResourceCache::getTexture2d(uint64_t Id)
{
    return _textureCache.getTexture2d(Id);
}

void FlaResourceCache::setCollection(const FlaCollection& collection, const std::string& key)
{
    _collections.set(collection.getRaw(), key);
}

FlaCollection FlaResourceCache::collectionForKey(const std::string& key)
{
    return FlaCollection(_collections.get(key));
}

void FlaResourceCache::clear()
{
    _textureCache.clear();
    _collections.clear();
    _programs.clear();
}

void FlaResourceCache::setTextureFrame(fla::TextureFrame* textureFrame, const std::string& key)
{
    assert(textureFrame->getTexture() == nullptr);
    _textureCache.setSpriteFrame(textureFrame, key);
}

fla::TextureFrame* FlaResourceCache::getTextureFrame(const std::string& key)
{
    return _textureCache.getSpriteFrame(key);
}

void FlaResourceCache::setGLProgram(FlaGLProgram* program, const std::string& key)
{
    _programs.set(program, key);
}

FlaGLProgram* FlaResourceCache::programForKey(const std::string& key)
{
    return _programs.get(key);
}
