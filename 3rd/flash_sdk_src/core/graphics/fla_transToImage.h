//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_TRANSTOIMAGE_H__
#define __FLA_TRANSTOIMAGE_H__

#include "../definition/fla_Definition.h"
#include "../base/fla_Image.h"
#include "../base/fla_BitmapData.h"
#include "../platform/fla_PlatformTraits.h"

namespace fla
{
    // 将定义转成图片
    Image::Ptr Definition_transToImage(const Definition& definition, PixelFormat pixelFormat, float scale);
    Image::Ptr Definition_transToImage(const Definition& definition, PixelFormat pixelFormat, const Size& size);
    void Definition_render(const Definition& definition, PlatformTraits::Graphics& graphics, const Size& size);
}

#endif



