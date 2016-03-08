//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLALUA_H__
#define __FLALUA_H__

#include "base/ccConfig.h"
#include "tolua++.h"
#include "FlaCollection.h"

struct FlaLua
{
    static int registerFlaSDK(lua_State* L);
    static void pushCollection(lua_State* L, const FlaCollection& collection);
    
    static FlaCollection toCollection(lua_State* L, int idx);
    static FlaDefinition toDefinition(lua_State* L, int idx);
};

#endif
