//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_RenderShape.h"
#include "fla_ShapeGraphicsUtils.h"

namespace fla
{
    bool isSolidFill(const Shape& shape, const Path& path)
    {
        if (path.fillStyle() >= 0)
        {
            if (shape.fillStyles[path.fillStyle()].isSolidStyle())
            {
                return true;
            }
        }
        return false;
    }
}
