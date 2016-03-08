//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../../base/fla_Base.h"

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_SKIA)

#include "fla_SkiaImage.h"
#include "SkImageEncoder.h"
#include "SkImageDecoder.h"

namespace fla
{
    SkiaImage::SkiaImage()
    {
    }

    SkiaImage::SkiaImage(const fla::BitmapData::Ptr& bitmapData)
    {
        _bitmapData = bitmapData;
        _bitmap.reset();
    }

    SkiaImage::~SkiaImage()
    {
    }

    Size SkiaImage::getSize() const
    {
        if (_bitmapData)
        {
            return Size(_bitmapData->getWidth(), _bitmapData->getHeight());
        }

        if (_bitmap.isNull())
        {
            return Size();
        }
        return Size(_bitmap.width(), _bitmap.height());
    }

    SkiaImage::Ptr SkiaImage::create()
    {
        return Ptr(new SkiaImage(NULL), false);
    }

    SkiaImage::Ptr SkiaImage::create(const fla::BitmapData::Ptr& bitmapData)
    {
        return Ptr(new SkiaImage(bitmapData), false);
    }

    void SkiaImage::savePng(const std::string& path)
    {
        if (_bitmapData && _bitmap.isNull())
        {
            _bitmap.setConfig(SkBitmap::kARGB_8888_Config,
                              _bitmapData->getWidth(),
                              _bitmapData->getHeight());
            _bitmap.setPixels(_bitmapData->getPixels());
        }
        SkImageEncoder::EncodeFile(path.c_str(), _bitmap, SkImageEncoder::kPNG_Type, 100);
    }
}

#endif
