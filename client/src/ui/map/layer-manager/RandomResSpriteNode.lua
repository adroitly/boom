
local MapConfig = require("ui.map.data-manager.MapConfig")

local M = class("ui.map.layer-manager.RandomResSpriteNode", function()
    return cc.Node:create()
end)

local function _getRandomSpriteFrame(randomResourceData)
    local resId = string.format("%d.png", randomResourceData:getResourceId())
    return CommonUI:createSpriteFrameTinyName("random", resId)
end

function M:ctor()
    self._sprite = cc.Sprite:create("ui/army-select.png")
    self:addChild(self._sprite)

    local size = self._sprite:getContentSize()
    self:setContentSize(size)
    self:setAnchorPoint(cc.p(0.5, 0.5))
    self._sprite:setPosition( cc.p(size.width/2, size.height/2) )

    self:setLocalZOrder(Enum.ZOrder.RandomRes)
end

function M:reloadData(randomResourceData)
    local frame = _getRandomSpriteFrame(randomResourceData)
    self._sprite:setSpriteFrame(frame)
end

return M