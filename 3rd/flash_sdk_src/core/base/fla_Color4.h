//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_COLOR4_H__
#define __FLA_COLOR4_H__

#include "fla_Base.h"

namespace fla
{
    // 颜色, 用rgba表示，每个分量的值为，0到1
    template <typename T>
    class ColorBase
    {
    public:
        ColorBase() : red(1.0), green(1.0), blue(1.0), alpha(1.0)
        {
        }

        ColorBase(T r, T g, T b, T a) : red(r), green(g), blue(b), alpha(a)
        {
        }

        bool isInvisible() const
        {
            return alpha == 0.0;
        }
        T red;
        T green;
        T blue;
        T alpha;
    };

    ///////////////////////////////////
    // 相等判断
    template <typename T>
    inline bool operator==(const ColorBase<T>& lhs, const ColorBase<T>& rhs)
    {
        return
        lhs.red == rhs.red &&
        lhs.green == rhs.green &&
        lhs.blue == rhs.blue &&
        lhs.alpha == rhs.alpha;
    }

    template <typename T>
    inline bool operator!=(const ColorBase<T>& lhs, const ColorBase<T>& rhs)
    {
        return !(lhs == rhs);
    }
    
    typedef ColorBase<real_t> Color4;
}

#endif
