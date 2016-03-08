local BackgroundLayer = require("ui.common.BackgroundLayer")
local MarketSellingLayerCell = require("ui.market.layers.MarketSellingLayerCell")
local FilterData = require("ui.market.datas.FilterData")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.market.MainLayer", function()
	return cc.Layer:create()
end)

local m_marketList = "auction_list"

local m_marketGet = "auction_get"

local m_marketOff = "auction_off"

local m_marketAdd = "auction_add"


function M:ctor()
	self._marketDataList = {}
	self:_createBackground()
	self:_createGridView()
	self:_createGridViewBottomLayer()
	self:_createUserSellingButton()
	self:_createWantSellButton()
	self:_createFilterButton()
	Event:registerNodeEvent(self)
end

function M:onFilterGoodsLayerDidBack(filterData, showText)
	if self._lastFilterData == filterData then
		return
	end
	self._bottomLayer:updateListNotEnd()
	self._nowLoadPage = 1
	self._lastFilterData = filterData
	self:_updateFilterButton(showText)
	self._marketDataList = {}
	self._gridView:reloadData()
	self:_loadDataFromServer()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	local commons =
	{
		[m_marketList] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onLoadDataSuccess(msgTable)
		end,
		[m_marketGet] = function(msgTable)
			CommonUI:showLoadingLayer(false)
			self:_onBuyCallBack(msgTable)
		end,
		[m_marketOff] = function(msgTable)
			self:_removeData(msgTable)
		end,
		[m_marketAdd] = function(msgTable)
			if 0 == msgTable.code then
				self:_reloadGrildVewByTop()
			end
		end
	}

	Function:safeCall(commons, cmd, msgTable)

end

function M:onExit()
	SocketManager:removeObserver(self)
end

function M:onEnterTransitionFinish()
	SocketManager:addObserver(self)
	self:_initData()
end

function M:_initData()
	self._marketDataList = {}
	self._nowLoadPage = 1
	self._isInitData = true
	self:_loadDataFromServer()
end

function M:_getSendToServerData()
	local filterData = self._lastFilterData
	local sendData = {}
	if Enum.ResourceTypeId.Item == filterData:getResourceId() then
		if not filterData:getBackpackType() then
			sendData = {page = self._nowLoadPage, resource_id = filterData:getResourceId()}
		else
			sendData = {page = self._nowLoadPage, resource_id = filterData:getResourceId(), item_id = filterData:getBackpackType()}
		end
	elseif Enum.ResourceTypeId.Hero == filterData:getResourceId() then
		if not filterData:getLevel() then
			sendData = {page = self._nowLoadPage, resource_id = filterData:getResourceId()}
		else
			sendData = {page = self._nowLoadPage, resource_id = filterData:getResourceId() , level = filterData:getLevel()}
		end
	elseif nil == filterData:getResourceId() then
		sendData = {page = self._nowLoadPage}
	end
	return sendData
end

function M:_loadDataFromServer()
	if self._nowLoadPage < 1 then
		self._nowLoadPage = 1
	end
	local sendData = {}
	if not self._lastFilterData then
		sendData = {page = self._nowLoadPage}
	else
		sendData = self:_getSendToServerData()
	end
	SocketManager:send(m_marketList, sendData)
	CommonUI:showLoadingLayer(true)
	self._isLoadInMain = true
end

function M:_removeMarketDataInListById(id)
	local index = 0
	for key,marketData in ipairs(self._marketDataList) do
		if id == marketData:getId() then
			index = key
			break
		end
	end
	if 0 ~= index then
		table.remove(self._marketDataList, index)
	end
end

function M:_findMarketDataHasInList(marketData)
	for _,tempMarketData in pairs(self._marketDataList) do
		if marketData:getId() == tempMarketData:getId() then
			return true
		end
	end
	return false
end

