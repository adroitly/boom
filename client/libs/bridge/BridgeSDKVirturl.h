//
//  BridgeSDK.hpp
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#ifndef BridgeSDKVirtual_H
#define BridgeSDKVirtual_H

namespace bridge
{
    class BridgeSDKPayData;
    
    class BridgeSDKVirtual
    {
    public:
        virtual void initSDK()  = 0;
        virtual void login()    = 0;
        virtual void logout()   = 0;
        virtual std::string getChannelId()    = 0;
        virtual std::string getUserId()   = 0;
        virtual std::string getUserName() = 0;
        virtual void pay(const BridgeSDKPayData& payInfo) = 0;
    };
}

#endif /* BridgeSDK_hpp */