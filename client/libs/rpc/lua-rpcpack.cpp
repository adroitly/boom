//
//  lua-rpcpack.cpp
//  RPCTest
//
//  Created by HJC on 15/2/11.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

/*#include "lua-rpcpack.h"
#include "rpcpack.h"
#include "libra/libra_string.h"
#include "ScopeGuard.h"


static int s_unpack(lua_State* L)
{
    if (lua_isnoneornil(L, 1))
    {
        return 0;
    }

    // session
    const char* begin = (const char*)lua_touserdata(L, 1);
    const char* end = begin + luaL_checkinteger(L, 2);

    uint16_t session = 0;
    libra_slice cmd;
    libra_slice data;

    rpc::message_unpack(begin, end, &session, &cmd, &data);

    lua_pushinteger(L, session);
    lua_pushlstring(L, cmd.begin, cmd.end - cmd.begin);

    if (data.begin < data.end)
    {
        lua_pushlightuserdata(L, (void*)data.begin);
        lua_pushinteger(L, data.end - data.begin);
        return 4;
    }
    return 2;
}

static int s_pack(lua_State* L)
{
    uint16_t session = luaL_checkint(L, 1);

    size_t cmd_size;
    size_t data_size;

    const char* cmd = luaL_checklstring(L, 2, &cmd_size);
    const char* data = luaL_checklstring(L, 3, &data_size);

    membuf_init_stack(result, 64);
    CLOVER_SCOPE_EXIT
    {
        membuf_finish(result);
    };

    uint16_t size = 0;
    membuf_push(result, &size, 2);

    libra_slice cmd_range = { cmd, cmd + cmd_size };
    libra_slice data_range = { data, data + data_size };
    rpc::message_pack(result, session, cmd_range, data_range);

    size = membuf_size(result) - 2;
    *reinterpret_cast<uint16_t*>(membuf_ptr(result, 0)) = htons(size);

    lua_pushlstring(L, (char*)membuf_ptr(result, 0), membuf_size(result));
    return 1;
}

int luaopen_rpcpack(lua_State* L)
{
    luaL_checkversion(L);
    luaL_Reg l[] = {
        { "unpack", s_unpack }, { "pack", s_pack }, { NULL, NULL },
    };
    luaL_newlib(L, l);
    return 1;
}
*/