function M:_onLoadDataSuccess(msgTable)
	if not self._isLoadInMain then
		return
	end
	self._isLoadInMain = false
	assert(msgTable.auctions)

	local lastCount = table.getn(self._marketDataList)
	local hasAddData = false
	for _,auction in ipairs(msgTable.auctions) do
		local marketData = require("ui.market.datas.MarketData"):newMarketDataByServer(auction)
		if false == self:_findMarketDataHasInList(marketData) then
			table.insert(self._marketDataList, marketData)
			hasAddData = true
		end
	end
	if self._nowLoadPage == 1 then
		if nil == self._lastFilterData then
			self:_rankDataByTime()
		elseif nil == self._lastFilterData:getLevel() and  nil == self._lastFilterData:getResourceId() then
			self:_rankDataByTime()
		end
	end
	if self._isInitData then
		self._gridView:reloadData()
		self._gridView:setContentOffset(self._gridView:minContainerOffset())
	elseif hasAddData then
		self:_reloadGrildVew()
	end
	self:_reloadBottomLayer(hasAddData)
end

function M:_reloadBottomLayer(hasAddData)
	if table.getn(self._marketDataList) % Enum.MarketConfig.OnePageNumber ~= 0 then
		self._bottomLayer:updateListEnd()
	elseif 0 == table.getn(self._marketDataList) then
		self._bottomLayer:updateListEnd()
	elseif true == hasAddData then
		self._bottomLayer:updateListNotEnd()
	else
		self._bottomLayer:updateListEnd()
	end
end

function M:_reloadGrildVew()
	self._gridView:reloadData()
	local minOffset = self._gridView:minContainerOffset()
	local maxOffset = self._gridView:maxContainerOffset()
	if 1 == self._nowLoadPage then
		self._gridView:setContentOffset(maxOffset)
	else
		local cellCount = table.getn(self._marketDataList)
		local lastCellLine = ((self._nowLoadPage - 1) * Enum.MarketConfig.OnePageNumber) / 2
		local lastLine = math.ceil(cellCount / 2) - lastCellLine
		local allLine = lastLine + lastCellLine
		local percentage = lastLine / allLine
		local offset = cc.p( minOffset.x * percentage , minOffset.y * percentage)
		self._gridView:setContentOffset(offset)
	end
end

function M:_loadNextPageData()
	local showListNumber = table.getn(self._marketDataList)
	self._nowLoadPage = math.floor(showListNumber / Enum.MarketConfig.OnePageNumber + 1)
	self:_loadDataFromServer()
	self._isInitData = false
end

function M:_createFilterButton()
	self._filterButton = CommonUI:createTextButton(self, __Localized("筛选"), "ui/login/register-bt.png")
	Layout:layout(self._filterButton, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))

	self._filterButton.onClicked = function()
		self:_onFilterButtonClick()
	end

end

function M:_updateFilterButton(showText)
	self._filterButton:setText(showText)
end


function M:_rankDataByTime()
	local function _sort(a, b)
		local compaire
		local aTime = a:getTime()
		local bTime = b:getTime()
		compaire = aTime > bTime
		return compaire
	end
	table.sort(self._marketDataList, _sort)
end


function M:_onFilterButtonClick()
	local layer = require("ui.market.layers.FilterGoodsLayer").new(self)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_reloadGrildVewByTop()
	self._nowLoadPage = 1
	self:_loadDataFromServer()
	self._isInitData = true
end

function M:onGridViewScrollDidStop(gridView)
	local grildVewiLayout = gridView:getContentLayout()
	if grildVewiLayout == GridView.ContentLayout.Bottom then
		if self._bottomLayer:isInEnd() then
			return
		end
		self:_loadNextPageData()
	elseif grildVewiLayout == GridView.ContentLayout.Top then
		self:_reloadGrildVewByTop()
	end
end

function M:onGridViewCellTouched(gridView, index)
	self:_checkConfirmToBuy(index)
end

function M:onGridViewCellCount(gridView)
	return table.getn(self._marketDataList)
end

function M:onGridViewLineHeight(gridView)
	return MarketSellingLayerCell.MarketSellingLayerCellSize.height
