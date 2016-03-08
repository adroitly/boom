//
//  BridgeNotification.cpp
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#include "BridgeNotification.h"
#include "CCLuaEngine.h"

using namespace cocos2d;
namespace bridge
{
    static void _postValueToLua(lua_State* L,
                                BridgeNotificationType notiType,
                                const BridgeNotificationValue& notiValue)
    {
        lua_pushnumber(L, (int)notiType);
        
        lua_newtable(L);
        for (auto it : notiValue)
        {
            lua_pushstring(L, it.first.c_str());
            lua_pushstring(L, it.second.c_str());
            lua_settable(L, -3);
        }
        
        lua_pcall(L, 2, 0, 0);
    }
    
    void bridgeNotification(BridgeNotificationType notiType,
                            const BridgeNotificationValue& notiValue)
    {
        auto engine = LuaEngine::getInstance();
        lua_State* L = engine->getLuaStack()->getLuaState();
        
        lua_getglobal(L, "c_bridgeSDKNotification");
        int type = lua_type(L, -1);
        if (LUA_TFUNCTION == type)
        {
            _postValueToLua(L, notiType, notiValue);
        }
        else
        {
            CCLog("Lua未注册全局函数c_bridgeSDKNotification");
        }
    }
    
    void bridgeNotification(BridgeNotificationType notiType)
    {
        bridgeNotification(notiType, BridgeNotificationValue());
    }
}