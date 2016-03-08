-- 以下接口都是由C/C++调用
-- 凡是C提供的接口，统一在函数前面加c_，比如c_BridgeSDK:initSDK()

function c_applicationDidEnterBackground()
    print("applicationDidEnterBackground")
    -- SocketManager:disconnect()
end

function c_applicationWillEnterForeground()
    print("applicationWillEnterForeground")
    -- SocketManager:connect()
end

function c_bridgeSDKNotification(notiType, notiValue)
    local nameTable = 
    {
        [1] = Listener.EventName.onListenSDKDidInitSuccess,
        [2] = Listener.EventName.onListenSDKDidInitFailed,
        [3] = Listener.EventName.onListenSDKDidLoginSuccess,
        [4] = Listener.EventName.onListenSDKDidLoginFailed,
        [5] = Listener.EventName.onListenSDKDidLogoutSuccess,
        [6] = Listener.EventName.onListenSDKDidLogoutFailed,
        [7] = Listener.EventName.onListenSDKDidPaySuccess,
        [8] = Listener.EventName.onListenSDKDidPayFailed,
        [9] = Listener.EventName.onListenSDKDidPayCancel,
    }
    local name = nameTable[notiType]
    assert(name)
    Listener:postEvent(name, notiValue)
end

function c_didRegisterForRemoteNotificationsWithDeviceToken(deviceToken)
    print("device token =", deviceToken)
end


