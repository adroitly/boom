//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaTexturePackage.h"
#include "./fla_TexturePackage.h"
#include "clover/Container.h"
using namespace cocos2d;

FlaTexturePackage::FlaTexturePackage()
{
    _impl = nullptr;
}

FlaTexturePackage::~FlaTexturePackage()
{
    clover::intrusive_ptr_safe_release(_impl);
}

FlaTexturePackage::FlaTexturePackage(const FlaTexturePackage& rhs) : FlaTexturePackage(rhs._impl)
{
}

FlaTexturePackage::FlaTexturePackage(fla::TexturePackage* impl)
{
    _impl = impl;
    clover::intrusive_ptr_safe_retain(_impl);
}

FlaTexturePackage& FlaTexturePackage::operator=(const FlaTexturePackage& rhs)
{
    clover::intrusive_ptr_safe_assign(_impl, rhs._impl);
    return *this;
}

bool FlaTexturePackage::isExit(const std::string& dir, const std::string& name)
{
    return fla::TexturePackage::isExit(dir, name);
}

bool FlaTexturePackage::load(const std::string& dir, const std::string& name, FlaPixelFormat format)
{
    return fla::TexturePackage::load(dir, name, (fla::PixelFormat)format);
}

bool FlaTexturePackage::loadAsync(const std::string& dir,
                                  const std::string& name,
                                  FlaPixelFormat format,
                                  const std::function<void(void)>& callback)
{
    return fla::TexturePackage::loadAsync(dir, name, (fla::PixelFormat)format, callback);
}

fla::TextureFrame* FlaTexturePackage::getSpriteFrame(const FlaDefinition& definition, float scale)
{
    return fla::TexturePackage::getSpriteFrame(definition.getRaw(), scale);
}

FlaTexturePackage FlaTexturePackage::pack(const std::vector<FlaDefinition>& definitions,
                                          float scale,
                                          FlaPixelFormat pixelFormat)
{
    auto ptrs = clover::transform(definitions,
                                  [](const FlaDefinition& def)
                                  {
                                      return fla::Definition::Ptr(def.getRaw());
                                  });
    auto impl = fla::TexturePackage::pack(ptrs, scale, (fla::PixelFormat)pixelFormat);
    return FlaTexturePackage(impl.get());
}

FlaTexturePackage FlaTexturePackage::packShapes(const FlaDefinition& root, float scale, FlaPixelFormat pixelFormat)
{
    auto impl = fla::TexturePackage::packShapes(root.getRaw(), scale, (fla::PixelFormat)pixelFormat);
    return FlaTexturePackage(impl.get());
}

bool FlaTexturePackage::isNull() const
{
    return !_impl;
}

bool FlaTexturePackage::saveAsPng(const std::string& dir, const std::string& name)
{
    if (_impl)
    {
        return _impl->saveAsPng(dir, name);
    }
    return false;
}

bool FlaTexturePackage::saveAsPngAsync(const std::string& dir, const std::string& name)
{
    if (_impl)
    {
        return _impl->saveAsPngAsync(dir, name);
    }
    return false;
}

bool FlaTexturePackage::transToSpriteFrames(const std::string& dir, const std::string& name)
{
    if (_impl)
    {
        return _impl->transToSpriteFrames(dir, name);
    }
    return false;
}
