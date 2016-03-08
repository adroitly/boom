//
//  BridgeSDKPayData.h
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#ifndef BridgeSDKPayData_h
#define BridgeSDKPayData_h

#include <string>

namespace bridge
{
    struct BridgeSDKPayData
    {
        BridgeSDKPayData(float price_,
                         const std::string& productId_,
                         const std::string& userId_,
                         const std::string& userName_,
                         const std::string& serverId_)
        :   price(price_),
            productId(productId_),
            userId(userId_),
            userName(userName_),
            serverId(serverId_)
        {}
        
        float       price;      // 产品价格
        std::string productId;  // 付费产品ID
        std::string userId;     // 用户ID
        std::string userName;   // 用户名
        std::string serverId;   // 区服ID
    };
}

#endif /* BridgeSDKPayData_h */
