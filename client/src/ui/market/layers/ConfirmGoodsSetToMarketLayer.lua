local MarketData = require("ui.market.datas.MarketData")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroDataManager = require("player-data.HeroDataManager")
local M = class("ui.market.layers.ConfirmGoodsSetToMarketLayer", function()
	return cc.Layer:create()
end)

local m_marketAdd = "auction_add"
local m_marketList = "auction_list"

function M:ctor()
	self._sellingNumber = 0
	self:_createBackground()
	self:_createSellingNumberLabel()
	self:_createGoodsIcon()
	self:_createNumberLabel()
	self:_createCostLabel()
	self:_createPriceLabel()
	self:_createSlider()
	self:_createInputPriceTextFieled()
	self:_createAddButton()
	self:_createSubButton()
	self:_createConfirmButton()
	Event:registerNodeEvent(self)
end

function M:reload(marketData)
	self._marketData = marketData
	self:_updateNodes()
	self:_sliderValueChanged()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	local commons =
	{
		[m_marketList] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onLoadDataSuccess(msgTable)
		end,
		[m_marketAdd] = function(msgTable)
			assert(msgTable and msgTable.code)
			CommonUI:showLoadingLayer(false)
			self:_showSocketCallBack(msgTable)
		end
	}
	Function:safeCall(commons, cmd, msgTable)
end

function M:onEnterTransitionFinish()
	local sendData = {page = 1, player_id = PlayerData:getPlayerId()}
	SocketManager:send(m_marketList, sendData)
	CommonUI:showLoadingLayer(true)
	SocketManager:addObserver(self)
end

function M:onExit()
	SocketManager:removeObserver(self)
end

function M:onInsertText()
	local value = math.floor(self._slider:getValue())
	self._slider:setValue(value)
end

function M:onDeleteBackward()
	local value = math.floor(self._slider:getValue())
	self._slider:setValue(value)
end

function M:_onLoadDataSuccess(msgTable)
	assert(msgTable and msgTable.auctions)
	self._sellingNumber = table.getn(msgTable.auctions)
	self:_updateSellingNumberLabel()
end

function M:_showSocketCallBack(msgTable)
	local showText = string.format(__Localized("拍卖%s"), msgTable.code == 0 and "成功" or "失败")
	CommonUI:lightTips(showText)
	if self._marketData:getResourceId() == Enum.ResourceTypeId.Hero then
		local heroId = self._marketData:getId()
		HeroDataManager:removeHeroDataById(heroId)
	end
	self:removeFromParent()
end

function M:_updateNodes()
	self._slider:setMaximumValue(self:_getMaxValue())
	self._goodsIcon:reloadByResoure(self._marketData:getResourceId(), self._marketData:getItemId(), self._marketData:getNumber(), self._marketData:getLevel())
	local price = self:_getPrice()
	self._priceTextField:setText(price)
end

function M:_createCostLabel()
	self._costLabel = CommonUI:createLabel(__Localized("当前总价为:10"), 30)
	self:addChild(self._costLabel)

	self._costLabel:setAnchorPoint(cc.p(0, 0))
	self._costLabel:setPosition(cc.p(0, Screen.height / 4))
end

function M:_createPriceLabel()
	self._priceLabel = CommonUI:createLabel(__Localized("出售单价:"), 30)
	self:addChild(self._priceLabel)
	self._priceLabel:setAnchorPoint(cc.p(0, 1))
	self._priceLabel:setPosition(cc.p(0, Screen.height / 4))
end

function M:_createInputPriceTextFieled()
	self._priceTextField = require("ui.common.EditBox").new(cc.size(200, 50), "ui/login/login-bt.png")
	self._priceTextField:setInputMode(cc.EDITBOX_INPUT_MODE_NUMERIC)
	self._priceTextField:setListener(self)
	self._priceTextField:setInputMode(cc.EDITBOX_INPUT_MODE_NUMERIC)
	self:addChild(self._priceTextField)
	self._priceTextField:setMaxLength(6)
	self._priceTextField:setAnchorPoint(0, 0.5)
	self._priceTextField:setFontColor(cc.c4b(255, 255, 255, 255))
	self._priceTextField:setText(1)
	local priceLabelSize = self._priceLabel:getContentSize()
	self._priceTextField:setPosition(cc.p(priceLabelSize.width, Screen.height / 4 - priceLabelSize.height / 2))
end

function M:onInsertEnd()
	local value = math.floor(self._slider:getValue())
	self._slider:setValue(value)
end

function M:onInsertChange()
	local value = math.floor(self._slider:getValue())
	self._slider:setValue(value)
end

function M:_createGoodsIcon()
	self._goodsIcon = require("ui.backpack.layer-manager.ItemIconButton").new()
	self:addChild(self._goodsIcon)
	self._goodsIcon:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
end

