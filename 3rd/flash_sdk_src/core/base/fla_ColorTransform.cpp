//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_ColorTransform.h"
#include <algorithm>
#include <string.h>
#include "libra/libra_math.h"

namespace fla
{
    static ColorTransform s_identity = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };

    const ColorTransform& ColorTransform::identity()
    {
        return s_identity;
    }

    void ColorTransform::setIdentity()
    {
        *this = s_identity;
    }

    bool ColorTransform::isIdentity() const
    {
        return *this == s_identity;
    }

    ColorTransform operator*(const ColorTransform& lhs, const ColorTransform& rhs)
    {
        ColorTransform result;
        result.rMult = lhs.rMult * rhs.rMult;
        result.gMult = lhs.gMult * rhs.gMult;
        result.bMult = lhs.bMult * rhs.bMult;
        result.aMult = lhs.aMult * rhs.aMult;

        result.rAdd = lhs.rMult * rhs.rAdd + lhs.rAdd;
        result.gAdd = lhs.gMult * rhs.gAdd + lhs.gAdd;
        result.bAdd = lhs.bMult * rhs.bAdd + lhs.bAdd;
        result.aAdd = lhs.aMult * rhs.aAdd + lhs.aAdd;
        return result;
    }

    static inline real_t s_clamp(real_t v)
    {
        return std::max<real_t>(0.0, std::min<real_t>(1.0, v));
    }

    Color4 operator*(const ColorTransform& trans, const Color4& s)
    {
        Color4 d;
        d.red = s.red * trans.rMult + trans.rAdd;
        d.green = s.green * trans.gMult + trans.gAdd;
        d.blue = s.blue * trans.bMult + trans.bAdd;
        d.alpha = s.alpha * trans.aMult + trans.aAdd;

        d.red = s_clamp(d.red);
        d.green = s_clamp(d.green);
        d.blue = s_clamp(d.blue);
        d.alpha = s_clamp(d.alpha);

        return d;
    }

    ColorTransform ColorTransform::make(real_t rM,
                                        real_t gM,
                                        real_t bM,
                                        real_t aM,
                                        real_t rA,
                                        real_t gA,
                                        real_t bA,
                                        real_t aA)
    {
        ColorTransform m;
        m.rMult = rM;
        m.gMult = gM;
        m.bMult = bM;
        m.aMult = aM;

        m.rAdd = rA;
        m.gAdd = gA;
        m.bAdd = bA;
        m.aAdd = aA;
        return m;
    }

    bool operator==(const ColorTransform& lhs, const ColorTransform& rhs)
    {
        return ::memcmp(&lhs, &rhs, sizeof(ColorTransform)) == 0;
    }

    bool operator!=(const ColorTransform& lhs, const ColorTransform& rhs)
    {
        return !(lhs == rhs);
    }

    ColorTransform lerp(const ColorTransform& lhs, const ColorTransform& rhs, real_t ratio)
    {
        ColorTransform trans;
        trans.rMult = libra_lerp(lhs.rMult, rhs.rMult, ratio);
        trans.gMult = libra_lerp(lhs.gMult, rhs.gMult, ratio);
        trans.bMult = libra_lerp(lhs.bMult, rhs.bMult, ratio);
        trans.aMult = libra_lerp(lhs.aMult, rhs.aMult, ratio);
        trans.rAdd = libra_lerp(lhs.rAdd, rhs.rAdd, ratio);
        trans.gAdd = libra_lerp(lhs.gAdd, rhs.gAdd, ratio);
        trans.bAdd = libra_lerp(lhs.bAdd, rhs.bAdd, ratio);
        trans.aAdd = libra_lerp(lhs.aAdd, rhs.aAdd, ratio);
        return trans;
    }
}
