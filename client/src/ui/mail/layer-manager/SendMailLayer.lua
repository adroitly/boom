local BackgroundLayer = require("ui.common.BackgroundLayer")
local TextInput = require("ui.common.InputUI")
local M = class("ui.mail.layer-manager.SendMailLayer", function()
    return cc.Layer:create()
end)

local kMessagePersonalSend = "message_personal_send"
local kGuildMessageSend = "guild_message_send"

function M:ctor(sendMailType, sendNickname)
    self._sendMailType = sendMailType
    self._sendNickname = sendNickname
    self:_createBackground()
    self:_createReceiveFrame()
    self:_createContentFrame()
    self:_createConfirmButton()
    if self._sendMailType ~= Enum.SendMailType.Guild and
        self._sendMailType ~= Enum.SendMailType.Personal then
        -- self:_createAddNameLayer()
    end
    Listener:addListener(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            Listener:removeListener(self)
            SocketManager:removeObserver(self)
        end
    end)
end

function M:onListenMailPersonalChanged(msgTable)
    CommonUI:showLoadingLayer(false)
    if PlayerData:isOwner(msgTable.from_player_id) then
        AlertView.new(__Localized("发送成功")).onClicked = function(index)
            self:removeFromParent()
            local layer = require("ui.mail.layer-manager.PersonalMailLayer").new(msgTable.to_player_id, msgTable.to_nickname)
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end
    end
end

-- 添加背景
function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "发送邮件")
    backgroundLayer:setBackButtonCallback(function ()
        self:removeFromParent()
    end)
end

function M:_createReceiveFrame()
    local label = CommonUI:createLabel("收信人", 26)
    self:addChild(label)
    Layout:layout(label, Screen.size, Layout.left_top, cc.p(10, BackgroundLayer.TitleHeight + 32))

    self._playerNameInput = require("ui.common.InputUI").new(26)
    self._playerNameInput:setPlaceHolder("请输入名称")
    self._playerNameInput:setMaxLength(20)
    self._playerNameInput:setTextColor(cc.c4b(255, 255, 255, 255))
    self:addChild(self._playerNameInput)
    self._playerNameInput:setAnchorPoint(cc.p(0, 1))
    Layout:layout(self._playerNameInput, Screen.size, Layout.left_top, cc.p(30 + label:getContentSize().width, BackgroundLayer.TitleHeight + 30))

    if self._sendMailType == Enum.SendMailType.Guild then
        self._playerNameInput:setString("全体势力成员")
        self._playerNameInput:setTouchEnabled(false)
    end
    if self._sendMailType == Enum.SendMailType.Personal then
        self._playerNameInput:setString(self._sendNickname)
        self._playerNameInput:setTouchEnabled(false)
    end
end

function M:_createContentFrame()
    local label = CommonUI:createLabel("邮件内容", 26)
    label:setTextColor(cc.c4b(255, 255, 255, 255))
    self:addChild(label)
    Layout:layout(label, Screen.size, Layout.left_top, cc.p(10, BackgroundLayer.TitleHeight + 100))

    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight + 140))
    local bgSize = background:getContentSize()

    self._contentTextInput = require("ui.common.InputUI").new(26)
    self._contentTextInput:setPlaceHolder("请输入发送的内容")
    self._contentTextInput:setMaxLength(120)
    self._contentTextInput:setTextWidth(bgSize.width - 40)
    self._contentTextInput:setAnchorPoint(cc.p(0, 1))
    self._contentTextInput:setTouchSize(cc.size(bgSize.width, bgSize.height))
    self._contentTextInput:setTextColor(cc.c4b(255, 255, 255, 255))
    background:addChild(self._contentTextInput)
    Layout:layout(self._contentTextInput, bgSize, Layout.left_top, cc.p(20, 30))
end

function M:_createConfirmButton()
    local confirmButton = CommonUI:createTextButton(self, "发送", "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom)

    confirmButton.onClicked = function()
        if self._sendMailType == Enum.SendMailType.Guild then
            self:_sendToGuild()
        else
            self:_sendToPersonal()
        end
    end
end

function M:_sendToPersonal()
    local playerNameStr = self._playerNameInput:getString()
    if playerNameStr == "" then
        AlertView.new(__Localized("收信人不能为空"))
        return
    end
    CommonUI:showLoadingLayer(true)
    local toPlayerName = self._playerNameInput:getString()
    local messageStr = self._contentTextInput:getString()
    local messageData = {to_player_name = toPlayerName, message = messageStr}
    SocketManager:send(kMessagePersonalSend, messageData)
end

function M:_sendToGuild()
    CommonUI:showLoadingLayer(true)
    local messageStr = self._contentTextInput:getString()
    SocketManager:send(kGuildMessageSend, {message = messageStr})
end

function M:_createAddNameLayer()
    local AddNameLayer = require("ui.mail.layer-manager.AddNameLayer")
    AddNameLayer:createWithParent(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kMessagePersonalSend then
        CommonUI:showLoadingLayer(false)
        if CommonUI:errorAlertView(msgTable.code) then
            return
        end
    end
    if cmd == kGuildMessageSend then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            AlertView.new(__Localized("发送成功"))
            self:removeFromParent()
        end
    end
end

return M