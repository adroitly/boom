//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionScene.h"

namespace fla
{
    Rect DefinitionScene::getBounds() const
    {
        return Rect(0, 0, _size.width, _size.height);
    }

    DefinitionScene::Ptr DefinitionScene::create()
    {
        return make_ptr<DefinitionScene>();
    }
}
