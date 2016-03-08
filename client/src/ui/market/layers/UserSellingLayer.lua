local UserSellingLayerCell = require("ui.market.layers.UserSellingLayerCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.market.layers.UserSellingLayer", function()
	return cc.Layer:create()
end)

local m_marketList = "auction_list"
local m_marketGet = "auction_get"
local m_marketOff = "auction_off"
local m_marketOn = "auction_on"

function M:ctor()
	self:_createBackground()
	self._marketDataList = {}
	self:_createSellingNumberLabel()
	self:_createGridView()
	Event:registerNodeEvent(self)
end

function M:onUserSellingCellDownDidBack(index)
	self._actionIndex = index
	local marketData = self._marketDataList[index + 1]
	local sendData = {id = marketData:getId()}
	CommonUI:showLoadingLayer(true)
	SocketManager:send(m_marketOff, sendData)
end

function M:onUserSellingCellTakebackDidBack(index)
	self._actionIndex = index
	local marketData = self._marketDataList[index + 1]
	local sendData = {id = marketData:getId(), player_id = PlayerData:getPlayerId()}
	CommonUI:showLoadingLayer(true)
	SocketManager:send(m_marketGet, sendData)
end

function M:onUserSellingCellUpDidBack(index)
	self._actionIndex = index
	local marketData = self._marketDataList[index + 1]
	local sendData = {id = marketData:getId()}
	CommonUI:showLoadingLayer(true)
	SocketManager:send(m_marketOn, sendData)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	local commons = 
	{
		[m_marketGet] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onTackbackCallBack(msgTable)
		end,
		[m_marketOff] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onDownCallBack(msgTable)
		end,
		[m_marketList] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onLoadDataSuccess(msgTable)
		end,
		[m_marketOn] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onUpCallBack(msgTable)
		end
	}
	Function:safeCall(commons, cmd, msgTable)
	
end

function M:onExit()
	SocketManager:removeObserver(self)
end

function M:onEnterTransitionFinish()
	SocketManager:addObserver(self)
	local sendData = {page = 1, player_id = PlayerData:getPlayerId()}
	SocketManager:send(m_marketList, sendData)
	CommonUI:showLoadingLayer(true)
end

function M:_onTackbackCallBack(msgTable)
	assert(msgTable and msgTable.code)
	if 0 == msgTable.code then
		CommonUI:lightTips(__Localized("取回成功"))
		self:_onTackBackSuccess()
		self._sellingNumber = self._sellingNumber - 1
		self:_updateSellingNumberLabel()
	else
		CommonUI:lightTips(__Localized("取回失败"))
	end
end

function M:_onDownCallBack(msgTable)
	assert(msgTable and msgTable.code)
	if 0 == msgTable.code then
		CommonUI:lightTips(__Localized("下架成功"))
		self:_onGoodsReloadSuccess(0)
	else
		CommonUI:lightTips(__Localized("下架失败"))
	end
end

function M:_onUpCallBack(msgTable)
	assert(msgTable and msgTable.code)
	if 0 == msgTable.code then
		CommonUI:lightTips(__Localized("上架成功"))
		self:_onGoodsReloadSuccess(PlayerData:getServerTime())
	else
		CommonUI:lightTips(__Localized("上架失败"))
	end
end

function M:onGridViewCellCount()
	return table.getn(self._marketDataList)
end

function M:onGridViewLineHeight(gridView)
	return UserSellingLayerCell.UserSellingLayerCellSize.height
end
function M:onGridViewCellAtIndex(gridView, index)
	local cell = gridView:dequeueCell()
	if not cell then
		cell = UserSellingLayerCell.new(self)
	end
	cell:reload(self._marketDataList[index + 1])
	return cell
end

function M:_onTackBackSuccess()
	table.remove(self._marketDataList, self._actionIndex + 1)
	self._gridView:reloadData()
end

function M:_onGoodsReloadSuccess(time)
	local marketData = self._marketDataList[self._actionIndex + 1]
	marketData:updateTime(time)
end

function M:_onLoadDataSuccess(msgTable)
	assert(msgTable.auctions)
	for _,auction in pairs(msgTable.auctions) do
		local marketData = require("ui.market.datas.MarketData"):newMarketDataByServer(auction)
		table.insert(self._marketDataList, marketData)
	end
	self._sellingNumber = table.getn(msgTable.auctions)
	self:_updateSellingNumberLabel()
	self._gridView:reloadData()
	if 0 == self._sellingNumber then
		self:_createShowNoSellingLabel()
	end
end

function M:_createGridView()
	local gridViewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
	self._gridView = GridView.new(gridViewSize, self, 1)
	self:addChild(self._gridView)
	self._gridView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("正在出售"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
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

function M:_createShowNoSellingLabel()
	local label = CommonUI:createLabel(__Localized("你尚未有商品正在出售"), 24)
	self:addChild(label)
	label:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
end

return M