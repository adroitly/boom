//
//  Lua_BridgeSDK_Register.cpp
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#include "Lua_BridgeSDK_Register.h"
#include "BridgeSDK.h"

namespace bridge
{
    static int lua_initSDK(lua_State* L)
    {
        BridgeSDK::getInstance()->initSDK();
        return 0;
    }
    
    static int lua_login(lua_State* L)
    {
        BridgeSDK::getInstance()->login();
        return 0;
    }
    
    static int lua_logout(lua_State* L)
    {
        BridgeSDK::getInstance()->logout();
        return 0;
    }
   
    static int lua_getChannelName(lua_State* L)
    {
        auto channelId = BridgeSDK::getInstance()->getChannelName();
//        assert(!channelId.empty());
        lua_pushstring(L, channelId.c_str());
        return 1;
    }
    
    static int lua_getUserId(lua_State* L)
    {
        auto userId = BridgeSDK::getInstance()->getUserId();
//        assert(!userId.empty());
        lua_pushstring(L, userId.c_str());
        return 1;
    }
    
    static int lua_getUserName(lua_State* L)
    {
        auto userName = BridgeSDK::getInstance()->getUserName();
//        assert(!userName.empty());
        lua_pushstring(L, userName.c_str());
        return 0;
    }
    
    static int lua_enterGame(lua_State* L)
    {
        BridgeSDK::getInstance()->enterGame();
        return 0;
    }
    
    static float getNumberValue(lua_State* L, const char* key)
    {
        lua_getfield(L, -1, key);
        auto value = luaL_checknumber(L, -1);
        lua_pop(L, 1);
        return value;
    }
    
    static std::string getStringValue(lua_State* L, const char* key)
    {
        lua_getfield(L, -1, key);
        auto value = lua_tostring(L, -1);
//        assert(nullptr != value);
        lua_pop(L, 1);
        return value;
    }
    
    static int lua_pay(lua_State* L)
    {
        if (!lua_istable(L, -1))
        {
            lua_error(L);
            return 0;
        }
        
        auto price =        getNumberValue(L, "price");
        auto produceId =    getStringValue(L, "productId");
        auto userId =       getStringValue(L, "userId");
        auto userName =     getStringValue(L, "userName");
        auto serverId =     getStringValue(L, "serverId");
        auto payData = bridge::BridgeSDKPayData(price, produceId,
                                                userId, userName, serverId);
        BridgeSDK::getInstance()->pay(payData);
        return 0;
    }
    
    int lua_register_bridge_sdk(lua_State* L)
    {
        tolua_open(L);
        tolua_module(L, "c_BridgeSDK", 0);
        tolua_beginmodule(L, "c_BridgeSDK");
        
        tolua_function(L, "initSDK",        lua_initSDK);
        tolua_function(L, "login",          lua_login);
        tolua_function(L, "logout",         lua_logout);
        tolua_function(L, "getChannelName",   lua_getChannelName);
        tolua_function(L, "getUserId",      lua_getUserId);
        tolua_function(L, "getUserName",    lua_getUserName);
        tolua_function(L, "pay",            lua_pay);
        tolua_function(L, "enterGame",      lua_enterGame);
        tolua_endmodule(L);
        return 0;
    }
}


