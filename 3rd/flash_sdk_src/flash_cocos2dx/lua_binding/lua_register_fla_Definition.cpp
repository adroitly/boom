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
#include "../../core/definition/fla_Definition.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "../src/fla_cocos2d_Texture.h"
#include "clover/ScopeGuard.h"

static int lua_transToTexture(lua_State* L)
{
    auto cobj = (fla::Definition*)tolua_tousertype(L, 1, 0);
    int argc = lua_gettop(L) - 1;
    if (argc == 1 || argc == 2 || argc == 3)
    {
        fla::PixelFormat pixelformat = fla::PixelFormat::RGBA8888;
        float scale = 1.0;
        float ratio = 0.0;
        
        if (argc == 1)
        {
            scale = luaL_checknumber(L, 2);
        }
        else if (argc == 2)
        {
            scale = luaL_checknumber(L, 2);
            pixelformat = (fla::PixelFormat)luaL_checkinteger(L, 3);
        }
        else
        {
            scale = luaL_checknumber(L, 2);
            ratio = luaL_checknumber(L, 3);
            pixelformat = (fla::PixelFormat)luaL_checkinteger(L, 4);
        }
        
        cocos2d::Texture2D* ret = fla::definition_transToTexture(cobj, scale, ratio, pixelformat);
        object_to_luaval(L, "cc.Texture2D", ret);
        return 1;
    }
    return 0;
}

static int lua_getFrameRate(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj)
                            {
                                auto dataInfo = cobj->getDataInfo();
                                return dataInfo ? dataInfo->getFrameRate() : 24;
                            });
}

static int lua_changeDefaultState(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj, const char* name)
                            {
                                fla::Definition_changeDefaultState(cobj, name);
                            });
}

static int lua_findState(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj, const char* name)
                            {
                                auto state = fla::Definition_findState(cobj, name);
                                flalua::pushDefinition(L, state);
                                return cclua::NResults(1);
                            });
}

static int lua_getChildPlacements(lua_State* L)
{
    auto definition = (fla::Definition*)tolua_tousertype(L, 1, 0);
    int argc = lua_gettop(L) - 1;
    if (argc == 1)
    {
        float scale = luaL_checknumber(L, 2);
        auto placements = FlaDefinition(definition).getChildPlacements(scale);
        lua_newtable(L);
        int index = 1;
        for (auto& placement : placements)
        {
            lua_newtable(L);
            flalua::pushDefinition(L, placement.definition);
            lua_setfield(L, -2, "definition");

            affinetransform_to_luaval(L, placement.transform);
            lua_setfield(L, -2, "transform");

            lua_pushinteger(L, placement.depth);
            lua_setfield(L, -2, "depth");

            lua_rawseti(L, -2, index);
            index++;
        }
        return 1;
    }
    return 0;
}

static int lua_getBounds(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj)
                            {
                                auto rect = FlaDefinition(cobj).getBounds();
                                rect_to_luaval(L, rect);
                                return cclua::NResults(1);
                            });
}

static int lua_loadFile(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](void* cls, const char* filePath)
                            {
                                auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
                                FlaErrorCode errorCode;
                                auto definition = FlaDefinition::loadData(data.getBytes(), data.getSize(), &errorCode);
                                flalua::pushDefinition(L, definition);
                                lua_pushinteger(L, (lua_Integer)errorCode);
                                return cclua::NResults(2);
                            });
}

static int setFixHscreen(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj, bool flag)
                            {
                                cobj->setFixHscreen(flag);
                            });
}

static int lua_getName(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj)
                            {
                                lua_pushstring(L, cobj->getName());
                                return cclua::NResults(1);
                            });
}

static int lua_getId(lua_State* L)
{
    return cclua::obj_call(L,
                            [=](fla::Definition* cobj)
                            {
                                return cobj->getId();
                            });
}

int lua_register_fla_Definition(lua_State* L)
{
    cclua::ToLuaCClass<FlaDefinition> cls(L, "Definition", "fla.Definition", "cc.Ref");
    tolua_function(L, "transToTexture", lua_transToTexture);
    tolua_function(L, "getFrameRate", lua_getFrameRate);
    tolua_function(L, "changeDefaultState", lua_changeDefaultState);
    tolua_function(L, "findState", lua_findState);
    tolua_function(L, "loadFile", lua_loadFile);
    tolua_function(L, "getChildPlacements", lua_getChildPlacements);
    tolua_function(L, "getBounds", lua_getBounds);
    tolua_function(L, "setFixHscreen", setFixHscreen);
    tolua_function(L, "getName", lua_getName);
    tolua_function(L, "getId", lua_getId);
    return 1;
}

#endif
