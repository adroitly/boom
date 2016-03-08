//
//  PlatformInterface.hpp
//  boom
//
//  Created by PatGame on 16/1/25.
//
//

#ifndef PlatformInterface_hpp
#define PlatformInterface_hpp

#include <stdio.h>

namespace platform
{
    // 打开网页、App、评论等
    void openUrl(const char* url);
    
    // 注册消息推送
    void registerRemoteNotification();
    
    // 获取版本号
    const char* getAppVersion();
}

#endif /* PlatformInterface_hpp */
