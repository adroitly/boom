//
//  BridgeNotification.h
//  boom
//
//  Created by PatGame on 15/12/11.
//
//

#ifndef BridgeNotification_h
#define BridgeNotification_h

#include <map>

namespace bridge
{
    enum class BridgeNotificationType
    {
        InitSDKSuccessful   = 1,
        InitSDKFailed       = 2,
        LoginSuccessful     = 3,
        LoginFailed         = 4,
        LogoutSuccessful    = 5,
        LogoutFailed        = 6,
        PaySuccessful       = 7,
        PayFailed           = 8,
        PayCancel           = 9,
    };
    
    typedef std::map<std::string, std::string> BridgeNotificationValue;
    void bridgeNotification(BridgeNotificationType notiType);
    void bridgeNotification(BridgeNotificationType notiType,
                            const BridgeNotificationValue& notiValue);
}

#endif /* BridgeNotification_h */
