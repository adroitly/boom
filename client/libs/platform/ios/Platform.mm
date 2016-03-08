//
//  PlatformInterface.cpp
//  boom
//
//  Created by PatGame on 16/1/25.
//
//

#include "Platform.h"

namespace platform
{
    void openUrl(const char* url)
    {
        NSString* strUrl = [NSString stringWithUTF8String:url];
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:strUrl]];
    }
    
    void registerRemoteNotification()
    {
        UIApplication* application = [UIApplication sharedApplication];
        if ([application respondsToSelector:@selector(isRegisteredForRemoteNotifications)])
        {
            //IOS8
            UIUserNotificationSettings *notiSettings = [UIUserNotificationSettings settingsForTypes:(UIUserNotificationTypeBadge | UIUserNotificationTypeAlert | UIRemoteNotificationTypeSound) categories:nil];
            
            [application registerUserNotificationSettings:notiSettings];
        }
        else
        {
            //IOS7
            [application registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge                                       |UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
        }
    }
    
    const char* getAppVersion()
    {
        NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
        NSString *version = [infoDictionary objectForKey:@"CFBundleVersion"];
        return [version UTF8String];
    }
}


