local SalaryShowLayerCell = require("ui.user-info.layers.SalaryShowLayerCell")
local M = class("ui.user-info.layers.SalaryShowLayer", function()
	return cc.Layer:create()
end)

function M:ctor()
	self:_initData()
	self:_createPageView()
	Event:registerNodeEvent(self)
end

function M:onEnter()
    Touch:registerTouchOneByOne(self, true)
    self:setLocalZOrder(Enum.ZOrder.Dialog)
end

function M:onTouchBegan(touch, event)
	local isHitted = Touch:isTouchHitted(self, touch)
	if self.onClicked then
		self.onClicked(isHitted)
	end
    return isHitted
end

function M:showPageByLevel(level)
	self._pageView:setPageIndex(level - 1)
end

function M:_initData()
	self._allLevels = {}
	for i=1,90 do
		table.insert(self._allLevels, i)
	end
end

function M:_createPageView()
	local viewSize = cc.size(SalaryShowLayerCell.SalaryShowLayerCellSize.height, 
								SalaryShowLayerCell.SalaryShowLayerCellSize.width)
	self._pageView = GridView.new(viewSize, self, 1)
	self:addChild(self._pageView)
	self._pageView:setScrollType(GridView.ScrollType.PageHorizontal)
	self:setContentSize(viewSize)
end

function M:onGridViewLineHeight(gridView, idx)
	return SalaryShowLayerCell.SalaryShowLayerCellSize.width
end

function M:onGridViewCellAtIndex(gridView, idx)
	local cell = gridView:dequeueCell()
	if nil == cell then
		cell = SalaryShowLayerCell.new()
	end
	cell:reload(self._allLevels[idx + 1])
	return cell
end

function M:onGridViewCellCount(gridView)
	return table.getn(self._allLevels)
end

return M