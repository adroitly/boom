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
#include "lua_cocos2dx_flashsdk.h"
#include "cclua/cclua.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "../../core/definition/fla_Collection.h"
#include "FlaDefinition.h"
#include "clover/ScopeGuard.h"

static int lua_loadFile(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](void* cls, const char* filePath)
                           {
                               auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
                               FlaErrorCode errorCode;
                               auto collection = FlaCollection::loadData(data.getBytes(), data.getSize(), &errorCode);
                               flalua::pushCollection(L, collection);
                               lua_pushinteger(L, (lua_Integer)errorCode);
                               return cclua::NResults(2);
                           });
}

static int lua_rootDefinition(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::Collection* collection)
                           {
                               flalua::pushDefinition(L, collection->rootDefinition());
                               return cclua::NResults(1);
                           });
}

static int lua_findDefinition(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla::Collection* collection, cclua::Index idx)
                           {
                               fla::Definition::Ptr defintion;
                               auto type = lua_type(L, idx.val);
                               if (type == LUA_TNUMBER)
                               {
                                   defintion = collection->findDefinition(lua_tonumber(L, idx.val));
                               }
                               else if (type == LUA_TSTRING)
                               {
                                   defintion = collection->findDefinition(lua_tostring(L, idx.val));
                               }
                               flalua::pushDefinition(L, defintion);
                               return cclua::NResults(1);
                           });
}

int lua_register_fla_Collection(lua_State* L)
{
    cclua::ToLuaCClass<FlaCollection> cls(L, "Collection", "fla.Collection", "cc.Ref");
    tolua_function(L, "loadFile", lua_loadFile);
    tolua_function(L, "rootDefinition", lua_rootDefinition);
    tolua_function(L, "findDefinition", lua_findDefinition);
    return 1;
}

#endif

