local TimeTools = require("ui.common.TimeTools")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local SystemMailData = require("ui.mail.data-manager.SystemMailData")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDetailLayer = require("ui.backpack.layer-manager.BackpackDetailLayer")
local ItemDataFrame = require("ui.backpack.data-manager.ItemDataFrame")
local ItemIconButton = require("ui.backpack.layer-manager.ItemIconButton")
local M = class("ui.mail.layer-manager.SystemMailDetailsLayer", function()
    return cc.Layer:create()
end)

local kGuildJoin = "guild_join"
local kMessageSystemSet = "message_system_set"

function M:ctor(mailData)
    self._mailData = mailData
    self:_createBackground()
    self:_createTime(mailData)
    self:_createTitle(mailData)
    self:_createContent(mailData)
    self:_createItemView(mailData)
    self:_createInviteButton(mailData)
    self:_createReceiveButton(mailData)
    Event:registerNodeEvent(self)
end

function M:onEnter()
    SocketManager:addObserver(self)
end

function M:onEnterTransitionFinish()
    local mailType = SystemMailData:getMailType(self._mailData)
    if mailType == Enum.MailType.Read then
        return
    end
    local itemList = SystemMailData:getItemDataList(self._mailData)
    if table.getn(itemList) == 0 then
        self:_sendReadRequest()
    end
end

function M:_sendReadRequest()
    CommonUI:showLoadingLayer(true)
    local mailId = SystemMailData:getMailId(self._mailData)
    SocketManager:send(kMessageSystemSet, {id = mailId, message_type = Enum.MailType.Read})
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildJoin then
        if not CommonUI:errorAlertView(msgTable.code) then
            AlertView.new(__Localized("已申请加入势力"))
        end
    end
    if cmd == kMessageSystemSet then
        CommonUI:showLoadingLayer(false)
        local itemList = SystemMailData:getItemDataList(self._mailData)
        local itemCount = table.getn(itemList)
        if itemCount > 0 then
            CommonUI:lightTips("领取成功")
            self._receiveButton:setEnabled(false)
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "系统邮件")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTime(mailData)
    local time = SystemMailData:getTime(mailData)
    local timeStr = TimeTools:getFormatTimeString(time)
    local timeLabel = CommonUI:createLabel(timeStr, 30)
    self:addChild(timeLabel)
    Layout:layout(timeLabel, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
end

function M:_createTitle(mailData)
    local titleBg = cc.Sprite:create("ui/mail/mail-title-frame.png")
    self:addChild(titleBg)
    Layout:layout(titleBg, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 35))

    local titleStr = SystemMailData:getMailTitle(mailData)
    local titleLabel = CommonUI:createLabel(titleStr, 30)
    self:addChild(titleLabel)
    Layout:layout(titleLabel, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 40))
end

function M:_createContent(mailData)
    self._contentBg = cc.Sprite:create("ui/mail/mail-bg.png")
    self:addChild(self._contentBg)
    Layout:layout(self._contentBg, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 90))

    local contentBgSize = self._contentBg:getContentSize()
    local content = SystemMailData:getMessage(mailData)
    local contentLabel = CommonUI:createLabel(content, 30)
    contentLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)
    contentLabel:setWidth(contentBgSize.width - 20)
    self:addChild(contentLabel)
    Layout:layout(contentLabel, Screen.size, Layout.left_top, cc.p(10, BackgroundLayer.TitleHeight + 100))
end

function M:_createItemView(mailData)
    local itemList = SystemMailData:getItemDataList(mailData)
    local itemCount = table.getn(itemList)
    if itemCount == 0 then
        return
    end
    local viewSize = cc.size(Screen.width - 80, 100)
    local scrollView = cc.ScrollView:create(viewSize)
    self._contentBg:addChild(scrollView)
    scrollView:setPosition(cc.p(40, 20))
    scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_HORIZONTAL)
    local iconSize = cc.size(100, 100)
    for i = 1, itemCount do
        local itemIcon = ItemIconButton.new()
        itemIcon:reloadByResoure(itemList[i]:getResourceId(), itemList[i]:getType(), itemList[i]:getNumber())
        itemIcon:setPosition(cc.p(iconSize.width * (i - 0.5), iconSize.height * 0.5))
        itemIcon.onClicked = function()
            if itemList[i]:getResourceId() ~= Enum.ResourceTypeId.Item then
                return
            end
            local layer = BackpackDetailLayer.new(itemList[i]:getType())
            layer:setLookOverState()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end
        scrollView:getContainer():addChild(itemIcon)
    end
    scrollView:setContentSize(cc.size(iconSize.width * itemCount, iconSize.height))
end

function M:_createInviteButton(mailData)
    local guildId = SystemMailData:getGuildId(mailData)
    if not guildId or guildId == 0 then
        return
    end
    local inviteButton = CommonUI:createTextButton(self, "申请加入", "ui/login/login-bt.png")
    Layout:layout(inviteButton, Screen.size, Layout.center_bottom)
    inviteButton.onClicked = function()
        SocketManager:send(kGuildJoin, {guild_id = guildId})
    end
end

function M:_createReceiveButton(mailData)
    local itemList = SystemMailData:getItemDataList(mailData)
    if table.getn(itemList) == 0 then
        return
    end
    self._receiveButton = CommonUI:createTextButton(self, "领取", "ui/login/login-bt.png")
    Layout:layout(self._receiveButton, Screen.size, Layout.center_bottom)
    self._receiveButton.onClicked = function()
        self:_sendReadRequest()
    end
    local mailType = SystemMailData:getMailType(mailData)
    self._receiveButton:setEnabled(mailType == Enum.MailType.UnRead)
end

return M