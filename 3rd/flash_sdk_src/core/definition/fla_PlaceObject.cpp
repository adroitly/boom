//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_PlaceObject.h"
#include <assert.h>

namespace fla
{
    PlaceObject::PlaceObject()
    {
        _depth = 0;
        _characterID = 0;
        _ratio = 0;
        _flags = 0;
        _blendMode = BlendMode::Normal;
    }

    void PlaceObject::setCharacterID(uint16_t Id)
    {
        assert(Id != 0);
        _characterID = Id;
        libra::bit_set(&_flags, Bit_HasCharacterID);
    }
}