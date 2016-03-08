
local ShopConfigReader = require("ui.recharge.data-manager.ShopConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.recharge.layer-manager.ShopItemCell", GridViewCell)

M.ShopItemCellSize = cc.size(100, 160)
local kIconSize = cc.size(100, 100)
function M:reset(id)
    local iconId = ShopConfigReader:getIconId(id)
    local iconName = string.format("%d.png", iconId)
    local frame = CommonUI:createSpriteFrameTinyName("stage-icon", iconName)
    self._itemIcon:setSpriteFrame(frame)
    self._itemIcon:setPosition(cc.p(M.ShopItemCellSize.width * 0.5, M.ShopItemCellSize.height - kIconSize.height * 0.5))

    local name = ShopConfigReader:getName(id)
    self._nameLabel:setString(name)

    local priceType, count = ShopConfigReader:getPrice(id)
    local priceName = BackpackConfigRead:getName(priceType)
    local priceStr = string.format("%d%s", count, priceName)
    self._priceLabel:setString(priceStr)
end

function M:ctor()
    self:setAnchorPoint(cc.p(0.5, 0.5))
    self:setContentSize(M.ShopItemCellSize)
    self:_createIcon()
    self:_createNameLabel()
    self:_createPriceLabel()
end

function M:_createIcon()
    self._itemIcon = cc.Sprite:create()
    self:addChild(self._itemIcon)
    self._itemIcon:setPosition(cc.p(M.ShopItemCellSize.width * 0.5, M.ShopItemCellSize.height - kIconSize.height * 0.5))
end

function M:_createNameLabel()
    self._nameLabel = CommonUI:createLabel("XXXX", 24)
    self:addChild(self._nameLabel)
    self._nameLabel:setPosition(cc.p(M.ShopItemCellSize.width * 0.5, self._itemIcon:getPositionY() - kIconSize.height * 0.5 - self._nameLabel:getContentSize().height * 0.5))
end

function M:_createPriceLabel()
    self._priceLabel = CommonUI:createLabel("XXXX", 24)
    self:addChild(self._priceLabel)
    self._priceLabel:setPosition(cc.p(M.ShopItemCellSize.width * 0.5, self._nameLabel:getPositionY() - self._nameLabel:getContentSize().height * 0.5 - self._priceLabel:getContentSize().height * 0.5))
end

return M