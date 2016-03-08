//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Lerp.h"
#include "libra/libra_math.h"

namespace fla
{
    Color4 lerp(const Color4& lhs, const Color4& rhs, real_t ratio)
    {
        auto r = libra_lerp(lhs.red, rhs.red, ratio);
        auto g = libra_lerp(lhs.green, rhs.green, ratio);
        auto b = libra_lerp(lhs.blue, rhs.blue, ratio);
        auto a = libra_lerp(lhs.alpha, rhs.alpha, ratio);
        return Color4(r, g, b, a);
    }

    Matrix lerp(const Matrix& lhs, const Matrix& rhs, real_t ratio)
    {
        return Matrix::lerp(lhs, rhs, ratio);
    }
}
