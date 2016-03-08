//
//  GameSdk.cpp
//  big-devil
//
//  Created by ming on 15/5/5.
//
//

#include "../GameSdk.h"
#include <iostream>

namespace SdkUtils
{
    void pay(const char *payCode, const char *cash)
    {
        printf("test pay code:%s cash : %s\n", payCode, cash);
        
        onPayFinish(payCode, 1);
//        onPayError(-1, "测试用的");
    }

    bool isMusicEnabled()
    {
        return true;
    }
    
    std::string getUUID()
    {
        return "patgame-big-devil";
    }

    void shareToWX(const std::string& content)
    {
        printf("微信分享 : %s\n", content.c_str());
    }

    std::string getPackageName()
    {
        return "ios";
    }

    std::string getVersion()
    {
        return "ios";
    }

    PatGameChannelId getChannelId()
    {
        return PatGameChannelId::OTHER;
    }
}
