#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "CodeIDESupport.h"
#include "Runtime.h"
#include "ConfigParser.h"
#include "lua_module_register.h"
#include "flash_sdk_src/flash_cocos2dx/FlaLua.h"
#include "ccex/lua_binding/lua_reg_ccex.h"
#include "fla_ex/lua_register_fla_ex.h"
#include "game/lua_register_game.h"
#include "lua_profile/profile.h"
#include "network/lua_binding/lua_network.h"
#include "../../../3rd/network/HttpClient.h"
#include "lkit_c/lkit_openlibs.h"
#include "ccex/lua_reg_ActionEx.h"

//#include "slog/slog.h"

#include <iostream>


namespace boost
{
    void throw_exception(std::exception const& e)
    {
    }
}

namespace network
{
    int lua_execute_function(lua_State* L, int args)
    {
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        return stack->executeFunction(args);
    }
}

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

static void s_saveLogToFile()
{
    auto filePath = FileUtils::getInstance()->getWritablePath() + "TestFile";
    freopen(filePath.c_str(), "a+", stdout);
    freopen(filePath.c_str(), "a+", stderr);
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    endRuntime();
#endif

    ConfigParser::purge();
}

// if you want a different context,just modify the value of glContextAttrs
// it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributions,now can only set six attributions:
    // red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

    GLView::setGLContextAttrs(glContextAttrs);
}

static std::string s_getKey()
{
    int key[] = { 80, 97, 116, 71, 97, 109, 101, 41, 94, 41, 33 };  // PatGame)^)!
    char result[20] = { 0 };
    for (int i = 0; i < 11; ++i)
    {
        result[i] = key[i];
    }
    return result;
}

#include "FlaSDK.h"
#include "clover/Data.h"
#include "libra/libra_fsys.h"
#include "clover/ScopeGuard.h"
#include "libra/libra_path.h"
#include "ccex/DispatchManager.h"
#include "game/GameUtils.h"
#include "lua-rpc-core.h"
#include "pbc/binding/lua/pbc-lua.h"
#include "lua-rpc-core.h"
#include "Lua_BridgeSDK_Register.h"
#include "lua_register_platform.h"

bool AppDelegate::applicationDidFinishLaunching()
{    
    ccex::DispatchManager::getInstance()->addFun([](float t)
                                                 {
                                                     ::network::HttpClient::getInstance().dispatchResponseCallbacks(2);
                                                     
                                                     rpc::getGlobalClient()->dispatchCallbacks(2);
                                                 });

    cocos2d::FileUtils::getInstance()->setPopupNotify(false);
    libra_path_set_separator('/');

    cocos2d::FileUtils::getInstance()->addSearchPath(GameUtils::getResourcePath(), true);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    initRuntime();
#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        Size viewSize = ConfigParser::getInstance()->getInitViewSize();
        string title = ConfigParser::getInstance()->getInitViewName();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        extern void createSimulator(const char* viewName,
                                    float width,
                                    float height,
                                    bool isLandscape = true);
        bool isLanscape = ConfigParser::getInstance()->isLanscape();
        createSimulator(title.c_str(), viewSize.width, viewSize.height, isLanscape);
#else
        glview = cocos2d::GLViewImpl::createWithRect(title.c_str(), Rect(0, 0, viewSize.width, viewSize.height));
        director->setOpenGLView(glview);
#endif
    }
    
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

    // If you want to use Quick-Cocos2d-X, please uncomment below code
    // register_all_quick_manual(L);

    LuaStack* stack = engine->getLuaStack();
    auto key = s_getKey();
    stack->setXXTEAKeyAndSign(key.c_str(), (int)key.length(), "__BIG_DEVIL__", strlen("__BIG_DEVIL__"));

    FlaLua::registerFlaSDK(L);
    lua_register_fla_ex(L);
    
    ccex::lua_reg_ccex(L);
    lua_register_game(L);
    bridge::lua_register_bridge_sdk(L);
    
    platform::lua_register_platform(L);
//    ccex::lua_reg_ActionEx(L);
//    easy_lua::lua_open_profile(L);
//    lua_setglobal(L, "profiler");

    network::lua_open_network(L);
    lua_setglobal(L, "network");
    
    luaL_requiref(L, "rpc.core", luaopen_rpc_core, 0);
    luaL_requiref(L, "protobuf.c", luaopen_protobuf_c, 0);

    lkit::openlibs(L);
    
    engine->executeScriptFile(ConfigParser::getInstance()->getEntryFile().c_str());
    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    GameUtils::callLuaFunction("c_applicationDidEnterBackground");
    
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    if (!FlaSDK::isAsyncManagerEmpty())
    {
        FlaSDK::purgeCachedData();
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    GameUtils::callLuaFunction("c_applicationWillEnterForeground");
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
