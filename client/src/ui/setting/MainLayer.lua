local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.setting.MainLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createBackground()
    self:_createEffectNodes()
    self:_createMusicNodes()
    self:_createWikiButton()
    self:_createLogoutButton()
end

function M:_createLogoutButton()
    local button = CommonUI:createTextButton(self, __Localized("注销帐号"), "ui/login/login-button.png")
    Layout:layout(button, Screen.size, Layout.center_bottom)
    button.onClicked = function()
        self:_onLogoutButtonClick()
    end
end

function M:_onLogoutButtonClick()
    local showText = string.format(__Localized("是否确定注销当前登录的\"%s\"帐号信息?"), PlayerData:getNickName())
    local view = AlertView.new(showText, __Localized("取消"), __Localized("注销"))
    view.onClicked = function(index)
        if 1 == index then
            self:_onLogoutAction()
        end
    end
end

function M:_createWikiButton()
    local wikiButton = CommonUI:createTextButton(self, __Localized("百科"), "ui/login/login-button.png")
    local buttonSize = wikiButton:getContentSize()
    wikiButton:setPosition(cc.p(buttonSize.width / 2, Screen.height * 0.65))
    wikiButton.onClicked = function()
        local layer = require("ui.wiki.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_onLogoutAction()
    SocketManager:disconnect()
    PlayerData:logout()
    Director:replaceSceneWithClass(app.firstUILayer)
end

function M:_createEffectNodes()
    local effectIsCloce = Audio:isEffectClose()
    local buttonText = __Localized("关闭")
    if effectIsCloce then
        buttonText = __Localized("开启")
    end
    local label = CommonUI:createLabel(__Localized("游戏音效"), 24)
    self._effectButton = CommonUI:createTextButton(self, buttonText, "ui/login/login-button.png")
    self:addChild(label)

    Layout:layout(self._effectButton, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
    local buttonX, buttonY = self._effectButton:getPosition()
    label:setPosition(cc.p(label:getContentSize().width, buttonY))

    self._effectButton.onClicked = function()
        self:_onEffectButtonClick()
    end
end

function M:_onEffectButtonClick()
    local effectIsCloce = Audio:isEffectClose()
    if effectIsCloce then
        Audio:setEffectClose(false)
        self._effectButton:setText(__Localized("关闭"))
    else
        Audio:setEffectClose(true)
        self._effectButton:setText(__Localized("开启"))
    end
end

function M:_onMusicButtonClick()
    local musicIsCloce = Audio:isMusicClose()
    if musicIsCloce then
        Audio:setMusicClose(false)
        self._musicButton:setText(__Localized("关闭"))
    else
        Audio:setMusicClose(true)
        self._musicButton:setText(__Localized("开启"))
    end
end

function M:_createMusicNodes()
    local musicIsCloce = Audio:isMusicClose()
    local buttonText = __Localized("关闭")
    if musicIsCloce then
        buttonText = __Localized("开启")
    end
    local label = CommonUI:createLabel(__Localized("背景音乐"), 24)
    self._musicButton = CommonUI:createTextButton(self, buttonText, "ui/login/login-button.png")
    self:addChild(label)

    Layout:layout(self._musicButton, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight * 2))

    local buttonX, buttonY = self._musicButton:getPosition()
    label:setPosition(cc.p(label:getContentSize().width, buttonY))
    self._musicButton.onClicked = function()
        self:_onMusicButtonClick()
    end
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, __Localized("设置"))
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

return M