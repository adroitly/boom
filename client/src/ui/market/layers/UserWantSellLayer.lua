local BackgroundLayer = require("ui.common.BackgroundLayer")
local UserWantSellLayerCell = require("ui.market.layers.UserWantSellLayerCell")
local MarketData = require("ui.market.datas.MarketData")
local HeroDataManager = require("player-data.HeroDataManager")
local FilterData = require("ui.market.datas.FilterData")
local M = class("ui.market.layers.UserWantSellLayer", function()
	return cc.Layer:create()
end)

local m_marketList = "auction_list"

function M:ctor()
	self:_initData()
	self:_createBackground()
	self:_createFilterButton()
	self:_createGridView()
	self:_createConfirmButton()
	Event:registerNodeEvent(self)
end

-- 代理
function M:onFilterGoodsLayerDidBack(filterData, showText)
	if self._lastFilterData == filterData then
		return
	end
	self._lastFilterData = filterData
	self._cellSelectIndex = nil
	self._marketDataList = {}
	self:_reloadShowData()
	self._gridView:reloadData()
	local minOffset = self._gridView:minContainerOffset()
	self._gridView:setContentOffset(minOffset)
	self:_updateFilterButton(showText)
end

function M:onUserWantSellLayerDidBack(index)
	self:_onCellClick(index)
end


function M:onGridViewCellTouched(gridView, index)
	self:_onCellClick(index)
end

function M:onGridViewCellCount(gridView)
	return table.getn(self._marketDataList)
end

function M:onGridViewLineHeight(gridView)
	return UserWantSellLayerCell.UserWantSellLayerCellSize.height
end

function M:onGridViewCellAtIndex(gridView, index)
	local cell = gridView:dequeueCell()
	if not cell then
		cell = UserWantSellLayerCell.new(self)
	end
	if index == self._cellSelectIndex then
		cell:setSelect(true)
	else
		cell:setSelect(false)
	end
	cell:reload(self._marketDataList[index + 1])
	return cell
end

function M:_reloadShowData()
	local filterData = self._lastFilterData
	if Enum.ResourceTypeId.Hero == filterData:getResourceId() then
		self:_addHeroDataToShow(filterData:getLevel())
	elseif Enum.ResourceTypeId.Item == filterData:getResourceId() then
		self:_addBackpackDataToShow(filterData:getBackpackType())
	elseif nil == filterData:getResourceId() then
		self:_addHeroDataToShow()
		self:_addBackpackDataToShow()
	end
end

function M:_addHeroDataToShow(level)
	local heroDataList = HeroDataManager:getBackpackHeroNoTeamList()
	for _,heroData in pairs(heroDataList) do
		local marketData = MarketData:newMarketDataByHeroData(heroData)
		if nil == level then
			table.insert(self._marketDataList , marketData)
		elseif level == marketData:getLevel() then
			table.insert(self._marketDataList , marketData)
		end
	end
end

function M:_addBackpackDataToShow(backpackType)
	local backpackDataList = PlayerData:getBackpackItemList()
	for _,backpackData in pairs(backpackDataList) do
		local marketData = MarketData:newMarketDataByBackpackData(backpackData)
		if nil == backpackType then
			table.insert(self._marketDataList , marketData)
		elseif marketData~= nil and backpackType == marketData:getItemId() then
			table.insert(self._marketDataList , marketData)
		end
	end
end

function M:_initData()
	self._marketDataList = {}
	self:_addHeroDataToShow()
	self:_addBackpackDataToShow()
end

function M:_onCellClick(index)
	if self._cellSelectIndex then
		if self._cellSelectIndex == index then
			return
		end
		local cell = self._gridView:cellAtIndex(self._cellSelectIndex)
		if cell then
			cell:setSelect(false)
		end
	end
	self._cellSelectIndex = index
	local cell = self._gridView:cellAtIndex(self._cellSelectIndex)
	cell:setSelect(true)
end

function M:_createFilterButton()
	self._filterButton = CommonUI:createTextButton(self, __Localized("筛选"), "ui/login/register-bt.png")
	Layout:layout(self._filterButton, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))
	self._filterButton.onClicked = function()
		self:_onFilterButtonClick()
	end
end

function M:_onConfirmButtonClick()
	local layer = require("ui.market.layers.ConfirmGoodsSetToMarketLayer").new()
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
	if nil == self._cellSelectIndex then
		layer:removeFromParent()
		CommonUI:lightTips(__Localized("请选择一个目标"))
		return
	end
	local marketData = self._marketDataList[self._cellSelectIndex + 1]
	layer:reload(marketData)
	self:removeFromParent()
end

function M:_createConfirmButton()
	local button = CommonUI:createTextButton(self, __Localized("确认物品"), "ui/login/login-button.png")
	button.onClicked = function()
		self:_onConfirmButtonClick()
	end
	Layout:layout(button, Screen.size, Layout.center_bottom)
end

function M:_updateFilterButton(showText)
	self._filterButton:setText(showText)
end

function M:_onFilterButtonClick()
	local layer = require("ui.market.layers.FilterGoodsLayer").new(self)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_createGridView()
	local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight * 2 - BackgroundLayer.BottomHeight)
	self._gridView = GridView.new(viewSize, self, 3)
	self:addChild(self._gridView)
	self._gridView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("我要卖"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M