//
//  GameSdk.cpp
//  big-devil
//
//  Created by ming on 15/5/5.
//
//

#include "GameSdk.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <stdlib.h>

#define GAMEAPP_CLASS "org/cocos2dx/lua/AppActivity"
#define GAMEHELPER_CLASS "org/cocos2dx/helper/GameHelper"

namespace SdkUtils
{
    // payCode 计费点编号， payPrice 计费价格，以分为单位 int型
    void pay(const char* payCode, const char* payPrice)
    {
        // SdkUtils::onPayFinish(payCode, 1);
        cocos2d::JniMethodInfo minfo;

        if (cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                                    GAMEAPP_CLASS,
                                                    "handlePayMsg",
                                                    "(Ljava/lang/String;Ljava/lang/String;)V"))
        {
            jstring code = minfo.env->NewStringUTF(payCode);
            jstring price = minfo.env->NewStringUTF(payPrice);
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, code, price);
        }
    }

    bool isMusicEnabled()
    {
        cocos2d::JniMethodInfo minfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(minfo, GAMEAPP_CLASS, "isMusicEnabled",
                        "()Z"))

        {
            bool enable = (bool)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            return enable;
        }
        return true;
    }

    std::string getPackageName()
    {
        std::string packageName;
        cocos2d::JniMethodInfo minfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(minfo, GAMEHELPER_CLASS, "getAndroidPackageName",
                        "()Ljava/lang/String;"))
        {
            jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            minfo.env->DeleteLocalRef(minfo.classID);
            packageName = cocos2d::JniHelper::jstring2string(str); 
            minfo.env->DeleteLocalRef(str);
        }
        return packageName;
    }

    std::string getVersion()
    {
        std::string versionName;
        cocos2d::JniMethodInfo minfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(minfo, GAMEHELPER_CLASS, "getAndroidVersion",
                        "()Ljava/lang/String;"))
        {
            jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            minfo.env->DeleteLocalRef(minfo.classID);
            versionName = cocos2d::JniHelper::jstring2string(str); 
            minfo.env->DeleteLocalRef(str);
        }
        return versionName;
    }

    std::string getUUID()
    {
        using namespace cocos2d;
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, GAMEHELPER_CLASS, "getUUID", "()Ljava/lang/String;"))
        {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            auto uuid = JniHelper::jstring2string(str);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(str);
            return uuid;
        }
        return "00000000000000000";
    }

    PatGameChannelId getChannelId()
    {
        //return SdkUtils::PatGameChannelId::JiuYue_KuaiFa;
        using namespace cocos2d;
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, GAMEAPP_CLASS, "getChannelId", "()Ljava/lang/String;")) 
        {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            auto pid = JniHelper::jstring2string(str);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(str);
            
           
            int ePid =atoi(pid.c_str());
            return (PatGameChannelId)ePid;
        }
        return PatGameChannelId::OTHER;

    }

    void shareToWX(const std::string& content) 
    {
        using namespace cocos2d;
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, GAMEAPP_CLASS, "shareToWx", "(Ljava/lang/String;)V"))
        {
            jstring conStr = t.env->NewStringUTF(content.c_str());
            t.env->CallStaticVoidMethod(t.classID, t.methodID,conStr);
            t.env->DeleteLocalRef(conStr);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}
