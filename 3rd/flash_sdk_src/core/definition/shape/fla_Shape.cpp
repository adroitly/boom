//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Shape.h"

namespace fla
{
    Rect Shape::computeEdgeBounds() const
    {
        if (paths.empty())
        {
            return Rect();
        }

        auto bounds = paths[0].edges<0>().computeEdgeBounds();
        auto size = paths.size();
        for (size_t i = 1; i < size; i++)
        {
            bounds.unionRect(paths[i].edges<0>().computeEdgeBounds());
        }
        return bounds;
    }
}
