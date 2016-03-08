//
//  lua_register_game.h
//  WeAreHeros
//
//  Created by HJC on 14/12/29.
//
//

#ifndef __LUA_REGISTER_GAME_H__
#define __LUA_REGISTER_GAME_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int lua_register_game(lua_State* L);

#endif
