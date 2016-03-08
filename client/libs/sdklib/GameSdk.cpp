//
//  GameSdk.cpp
//  big-devil
//
//  Created by JiangPaifeng on 15/6/1.
//
//

#include "GameSdk.h"
#include "./pay/GamePay.h"
#include "platform/CCPlatformConfig.h"

namespace SdkUtils
{
    void onPayFinish(const char* payCode, double mount)
    {
        GamePay::getInstance()->onFinish(payCode, mount);
    }

    void onPayError(int errorCode, const char* msg)
    {
        GamePay::getInstance()->onError(errorCode, msg);
    }
    
    std::string getPatform()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        return "android";
#else
        return "ios";
#endif
    }
}