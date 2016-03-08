local M = class("ui.market.layers.UserWantSellLayerCell", function()
	return GridViewCell.new()
end)
M.UserWantSellLayerCellSize = cc.size(0, 200)

function M:setSelect(isSelect)
	local backSpriteName = {"ui/team/ui-un-0012b.png", "ui/team/ui-un-0012a.png"}
	self._backgroundSprite:setTexture(isSelect and backSpriteName[1] or backSpriteName[2])
end

function M:ctor(delegate)
	self._delegate = delegate
	self:_testBackground()
	self:_createGoodIcon()
end
function M:reload(marketData)
	self._goodsIcon:reloadByResoure(marketData:getResourceId(), marketData:getItemId(), marketData:getNumber(), marketData:getLevel())
end
function M:_createGoodIcon()
	self._goodsIcon = require("ui.backpack.layer-manager.ItemIconButton").new()
	self:addChild(self._goodsIcon)
	self._goodsIcon.onClicked = function()
		self:_onGoodsIconClick()
	end
end

function M:_testBackground()
	self._backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	local backSpriteSize = self._backgroundSprite:getContentSize()
	self._backgroundSprite:setScaleX(0.3)
	self:addChild(self._backgroundSprite)
end

function M:_onGoodsIconClick()
	self._delegate:onUserWantSellLayerDidBack(self:getIndex())
end

return M