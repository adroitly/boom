//
//  PlatformInterface.cpp
//  boom
//
//  Created by PatGame on 16/1/25.
//
//

#include "Platform.h"
#include <android/log.h>
#include <stdlib.h>
#include <stdio.h>
#include "platform/android/jni/JniHelper.h"
#define GAME_PLATFORM_CLASS "org/cocos2dx/helper/Platform"
const char* callStringJNIMethod(char* method)
{
    cocos2d::JniMethodInfo minfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo, GAME_PLATFORM_CLASS, method,
                                                "()Ljava/lang/String;"))
    {
        jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        JNIEnv * env = minfo.env;
        minfo.env->DeleteLocalRef(minfo.classID);
//        value = cocos2d::JniHelper::jstring2string(str);
        const char *value = (env)->GetStringUTFChars(str, false);
        minfo.env->DeleteLocalRef(str);
        return value;
    }
    return "error";
}
namespace platform
{
    void openUrl(const char* url) {}
    
    void registerRemoteNotification() {}
    
    const char * getAppVersion(){ return callStringJNIMethod("getAppVersion");}
    
}