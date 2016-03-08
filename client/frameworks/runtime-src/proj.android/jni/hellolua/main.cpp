#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "ConfigParser.h"
#include "game/GameUtils.h"
#include "MobClickJniHelper.h"

#define LOG_TAG "main"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init(JNIEnv* env, jobject thiz)
{
    LOGD("cocos_android_app_init");
    AppDelegate* pAppDelegate = new AppDelegate();
}

extern "C" {
bool Java_org_cocos2dx_lua_AppActivity_nativeIsLandScape(JNIEnv* env, jobject thisz)
{
    return ConfigParser::getInstance()->isLanscape();
}

bool Java_org_cocos2dx_lua_AppActivity_nativeIsDebug(JNIEnv* env, jobject thisz)
{
#if (COCOS2D_DEBUG > 0)
    return true;
#else
    return false;
#endif
}

void Java_org_cocos2dx_lua_AppActivity_handleLowMemory(JNIEnv* env, jobject thiz)
{
    GameUtils::removeAllUnusedResources();
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

}
