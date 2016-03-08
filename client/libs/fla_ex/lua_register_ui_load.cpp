//
//  lua_register_ui_load.cpp
//  big-devil
//
//  Created by PatGame on 15/3/17.
//
//

#include "lua_register_ui_load.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "FlaLua.h"
#include "FlaUI.h"
#include "SDKWrapper.h"

static bool s_getNames(const char* begin, const char* end, std::vector<std::string>& names)
{
    names.clear();
    auto iter = std::find(begin, end, ':');
    if (iter != end)
    {
        names.push_back(std::string(begin, iter) + ".bin");
        names.push_back(std::string(iter + 1, end));
        return true;
    }
    return false;
}

static fla_ex::UIPreloadInfo s_parseUIPreloadInfo(lua_State* L, int idx)
{
    fla_ex::UIPreloadInfo info;
    if (lua_istable(L, idx))
    {
        lua_getfield(L, idx, "scale");
        if (lua_isnumber(L, -1))
        {
            info.scale = lua_tonumber(L, -1);
        }
        lua_pop(L, 1);

        lua_getfield(L, idx, "format");
        if (lua_isnumber(L, -1))
        {
            info.format = (FlaPixelFormat)lua_tointeger(L, -1);
        }
        lua_pop(L, 1);

        lua_getfield(L, idx, "save");
        if (lua_type(L, -1) == LUA_TBOOLEAN)
        {
            info.saveToFile = lua_toboolean(L, -1);
        }
        lua_pop(L, 1);
    }
    return info;
}

static int s_lua_getSpriteFrame(lua_State* L)
{
    cocos2d::SpriteFrame* spriteFrame = nullptr;
    if (lua_type(L, 1) == LUA_TSTRING)
    {
        std::vector<std::string> names;
        names.reserve(2);

        size_t len;
        const char* str = lua_tolstring(L, 1, &len);

        if (s_getNames(str, str + len, names))
        {
            auto collection = fla_ex::getCollection(names[0]);
            auto preloadInfo = s_parseUIPreloadInfo(L, 2);
            spriteFrame = fla_ex::getSpriteFrame(collection, names[1], preloadInfo);
        }
    }
    else
    {
        auto collection = FlaLua::toCollection(L, 1);
        std::string name = luaL_checkstring(L, 2);
        auto preloadInfo = s_parseUIPreloadInfo(L, 3);
        spriteFrame = fla_ex::getSpriteFrame(collection, name, preloadInfo);
    }

    object_to_luaval(L, "cc.SpriteFrame", spriteFrame);
    return 1;
}

static FlaDefinition s_getDefinition(lua_State* L, int idx, std::vector<std::string>& names)
{
    if (lua_type(L, idx) != LUA_TSTRING)
    {
        return FlaLua::toDefinition(L, idx);
    }

    size_t len;
    const char* str = lua_tolstring(L, idx, &len);
    if (s_getNames(str, str + len, names))
    {
        auto collection = fla_ex::getCollection(names[0]);
        return collection.findDefinition(names[1]);
    }

    return FlaDefinition();
}

static int s_lua_loadSpriteFrames(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    size_t len = lua_objlen(L, 1);
    std::vector<FlaDefinition> definitions;
    definitions.reserve(len);

    std::vector<std::string> names;
    names.reserve(2);

    for (int i = 1; i <= len; i++)
    {
        lua_rawgeti(L, 1, i);
        FlaDefinition def = s_getDefinition(L, -1, names);
        if (!def.isNull())
        {
            definitions.push_back(def);
        }
        lua_pop(L, 1);
    }

    auto info = s_parseUIPreloadInfo(L, 2);
    fla_ex::loadSpriteFrames(definitions, info);
    return 0;
}

static int s_lua_getTexture2D(lua_State* L)
{
    std::vector<std::string> names;
    names.reserve(2);
    FlaDefinition def = s_getDefinition(L, 1, names);
    auto info = s_parseUIPreloadInfo(L, 2);
    auto texture2d = def.transToTexture(info.scale, info.format);
    object_to_luaval(L, "cc.Texture2D", texture2d);
    return 1;
}

static int s_lua_loadUIAsync(lua_State* L)
{
    const char* name = lua_tostring(L, 1);
    fla_ex::loadUIAsync(name);    
    return 0;
}

int lua_register_ui_load(lua_State* L)
{
    tolua_function(L, "getSpriteFrame", s_lua_getSpriteFrame);
    tolua_function(L, "getTexture2D", s_lua_getTexture2D);
    tolua_function(L, "loadSpriteFrames", s_lua_loadSpriteFrames);
    tolua_function(L, "loadUIAsync", s_lua_loadUIAsync);
    return 1;
}
