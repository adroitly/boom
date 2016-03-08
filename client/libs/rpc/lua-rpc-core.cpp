//
//  lua-rpc-core.cpp
//  RPCTest
//
//  Created by HJC on 15/2/12.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#include "lua-rpc-core.h"

#if LUA_VERSION_NUM == 501
#define luaL_newlib(L, reg) luaL_register(L, "rpc.core", reg)
#endif

namespace rpc
{
    static const char* s_tableKey   = "rpc.core";
    static const char* s_msgKey     = "msg";
    static const char* s_statsKey   = "sts";

    RpcClient* getGlobalClient()
    {
        static RpcClient s_client;
        return &s_client;
    }

    void cache_setfield(lua_State* L, const char* tableName, const char* key)
    {
        if (tableName == nullptr)
        {
            lua_setfield(L, LUA_REGISTRYINDEX, key);
        }
        else
        {
            luaL_getsubtable(L, LUA_REGISTRYINDEX, tableName);
            lua_pushvalue(L, -2);
            lua_setfield(L, -2, key);
            lua_pop(L, 2);
        }
    }

    void cache_getfield(lua_State* L, const char* tableName, const char* key)
    {
        if (tableName == nullptr)
        {
            lua_getfield(L, LUA_REGISTRYINDEX, key);
        }
        else
        {
            lua_getfield(L, LUA_REGISTRYINDEX, tableName);

            luaL_getsubtable(L, LUA_REGISTRYINDEX, tableName);
            lua_getfield(L, -1, key);
            lua_replace(L, -2);
        }
    }
}

static void on_status(void* ctx,
                      const char* cmd,
                      const char* errorMsg,
                      const char* socketKey)
{
    lua_State* L = (lua_State*)ctx;
    rpc::cache_getfield(L, rpc::s_tableKey, rpc::s_statsKey);
    if (lua_isfunction(L, -1))
    {
        lua_pushstring(L, cmd);
        lua_pushstring(L, errorMsg);
        if (nullptr == socketKey)
            lua_pushnil(L);
        else
            lua_pushstring(L, socketKey);
        int res = lua_pcall(L, 3, 0, 0);
        if (res != 0)
        {
            const char* sz = lua_tostring(L, -1);
            printf("Lua C调用错误：%s\n", sz);
        }
    }
    else
    {
        lua_pop(L, 1);
    }
}

static void on_message(void* ctx, const char* cmd,
                       const void* data,
                       size_t size,
                       const char* socketKey)
{
    lua_State* L = (lua_State*)ctx;
    rpc::cache_getfield(L, rpc::s_tableKey, rpc::s_msgKey);
    
    if (lua_isfunction(L, -1))
    {
        lua_pushstring(L, cmd);
        lua_pushlstring(L, (char*)data, size);
        if (nullptr == socketKey)
            lua_pushnil(L);
        else
            lua_pushstring(L, socketKey);
        int res = lua_pcall(L, 3, 0, 0);
        if (res != 0)
        {
            const char* sz = lua_tostring(L, -1);
            char buf[1024] = {0};
            sprintf(buf, "语法错误：%s", sz);
            on_status(ctx, "SyntaxError", buf, nullptr);
        }
    }
    else
    {
        lua_pop(L, 1);
    }
}

static int s_connect(lua_State* L)
{
    const char* ip = luaL_checkstring(L, 1);
    auto port = luaL_checkint(L, 2);
    auto key = lua_tostring(L, 3);
    rpc::getGlobalClient()->connect(ip, port, key);
//    lua_pushboolean(L, res);
    return 0;
}

static int s_disconnect(lua_State* L)
{
    auto key = lua_tostring(L, 1);
    rpc::getGlobalClient()->disconnect(key);
    return 0;
}

static int s_send(lua_State* L)
{
    auto cmd = luaL_checkstring(L, 1);
    size_t data_size;
    auto data = luaL_checklstring(L, 2, &data_size);
    auto key = lua_tostring(L, 3);
    rpc::getGlobalClient()->send(cmd, data, data_size, key);
    return 0;
}

static int s_callback(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TFUNCTION);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    lua_pushvalue(L, 1);
    rpc::cache_setfield(L, rpc::s_tableKey, rpc::s_msgKey);

    lua_pushvalue(L, 2);
    rpc::cache_setfield(L, rpc::s_tableKey, rpc::s_statsKey);

    rpc::getGlobalClient()->setCallback(L, on_message, on_status);
    return 0;
}

int luaopen_rpc_core(lua_State* L)
{
    luaL_Reg l[] = {
        { "connect",    s_connect       },
        { "disconnect", s_disconnect    },
        { "send",       s_send          },
        { "callback",   s_callback      },
        { NULL, NULL },
    };
    luaL_newlib(L, l);
    return 1;
}
