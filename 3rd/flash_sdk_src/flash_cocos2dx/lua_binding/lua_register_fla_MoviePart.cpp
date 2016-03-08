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

#include "FlaSDK.h"
#include "tolua_fix.h"
#include "lua_cocos2dx_flashsdk.h"
#include "cclua/cclua.hpp"
#include "LuaBasicConversions.h"
#include "../src/fla_MoviePart.h"
#include "clover/ScopeGuard.h"

static int lua_hide(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part)
                           {
                               part->hide();
                           });
}

static int lua_show(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part)
                           {
                               part->show();
                           });
}

static int lua_replaceDefinition(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part, cclua::Index idx)
                           {
                               fla::Definition* definition;
                               if (!luaval_to_object(L, idx.val, "fla.Definition", &definition))
                               {
                                   return;
                               }
                               part->replaceDefinition(definition);
                           });
}

static int lua_resetDefintion(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part)
                           {
                               part->resetDefinition();
                           });
}

static int lua_changeState(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part, cclua::Index idx)
                           {
                               auto type = lua_type(L, idx.val);
                               if (type == LUA_TSTRING)
                               {
                                   const char* name = lua_tostring(L, idx.val);
                                   return part->changeState(name);
                               }
                               else if (type == LUA_TNUMBER)
                               {
                                   int stateIdx = (int)luaL_checkinteger(L, idx.val);
                                   return part->changeState(stateIdx);
                               }
                               return false;
                           });
}

static int lua_setTranslation(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part, float x, float y)
                           {
                               part->setTranslation(x, y);
                           });
}


static int lua_findMoviePart(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::MoviePart* part, cclua::Index idx)
                           {
                               auto type = lua_type(L, idx.val);
                               fla::MoviePart* result = nullptr;
                               if (type == LUA_TSTRING)
                               {
                                   const char* name = lua_tostring(L, idx.val);
                                   result = part->findMoviePart(name);
                               }
                               else if (type == LUA_TNUMBER)
                               {
                                   int stateIdx = (int)luaL_checkinteger(L, idx.val);
                                   result = part->findMoviePart(stateIdx);
                               }
                               
                               flalua::pushMoviePart(L, FlaMoviePart(result));
                               return cclua::NResults(1);
                           });
}

int lua_register_fla_MoviePart(lua_State* L)
{
    cclua::ToLuaCClass<FlaDefinition> cls(L, "MoviePart", "fla.MoviePart", "cc.Ref");
    
    tolua_function(L, "hide", lua_hide);
    tolua_function(L, "show", lua_show);
    tolua_function(L, "replaceDefinition", lua_replaceDefinition);
    tolua_function(L, "resetDefinition", lua_resetDefintion);
    tolua_function(L, "changeState", lua_changeState);
    tolua_function(L, "setTranslation", lua_setTranslation);
    tolua_function(L, "findMoviePart", lua_findMoviePart);
    return 1;
}

#endif
