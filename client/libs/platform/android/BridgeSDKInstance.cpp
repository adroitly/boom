

#include "BridgeSDKInstance.h"
#include "BridgeNotification.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <stdlib.h>
#include <stdio.h>

#define GAME_SDK_CLASS "org/cocos2dx/lua/BridgeSDKInstance"
#define PAY_SDK_CLASS "org/cocos2dx/lua/BridgeSDKPayData"

void callVoidJNIMethod(const char* method)
{
    // SdkUtils::onPayFinish(payCode, 1);
    cocos2d::JniMethodInfo minfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                                GAME_SDK_CLASS,
                                                method,
                                                "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }

}
std::string callStringJNIMethod(const char* method)
{
    std::string value;
    cocos2d::JniMethodInfo minfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo, GAME_SDK_CLASS, method,
                                                "()Ljava/lang/String;"))
    {
        jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
        value = cocos2d::JniHelper::jstring2string(str);
        minfo.env->DeleteLocalRef(str);
    }
    return value;

}
/**
 SDK返回调用bridge
 **/
void BridgeSDKInstance::initSDK()
{
    /**
     * 必填：SDK初始化
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKFailed);
     */
    callVoidJNIMethod("initSDK");
}
/**
 SDK返回调用bridge
 **/
void BridgeSDKInstance::login()
{
    /**
     * 必填：登录接口
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::LoginSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::LoginFailed);
     */
    callVoidJNIMethod("login");
}
/**
 SDK返回调用bridge
 **/
void BridgeSDKInstance::logout()
{
    /**
     * 必填：登出
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutFailed);
     */
    
    callVoidJNIMethod("logout");
}

std::string BridgeSDKInstance::getChannelName()
{
    /**
     * 必填：与我们服务器协商渠道ID
     */
    return callStringJNIMethod("getChannelName");
}

std::string BridgeSDKInstance::getUserId()
{
    /**
     * 必填：由合作商sdk登录成功后的用户ID
     */
    return callStringJNIMethod("getUserId");
}

std::string BridgeSDKInstance::getUserName()
{
    /**
     * 必填：由合作商sdk登录成功后的用户名
     */
    return callStringJNIMethod("getUserName");
}
/**
 SDK返回调用bridge
 **/

void BridgeSDKInstance::pay(const bridge::BridgeSDKPayData& payInfo)
{
    /**
     * 必填：支付接口
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::PaySuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::PayFailed);
     * 取消：bridge::bridgeNotification(bridge::BridgeNotificationType::PayCancel);
     */
    // SdkUtils::onPayFinish(payCode, 1);
    cocos2d::JniMethodInfo minfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo,
                                                PAY_SDK_CLASS,
                                                "pay",
                                                "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        float price = payInfo.price;      // 产品价格
        std::string productId = payInfo.productId;  // 付费产品ID
        std::string userId = payInfo.userId;     // 用户ID
        std::string userName = payInfo.userName;   // 用户名
        std::string serverId = payInfo.serverId;   // 区服ID
        
        char priceStr[50];
        sprintf(priceStr, "%f", price);
        
        jstring jprice = minfo.env->NewStringUTF(priceStr);      // 产品价格
        jstring jproductId = minfo.env->NewStringUTF(productId.c_str());  // 付费产品ID
        jstring juserId = minfo.env->NewStringUTF(userId.c_str());     // 用户ID
        jstring juserName = minfo.env->NewStringUTF(userName.c_str());   // 用户名
        jstring jserverId = minfo.env->NewStringUTF(serverId.c_str());   // 区服ID
        
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jprice, jproductId, juserId, juserName, jserverId);
        
        minfo.env->DeleteLocalRef(minfo.classID);
        minfo.env->DeleteLocalRef(jprice);
        minfo.env->DeleteLocalRef(jproductId);
        minfo.env->DeleteLocalRef(juserId);
        minfo.env->DeleteLocalRef(juserName);
        minfo.env->DeleteLocalRef(jserverId);
    }
    
}

