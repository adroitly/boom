//
//  GameSdk.h
//  big-devil
//
//  Created by ming on 15/5/5.
//
//

#ifndef __BOOM__GameSdk__
#define __BOOM__GameSdk__

#include <string>

namespace SdkUtils
{
	enum class PatGameChannelId
    {
    	OTHER   = 0,  //其他
        CHINAMOBILE_CNGAMES   = 1,  //移动基地
        CHINAMOBILE_MM        = 2,  //移动MM
        SIWANG                = 3,  //四网
        AIYOUXI               = 4,  //爱游戏
    };
    
    void pay(const char* payCode,const char* payPrice);
    bool isMusicEnabled();
    void onPayFinish(const char* payCode, double mount);
    void onPayError(int errorCode, const char* msg);
    std::string getUUID();
    void shareToWX(const std::string& content);
    std::string getPackageName();
    std::string getVersion();
    PatGameChannelId getChannelId();
    std::string getPatform();
    
}

#endif /* defined(__BOOM__GameSdk__) */
