//
//  lua_register_hero_modules.cpp
//  WeAreHeros
//
//  Created by HJC on 14/11/24.
//
//

#include "lua_register_fla_ex.h"
#include "lua_register_ui_load.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaEngine.h"
#include "CCLuaValue.h"
#include "libra/libra_strbuf.h"
#include "clover/ScopeGuard.h"
#include "RoleGLProgram.h"
#include "SDKWrapper.h"
#include "./fla_ex/Preloader.h"
#include "RoleNode.h"
#include "FlaLua.h"
#include "cclua/cclua.hpp"

int lua_cocos2dx_flasdk_FlaRoleNode_createWithDefinition(lua_State* L)
{
    int argc = lua_gettop(L) - 1;
    if (argc == 2 || argc == 1)
    {
        fla::Definition* definition;
        if (!luaval_to_object<fla::Definition>(L, 2, "fla.Definition", &definition))
        {
            return 0;
        }

        float scale = 1.0;
        if (argc == 2)
        {
            scale = luaL_checknumber(L, 3);
        }

        auto ret = fla_ex::RoleNode::createWithDefinition(FlaDefinition(definition), scale);
        object_to_luaval(L, "fla.ex.RoleNode", ret);
        return 1;
    }
    return 0;
}

static int lua_FlaRoleNode_setShaderFlags(lua_State* L)
{
    fla_ex::RoleNode* cobj = (fla_ex::RoleNode*)tolua_tousertype(L, 1, 0);
    int argc = lua_gettop(L) - 1;
    if (argc == 1)
    {
        size_t len = lua_objlen(L, 2);
        if (len == 4)
        {
            GLint flags[4];
            for (int i = 0; i < 4; i++)
            {
                lua_rawgeti(L, 2, i + 1);
                flags[i] = (GLint)lua_tonumber(L, -1);
                lua_pop(L, 1);
            }
            cobj->setShaderFlags(flags);
        }
    }
    return 0;
}

static int lua_FlaRoleNode_setPixelFormat(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](fla_ex::RoleNode* node, int format)
                           {
                               node->setPixelFormat((FlaPixelFormat)format);
                           });
}

static int lua_register_cocos2dx_flasdk_FlaRoleNode(lua_State* L)
{
    cclua::ToLuaCClass<fla_ex::RoleNode> cls(L, "RoleNode", "fla.ex.RoleNode", "fla.TimeMovieNode");
    tolua_function(L, "createWithDefinition", lua_cocos2dx_flasdk_FlaRoleNode_createWithDefinition);
    tolua_function(L, "setShaderFlags", lua_FlaRoleNode_setShaderFlags);
    tolua_function(L, "setPixelFormat", lua_FlaRoleNode_setPixelFormat);
    return 1;
}

static int lua_fla_getGlobalCacheStrategy(lua_State* tolua_S)
{
    int pixelFormat = luaL_checkint(tolua_S, 1);
    FlaCacheStrategy* strategy = fla_ex::getGlobalCacheStrategy((FlaPixelFormat)pixelFormat);
    lua_pushlightuserdata(tolua_S, strategy);
    return 1;
}

static fla_ex::PreloadItem s_parseePreloadItem(lua_State* L, int index)
{
    fla_ex::PreloadItem item;

    lua_getfield(L, index, "definition");

    fla::Definition* definition;
    luaval_to_object<fla::Definition>(L, -1, "fla.Definition", &definition);

    item.definition = FlaDefinition(definition);
    lua_pop(L, 1);

    lua_getfield(L, index, "scale");
    item.scale = lua_isnil(L, -1) ? 1.0 : lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "format");
    item.format = lua_isnil(L, -1) ? FlaPixelFormat::RGBA4444 : FlaPixelFormat::RGBA8888;
    lua_pop(L, 1);

    return item;
}

static std::vector<fla_ex::PreloadItem> s_parsePreloadItems(lua_State* L, int index)
{
    size_t len = lua_objlen(L, index);
    std::vector<fla_ex::PreloadItem> items;
    items.reserve(len);

    for (size_t i = 0; i < len; i++)
    {
        lua_rawgeti(L, index, (int)i + 1);
        if (lua_istable(L, -1))
        {
            auto item = s_parseePreloadItem(L, -1);
            items.push_back(item);
        }
        lua_pop(L, 1);
    }
    return std::move(items);
}

static int lua_fla_preload(lua_State* L)
{
    assert(L);
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TTABLE);
    LUA_FUNCTION handler = toluafix_ref_function(L, 3, 0);

    auto roleItems = s_parsePreloadItems(L, 1);
    auto effectItems = s_parsePreloadItems(L, 2);

    fla_ex::Preloader* preloader = new fla_ex::Preloader();
    ScriptHandlerMgr::HandlerType onProgressType = ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN;
    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)preloader, handler, onProgressType);

    preloader->onFinish = [=]
    {
        preloader->release();
    };

    preloader->onProgress = [=](int total, int current)
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(preloader, onProgressType);
        if (0 == handler)
        {
            return;
        }

        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->pushInt(total);
        stack->pushInt(current);
        stack->executeFunctionByHandler(handler, 2);
    };

    preloader->preload(roleItems, effectItems);
    return 0;
}

static int lua_fla_setRolePackageStateNames(lua_State* L)
{
    std::vector<std::string> stateNames;
    if (luaval_to_std_vector_string(L, 1, &stateNames))
    {
        fla_ex::RoleCacheStrategy::setPackageStateNames(stateNames);
    }
    return 0;
}

static int s_lua_loadRoleDefaultProgram(lua_State* L)
{
    if (lua_isnil(L, 1))
    {
        fla_ex::RoleGLProgram::loadDefaultProgram(nullptr);
    }
    else
    {
        const char* string = luaL_checkstring(L, 1);
        fla_ex::RoleGLProgram::loadDefaultProgram(string);
    }
    return 0;
}

static int s_lua_getCollection(lua_State* L)
{
    auto bin = luaL_checkstring(L, 1);
    auto collection = fla_ex::getCollection(bin);
    FlaLua::pushCollection(L, collection);
    return 1;
}

int lua_register_fla_ex(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, "fla", 0);
    tolua_beginmodule(L, "fla");
    CLOVER_SCOPE_EXIT
    {
        tolua_endmodule(L);
    };

    tolua_module(L, "ex", 0);
    tolua_beginmodule(L, "ex");
    CLOVER_SCOPE_EXIT
    {
        tolua_endmodule(L);
    };

    lua_register_cocos2dx_flasdk_FlaRoleNode(L);
    tolua_function(L, "getGlobalCacheStrategy", lua_fla_getGlobalCacheStrategy);
    tolua_function(L, "getCollection", s_lua_getCollection);
    tolua_function(L, "preload", lua_fla_preload);
    tolua_function(L, "setRolePackageStateNames", lua_fla_setRolePackageStateNames);
    tolua_function(L, "loadRoleDefaultProgram", s_lua_loadRoleDefaultProgram);
    lua_register_ui_load(L);

    return 1;
}
