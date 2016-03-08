//
//  lua_register_PlatformInterface.hpp
//  boom
//
//  Created by PatGame on 16/1/25.
//
//

#ifndef lua_register_PlatformInterface_hpp
#define lua_register_PlatformInterface_hpp

#include "tolua++.h"

namespace platform
{
    int lua_register_platform(lua_State* L);
}

#endif /* lua_register_PlatformInterface_hpp */
