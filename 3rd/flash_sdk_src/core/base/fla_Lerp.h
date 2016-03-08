//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_LERP__
#define __FLA_LERP__

#include "fla_Color4.h"
#include "fla_ColorTransform.h"

namespace fla
{
    Color4 lerp(const Color4& lhs, const Color4& rhs, real_t ratio);
    Matrix lerp(const Matrix& lhs, const Matrix& rhs, real_t ratio);
}

#endif
