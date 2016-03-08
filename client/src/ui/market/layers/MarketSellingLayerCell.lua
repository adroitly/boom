local M = class("ui.market.layers.MarketSellingLayerCell", function()
	return GridViewCell.new()
end)

M.MarketSellingLayerCellSize = cc.size(Screen.width / 2, 200)

local m_labelInterval = 20

function M:ctor()
	self:_init()
end

function M:reload(marketData)
	assert(marketData)
	self._marketData = marketData
	self:_updateNodes(marketData)
end

function M:_updateNodes(marketData)
	self._userNameLabel:setString(self:_getUserName())
	self._priceLabel:setString(string.format(__Localized("单价:%d元宝"), self:_getPrice()))
	self._numberLabel:setString(string.format(__Localized("数量:%d"), self:_getNumber()))
	self._goodsIcon:reloadByResoure(marketData:getResourceId(), marketData:getItemId(), marketData:getNumber(), marketData:getLevel())
end

function M:_init()
	self:_testBackground()
	self:setContentSize(cc.size(Screen.width / 2, M.MarketSellingLayerCellSize.height))
	self:_createUserNameLabel()
	self:_createPriceLabel()
	self:_createNumberLabel()
	self:_createGoodIcon()
end

function M:_testBackground()
	local backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	local backSpriteSize = backgroundSprite:getContentSize()
	backgroundSprite:setScaleX(0.5)
	self:addChild(backgroundSprite)
end

function M:_createGoodIcon()
	self._goodsIcon = require("ui.backpack.layer-manager.ItemIconButton").new()
	local iconSize = self._goodsIcon:getContentSize()
	self:addChild(self._goodsIcon)
	self._goodsIcon:setSwallowTouches(false)
	self._goodsIcon:setPosition(cc.p(-M.MarketSellingLayerCellSize.width / 2 + iconSize.height , 0))
	self._goodsIcon:setNumberLabelVisible(false)
end

function M:_createUserNameLabel()
	self._userNameLabel = CommonUI:createLabel("玩家名字6个字", 24)
	self:addChild(self._userNameLabel)
	self._userNameLabel:setAnchorPoint(cc.p(0,1))
	local position = cc.p(cc.p(- M.MarketSellingLayerCellSize.width / 2 + m_labelInterval, M.MarketSellingLayerCellSize.height / 2 - m_labelInterval))
	self._userNameLabel:setPosition(position)
end

function M:_createNumberLabel()
	self._numberLabel = CommonUI:createLabel("数量:999999", 24)
	self:addChild(self._numberLabel)
	self._numberLabel:setAnchorPoint(cc.p(0,1))
end

function M:_createPriceLabel()
	self._priceLabel = CommonUI:createLabel("单价:999999元宝", 24)
	self:addChild(self._priceLabel)
	self._priceLabel:setAnchorPoint(cc.p(0,0))
end

function M:_getUserName()
	return self._marketData:getNickName()
end

function M:_getPrice()
	return self._marketData:getPrice()
end

function M:_getNumber()
	return self._marketData:getNumber()
end

return M