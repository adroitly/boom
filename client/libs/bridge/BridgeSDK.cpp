//
//  BridgeSDK.cpp
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#include "BridgeSDK.h"
#include "BridgeSDKInstance.h"

namespace bridge {
    
    static BridgeSDK* s_bridgeSDKRef = nullptr;
    BridgeSDK* BridgeSDK::getInstance()
    {
        if (nullptr == s_bridgeSDKRef)
        {
            s_bridgeSDKRef = new BridgeSDK();
        }
        return s_bridgeSDKRef;
    }
    
    BridgeSDK::BridgeSDK()
    {
        _virtual = new BridgeSDKInstance();
    }
    
    BridgeSDK::~BridgeSDK()
    {
        delete (BridgeSDKInstance *)_virtual;
    }
    
    void BridgeSDK::initSDK()
    {
        _virtual->initSDK();
    }
    
    void BridgeSDK::login()
    {
        _virtual->login();
    }
    
    void BridgeSDK::logout()
    {
        _virtual->logout();
    }
    
    const std::string BridgeSDK::getChannelName()
    {
        return _virtual->getChannelName();
    }
    
    const std::string BridgeSDK::getUserId()
    {
        return _virtual->getUserId();
    }
    
    const std::string BridgeSDK::getUserName()
    {
        return _virtual->getUserName();
    }
    
    void BridgeSDK::pay(const BridgeSDKPayData& payInfo)
    {
        _virtual->pay(payInfo);
    }

    void BridgeSDK::enterGame()
    {
        _virtual->enterGame();
    }
}


