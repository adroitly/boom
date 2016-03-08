local BackgroundLayer = require("ui.common.BackgroundLayer")
local NameConfigReader = require("ui.login.NameConfigReader")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.login.CreateRoleLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createBackground()
    self:_createSelectRoleLayer()
    self:_createSexButton()
    self:_createTextInput()
    self:_createRandomButton()
    self:_createComfirmButton()
    self:_createCountryButtons()
    SocketManager:addObserver(self)
    Event:registerNodeEvent(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if Command.ConnectSuccess == cmd then 
        local tp = PlayerData:getType()
        local id = ServerConfigInfo:getServerAccountId()
        local nickName = self._textFieldInput:getString()
        local const_role_create_type = 1
        local sex = self._roleSelectLayer:getSelectedSex()
        local icon = self._roleSelectLayer:getSelectedIcon()
        local requestData = { type=tp, id=id, nickname=nickName, login_type=const_role_create_type, sex = sex, icon = icon, country = self._selectedCountryId, platform_id = Platform:getPlatformId(),
            channel_id  = Platform:getChannelId()}
        SocketManager:send(Command.Login, requestData)
    elseif Command.Login == cmd then
        CommonUI:showLoadingLayer(false)
        self:_loginCallback(msgTable)
    end
end 

function M:_loginCallback(msgTable)
    local code = msgTable.code
    assert(code)
    if 0==code then 
        PlayerData:initLoginInfo(msgTable)
        MapManager:loadMapMainLayer()
    else
        CommonUI:errorAlertView(code)
    end
end

function M:_createSelectRoleLayer()
    self._roleSelectLayer = require("ui.login.RoleSelectLayer").new()
    self:addChild(self._roleSelectLayer)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "选择角色")
    background:setBackButtonCallback(function()
        Director:replaceSceneWithClass(app.firstUILayer)
    end)
end

function M:_getRandomName()
    local maxSurnameCount = NameConfigReader:getMaxCountSurname()
    local maxNameCount = NameConfigReader:getMaxCountName()
    local surnameIndex = math.random(maxSurnameCount)
    local nameIndex = math.random(maxNameCount)
    local name = string.format("%s%s",NameConfigReader:getSurnameByIndex(surnameIndex), NameConfigReader:getNameByIndex(nameIndex))
    return name
end

function M:_createSexButton()
    local buttonRadioLayer = ButtonRadioLayer.new({
        {"ui/login/login-up.png", nil, "ui/login/login-down.png", "男", 30},
        {"ui/login/login-up.png", nil, "ui/login/login-down.png", "女", 30},
    })
    self:addChild(buttonRadioLayer)
    buttonRadioLayer:setLayout(cc.size(Screen.width, 100), ButtonSetLayer.LayoutType.FromTopToBottom)
    buttonRadioLayer:setPosition(cc.p(0, 80))
    buttonRadioLayer.onClicked = function(sender, index)
        self._roleSelectLayer:showMaleView((index + 1) == Enum.Sex.Male )
    end
end

function M:_createTextInput()
    self._textFieldInput = require("ui.common.InputUI").new(26)
    self._textFieldInput:setMaxLength(14)
    self._textFieldInput:setTextColor(cc.c4b(255, 255, 255, 255))
    self._textFieldInput:setString(self:_getRandomName())
    self:addChild(self._textFieldInput)
    self._textFieldInput:setPosition(Screen.cx, 250)
end

function M:_createRandomButton()
    local button = CommonUI:createTextButton(self, "随机名称", "ui/login/login-up.png", "ui/login/login-down.png")
    button:setPosition(cc.p(Screen.width / 2 + 200, 250))
    button.onClicked = function()
        self._textFieldInput:setString(self:_getRandomName())
    end
end

function M:_createComfirmButton()
    local button = CommonUI:createTextButton(self, "确定创建", "ui/login/login-up.png", "ui/login/login-down.png")
    button.onClicked = function()
        local string = self._textFieldInput:getString()
        if string.len(string) == 0 then 
            CommonUI:lightTips("名字不能为空")
            return
        end
        CommonUI:showLoadingLayer(true)
        SocketManager:connect(ServerConfigInfo:getServerIp(), ServerConfigInfo:getServerPort())
    end
    Layout:layout(button, Screen.size, Layout.center_bottom)
end

function M:_createCountryButtons()
    local setInfo = {
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "魏", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "蜀", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "吴", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "西凉", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "东辽", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "南越", 30},
    }
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    local btnSize = tempSprite:getContentSize()
    local ButtonSetLayer = require("libs.widget.ButtonRadioLayer")
    local buttonSetLayer = ButtonSetLayer.new(setInfo)
    buttonSetLayer:setLayout(cc.size(Screen.width, btnSize.height * 2), buttonSetLayer.FromTopToBottom, 3, btnSize.height)
    self:addChild(buttonSetLayer)
    buttonSetLayer:setPosition(cc.p(0, Screen.height - BackgroundLayer.TitleHeight - btnSize.height * 2))
    buttonSetLayer.onClicked = function(sender, index)
        self:_onTagSelected(sender, index)
    end
end

function M:_onTagSelected(sender, index)
    self._selectedCountryId = index + 1
end

return M

