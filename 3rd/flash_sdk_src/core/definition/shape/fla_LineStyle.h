//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLASTYLE_H__
#define __FLASTYLE_H__

#include <stdint.h>
#include <memory.h>
#include "../../base/fla_Color4.h"
#include "../../utility/fla_Holder.h"

namespace fla
{
    enum class LineCapStyle : uint8_t
    {
        Round = 0,
        NoCap = 1,
        Square = 2,
    };

    enum class LineJoinStyle : uint8_t
    {
        Round = 0,
        Bevel = 1,
        Miter = 2,
    };

    template <int N>
    struct LineStyleBase
    {
        LineStyleBase()
        {
            memset(this, 0, sizeof(LineStyleBase));
            onlyWidthAndColor = true;
        }

        LineCapStyle startCapStyle;
        LineCapStyle endCapStyle;
        LineJoinStyle jointStyle;

        uint8_t hasFillFlag : 1;
        uint8_t noHScaleFlag : 1;
        uint8_t noVScaleFlag : 1;
        uint8_t pixelHintingFlag : 1;
        uint8_t noClose : 1;
        uint8_t onlyWidthAndColor : 1;
        real_t miterLimitFactor;

        Holder<real_t, N> width;
        Holder<Color4, N> color;

        bool operator==(const LineStyleBase& rhs) const
        {
            return memcmp(this, &rhs, sizeof(LineStyleBase)) == 0;
        }

        inline bool operator!=(const LineStyleBase& rhs) const
        {
            return !(*this == rhs);
        }

        bool isInvisible() const;
    };

    template <>
    inline bool LineStyleBase<1>::isInvisible() const
    {
        return color.val.isInvisible();
    }

    template <>
    inline bool LineStyleBase<2>::isInvisible() const
    {
        return color.start.isInvisible() && color.end.isInvisible();
    }

    typedef LineStyleBase<1> LineStyle;
    typedef LineStyleBase<2> MorphLineStyle;
}

#endif
