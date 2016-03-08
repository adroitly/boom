//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BitmapData.h"
#include <stdlib.h>
#include <memory.h>
#include <cassert>
#include "libra/libra_math.h"

namespace fla
{
    static inline bool s_isPxielFormat4444(PixelFormat pixelFormat)
    {
        return (pixelFormat == PixelFormat::RGBA4444 || pixelFormat == PixelFormat::ARGB4444);
    }

    static inline int s_byteSizeOfPixelFormat(PixelFormat pixelFormat)
    {
        if (s_isPxielFormat4444(pixelFormat))
        {
            return 2;
        }
        return 4;
    }

    BitmapData::Ptr BitmapData::create(int width, int height, PixelFormat pixelFormat)
    {
        return Ptr(new BitmapData(width, height, pixelFormat), false);
    }

    BitmapData::Ptr BitmapData::create(void* pixels,
                                       bool copyPixels,
                                       int width,
                                       int height,
                                       PixelFormat pixelFormat)
    {
        return Ptr(new BitmapData(pixels, copyPixels, width, height, pixelFormat), false);
    }

    BitmapData::BitmapData(void* pixels,
                           bool copyPixels,
                           int width,
                           int height,
                           PixelFormat pixelFormat)
    {
        _width = width;
        _height = height;
        _contentWidth = width;
        _contentHeight = height;
        _pixelFormat = pixelFormat;

        assert(pixels);

        _pixels = pixels;
        _needFreePixels = copyPixels;

        if (copyPixels)
        {
            auto pixelLength = _width * _height * s_byteSizeOfPixelFormat(pixelFormat);
            _pixels = malloc(pixelLength);
            memcpy(_pixels, pixels, pixelLength);
        }
    }

    BitmapData::BitmapData(int width, int height, PixelFormat pixelFormat)
    {
        _width = width;
        _height = height;
        _contentWidth = width;
        _contentHeight = height;
        _pixelFormat = pixelFormat;
        _needFreePixels = true;

        if (libra::is_odd(_width))
        {
            _width = _width + 1;
        }

        auto pixelLength = _width * _height * s_byteSizeOfPixelFormat(pixelFormat);
        _pixels = malloc(pixelLength);
        memset(_pixels, 0, pixelLength);
    }

    BitmapData::BitmapData()
    {
        _width = 0;
        _height = 0;
        _contentWidth = 0;
        _contentHeight = 0;
        _pixelFormat = PixelFormat::RGBA8888;
        _pixels = nullptr;
        _needFreePixels = true;
    }

    BitmapData::~BitmapData()
    {
        if (_needFreePixels && _pixels)
        {
            free(_pixels);
        }
    }

    void BitmapData::setContentSize(int width, int height)
    {
        _contentWidth = width;
        _contentHeight = height;
    }

    bool BitmapData::isFormat8888() const
    {
        return _pixelFormat == PixelFormat::RGBA8888;
    }

    bool BitmapData::isFormat4444() const
    {
        return s_isPxielFormat4444(_pixelFormat);
    }

    size_t BitmapData::getPixelLength() const
    {
        return _width * _height * s_byteSizeOfPixelFormat(_pixelFormat);
    }

    static void s_flip4444(uint16_t* pixel, const uint16_t* begin, int size)
    {
        auto end = begin + size;
        for (auto iter = begin; iter != end; ++iter, pixel++)
        {
            *pixel = (*iter << 4) | (*iter >> 12);
        }
    }

    static void s_rgba888_to_4444(uint16_t* pixel, const uint32_t* begin, int size)
    {
        auto end = begin + size;
        for (auto iter = begin; iter != end; ++iter, pixel++)
        {
            auto pixel32 = *iter;

            // unpack the source data as 8 bit values
            auto R = ((pixel32 >> 0) & 0xFF);
            auto G = ((pixel32 >> 8) & 0xFF);
            auto B = ((pixel32 >> 16) & 0xFF);
            auto A = ((pixel32 >> 24) & 0xFF);

            // convert to 4 bit vales
            R >>= 4;
            G >>= 4;
            B >>= 4;
            A >>= 4;

            *pixel = (R << 12) | (G << 8) | (B << 4) | A;
        }
    }

    BitmapData::Ptr BitmapData::copyBitmapData(void* pixel, PixelFormat pixelFormat) const
    {
        auto bitmap = Ptr(new BitmapData(), false);
        assert(bitmap->_pixels == nullptr);

        bitmap->_pixels = pixel;
        bitmap->_pixelFormat = pixelFormat;
        bitmap->_width = _width;
        bitmap->_height = _height;
        bitmap->_contentWidth = _contentWidth;
        bitmap->_contentHeight = _contentHeight;

        return bitmap;
    }

    BitmapData::Ptr BitmapData::changePixelFormat(PixelFormat pixelFormat) const
    {
        if (pixelFormat == _pixelFormat)
        {
            auto pixelLength = getPixelLength();
            auto pixels = malloc(pixelLength);
            memcpy(pixels, _pixels, pixelLength);
            return copyBitmapData(pixels, pixelFormat);
        }

        if (_pixelFormat == PixelFormat::RGBA4444 && pixelFormat == PixelFormat::ARGB4444)
        {
            auto pixels = malloc(getPixelLength());
            s_flip4444((uint16_t*)pixels, (uint16_t*)_pixels, _width * _height);
            return copyBitmapData(pixels, pixelFormat);
        }

        if (_pixelFormat == PixelFormat::ARGB4444 && pixelFormat == PixelFormat::RGBA4444)
        {
            auto pixels = malloc(getPixelLength());
            s_flip4444((uint16_t*)pixels, (uint16_t*)_pixels, _width * _height);
            return copyBitmapData(pixels, pixelFormat);
        }

        if (_pixelFormat == PixelFormat::RGBA8888 && pixelFormat == PixelFormat::RGBA4444)
        {
            auto numOfPixels = _width * _height;
            auto pixels = malloc(numOfPixels * 2);
            s_rgba888_to_4444((uint16_t*)pixels, (uint32_t*)_pixels, numOfPixels);
            return copyBitmapData(pixels, pixelFormat);
        }

        assert(false);
        return BitmapData::Ptr();
    }
}
