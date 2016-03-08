local M = class("ui.common.PageView", function()
	return cc.Node:create()
end)

-- 废弃，请使用GridView
local function _registerTouchOneByOne(node)
	-- 除去事件，再向下传递事件，不然点击无法滚动
	local dispatcher = cc.Director:getInstance():getEventDispatcher()
    dispatcher:removeEventListenersForTarget(node)
	Touch:registerTouchOneByOne(node, false)
end

local function _assertDelegate(delegate)
	assert(delegate and delegate.onPageViewCellSize and 
		delegate.onPageViewCellAtIndex and delegate.onPageViewCellCount)
end

local function _getCellCount(len, childCount)
	local remainder = len % childCount
	remainder = 0 == remainder and 0 or 1
	local count = len / childCount + remainder
	return math.floor(count)
end

function M:dequeueCell()
	if nil == self._nowReloadCell then
		return nil
	end
	return self._nowReloadCell[self._reloadCellIndex]
end

function M:getContentOffset()
	return self._tableView:getContentOffset()
end
function M:getViewSize()
	return self._tableView:getViewSize()
end

function M:getContentSize()
	return self._tableView:getContentSize()
end

function M:setContentOffset(...)
	self._tableView:setContentOffset(...)
end

function M:reloadData()
	self._tableView:reloadData()
end

-- 本方法只使用一个的时候
function M:cellAtIndex(index)
	local cellIndex = index / self._cellChildCount
	local cellChildIndex = index % self._cellChildCount + 1
	local cell = self._tableView:cellAtIndex(cellIndex)
	if cell then
		return cell[cellChildIndex]
	end
end

--[[
viewSize 显示的大小
delegate ,代理
cellChildCount 一个cell放置多少个部件
]]

function M:ctor(viewSize, delegate, cellChildCount)
	assert(viewSize)
	_assertDelegate(delegate)
	self._reloadCellIndex = 0
	self._cellChildCount = cellChildCount or 1
	self._viewSize = viewSize
	self._delegate = delegate
	self:_init()
end
function M:_init()
	self._tableView = require("share.TableView").new(self._viewSize, self)
	self:addChild(self._tableView)
end

function M:onTableViewCellTouched(tableView, cell)
	if self._delegate.onPageViewCellTouched then
		self._delegate:onPageViewCellTouched(self, cell)
	end
end

function M:onTableViewCellSize(tableView, idx)
	local nowIndex = idx * self._cellChildCount
	local sizeWidth = 0
	local sizeHeight = 0
	for key=1,self._cellChildCount do

		local width, height = self._delegate:onPageViewCellSize(self, key + nowIndex - 1)
		sizeWidth = sizeWidth + width
		sizeHeight = sizeHeight + height
		
	end
	return sizeWidth, sizeHeight
end

function M:_getChilds(isNew, parent, idx)
	local nowIndex = idx * self._cellChildCount
	local nodeWidth = self._viewSize.width / self._cellChildCount
	for index=1, self._cellChildCount do
		local childIndex = index + nowIndex - 1
		self._reloadCellIndex = index

		local child = self._delegate:onPageViewCellAtIndex(self, childIndex)

		if isNew then
			parent:addChild(child)
			_registerTouchOneByOne(child)
		end

		child:setPositionX(nodeWidth * (index - 0.5))
		parent[index] = child
	end
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	self._nowReloadCell = cell
	local cellIsNew = false
	if nil == cell then
		cellIsNew = true
		cell = cc.TableViewCell:create()
	end
	self:_getChilds(cellIsNew, cell, idx)
	return cell
end

function M:onTableViewCellCount(tableView)
	return _getCellCount(self._delegate:onPageViewCellCount(tableView), self._cellChildCount)
end


return M