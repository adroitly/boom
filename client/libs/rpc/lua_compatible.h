//
//  lua_compatible.h
//  WeAreHeros
//
//  Created by HJC on 15/2/15.
//
//

#ifndef __LUA_COMPATIBLE__
#define __LUA_COMPATIBLE__

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#if LUA_VERSION_NUM == 501

#define lua_rawlen lua_objlen
#define luaL_checkversion(L)

int lua_absindex(lua_State* L, int idx);
int luaL_getsubtable(lua_State* L, int idx, const char* fname);
void luaL_requiref(lua_State* L, const char* modname, lua_CFunction openf, int glb);

#endif

#endif
