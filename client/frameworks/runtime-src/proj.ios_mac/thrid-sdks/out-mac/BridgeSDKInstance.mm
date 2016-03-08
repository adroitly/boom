

#include "BridgeSDKInstance.h"
#include "BridgeNotification.h"

static NSString* const_userid_key = @"user_id";
void BridgeSDKInstance::initSDK()
{
    /**
     * 必填：SDK初始化
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKFailed);
     */
    
    bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKSuccessful);
}

void BridgeSDKInstance::login()
{
    /**
     * 必填：登录接口
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::LoginSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::LoginFailed);
     */
    
    bridge::bridgeNotification(bridge::BridgeNotificationType::LoginSuccessful);
}

void BridgeSDKInstance::logout()
{
    /**
     * 必填：登出
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutFailed);
     */
    
    bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutSuccessful);
    
    [[NSUserDefaults standardUserDefaults] setObject:nullptr forKey:const_userid_key];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

std::string BridgeSDKInstance::getChannelName()
{
    /**
     * 必填：[平台:渠道]，由Lua解析所需平台id和渠道id
     */
    return "PatgameOutnet:outnet";
}

std::string BridgeSDKInstance::getUserId()
{
    /**
     * 必填：由合作商sdk登录成功后的用户ID
     */
    
    // 测试用
    NSString* userId = [[NSUserDefaults standardUserDefaults] objectForKey:const_userid_key];
    if (nullptr == userId)
    {
        userId = [NSString stringWithFormat:@"%d", (int)[NSDate timeIntervalSinceReferenceDate]];
        [[NSUserDefaults standardUserDefaults] setObject:userId forKey:const_userid_key];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    
    return [userId UTF8String];
}

std::string BridgeSDKInstance::getUserName()
{
    /**
     * 必填：由合作商sdk登录成功后的用户名
     */
    return "1";
}

void BridgeSDKInstance::pay(const bridge::BridgeSDKPayData& payInfo)
{
    /**
     * 必填：支付接口
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::PaySuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::PayFailed);
     * 取消：bridge::bridgeNotification(bridge::BridgeNotificationType::PayCancel);
     */
    
    bridge::bridgeNotification(bridge::BridgeNotificationType::PaySuccessful);
}



