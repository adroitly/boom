local ConfirmGoodsSetToMarketLayer = require("ui.market.layers.ConfirmGoodsSetToMarketLayer")
local M = class("ui.market.layers.UserSellingLayerCell", function()
	return GridViewCell.new()
end)

M.UserSellingLayerCellSize = cc.size(Screen.width, 200)

local m_marketGet = "auction_get"
local m_marketOff = "auction_off"

function M:ctor(delegate)
	self._delegate = delegate
	self:_createGoodsIcon()
	self:_createNumberLabel()
	self:_createPriceLabel()
	self:_createCostLabel()
	self:_createDownButton()
	self:_createUpButton()
	self:_createTakebackButton()
	self:_createSurplusTimeLabel()
	Event:registerNodeEvent(self)
end

function M:reload(marketData)
	self._marketData = marketData
	self:_updateNodes(marketData)
end

function M:onEnterTransitionFinish()
	TimerInterval:addTimer(self, 1)
end

function M:onUpdate()
	self:_reloadTime()
end

function M:onExit()
	TimerInterval:removeTimer(self)
end


function M:_updateNodes()
	self._goodsIcon:reloadByResoure(marketData:getResourceId(), marketData:getItemId(), marketData:getNumber(), marketData:getLevel())
	self._costLabel:setString(string.format(__Localized("总 价 : %d 元宝"), self:_getCost()))
	self._numberLabel:setString(string.format(__Localized("数 量 : %d"), self:_getNumber()))
	self._priceLabel:setString(string.format(__Localized("单 价 : %d 元宝"), self:_getPrice()))
	self:_reloadTime()
end

function M:_reloadTime()
	local surplusTime = self:_getSurplusTime()
	if surplusTime < 0 then
		surplusTime = 0
		self._downButton:setVisible(false)
		self._upButton:setVisible(true)
		self._takebackButton:setVisible(true)
		self._surplusTimeLabel:setVisible(false)
	else
		self._downButton:setVisible(true)
		self._upButton:setVisible(false)
		self._takebackButton:setVisible(false)
		self._surplusTimeLabel:setVisible(true)
	end
	local timeStr = Function:timeToDateString(surplusTime)
	self._surplusTimeLabel:setString(string.format("%s", timeStr))
end

function M:_onDownButtonClick()
	self._delegate:onUserSellingCellDownDidBack(self:getIndex())
end

function M:_onUpButtonClick()
	self._delegate:onUserSellingCellUpDidBack(self:getIndex())
end

function M:_onTakebackButtonClick()
	self._delegate:onUserSellingCellTakebackDidBack(self:getIndex())
end

function M:_createTakebackButton()
	self._takebackButton = CommonUI:createTextButton(self, __Localized("取回"), "ui/login/login-button.png")

	self._takebackButton.onClicked = function()
		self:_onTakebackButtonClick()
	end

	local buttonSize = self._takebackButton:getContentSize()
	self._takebackButton:setPosition(cc.p(M.UserSellingLayerCellSize.width / 2 - buttonSize.width / 2, - buttonSize.height / 2))
end

function M:_createUpButton()
	self._upButton = CommonUI:createTextButton(self, __Localized("上架"), "ui/login/login-button.png")

	self._upButton.onClicked = function()
		self:_onUpButtonClick()
	end

	local buttonSize = self._upButton:getContentSize()
	self._upButton:setPosition(cc.p(M.UserSellingLayerCellSize.width / 2 - buttonSize.width / 2, buttonSize.height / 2))
end


function M:_createDownButton()
	self._downButton = CommonUI:createTextButton(self, __Localized("下架"), "ui/login/login-button.png")

	self._downButton.onClicked = function()
		self:_onDownButtonClick()
	end

	local buttonSize = self._downButton:getContentSize()
	self._downButton:setPosition(cc.p(M.UserSellingLayerCellSize.width / 2 - buttonSize.width / 2 , 0))
end

function M:_createGoodsIcon()
	self._goodsIcon = require("ui.backpack.layer-manager.ItemIconButton").new()
	self:addChild(self._goodsIcon)

	local iconSize = self._goodsIcon:getContentSize()
	self._goodsIcon:setPosition(cc.p(- M.UserSellingLayerCellSize.width / 2 + iconSize.width, 0))
end

function M:_createCostLabel()
	self._costLabel = CommonUI:createLabel(__Localized("元宝X999999"), 24)
	self._costLabel:setAnchorPoint(cc.p(0, 0.5))
	self:addChild(self._costLabel)

	local labelSize = self._numberLabel:getContentSize()
	self._costLabel:setPosition(cc.p(-labelSize.width / 2, -labelSize.height))
end

function M:_createSurplusTimeLabel()
	self._surplusTimeLabel = CommonUI:createLabel(__Localized("剩余时间:9999999"), 24)
	self:addChild(self._surplusTimeLabel)
	local buttonSize = self._goodsIcon:getContentSize()
	local posi = cc.p(M.UserSellingLayerCellSize.width / 2 - buttonSize.width , buttonSize.width / 2)
	self._surplusTimeLabel:setPosition(posi)
end

function M:_createPriceLabel()
	self._priceLabel = CommonUI:createLabel(__Localized("单价:9999999"), 24)
	self._priceLabel:setAnchorPoint(cc.p(0, 0.5))
	self:addChild(self._priceLabel)

	local labelSize = self._numberLabel:getContentSize()
	self._priceLabel:setPosition(cc.p(-labelSize.width / 2, labelSize.height))
end

function M:_createNumberLabel()
	self._numberLabel = CommonUI:createLabel(__Localized("单价:9999999"), 24)
	self._numberLabel:setAnchorPoint(cc.p(0, 0.5))
	self:addChild(self._numberLabel)

	local labelSize = self._numberLabel:getContentSize()
	self._numberLabel:setPosition(cc.p(-labelSize.width / 2, 0))
end

function M:_getPrice()
	return self._marketData:getPrice()
end

function M:_getNumber()
	return self._marketData:getNumber()
end

function M:_getCost()
	return self:_getNumber() * self:_getPrice()
end

function M:_getSurplusTime()
	local time = 3 * 24 * 3600 - (PlayerData:getServerTime() - self._marketData:getTime())
	return time
end

return M