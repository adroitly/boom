//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_SKIAIMAGE__
#define __FLA_SKIAIMAGE__

#include "Core/Base/fla_Image.h"
#include "Core/Base/fla_BitmapData.h"
#include "SkBitmap.h"

namespace fla
{
    class SkiaImage : public Image
    {
    public:
        static Ptr create();
        static Ptr create(const BitmapData::Ptr& data);
        ~SkiaImage();

        virtual Size getSize() const override;
        virtual void savePng(const std::string& path) override;

    private:
        SkiaImage();
        SkiaImage(SkBitmap bitmap);
        SkiaImage(const fla::BitmapData::Ptr& bitmapData);

    private:
        SkBitmap             _bitmap;
        fla::BitmapData::Ptr _bitmapData;
    };
}

#endif
