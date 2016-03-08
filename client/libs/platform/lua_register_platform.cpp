//
//  lua_register_PlatformInterface.cpp
//  boom
//
//  Created by PatGame on 16/1/25.
//
//

#include "lua_register_Platform.h"
#include "Platform.h"

namespace platform
{
    static int lua_openUrl(lua_State* L)
    {
        auto url = luaL_checkstring(L, -1);
        platform::openUrl(url);
        return 0;
    }
    
    static int lua_registerRemoteNotification(lua_State* L)
    {
        platform::registerRemoteNotification();
        return 0;
    }
    
    static int lua_getAppVersion(lua_State* L)
    {
        auto version = platform::getAppVersion();
        lua_pushstring(L, version);
        return 1;
    }
    
    int lua_register_platform(lua_State* L)
    {
        tolua_open(L);
        tolua_module(L, "c_Platform", 0);
        tolua_beginmodule(L, "c_Platform");
        
        tolua_function(L, "registerRemoteNotification", lua_registerRemoteNotification);
        tolua_function(L, "openUrl",        lua_openUrl);
        tolua_function(L, "getAppVersion",  lua_getAppVersion);
        tolua_endmodule(L);
        return 0;
    }
}