function M:_createSlider()
	self._slider = ControlSlider.new("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
    self:addChild(self._slider)

	local goodsIconSize = self._goodsIcon:getContentSize()
	self._slider:setPosition(cc.p(Screen.width / 2, Screen.height / 2 - goodsIconSize.height))
    self._slider:setMinimumValue(1)
    self._slider:setMaximumValue(1)

    self._slider.onValueChanged = function(sender, value)
        self:_sliderValueChanged()
    end
end


function M:_addButtonClick()
	local value = math.floor(self._slider:getValue())
	if value > math.floor(self._slider:getMaximumValue()) - 1 then
		return
	end
	value = value + 1
	self._slider:setValue(value)
end

function M:_subButtonClick()
	local value = math.floor(self._slider:getValue())
	if value < 2 then
		return
	end
	value = value - 1
	self._slider:setValue(value)
end

function M:_createAddButton()
	local addButton = ButtonLongPress.new("ui/team/button-add.png", "ui/team/button-add.png")
	addButton.onClicked = function()
		self:_addButtonClick()
	end
    self:addChild(addButton)

	local sliderX, sliderY = self._slider:getPosition()
	local sliderSize = self._slider:getContentSize()
	local buttonSize = addButton:getContentSize()
	addButton:setPosition(cc.p(sliderX + sliderSize.width / 2 + buttonSize.width, sliderY))
end

function M:_createSubButton()
	local subButton = ButtonLongPress.new("ui/team/button-sub.png", "ui/team/button-sub.png")
	subButton.onClicked = function()
		self:_subButtonClick()
	end
	self:addChild(subButton)

	local sliderX, sliderY = self._slider:getPosition()
	local sliderSize = self._slider:getContentSize()
	local buttonSize = subButton:getContentSize()
	subButton:setPosition(cc.p(sliderX - sliderSize.width / 2 - buttonSize.width, sliderY))
end

function M:_createNumberLabel()
	self._goodsNumberLabel = CommonUI:createLabel("1/100", 30)
	self:addChild(self._goodsNumberLabel)

	self._goodsNumberLabel:setAnchorPoint(cc.p(1,0.5))
	local goodsIconSize = self._goodsIcon:getContentSize()
	self._goodsNumberLabel:setPosition(cc.p(Screen.width, Screen.height / 2 - goodsIconSize.height))
end

function M:_getMaxValue()
	return self._marketData:getNumber()
end

function M:_getPrice()
	return self._marketData:getPrice()
end

function M:_sliderValueChanged()
	local sliderValue = math.floor(self._slider:getValue())
	local price = tonumber(self._priceTextField:getText()) or 0
	local numberText = string.format("%d/%d", sliderValue, self:_getMaxValue())
	self._goodsNumberLabel:setString(numberText)
	local costText = string.format(__Localized("当前总价为:%d"), price * sliderValue)
	self._costLabel:setString(costText)
end

function M:_sendAddToMarket()
	local sendData = {item_id = self._marketData:getId(), resource_id = self._marketData:getResourceId(),
			number = math.floor(self._slider:getValue()), price = tonumber(self._priceTextField:getString())}
	SocketManager:send(m_marketAdd, sendData)
	CommonUI:showLoadingLayer(true)
end

function M:_onConfirmButtonClick()
	if self._sellingNumber >= Enum.MarketConfig.MaxSellNumber then
		CommonUI:lightTips(__Localized("当前可上架物品已满"))
		return
	end
	local inputPrice = tonumber(self._priceTextField:getString())
	if nil == inputPrice then
		CommonUI:lightTips(__Localized("输入价格有误"))
		return
	elseif inputPrice < (self:_getPrice() * 0.5) then
		CommonUI:lightTips(string.format(__Localized("请检查输入是否大于最低价格:%d的一半"), self:_getPrice()))
		return
	end
	local number = math.floor(self._slider:getValue())
	local tempMarketData = MarketData.new()
	Table:copy(tempMarketData, self._marketData)
	tempMarketData:updateNumber(number)
	tempMarketData:updatePrice(inputPrice)

	local layer = require("ui.market.layers.MarketConfirmLayer"):createSellConfirmLayer(function()
		self:_sendAddToMarket()
	end)

	layer:reload(tempMarketData)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_createConfirmButton()
	local button = CommonUI:createTextButton(self, __Localized("放市场"), "ui/login/login-button.png")
	button:setPosition(cc.p(Screen.width / 2, BackgroundLayer.BottomHeight / 2))
	button.onClicked = function()
		self:_onConfirmButtonClick()
	end
end

function M:_updateSellingNumberLabel()
	local showText = string.format(__Localized("当前出售物品:%d/%d"), self._sellingNumber, Enum.MarketConfig.MaxSellNumber)
	self._sellingNumberLabel:setString(showText)
end

function M:_createSellingNumberLabel()
	local showText = string.format(__Localized("当前出售物品:%d/%d"), 0, Enum.MarketConfig.MaxSellNumber)
	self._sellingNumberLabel = CommonUI:createLabel(showText, 24)
	self:addChild(self._sellingNumberLabel)

	self._sellingNumberLabel:setAnchorPoint(0, 0.5)
	self._sellingNumberLabel:setPosition(0, BackgroundLayer.BottomHeight / 2)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("放市场"))
	background:setBackButtonCallback(function(returnType)
		self:removeFromParent()
	end)
end

return M