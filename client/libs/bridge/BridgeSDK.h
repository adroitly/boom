//
//  BridgeSDK.hpp
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#ifndef BridgeSDK_hpp
#define BridgeSDK_hpp

#include <string>
#include "BridgeSDKVirtual.h"
#include "BridgeSDKPayData.h"

namespace bridge
{
    class BridgeSDK
    {
    public:
        /**
         *  单例
         */
        static BridgeSDK* getInstance();
        
        /**
         *  初始化SDK
         */
        void initSDK();
        
        /**
         *  请求登陆游戏
         */
        void login();
        
        /**
         *  请求登出游戏，返回通知：NotificationNameLogout
         */
        void logout();
        
        /**
         *  渠道的ID，与我们服务器协议
         */
        const std::string getChannelName();
        
        /**
         *  SDK的userId
         */
        const std::string getUserId();
        
        /**
         *  SDK的userName
         */
        const std::string getUserName();
        
        /**
         *  请求付费
         */
        void pay(const BridgeSDKPayData& payInfo);
        
        /**
         * 玩家进入游戏
         */
        void enterGame();
        
    private:
        BridgeSDKVirtual*     _virtual;
        
    private:
        BridgeSDK();
        ~BridgeSDK();
        
    };
}

#endif /* BridgeSDK_hpp */
