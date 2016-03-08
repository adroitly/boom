//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __LUA_COCOS2DX_FLASHSDK_H__
#define __LUA_COCOS2DX_FLASHSDK_H__

#include "base/ccConfig.h"
#include "tolua++.h"
#include "../../core/definition/fla_Definition.h"
#include "../FlaMoviePart.h"

int register_all_cocos2dx_flasdk(lua_State* L);

namespace flalua
{
    void pushCollection(lua_State* L, const FlaCollection& collection);
    FlaCollection toCollection(lua_State* L, int idx);
    FlaDefinition toDefinition(lua_State* L, int idx);
    
    void pushDefinition(lua_State* L, const FlaDefinition& defintion);
    void pushDefinition(lua_State* L, const fla::Definition::Ptr& defintion);
    
    void pushMoviePart(lua_State* L, const FlaMoviePart& part);
}

#endif
