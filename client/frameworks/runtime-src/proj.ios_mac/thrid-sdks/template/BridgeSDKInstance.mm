

#include "BridgeSDKInstance.h"
#include "BridgeNotification.h"

void BridgeSDKInstance::initSDK()
{
    /**
     * 必填：SDK初始化
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKSuccessful)
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::InitSDKFailed);
     */
    
}

void BridgeSDKInstance::login()
{
    /**
     * 必填：登录接口
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::LoginSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::LoginFailed);
     */

}

void BridgeSDKInstance::logout()
{
    /**
     * 必填：登出
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutSuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::LogoutFailed);
     */
    
}

std::string BridgeSDKInstance::getChannelId()
{
    /**
     * 必填：[平台:渠道]，由Lua解析所需平台id和渠道id
     */
    return "平台名称:渠道名称";
}

std::string BridgeSDKInstance::getUserId()
{
    /**
     * 必填：由合作商sdk登录成功后的用户ID
     */
    return "2";
}

std::string BridgeSDKInstance::getUserName()
{
    /**
     * 必填：由合作商sdk登录成功后的用户名
     */
    return "3";
}

void BridgeSDKInstance::pay(const bridge::BridgeSDKPayData& payInfo)
{
    /**
     * 必填：支付接口
     * 成功：bridge::bridgeNotification(bridge::BridgeNotificationType::PaySuccessful);
     * 失败：bridge::bridgeNotification(bridge::BridgeNotificationType::PayFailed);
     * 取消：bridge::bridgeNotification(bridge::BridgeNotificationType::PayCancel);
     */
    
}

