local SearchGoodsCell = require("ui.backpack.layer-manager.SearchGoodsCell")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.backpack.layer-manager.SearchGoodsLayer", function()
	return cc.Layer:create()
end)

function M:ctor()
	self._cellSize = 10
	self:_createBackground()
	self:_createShowLabel()
	self:_createGoToSearchTableView()
	self:_setupEventHandler()

end

function M:onTouchBegan(touch, event)
	return true
end

function M:reloadByBackpackId(backpackId)
	self:_updateSearch(backpackId)
end

function M:_updateSearch(backpackId)
	local packDesc = BackpackConfigRead:getDesc(backpackId)
	self._showLabel:setString(packDesc)
end

function M:_setupEventHandler()
    Touch:registerTouchOneByOne(self, true)
end

function M:_createGoToSearchTableView()
	local showLabelSize = self._showLabel:getContentSize()
	local tableViewSize = cc.size(
		Screen.width, 
		Screen.height - showLabelSize.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight
		)
	self._tableView = require("share.TableView").new(tableViewSize, self)
	self._tableView:setPosition(0, 100)
    self._tableView:reloadData()
	self:addChild(self._tableView)
end
function M:onTableViewCellTouched(tableView, cell)
end
function M:onTableViewCellSize(tableView, idx)
	return SearchGoodsCell.SearchGoodsCellSize.width, SearchGoodsCell.SearchGoodsCellSize.height
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = SearchGoodsCell.new()
	end
    return cell
end

function M:onTableViewCellCount(tableView)
	return self._cellSize
end

function M:_createShowLabel()
	self._showLabel = CommonUI:createLabel("Test\nTest")
	self._showLabel:setAnchorPoint(0, 0.5)
	self._showLabel:setAlignment(0)
	local labelSize = self._showLabel:getContentSize()
	self._showLabel:setWidth(Screen.width)
	self._showLabel:setPosition(cc.p(0, Screen.height - labelSize.height / 2 - BackgroundLayer.TitleHeight))
	self:addChild(self._showLabel)
end

function M:_createBackground()

	local backgroundLayer = BackgroundLayer.new(self, __Localized("获取"))
	self._contentSize = cc.size(Screen.width, Screen.height)
	backgroundLayer:setBackButtonCallback(function()
		self:removeFromParent()
	end)

end

return M