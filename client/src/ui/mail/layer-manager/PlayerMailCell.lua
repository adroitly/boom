
local PersonalMailData = require("ui.mail.data-manager.PersonalMailData")
local TimeTools = require("ui.common.TimeTools")
local PersonalMailDataManager = require("player-data.PersonalMailDataManager")
local ToggleButton = require("share.toggle-button.ToggleButton")
local M = class("ui.team.layer-manager.PlayerMailCell", function()
    return cc.TableViewCell:new()
end)

M.PlayerMailCellSize = cc.size(750, 123)
local kPlayerBaseInfo2 = "player_base_info2"

function M:isSelected()
    return self._selectedButton:isSelected()
end

function M:showSelectButton(isShow)
    self._selectedButton:setVisible(isShow)
end

function M:setSelected(isSelected)
    self._selectedButton:setSelected(isSelected)
end

function M:resetMailData(mailData)
    self._mailData = mailData
    local nameStr = PersonalMailData:getNickname(mailData)
    self._nicknameLabel:setString(nameStr)
    Layout:layout(self._nicknameLabel, M.PlayerMailCellSize, Layout.left_top, cc.p(120, 20))

    -- 获取最新那条
    local playerId = PersonalMailData:getPlayerId(mailData)
    local personalMailData = PersonalMailDataManager:getNewestPersonalMailData(playerId)
    local messageStr = PersonalMailData:getMessage(personalMailData)
    messageStr = Utils:cutStringByWidth(M.PlayerMailCellSize.width - 300, messageStr, self._messageLabel:getSystemFontSize(), self._messageLabel:getSystemFontName())
    self._messageLabel:setString(messageStr)
    Layout:layout(self._messageLabel, M.PlayerMailCellSize, Layout.left_center, cc.p(120, 0)) 

    local time = PersonalMailData:getTime(personalMailData)
    local timeStr = TimeTools:getTimeDiffString(PlayerData:getServerTime(), time)
    self._timeLabel:setString(tostring(timeStr))
    Layout:layout(self._timeLabel, M.PlayerMailCellSize, Layout.right_top, cc.p(30, 30)) 

    self:setSelected(false)

    local isRead = PersonalMailData:isRead(mailData)
    self:_setRead(isRead)

    local iconName = PersonalMailData:getIcon(personalMailData) .. ".png"
    local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
    self._headIcon:changeNormalSpriteWithFrame(frame)
end

function M:ctor()
    self:_createBackground()
    self:_createInfoLabels()
    self:_createSelectButton()
    self:_createHeadIcon()
end

function  M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.PlayerMailCellSize)
    background:setAnchorPoint(cc.p(0, 0))
    return background
end

function M:_createHeadIcon()
    local frame = CommonUI:createSpriteFrameTinyName("hero-icon", "20100.png")
    self._headIcon = Button.new()
    self._headIcon:changeNormalSpriteWithFrame(frame)
    self:addChild(self._headIcon)
    self._headIcon.onClicked = function()
        CommonUI:showLoadingLayer(true)
        local playerId = PersonalMailData:getPlayerId(self._mailData)
        SocketManager:send(kPlayerBaseInfo2, {target_id = playerId})
    end
    self._headIcon:setPosition(cc.p(60, M.PlayerMailCellSize.height * 0.5))
end

function M:_createInfoLabels()
    self._nicknameLabel = CommonUI:createLabel("name", 30)
    self:addChild(self._nicknameLabel)
    
    self._timeLabel = CommonUI:createLabel("time", 24)
    self:addChild(self._timeLabel)
    
    self._messageLabel = CommonUI:createLabel("message", 24)
    self:addChild(self._messageLabel)
end

function M:_createUnreadSymbol()
    local symbol = cc.Sprite:create("ui/mail/mail-unread.png")
    self:addChild(symbol)
    Layout:layout(symbol, M.PlayerMailCellSize, Layout.right_center, cc.p(120, 0))
    return symbol
end

function M:_createSelectButton()
    local button = ToggleButton.new("ui/mail/mail-unselected.png", "ui/mail/mail-selected.png")
    Layout:layout(button, M.PlayerMailCellSize, Layout.right_bottom, cc.p(20, 10))
    self:addChild(button)
    button:setVisible(false)
    self._selectedButton = button
end

function M:_setRead(isRead)
    if not isRead then
        if not self._unreadSymbol then
            self._unreadSymbol = self:_createUnreadSymbol()
        end
    else
        if self._unreadSymbol then
            self._unreadSymbol:removeFromParent()
            self._unreadSymbol = nil
        end
    end
end

return M