end

function M:onGridViewCellAtIndex(gridView, index)
	local cell = gridView:dequeueCell()
	if not cell then
		cell = MarketSellingLayerCell.new()
	end
	cell:reload(self._marketDataList[index + 1])
	return cell
end

function M:_checkConfirmToBuy(index)
	local MarketConfirmLayer = require("ui.market.layers.MarketConfirmLayer")
	local layer = MarketConfirmLayer:createBuyConfirmLayer(function()
		self:_onConfirmBuy(index + 1)
	end)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)

	layer:reload(self._marketDataList[index + 1])
end

function M:_checkGoldEnough(marketData)
	local price = marketData:getPrice()
	local number = marketData:getNumber()
	local cost = price * number
	local goldBackpackData = BackpackDataManager:getBackpackDataByType(Enum.ResourceType.Gold)
	if nil == goldBackpackData then
		self:_openRechargeNode()
		return false
	elseif cost > goldBackpackData:getItemNumber() then
		self:_openRechargeNode()
		return false
	end
	return true
end

function M:_checkIsOwn(marketData)
	local nickName = marketData:getNickName()
	if nickName == PlayerData:getNickName() then
		local alertView = AlertView.new(__Localized("当前物品是你拍卖的物品，是否购买"), __Localized("取消"), __Localized("购买"))
		alertView.onClicked = function(clickIndex)
			if 1 == clickIndex then
				self:_sendBuyToServer(marketData)
			end
		end
		return true
	end
	return false
end

function M:_onConfirmBuy(index)
	local marketData = self._marketDataList[index]
	if false == self:_checkGoldEnough(marketData) then
		return
	elseif true == self:_checkIsOwn(marketData) then
		return
	end
	self:_sendBuyToServer(marketData)
end

function M:_sendBuyToServer(marketData)
	self._buyMarketData = marketData
	local sendData = {id = marketData:getId()}
	SocketManager:send(m_marketGet, sendData)
	CommonUI:showLoadingLayer(true)
end

function M:_onBuyCallBack(msgTable)
	assert(msgTable and msgTable.code)
	if 0 == msgTable.code then
		CommonUI:lightTips(__Localized("购买成功"))
		self:_removeData(msgTable)
	elseif ServerErrorCode.AUCTION_OFF == msgTable.code then
		if nil == self._buyMarketData then
			return
		end
		self:_removeMarketDataInListById(self._buyMarketData:getId())
		self:_reloadGrildVew()
		CommonUI:lightTips(__Localized("当前商品已被购买"))
	end
	self._buyMarketData = nil
end

function M:_removeData(msgTable)
	if 0 == msgTable.code then
		self:_removeMarketDataInListById(msgTable.id)
		self:_reloadGrildVew()
	end
end

function M:_createGridView()
	local gridViewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight * 2)
	self._gridView = GridView.new(gridViewSize, self, 2)
	self:addChild(self._gridView)
	self._gridView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
end

function M:_createGridViewBottomLayer()
	self._bottomLayer = require("ui.market.layers.MarketBottomLayer").new()
	self._gridView:setBottomLayer(self._bottomLayer)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("拍卖行"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

function M:_createWantSellButton()
	local button = CommonUI:createTextButton(self, __Localized("我要卖"), "ui/login/login-button.png")
	button:setPosition(cc.p(Screen.width * 0.75, BackgroundLayer.BottomHeight / 2))
	button.onClicked = function()
		local layer = require("ui.market.layers.UserWantSellLayer").new()
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(layer)
	end
end

function M:_createUserSellingButton()
	local button = CommonUI:createTextButton(self, __Localized("正在出售"), "ui/login/login-button.png")
	button:setPosition(cc.p(Screen.width * 0.25, BackgroundLayer.BottomHeight / 2))
	button.onClicked = function()
		local layer = require("ui.market.layers.UserSellingLayer").new()
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(layer)
	end
end

function M:_openRechargeNode()
	CommonUI:alertRechargeLayer()
end

return M