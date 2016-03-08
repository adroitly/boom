//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_IMAGE__
#define __FLA_IMAGE__

#include <boost/noncopyable.hpp>
#include <string>
#include <memory>
#include <vector>
#include <cassert>
#include "fla_Base.h"
#include "clover/ImmutableData.h"
#include "clover/IntrusiveObject.h"

namespace clover
{
    typedef ImmutableData<MemNull, MemNull> LightData;
}

namespace fla
{
    class Image : public clover::IntrusiveObject<Image>
    {
    public:
        Image();
        virtual ~Image();

        virtual Size getSize() const = 0;
        virtual void savePng(const std::string& path) = 0;

        virtual bool isSupportScale() const
        {
            return false;
        }

        virtual Ptr scaleImageData(float scale, const Size& oldSize, Size* newSize)
        {
            FLA_UNUSED(scale);
            FLA_UNUSED(newSize);
            FLA_UNUSED(oldSize);
            return Ptr();
        }

        // 顺序不要修改
        enum class ImageType
        {
            Png = 0,
            Bitmap = 1,
            Jpeg = 2,
        };

        ImageType getImageType() const;
        const std::vector<uint8_t>& getImageData() const;

        void setImageData(const clover::LightData& data, ImageType imageType);

    private:
        std::vector<uint8_t> _imageData;
        ImageType _type;
    };
}

#endif
