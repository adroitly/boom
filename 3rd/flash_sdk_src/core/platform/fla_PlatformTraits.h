//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_PLATFORMTRAITS__
#define __FLA_PLATFORMTRAITS__

#include "../base/fla_Base.h"

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_MAC) || (FLA_TARGET_PLATFORM == FLA_PLATFORM_IOS)
#include "./ios_mac/fla_QuartzGraphics.h"
#include "./ios_mac/fla_QuartzImage.h"

namespace fla
{
    struct PlatformTraits
    {
        typedef fla::QuartzGraphics Graphics;
        typedef fla::QuartzBitmapGraphics BitmapGraphics;
        typedef fla::QuartzImage Image;
    };
}

#endif

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_SKIA)
#include "./skia/fla_SkiaGraphics.h"
#include "./skia/fla_SkiaImage.h"

namespace fla
{
    struct PlatformTraits
    {
        typedef fla::SkiaGraphics Graphics;
        typedef fla::SkiaBitmapGraphics BitmapGraphics;
        typedef fla::SkiaImage Image;
    };
}
#endif

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_QT)
#include "./qt/fla_QtGraphics.h"
#include "./qt/fla_QtImage.h"

namespace fla
{
    struct PlatformTraits
    {
        typedef fla::QtGraphics Graphics;
        typedef fla::QtBitmapGraphics BitmapGraphics;
        typedef fla::QtImage Image;
    };
}
#endif

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_NULL)
#include "./null/fla_NullGraphics.h"
#include "./null/fla_NullImage.h"

namespace fla
{
    struct PlatformTraits
    {
        typedef fla::NullGraphics Graphics;
        typedef fla::NullBitmapGraphics BitmapGraphics;
        typedef fla::NullImage Image;
    };
}
#endif

#endif
