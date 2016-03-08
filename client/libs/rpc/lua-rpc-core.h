//
//  lua-rpc-core.h
//  RPCTest
//
//  Created by HJC on 15/2/12.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#ifndef __LUA_RPC_CORE_H__
#define __LUA_RPC_CORE_H__

#include "libra/libra_config.h"
#include "RpcClient.h"
#include "lua_compatible.h"

namespace rpc
{
    RpcClient* getGlobalClient();

    void cache_setfield(lua_State* L, const char* tableName, const char* key);
    void cache_getfield(lua_State* L, const char* tableName, const char* key);
}

libra_extern int luaopen_rpc_core(lua_State* L);

#endif
