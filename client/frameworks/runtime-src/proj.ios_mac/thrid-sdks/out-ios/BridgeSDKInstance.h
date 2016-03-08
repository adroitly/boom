//
//  PatGameInstance.h
//  Game
//
//  Created by JIUJIU on 15/4/27.
//
//

#ifndef __Game__PatGameInstance__
#define __Game__PatGameInstance__

#include "BridgeSDK.h"

class BridgeSDKInstance : public bridge::BridgeSDKVirtual
{
public:
    void initSDK() override;
    void login() override;
    void logout() override;
    
    std::string getChannelName() override;
    std::string getUserId() override;
    std::string getUserName() override;
    void pay(const bridge::BridgeSDKPayData& payInfo) override;
};

#endif /* defined(__Game__PatGameInstance__) */
