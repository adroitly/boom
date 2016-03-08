//
//  lua_register_pay.cpp
//  big-devil
//
//  Created by JiangPaifeng on 15/6/1.
//
//

#include "lua_register_pay.h"
#include "pay/GamePay.h"
#include "tolua_fix.h"
#include "cocos2d/LuaScriptHandlerMgr.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

static int lua_pay(lua_State* L)
{
    int argc = lua_gettop(L);
    assert(argc == 1);
    const char* payCode = luaL_checkstring(L, 1);
    GamePay::getInstance()->pay(payCode);
    return 0;
}

typedef enum
{
    EVENT_PAY_FINISH = (int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN + 1,
    EVENT_PAY_ERROR,
} EventHandler;

static int s_getHandlerWithEvent(EventHandler event)
{
    auto type = (ScriptHandlerMgr::HandlerType)event;
    auto handlerMgr = ScriptHandlerMgr::getInstance();
    auto gamePay = GamePay::getInstance();
    return handlerMgr->getObjectHandler((void *)gamePay, type);
}

static void s_finishCallback(const char* payCode, double mount)
{
    int handler = s_getHandlerWithEvent(EVENT_PAY_FINISH);
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    stack->executeFunctionByHandler(handler, 0);
}

static void s_errorCallback(const char* payCode, int errorCode, const char* msg)
{
    int handler = s_getHandlerWithEvent(EVENT_PAY_ERROR);
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    stack->executeFunctionByHandler(handler, 0);
}

static int lua_setFinishCallback(lua_State* L)
{
    auto gamePay = GamePay::getInstance();
    auto handlerMgr = ScriptHandlerMgr::getInstance();
    auto type = (ScriptHandlerMgr::HandlerType)EVENT_PAY_FINISH;
    
    int argc = lua_gettop(L);
    if (argc == 1 && lua_isfunction(L, 1))
    {
        LUA_FUNCTION handler = toluafix_ref_function(L, 1, 0);
        handlerMgr->addObjectHandler((void *)gamePay, handler, type);
        gamePay->setFinishCallback(s_finishCallback);
        return 0;
    }
    
    handlerMgr->removeObjectHandler((void *)gamePay, type);
    gamePay->setFinishCallback(GamePay::OnFinishFunc());
    
    return 0;
}

static int lua_setErrorCallback(lua_State* L)
{
    auto gamePay = GamePay::getInstance();
    auto handlerMgr = ScriptHandlerMgr::getInstance();
    auto type = (ScriptHandlerMgr::HandlerType)EVENT_PAY_ERROR;
    
    int argc = lua_gettop(L);
    if (argc == 1 && lua_isfunction(L, 1))
    {
        LUA_FUNCTION handler = toluafix_ref_function(L, 1, 0);
        handlerMgr->addObjectHandler((void *)gamePay, handler, type);
        gamePay->setErrorCallback(s_errorCallback);
        return 0;
    }
    
    handlerMgr->removeObjectHandler((void *)gamePay, type);
    gamePay->setErrorCallback(GamePay::OnErrorFunc());
    
    return 0;
}

static int lua_getCashWithCode(lua_State* L)
{
    int argc = lua_gettop(L);
    assert(argc == 1);
    auto payCode = luaL_checkstring(L, 1);
    
    auto gamePay = GamePay::getInstance();
    lua_pushinteger(L, gamePay->getCashWithCode(payCode));
    return 1;
}

int lua_register_pay(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, "pay", 0);
    tolua_beginmodule(L, "pay");
    
    tolua_function(L, "pay", lua_pay);
    tolua_function(L, "setFinishCallback", lua_setFinishCallback);
    tolua_function(L, "setErrorCallback", lua_setErrorCallback);
    tolua_function(L, "getCashWithCode", lua_getCashWithCode);
    
    tolua_endmodule(L);
    return 0;
}