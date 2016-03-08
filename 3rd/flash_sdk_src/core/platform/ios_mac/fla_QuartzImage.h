//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_QUARTZIMAGE__
#define __FLA_QUARTZIMAGE__

#include "../../base/fla_Image.h"
#include "../../base/fla_BitmapData.h"
#include <CoreGraphics/CoreGraphics.h>

namespace fla
{
    class QuartzImage : public Image
    {
    public:
        static Ptr create(CGImageRef image);
        static Ptr create(const fla::BitmapData::Ptr& bitmapData);
        static Ptr create();

        ~QuartzImage();

        virtual Size getSize() const override;
        virtual void savePng(const std::string& path) override;
        CGImageRef getImage() const;

    private:
        QuartzImage(CGImageRef image);
        QuartzImage(const fla::BitmapData::Ptr& bitmapData);

    private:
        CGImageRef           _image;
        fla::BitmapData::Ptr _bitmapData;
    };

    CGImageRef createRefWithNoCopyPixels(const void* pixels, int width, int height);
}

#endif
