//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaBitmapData.h"
#include "fla_cocos2d_Texture.h"
#include "./fla_AsynManager.h"
#include "../../core/base/fla_BitmapData.h"

FlaBitmapData::FlaBitmapData() : FlaBitmapData(nullptr)
{
}

FlaBitmapData::FlaBitmapData(fla::BitmapData* impl) : _impl(impl)
{
    clover::intrusive_ptr_safe_retain(_impl);
}

FlaBitmapData::~FlaBitmapData()
{
    clover::intrusive_ptr_safe_release(_impl);
}

FlaBitmapData::FlaBitmapData(const FlaBitmapData& rhs)
{
    _impl = rhs._impl;
    clover::intrusive_ptr_safe_retain(_impl);
}

FlaBitmapData& FlaBitmapData::operator=(const FlaBitmapData& rhs)
{
    clover::intrusive_ptr_safe_assign(_impl, rhs._impl);
    return *this;
}

bool FlaBitmapData::isNull() const
{
    return !_impl;
}

int FlaBitmapData::getWidth() const
{
    return _impl ? _impl->getWidth() : 0;
}

int FlaBitmapData::getHeight() const
{
    return _impl ? _impl->getHeight() : 0;
}

int FlaBitmapData::getContentWidth() const
{
    return _impl ? _impl->getContentWidth() : 0;
}

int FlaBitmapData::getContentHeight() const
{
    return _impl ? _impl->getContentHeight() : 0;
}

cocos2d_bridge::Texture2D* FlaBitmapData::transToTexture(FlaPixelFormat format) const
{
    return fla::bitmap_transToTexture(_impl, static_cast<fla::PixelFormat>(format));
}

bool FlaBitmapData::saveAsPng(const std::string& filePath) const
{
    return fla::saveBitmapToPngFile(_impl, filePath);
}

bool FlaBitmapData::saveAsPngAsync(const std::string& filePath) const
{
    return fla::AsyncManager::getInstance().saveBitmapAsync(_impl, filePath);
}

cocos2d_bridge::Texture2D* FlaBitmapData::loadPngTexture(const std::string& filePath, FlaPixelFormat format)
{
    auto pixelFormat = static_cast<fla::PixelFormat>(format);
    return fla::texture_loadPngFromFile(filePath, pixelFormat);
}

