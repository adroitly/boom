//
//  GameSdkNotify.cpp
//  big-devil
//
//  Created by ming on 15/5/5.
//
//

#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include "GameSdk.h" 

#define LOG_TAG "GameSdkNotify"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {

    // jstring To char*  
    char* jstringTostring(JNIEnv* env, jstring jstr)  
    {  
        char* rtn = NULL;  
        jclass clsstring = env->FindClass("java/lang/String");  
        jstring strencode = env->NewStringUTF("utf-8");  
        jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");  
        jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);  
        jsize alen = env->GetArrayLength(barr);  
        jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);  
        if (alen > 0)  
        {  
            rtn = (char*)malloc(alen + 1);  
            memcpy(rtn, ba, alen);  
            rtn[alen] = 0;  
        }  
        env->ReleaseByteArrayElements(barr, ba, 0);  
        return rtn;  
    }
    

    //支付完成消息
    void Java_org_cocos2dx_lua_AppActivity_payFinished(JNIEnv* env, jobject thiz,jstring payCode,jdouble amount)
    {
        char* cPayCode = jstringTostring(env, payCode); 
        // LOGD("支付完成消息 payCode:%s,amount:%d",cPayCode,amount);
        SdkUtils::onPayFinish(cPayCode, amount);
        free(cPayCode);
    }

    //支付失败消息
    void Java_org_cocos2dx_lua_AppActivity_payError(JNIEnv* env, jobject thiz,jint code,jstring msg)
    {
        // LOGD("支付失败消息 code:%d,msg:%s",code,msg);
        char* cMsg = jstringTostring(env, msg); 
        SdkUtils::onPayError(code, cMsg);
        free(cMsg);
    }

}
