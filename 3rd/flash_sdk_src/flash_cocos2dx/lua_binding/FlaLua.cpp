//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../../core/base/fla_Base.h"
#if FLA_USE_LUA_BINDING == 1

#include "../FlaLua.h"
#include "lua_cocos2dx_flashsdk.h"

int FlaLua::registerFlaSDK(lua_State* tolua_S)
{
    return register_all_cocos2dx_flasdk(tolua_S);
}

void FlaLua::pushCollection(lua_State* L, const FlaCollection& collection)
{
    flalua::pushCollection(L, collection);
}

FlaCollection FlaLua::toCollection(lua_State* L, int idx)
{
    return flalua::toCollection(L, idx);
}

FlaDefinition FlaLua::toDefinition(lua_State* L, int idx)
{
    return flalua::toDefinition(L, idx);
}

#endif
