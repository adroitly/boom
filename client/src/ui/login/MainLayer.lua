local M = class("ui.login.MainLayer", function()
    return cc.Layer:create()
end)

local eConnectTag = 
{
    Unknow      = 0,
    Login       = 1,
    Register    = 2, 
}

local kAccountServerSocketKey = "kAccountServerSocketKey"
local function _connectFaild(msgTable, key)
    AlertView.new(__Localized("连接服务器失败"))
    CommonUI:showLoadingLayer(false)
end

local function _connectIng(msgTable, key)
    CommonUI:showLoadingLayer(true)
end

function M:ctor()
    self:_createBackground()
	self:_setupLoginButton()
	self:_setupDeleteUserButton()
  	self:_showVersionLabel()
    
    self._connectTag = eConnectTag.Unknow
    GameController:startController()

    Listener:addListener(self)
    SocketManager:addObserver(self)
    Event:registerNodeEvent(self)
end

function M:onExit()
    Listener:removeListener(self)
    SocketManager:removeObserver(self)
end

-- 初始化逻辑：检查资源版本 -> 获取服务器列表 -> 初始化SDK
function M:onEnterTransitionFinish()
    require("ui.login.CheckVersionLayer"):checkVersion(function()
        self:_loadServerList()
    end)
end

function M:_loadServerList()
    self._serverListLayer = require("ui.login.ServerListLayer").new(function()
        self:_initSDK()
    end)
    self:addChild(self._serverListLayer)
end

function M:_initSDK()
    CommonUI:showLoadingLayer(true)
    c_BridgeSDK:initSDK()
end
------------------------------------------------

function M:_showVersionLabel()
	local version = CommonUI:createLabel(c_Platform:getAppVersion(), 20)
    version:setTextColor(cc.c4b(123, 111, 11, 255))
    self:addChild(version)
    Layout:layout(version, Screen.size, Layout.right_bottom, 10)
end


--[[
    * 描述：登录逻辑
    1. 登录第三方SDK，返回platform userid
    2. 使用channle id和platform userid请求账号服务器，返回user id
    3. 使用user id登录逻辑服务器，返回player userid
    4. 游戏内的交互统一使用player userid
--]]

function M:_setupLoginButton()
    local loginButton = CommonUI:createTextButton(self, "登录", "ui/login/login-up.png", "ui/login/login-down.png")
    loginButton:setPosition(cc.p(Screen.width / 2, 100))
    loginButton.onClicked = function()
        CommonUI:showLoadingLayer(true)
        self._serverListLayer:saveServerIdForLastLogin()
        c_BridgeSDK:login()
    end
end

function M:_setupDeleteUserButton()
    local deleteBt = CommonUI:createTextButton(self, "注销", "ui/login/login-up.png", "ui/login/login-down.png")
	deleteBt:setPosition(cc.p(Screen.width - 100, Screen.height-60))
    deleteBt.onClicked = function()
        c_BridgeSDK:logout()
		PlayerData:logout()
	end
end

function M:_registerResponse(msgTable, key)
    SocketManager:disconnect(kAccountServerSocketKey)

    ServerConfigInfo:setServerAccountId(msgTable.userid)
    self:_connectAccountServer()
end

function M:_loginResponse(msgTable)
    local code = msgTable.code
    assert(code)
    if 0==code then 
        PlayerData:initLoginInfo(msgTable)
        MapManager:loadMapMainLayer()
    elseif ServerErrorCode.USER_IS_NULL==code then 
        CommonUI:showLoadingLayer(false)
        Director:replaceSceneWithClass("ui.login.CreateRoleLayer")
    else 
        AlertView.new(string.format("login error code = %d", code))
    end
end

function M:_connectSuccess(msgTable, key)
    CommonUI:showLoadingLayer(false)
    if self._connectTag == eConnectTag.Login then 
        local const_login_type = 0
        local loginData = { 
            type        = PlayerData:getType(), 
            login_type  = const_login_type, 
            id          = ServerConfigInfo:getServerAccountId(),
            platform_id = Platform:getPlatformId(),
            channel_id  = Platform:getChannelId()
        }
        SocketManager:send(Command.Login, loginData) 
    elseif self._connectTag == eConnectTag.Register then
        local registerData = {
            channel_id = tostring(Platform:getChannelId()),
            platform_userid = c_BridgeSDK:getUserId(),
        }
        SocketManager:send(Command.Register, registerData, kAccountServerSocketKey) 
    else 
        assert(false, "未注册状态")
    end
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local cmdTable = 
    {
        [Command.ConnectSuccess] = function(msgTable, key)
            self:_connectSuccess(msgTable, key)
        end,
        [Command.ConnectFailed] = function(msgTable, key)
            _connectFaild(msgTable, key)
        end, 
        [Command.ConnectIng] = function(msgTable, key)
            _connectIng(msgTable, key)
        end, 
        [Command.Login] = function(msgTable, key)
            self:_loginResponse(msgTable)
        end, 
        [Command.Register] = function(msgTable, key)
            self:_registerResponse(msgTable, key)
        end
    };

    Function:safeCall(cmdTable, cmd, msgTable, key)
end

function M:_createBackground()
    local backgroundSprite = cc.Sprite:create("ui/login/login-bg.png")
    backgroundSprite:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
    self:addChild(backgroundSprite)
end

function M:_createAlertNoticeLayer()
    local layer = require("ui.notice.notice-manager.AlertNoticeLayer"):createStartGameAlertLayer()
    self:addChild(layer)
end

function M:onListenSDKDidInitSuccess(notiValue)
    CommonUI:showLoadingLayer(false)
    CommonUI:lightTips("初始化SDK成功")
    self:_createAlertNoticeLayer()
end

function M:onListenSDKDidInitFaild(notiValue)
   CommonUI:showLoadingLayer(false) 
   CommonUI:lightTips("初始化SDK失败")
end

function M:_connectAccountServer()
    local serverIp = self._serverListLayer:getIp()
    local serverPort = self._serverListLayer:getPort()
    assert(serverIp and serverPort)
    ServerConfigInfo:setServerIp(serverIp, serverPort)

    self._connectTag = eConnectTag.Login
    SocketManager:connect(ServerConfigInfo:getServerIp(), ServerConfigInfo:getServerPort())
end

function M:onListenSDKDidLoginSuccess(notiValue)
    -- 账号逻辑服务器
    self._connectTag = eConnectTag.Register
    SocketManager:connect(ServerConfigInfo:getServerAccountIp(), ServerConfigInfo:getServerAccountPort(), kAccountServerSocketKey)
end

function M:onListenSDKDidLoginFailed(notiValue)
    CommonUI:showLoadingLayer(false)
    CommonUI:lightTips("SDK登录失败")
end

return M


