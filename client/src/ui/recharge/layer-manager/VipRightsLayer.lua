local BackgroundLayer = require("ui.common.BackgroundLayer")
local VipRightsCell = require("ui.recharge.layer-manager.VipRightsCell")
local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local TimeTools = require("ui.common.TimeTools")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.recharge.layer-manager.VipRightsLayer", function()
    return cc.Layer:create()
end)

local kVipRewardReceive = "vip_reward_receive"
local kUserInfo         = "user_info"
function M:ctor()
    self:_createBackground()
    self:_createVipPageView()
    self:_createArrows()
    self:_createPageLabel()
    self:_createPlayerInfo()

    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if "exit" == event then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:_createPlayerInfo()
    local playerInfoBg = self:_createPlayerInfoBackground()
    local bgSize = playerInfoBg:getContentSize()
    local frame = PlayerData:getPlayerIconFrame()
    local icon = cc.Sprite:createWithSpriteFrame(frame)
    playerInfoBg:addChild(icon)
    Layout:layout(icon, bgSize, Layout.left_center, cc.p(20, 0))

    local iconPosX, iconPosY = icon:getPosition()
    local iconSize = icon:getContentSize()

    local vipLv = PlayerData:getUserInfoData():getVip()
    local vipStr = string.format("VIP %d", vipLv)
    local vipLabel = CommonUI:createLabel(vipStr, 30)
    playerInfoBg:addChild(vipLabel)
    vipLabel:setAnchorPoint(cc.p(0, 1))
    vipLabel:setPosition(cc.p(iconPosX + iconSize.width * 0.5 + 10, iconPosY + iconSize.height * 0.5))

    local needRechargeStr = ""
    local needRecharge = 0
    local curRecharge = PlayerData:getUserInfoData():getRMB()
    if vipLv == VipConfigReader:getMaxLevel() then
        needRechargeStr = "已达到最高等级"
    else
        needRecharge = VipConfigReader:getNeedRecharge(vipLv)
        needRechargeStr = string.format("再充值%d元可成为VIP%d", needRecharge - curRecharge, (vipLv + 1))
    end
    local needRechargeLabel = CommonUI:createLabel(needRechargeStr, 30)
    playerInfoBg:addChild(needRechargeLabel)
    needRechargeLabel:setAnchorPoint(cc.p(0, 0.5))
    needRechargeLabel:setPosition(cc.p(vipLabel:getPositionX(), iconPosY))

    local progressBar = ProgressBar.new("ui/hero-museum/progressbg.png","ui/hero-museum/progressup.png")
    playerInfoBg:addChild(progressBar)
    local progressBarSize = progressBar:getContentSize()
    progressBar:setPosition(cc.p(vipLabel:getPositionX() + progressBarSize.width * 0.5, iconPosY - iconSize.height * 0.5 + progressBarSize.height * 0.5))
    progressBar:setPercentage(curRecharge / needRecharge * 100)

    local percentageStr = string.format("%d/%d", curRecharge, needRecharge)
    local progressLabel = CommonUI:createLabel(percentageStr, 30)
    playerInfoBg:addChild(progressLabel)
    progressLabel:setPosition(progressBar:getPosition())

    self:_createRewardButton(playerInfoBg)
end

function M:_createRewardButton(parent)
    self._rewardButton = CommonUI:createTextButton(parent, "每日奖励", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(self._rewardButton, parent:getContentSize(), Layout.right_top, cc.p(20, 20))
    self._rewardButton.onClicked = function()
        SocketManager:send(kVipRewardReceive, {})
    end

    local vipLv = PlayerData:getUserInfoData():getVip()
    local rewardList = VipConfigReader:getReward(vipLv)
    local str = ""
    for _, reward in ipairs(rewardList) do
        local name = BackpackConfigRead:getName(reward.id)
        local count = reward.count
        str = str .. string.format("%s×%d", name, count) .. " "
    end
    local buttonSize = self._rewardButton:getContentSize()
    local label = CommonUI:createLabel(str, 24)
    label:setWidth(buttonSize.width)
    parent:addChild(label)
    Layout:layout(label, parent:getContentSize(), Layout.right_top, cc.p(20, 20 + buttonSize.height))
    self:_updateRewardState()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kVipRewardReceive then
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips(__Localized("领取成功"))
        end
        self:_updateRewardState()
    end
end

function M:_updateRewardState()
    local vipLv = PlayerData:getUserInfoData():getVip()
    if vipLv == 1 then
        self._rewardButton:setEnabled(false)
        return
    end
    local vipRewardReceiveTime = PlayerData:getUserInfoData():getVipRewardReceiveTime()
    local isSameDay = TimeTools:isSameDay(PlayerData:getServerTime(), vipRewardReceiveTime)
    if isSameDay then
        self._rewardButton:setEnabled(false)
    else
        self._rewardButton:setEnabled(true)
    end
end

function M:_createPlayerInfoBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    local offsetY = 0.5 * ((Screen.height - BackgroundLayer.TitleHeight - VipRightsCell.VipRightsCellSize.height) - background:getContentSize().height)
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + offsetY))
    return background
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("Vip权限"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createArrows()
    local leftArrow = CommonUI:createTextButton(self, "", "ui/city/arrow.png")
    Layout:layout(leftArrow, Screen.size, Layout.left_bottom, cc.p(0, VipRightsCell.VipRightsCellSize.height * 0.5))
    leftArrow:setRotation(180)
    leftArrow.onClicked = function()
        local pageIndex = self._pageView:getPageIndex()
        if pageIndex > 0 then
            self._pageView:setPageIndex(pageIndex - 1, true)
        end
    end

    local rightArrow = CommonUI:createTextButton(self, "", "ui/city/arrow.png")
    Layout:layout(rightArrow, Screen.size, Layout.right_bottom, cc.p(0, VipRightsCell.VipRightsCellSize.height * 0.5))
    rightArrow.onClicked = function()
        local pageIndex = self._pageView:getPageIndex()
        local maxPageIndex = self:_getPageCount() - 1
        if pageIndex < maxPageIndex then
            self._pageView:setPageIndex(pageIndex + 1, true)
        end
    end
end

function M:_createPageLabel()
    self._pageLabel = CommonUI:createLabel("", 30)
    self:addChild(self._pageLabel)
    self:_updatePageLabel()
end

function M:_updatePageLabel()
    local str = string.format("%d/%d", self._pageView:getPageIndex() + 1, self:_getPageCount())
    self._pageLabel:setString(str)
    Layout:layout(self._pageLabel, Screen.size, Layout.center_bottom)
end

function M:_createVipPageView()
    self._pageView = GridView.new(VipRightsCell.VipRightsCellSize, self, 1)
    self:addChild(self._pageView)
    self._pageView:setScrollType(GridView.ScrollType.PageHorizontal)
    local vip = PlayerData:getUserInfoData():getVip()
    self._pageView:setPageIndex(vip - 1)
end

function M:onGridViewCellCount()
    return self:_getPageCount()
end

function M:onGridViewLineHeight()
    return VipRightsCell.VipRightsCellSize.height
end

function M:onGridViewScrollDidStop(pageView)
    self:_updatePageLabel()
end

function M:onGridViewCellAtIndex(pageView, idx)
    local cell = pageView:dequeueCell()
    if nil == cell then
        cell = VipRightsCell.new()
    end
    cell:reset(idx + 1)
    return cell
end

function M:_getPageCount()
    return VipConfigReader:getMaxLevel()
end

return M
