local BackgroundLayer = require("ui.common.BackgroundLayer")
local FilterGoodsLayerCell = require("ui.market.layers.FilterGoodsLayerCell")
local FilterData = require("ui.market.datas.FilterData")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.market.layers.FilterGoodsLayer", function()
	return cc.Layer:create()
end)


function M:onFilterGoodsCellDidBack(index, showText)
	if self._tableViewStop then
		if self._delegate.onFilterGoodsLayerDidBack then
			self._delegate:onFilterGoodsLayerDidBack(self._filterDataList[index + 1], showText)
		end
	end
end

function M:ctor(delegate)
	self._delegate = delegate
	self:_initFilterData()
	self:_init(delegate)
end

function M:_init()
	self:_registerClickHandler()
	self:_createBackground()
	self:_createTableView()
	self:setContentSize(cc.size(FilterGoodsLayerCell.FilterGoodsLayerCellSize.width, Screen.height - BackgroundLayer.TitleHeight * 2))
end

function M:_initFilterData()
	self._filterDataList = {}

	local nullFilter = FilterData:newNullFilterData()
	table.insert(self._filterDataList, nullFilter)

	local filterData = FilterData:newBackpackFilerData()
	table.insert(self._filterDataList, filterData)

	for _,backpackType in pairs(BackpackConfigRead:getAllConfig()) do
		if 2 ~= BackpackConfigRead:getItemType(backpackType) then
			local filterHeroData = FilterData:newBackpackFilerData(backpackType)
			table.insert(self._filterDataList, filterHeroData)
		end
	end

	local allHeroFilterData = FilterData:newHeroFilterData()
	table.insert(self._filterDataList, allHeroFilterData)

	for level=1,10 do
		local filterHeroData = FilterData:newHeroFilterData(level)
		table.insert(self._filterDataList, filterHeroData)
	end
end

function M:onTouchBegan(touch,event)
	self._beganLocation = touch:getLocation()
	self._tableViewStop = true
	return true
end

function M:onTouchMoved(touch,event)
	local location = touch:getLocation()
	if location.y - self._beganLocation.y > 5 then
		self._tableViewStop = false
	else
		self._tableViewStop = true
	end
end

function M:onTouchEnded(touch,event)
	local isTouchOutSide = Touch:isTouchHitted(self, touch)
	if false == isTouchOutSide and true == self._tableViewStop then
		self:_onClickOutSide()
	end
	self._tableViewStop = true
end

function M:onTableViewCellTouched()
	-- body
end

function M:onTableViewCellSize(tableView)
	return FilterGoodsLayerCell.FilterGoodsLayerCellSize.height, FilterGoodsLayerCell.FilterGoodsLayerCellSize.height
end
function M:onTableViewCellAtIndex(tableView, index)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = FilterGoodsLayerCell.new(self)
	end
	cell:reload(self._filterDataList[index + 1])
	return cell
end
function M:onTableViewCellCount(tableView)
	return table.getn(self._filterDataList)
end
function M:_createTableView()
	local viewSize = cc.size(FilterGoodsLayerCell.FilterGoodsLayerCellSize.width, Screen.height - BackgroundLayer.TitleHeight * 2 - BackgroundLayer.BottomHeight)
	self._tableView = require("share.TableView").new(viewSize, self)
	self:addChild(self._tableView)
	self._tableView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
end
function M:_createBackground()
	local background = cc.LayerColor:create(cc.c4b(0, 0, 0, 40))
	self:addChild(background)
end

function M:_onClickOutSide()
	Touch:removeTouchOneByOne(self)
	self:removeFromParent()
end

function M:_registerClickHandler()
	Touch:registerTouchOneByOne(self, true)
end

return M