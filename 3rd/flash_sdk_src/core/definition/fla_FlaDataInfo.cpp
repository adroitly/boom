//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_FlaDataInfo.h"
#include "./fla_DefinitionImage.h"
#include <string.h>

namespace fla
{
    FlaDataInfo::FlaDataInfo()
    {
        _frameRate = 24;
        memset(_md5, 0, sizeof(_md5));
    }

    FlaDataInfo::Ptr FlaDataInfo::create()
    {
        return Ptr(new FlaDataInfo(), false);
    }

    void FlaDataInfo::setFrameRate(float frameRate)
    {
        _frameRate = frameRate;
    }

    float FlaDataInfo::getFrameRate() const
    {
        return _frameRate;
    }

    void FlaDataInfo::setDataMd5(const std::string& md5str, const uint8_t md5[16])
    {
        _md5str = md5str;
        memcpy(_md5, md5, 16);
    }

    const std::string& FlaDataInfo::getMd5String() const
    {
        return _md5str;
    }
    
    bool FlaDataInfo::isSameMd5(const FlaDataInfo& dataInfo)
    {
        return memcmp(_md5, dataInfo._md5, 16) == 0;
    }

    DefinitionImage::Ptr FlaDataInfoWithImages::findImage(int Id) const
    {
        auto iter = _images.find(Id);
        if (iter != _images.end())
        {
            return iter->second;
        }
        return DefinitionImage::Ptr();
    }

    void FlaDataInfoWithImages::addImage(const DefinitionImage::Ptr& image)
    {
        _images[image->getId()] = image;
    }

    FlaDataInfoWithImages::Ptr FlaDataInfoWithImages::create()
    {
        return Ptr(new FlaDataInfoWithImages(), false);
    }
}
