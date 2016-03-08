//
//  lua_register_game.cpp
//  WeAreHeros
//
//  Created by HJC on 14/12/29.
//
//

#include "cocos2d.h"
#include "lua_register_game.h"
#include "GameUtils.h"
#include "clover/ScopeGuard.h"
//#include "sdklib/GameSdk.h"

static int lua_removeAllUnusedResources(lua_State* L)
{
    GameUtils::removeAllUnusedResources();
    return 0;
}

static int lua_getPackagePath(lua_State* L)
{
    auto path = GameUtils::getPackagePath();
    lua_pushlstring(L, path.c_str(), path.size());
    return 1;
}

static int lua_saveDecryptString(lua_State* L)
{
    const char* content = luaL_checkstring(L, 1);
    const char* path = luaL_checkstring(L, 2);
    GameUtils::saveDecryptString(content, path);
    return 0;
}

static int lua_readDecryptFile(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    auto content = GameUtils::readDecryptFile(path);
    lua_pushstring(L, content.c_str());
    return 1;
}

static int lua_getResourcePath(lua_State* L)
{
    auto path = GameUtils::getResourcePath();
    lua_pushlstring(L, path.c_str(), path.size());
    return 1;
}
static int lua_removeDirContent(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    GameUtils::removeDirContent(path);
    return 0;
}

static int lua_bxor(lua_State* L)
{
    auto a = luaL_checkint(L, 1);
    auto b = luaL_checkint(L, 2);
    lua_pushinteger(L, a ^ b);
    return 1;
}

int lua_register_game(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, "game", 0);
    tolua_beginmodule(L, "game");
    CLOVER_SCOPE_EXIT
    {
        tolua_endmodule(L);
    };

    tolua_function(L, "removeAllUnusedResources", lua_removeAllUnusedResources);
    tolua_function(L, "getPackagePath", lua_getPackagePath);
    tolua_function(L, "getResourcePath", lua_getResourcePath);
    tolua_function(L, "saveDecryptString", lua_saveDecryptString);
    tolua_function(L, "readDecryptFile", lua_readDecryptFile);
    tolua_function(L, "removeDirContent", lua_removeDirContent);
    tolua_function(L, "bxor", lua_bxor);
    return 0;
}
