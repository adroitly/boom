local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDetailLayer = require("ui.backpack.layer-manager.BackpackDetailLayer")
local M = class("ui.recharge.layer-manager.VipGiftsCell", function()
    return cc.TableViewCell:new()
end)

local kVipGiftRecevie = "vip_gift_recevie"

M.VipGiftsCellSize = cc.size(752, 193)

function M:reset(giftLv, isRecevied)
    self._giftLv = giftLv
    local giftsName = string.format("VIP%d礼包", giftLv)
    self._vipLevelLabel:setString(giftsName)
    self:_updateScrollView(giftLv)
    self._recevieLabel:setVisible(isRecevied)
end

function M:ctor()
    self:_createBackground()
    self:_createLevelLabel()
    self:_createScrollView()
    self:_createRecevieLabel()

    Touch:registerTouchOneByOne(self, false)
end

function M:onTouchBegan(touch, event)
    for _, itemIcon in ipairs(self._itemIconList) do
        if Touch:isTouchHitted(itemIcon, touch) then
            return false
        end
    end
    local hitTest = Touch:isTouchHitted(self, touch)
    return hitTest
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch, event)
    local hitTest = Touch:isTouchHitted(self, touch)
    if hitTest then
        self:_toGetGift()
    end
end

function M:onTouchCancelled(touch, event)
end

function M:_toGetGift()
    local vipLv = PlayerData:getUserInfoData():getVip()
    if vipLv >= self._giftLv then
        CommonUI:showLoadingLayer(true)
        SocketManager:send(kVipGiftRecevie, {gift_lv = self._giftLv})
    else
        local layer = require("ui.recharge.layer-manager.RechargeLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.VipGiftsCellSize)
    background:setAnchorPoint(cc.p(0, 0))
    return background
end

function M:_createRecevieLabel()
    self._recevieLabel = CommonUI:createLabel("已领取", 30)
    self:addChild(self._recevieLabel)
    Layout:layout(self._recevieLabel, M.VipGiftsCellSize, Layout.right_top, cc.p(40, 20))
    self._recevieLabel:setRotation(45)
end

function M:_createLevelLabel()
    self._vipLevelLabel = CommonUI:createLabel("Vip1礼包", 30)
    self:addChild(self._vipLevelLabel)
    Layout:layout(self._vipLevelLabel, M.VipGiftsCellSize, Layout.left_top, cc.p(40, 20))
end

function M:_createScrollView()
    local viewSize = cc.size(M.VipGiftsCellSize.width - 80, 100)
    self._scrollView = cc.ScrollView:create(viewSize)
    self:addChild(self._scrollView)
    self._scrollView:setPosition(cc.p(40, 10))
    self._scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_HORIZONTAL)
end

function M:_updateScrollView(vipLv)
    self._itemIconList = {}
    self._scrollView:getContainer():removeAllChildren()
    local packList = VipConfigReader:getGiftsPack(vipLv)
    local iconSize = cc.size(100, 100)
    local iconCount = table.getn(packList)
    for i = 1, iconCount do
        local iconName = string.format("%d.png", packList[i].id)
        local frame = CommonUI:createSpriteFrameTinyName("stage-icon", iconName)
        local itemIcon = Button.new()
        itemIcon:changeNormalSpriteWithFrame(frame)
        itemIcon:setSwallowTouches(false)
        itemIcon.onClicked = function()
            local layer = BackpackDetailLayer.new(packList[i].id)
            layer:setLookOverState()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end
        self._scrollView:getContainer():addChild(itemIcon)
        itemIcon:setPosition(cc.p(iconSize.width * (i - 0.5), iconSize.height * 0.5))
        table.insert(self._itemIconList, itemIcon)

        local priceName = BackpackConfigRead:getName(packList[i].id)
        local name = string.format("%s×%d", priceName, packList[i].count)
        local countLabel = CommonUI:createLabel(name, 20)
        itemIcon:addChild(countLabel)
        Layout:layout(countLabel, itemIcon:getContentSize(), Layout.center_bottom, cc.p(0, 10))
    end
    self._scrollView:setContentSize(cc.size(iconSize.width * iconCount, iconSize.height))
end
return M