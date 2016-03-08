//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Image.h"
#include <memory>

namespace fla
{
    void Image::setImageData(const clover::LightData& data, ImageType type)
    {
        _type = type;
        _imageData.resize(data.size());
        memcpy(&_imageData[0], data.data(), data.size());
    }

    const std::vector<uint8_t>& Image::getImageData() const
    {
        return _imageData;
    }

    Image::ImageType Image::getImageType() const
    {
        return _type;
    }

    Image::Image() : _type(ImageType::Png)
    {
    }

    Image::~Image()
    {
    }
}
