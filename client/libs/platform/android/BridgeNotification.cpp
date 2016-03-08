

#include "MobClickJniHelper.h"
#include "platform/android/jni/JniHelper.h"
#include "BridgeNotification.h"

#define LOG_TAG "JavaBridgeNotification"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C"
{
    /**
     bri
     **/
    void Java_org_cocos2dx_helper_BridgeNotification_bridgeNotificationCallBack(JNIEnv* env, jobject thiz, jint state)
    {
        bridge::BridgeNotificationType type;
//        int bridgeNotificationType = state
        LOGD("BridgeNotificationType = %d",state);
        type = bridge::BridgeNotificationType(state);
        bridge::bridgeNotification(type);
    }
}

