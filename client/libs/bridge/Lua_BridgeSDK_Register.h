//
//  Lua_BridgeSDK_Register.hpp
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#ifndef Lua_BridgeSDK_Register_hpp
#define Lua_BridgeSDK_Register_hpp

#include "tolua++.h"

namespace bridge
{
    int lua_register_bridge_sdk(lua_State* L);
}

#endif /* Lua_BridgeSDK_Register_hpp */
