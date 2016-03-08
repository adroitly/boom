//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BASE_H__
#define __FLA_BASE_H__

#include "kmath/km_rect2.h"
#include "kmath/km_size2.h"
#include "kmath/km_mat3.h"
#include <type_traits>

namespace fla
{
    typedef float real_t;  // 浮点类型
    typedef km::Rect2 Rect;
    typedef km::Vec2 Point;
    typedef km::Size Size;
    typedef km::Mat3 Matrix;

    struct IntPoint
    {
        IntPoint(int x_, int y_) : x(x_), y(y_)
        {
        }
        IntPoint() : x(0), y(0)
        {
        }
        IntPoint operator+(const IntPoint& rhs) const
        {
            return IntPoint(x + rhs.x, y + rhs.y);
        }

        int x;
        int y;
    };
}

#ifndef FLA_UNUSED
#define FLA_UNUSED(a) (void) a
#endif

#ifndef FLA_USE_LUA_BINDING
#define FLA_USE_LUA_BINDING 0
#endif

// 公开的
#ifndef FLA_FOR_PUBLIC
#define FLA_FOR_PUBLIC 0
#endif

#define FLA_PLATFORM_NULL 0
#define FLA_PLATFORM_IOS 1
#define FLA_PLATFORM_MAC 2
#define FLA_PLATFORM_SKIA 3
#define FLA_PLATFORM_QT 4

// QT
#if defined(PLATFORM_QT) && !defined(FLA_TARGET_PLATFORM)
#define FLA_TARGET_PLATFORM FLA_PLATFORM_QT
#endif

// Skia
#if defined(PLATFORM_SKIA) && !defined(FLA_TARGET_PLATFORM)
#define SK_SUPPORT_LEGACY_SHADER_LOCALMATRIX
#define FLA_TARGET_PLATFORM PLATFORM_SKIA
#endif

// Mac
#if defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && !defined(FLA_TARGET_PLATFORM)
#undef FLA_TARGET_PLATFORM
#define FLA_TARGET_PLATFORM FLA_PLATFORM_MAC
#endif

// iOS
#if defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && !defined(FLA_TARGET_PLATFORM)
#define FLA_TARGET_PLATFORM FLA_PLATFORM_IOS
#endif

#if !defined(FLA_TARGET_PLATFORM)
#define SK_SUPPORT_LEGACY_SHADER_LOCALMATRIX
#define FLA_TARGET_PLATFORM FLA_PLATFORM_SKIA
#endif

#endif
