//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================
#ifndef __FLA_COLORTRANSFORM_H__
#define __FLA_COLORTRANSFORM_H__

#include "fla_Base.h"
#include "fla_Color4.h"

namespace fla
{
    // 颜色变换
    class ColorTransform final
    {
    public:
        real_t rMult;
        real_t gMult;
        real_t bMult;
        real_t aMult;
        
        real_t rAdd;
        real_t gAdd;
        real_t bAdd;
        real_t aAdd;

        static const ColorTransform& identity();
        static ColorTransform make(real_t rM,
                                   real_t gM,
                                   real_t bM,
                                   real_t aM,
                                   real_t rA,
                                   real_t gA,
                                   real_t bA,
                                   real_t aA);

        void setIdentity();
        bool isIdentity() const;
    };

    static_assert(std::is_pod<ColorTransform>::value, "");

    bool operator==(const ColorTransform& lhs, const ColorTransform& rhs);
    bool operator!=(const ColorTransform& lhs, const ColorTransform& rhs);

    ColorTransform lerp(const ColorTransform& lhs, const ColorTransform& rhs, real_t ratio);
    ColorTransform operator*(const ColorTransform& lhs, const ColorTransform& rhs);
    Color4 operator*(const ColorTransform& trans, const Color4& s);
}

#endif
