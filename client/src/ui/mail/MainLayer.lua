
local GameMailDataManager = require("player-data.GameMailDataManager")
local SystemMailDataManager = require("player-data.SystemMailDataManager")
local PersonalMailDataManager = require("player-data.PersonalMailDataManager")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.mail.MainLayer", function()
    return cc.Layer:create()
end)

local paddingY = 20

function M:ctor()
    self:_createBackground()
    self:_createGameTitle()
    self:_createPersonalTitle()
    self:_createSystemTitle()

    Listener:addListener(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            Listener:removeListener(self)
        end
    end)
    
end

function M:onListenMailSystemChanged()
    self:_checkSystemMail()
end

function M:onListenMailPersonalChanged()
    self:_checkPersonalMail()
end

function M:onListenMailGameChanged()
    self:_checkGameMail()
    
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "邮件")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createGameTitle()
    local background = Button.new("ui/mail/mail-title-bg.png", "ui/mail/mail-title-bg.png")
    self:addChild(background)
    background.onClicked = function()
        self:_gotoGameMail()
    end
    background:setPosition(cc.p(Screen.size.width * 0.5, 
                Screen.size.height - BackgroundLayer.TitleHeight - background:getContentSize().height * 0.5 - paddingY))
    local title = cc.Sprite:create("ui/mail/mail-game-title.png")
    Layout:layout(title, background:getContentSize(), Layout.center)
    background:addChild(title)

    self._gameMailTip = cc.Sprite:create("ui/mail/mail-unread.png")
    Layout:layout(self._gameMailTip, background:getContentSize(), Layout.right_center, cc.p(50, 0))
    background:addChild(self._gameMailTip)
    
    self:_checkGameMail()
end

function M:_createPersonalTitle()
    local background = Button.new("ui/mail/mail-title-bg.png", "ui/mail/mail-title-bg.png")
    self:addChild(background)
    background.onClicked = function()
        self:_gotoPersonalMail()
    end
    background:setPosition(cc.p(Screen.size.width * 0.5, 
            Screen.size.height - BackgroundLayer.TitleHeight - background:getContentSize().height * 1.5 - paddingY * 2))
    local title = cc.Sprite:create("ui/mail/mail-player-title.png")
    Layout:layout(title, background:getContentSize(), Layout.center)
    background:addChild(title)

    self._playerMailTip = cc.Sprite:create("ui/mail/mail-unread.png")
    Layout:layout(self._playerMailTip, background:getContentSize(), Layout.right_center, cc.p(50, 0))
    background:addChild(self._playerMailTip)
    
    self:_checkPersonalMail()
end

function M:_createSystemTitle()
    local background = Button.new("ui/mail/mail-title-bg.png", "ui/mail/mail-title-bg.png")
    self:addChild(background)
    background.onClicked = function()
        self:_gotoSystemMail()
    end
    background:setPosition(cc.p(Screen.size.width * 0.5, Screen.size.height - BackgroundLayer.TitleHeight - background:getContentSize().height * 2.5 - paddingY * 3))
    local title = cc.Sprite:create("ui/mail/mail-system-title.png")
    Layout:layout(title, background:getContentSize(), Layout.center)
    background:addChild(title)

    self._systemMailTip = cc.Sprite:create("ui/mail/mail-unread.png")
    Layout:layout(self._systemMailTip, background:getContentSize(), Layout.right_center, cc.p(50, 0))
    background:addChild(self._systemMailTip)

    self:_checkSystemMail()
end

function M:_checkPersonalMail()
    local unreadCount = PersonalMailDataManager:getUnreadMailCount()
    self._playerMailTip:setVisible(unreadCount > 0)
end

function M:_checkSystemMail()
    local unreadCount = SystemMailDataManager:getUnreadMailCount()
    self._systemMailTip:setVisible(unreadCount > 0)
end

function M:_checkGameMail()
    local unreadCount = GameMailDataManager:getUnreadMailCount()
    self._gameMailTip:setVisible(unreadCount > 0)
end

function M:_gotoPersonalMail()
    local playerMailLayer = require("ui.mail.layer-manager.PlayerMailLayer").new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(playerMailLayer)
end

function M:_gotoGameMail()
    local gameMailLayer = require("ui.mail.layer-manager.GameMailLayer").new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(gameMailLayer)
end

function M:_gotoSystemMail()
    local systemMailLayer = require("ui.mail.layer-manager.SystemMailLayer").new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(systemMailLayer)
end

return M