
local RechargeConfigReader = require("ui.recharge.data-manager.RechargeConfigReader")
local M = class("ui.recharge.layer-manager.RechargeItemCell", GridViewCell)

M.RechargeItemCellSize = cc.size(100, 200)
local kIconSize = cc.size(100, 100)

function M:reset(id)
    local iconId = RechargeConfigReader:getIconId(id)
    local iconName = string.format("recharge%d.png", id)
    local frame = CommonUI:createSpriteFrameTinyName("recharge-icon", iconName)
    self._itemIcon:setSpriteFrame(frame)
    self._itemIcon:setPosition(cc.p(M.RechargeItemCellSize.width * 0.5, M.RechargeItemCellSize.height - kIconSize.height * 0.5))

    local name = RechargeConfigReader:getName(id)
    self._nameLabel:setString(name)

    local price = RechargeConfigReader:getPrice(id)
    local priceStr = string.format("%d人民币", price)
    self._priceLabel:setString(priceStr)
end

function M:ctor()
    self:setAnchorPoint(cc.p(0.5, 0.5))
    self:setContentSize(M.RechargeItemCellSize)
    self:_createIcon()
    self:_createNameLabel()
    self:_createPriceLabel()

end

function M:_createIcon()
    self._itemIcon = cc.Sprite:create()
    self:addChild(self._itemIcon)
    self._itemIcon:setPosition(cc.p(M.RechargeItemCellSize.width * 0.5, M.RechargeItemCellSize.height - kIconSize.height * 0.5))
end

function M:_createNameLabel()
    self._nameLabel = CommonUI:createLabel("XXXX", 24)
    self:addChild(self._nameLabel)
    self._nameLabel:setPosition(cc.p(M.RechargeItemCellSize.width * 0.5, self._itemIcon:getPositionY() - kIconSize.height * 0.5 - self._nameLabel:getContentSize().height * 0.5))
end

function M:_createPriceLabel()
    self._priceLabel = CommonUI:createLabel("XXXX", 24)
    self:addChild(self._priceLabel)
    self._priceLabel:setPosition(cc.p(M.RechargeItemCellSize.width * 0.5, self._nameLabel:getPositionY() - self._nameLabel:getContentSize().height * 0.5 - self._priceLabel:getContentSize().height * 0.5))
end

return M