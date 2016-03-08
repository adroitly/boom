//
//  lua_register_umeng.cpp
//  big-devil
//
//  Created by JiangPaifeng on 15/5/27.
//
//

#include "lua_register_umeng.h"

#if ANDROID
#include "MobClickCpp.h"

static int lua_startStage(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc != 1)
    {
        return 0;
    }
    
    auto stage = luaL_checkstring(L, 1);
    umeng::MobClickCpp::startLevel(stage);
    
    return 0;
}

static int lua_finishStage(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc != 1)
    {
        return 0;
    }
    
    auto stage = luaL_checkstring(L, 1);
    umeng::MobClickCpp::finishLevel(stage);
    
    return 0;
}

static int lua_failStage(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc != 1)
    {
        return 0;
    }
    
    auto stage = luaL_checkstring(L, 1);
    umeng::MobClickCpp::failLevel(stage);
    
    return 0;
}

static int lua_setUserLevel(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc != 1)
    {
        return 0;
    }
    
    auto level = luaL_checkstring(L, 1);
    umeng::MobClickCpp::setUserLevel(level);
    
    return 0;
}

static int lua_buy(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc != 3)
    {
        return 0;
    }
    
    const char* item = luaL_checkstring(L, 1);
    int amount = luaL_checkint(L, 2);
    double price = luaL_checknumber(L, 3);
    umeng::MobClickCpp::buy(item, amount, price);
    
    return 0;
}

#else

static int lua_startStage(lua_State* L){ return 0; }
static int lua_finishStage(lua_State* L){ return 0; }
static int lua_failStage(lua_State* L){ return 0; }
static int lua_setUserLevel(lua_State* L){ return 0; }
static int lua_buy(lua_State* L){ return 0; }

#endif

int lua_register_umeng(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, "umeng", 0);
    tolua_beginmodule(L, "umeng");
    
    tolua_function(L, "startStage", lua_startStage);
    tolua_function(L, "finishStage", lua_finishStage);
    tolua_function(L, "failStage", lua_failStage);
    
    tolua_function(L, "setUserLevel", lua_setUserLevel);
    tolua_function(L, "buy", lua_buy);
    
    
    tolua_endmodule(L);
    return 0;
}