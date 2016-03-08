//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_NULLGRAPHICS_H__
#define __FLA_NULLGRAPHICS_H__

#include "core/base/fla_BitmapData.h"
#include "core/graphics/fla_Graphics.h"

namespace fla
{
    // 使用Quartz实现的图形接口
    class NullGraphics : public fla::Graphics
    {
    public:
        void drawImage(const Size& imageSize, const Image& image, const Matrix& trans)
        {
        }

        void drawImage(const Size& imageSize, const Image& image, const Rect& rect)
        {
        }

        void clipToRect(const Rect& rt)
        {
        }
    };

    ////////////////////////////////////////////////////////////////////////
    class NullBitmapGraphics : public NullGraphics
    {
    public:
        explicit NullBitmapGraphics(int width, int height, PixelFormat pixelFormat)
        {
        }

        void flipAndScale(real_t scale)
        {
        }

        fla::Image::Ptr createImage() const
        {
            return fla::Image::Ptr();
        }

        fla::BitmapData::Ptr getBitmapData() const
        {
            return fla::BitmapData::Ptr();
        }
    };
}

#endif
