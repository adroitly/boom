//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_UTILS_H__
#define __FLA_UTILS_H__

#include "fla_Base.h"
#include <string>

namespace fla
{
    Rect adjustRectForRender(const Rect& rt, real_t sizeScale);
    Point adjustPointForRender(const Rect& rt);

    std::string keyOfCache(const std::string& dataMd5, int Id, int tag, float scale, float ratio);
}

#endif
