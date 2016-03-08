#include "lua_cocos2dx_audioengine_auto.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "AudioEngine.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


TOLUA_API int register_all_cocos2dx_audioengine(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccexp",0);
	tolua_beginmodule(tolua_S,"ccexp");


	tolua_endmodule(tolua_S);
	return 1;
}

#endif
