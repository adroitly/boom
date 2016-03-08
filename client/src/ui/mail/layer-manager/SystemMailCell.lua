
local TimeTools = require("ui.common.TimeTools")
local SystemMailData = require("ui.mail.data-manager.SystemMailData")
local ToggleButton = require("share.toggle-button.ToggleButton")
local M = class("ui.team.layer-manager.SystemMailCell", function()
    return cc.TableViewCell:new()
end)

M.SystemMailCellSize = cc.size(752, 123)

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
    local titleStr = SystemMailData:getMailTitle(mailData)
    self._titleLabel:setString(titleStr)

    local time = SystemMailData:getTime(mailData)
    local timeStr = TimeTools:getTimeDiffString(PlayerData:getServerTime(), time)
    self._timeLabel:setString(timeStr)
    self:setSelected(false)
    local mailType = SystemMailData:getMailType(mailData)
    self:_setRead(mailType == Enum.MailType.Read)
end

function M:ctor()
    self:_createBackground()
    self:_createInfoLabels()
    self:_createSelectButton()
end

function M:_createBackground()
    self._background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(self._background)
    self:setContentSize(M.SystemMailCellSize)
    self._background:setAnchorPoint(cc.p(0, 0))
end

function M:_createInfoLabels()
    local nameLabel = CommonUI:createLabel("系统", 30)
    nameLabel:setAnchorPoint(cc.p(0, 1))
    self:addChild(nameLabel)
    Layout:layout(nameLabel, M.SystemMailCellSize, Layout.left_top, cc.p(30, 30))

    self._timeLabel = CommonUI:createLabel("time", 24)
    self._timeLabel:setAnchorPoint(cc.p(1, 1))
    self:addChild(self._timeLabel)
    Layout:layout(self._timeLabel, M.SystemMailCellSize, Layout.right_top, cc.p(30, 30)) 

    self._titleLabel= CommonUI:createLabel("title", 24)
    self:addChild(self._titleLabel)
    Layout:layout(self._titleLabel, M.SystemMailCellSize, Layout.center)
end

function M:_createUnreadSymbol()
    local symbol = cc.Sprite:create("ui/mail/mail-unread.png")
    self:addChild(symbol)
    Layout:layout(symbol, M.SystemMailCellSize, Layout.left_bottom, cc.p(35, 20))
    return symbol
end

function M:_createSelectButton()
    local button = ToggleButton.new("ui/mail/mail-unselected.png", "ui/mail/mail-selected.png")
    Layout:layout(button, M.SystemMailCellSize, Layout.right_bottom, cc.p(20, 10))
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