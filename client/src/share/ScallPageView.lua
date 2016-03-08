local TableView = require("share.TableView")
local M = class("share.ScallPageView", function()
	return cc.Node:create()
end)

local function _abs(number)
	return math.abs(number)
end

local function _assertDelegate(delegate)
	assert(delegate and delegate.onPageViewCellSize and 
		delegate.onPageViewCellAtIndex and delegate.onPageViewCellCount)
end

local function _getNumber(number)
	local tempNumber = number * 10
	local residue = tempNumber % 10
	if residue >= 4 then
		return math.floor(number) + 1
	else
		return math.floor(number)
	end
end

--  index，effect是否有滚动效果
function M:setShowPageByIndex(index , effect)
	index = index - 1
	if index < 0 or index > self._pageCount then
		return
	end
	self._nowPageNumber = index
	local offSet = self:_getOffsetByPageNumber(self._nowPageNumber)
	self._tableView:setContentOffset(offSet, effect)
end

function M:onTableViewCellTouched(tableView, cell)
	if self._delegate.onPageViewTouched then
		self._delegate:onPageViewTouched(tableView, cell)
	end
end

function M:onTableViewCellSize(tableView, idx)
	local width,height = self._delegate:onPageViewCellSize(tableView)
	self._cellSizeWidth = height
	return width,height
end

function M:onTableViewCellAtIndex(tableView, idx)
	return self._delegate:onPageViewCellAtIndex(tableView, idx)
end

function M:onTableViewCellCount(tableView)
	self._pageCount = self._delegate:onPageViewCellCount(tableView, idx)
	return self._pageCount
end

function M:onTouchBegan(touch,event)
	self._isMove = false
	self._reckonLocation = touch:getLocation()
	self._beganLocaltion = self._reckonLocation
	return self:_hinTouch(touch)
end

function M:onTouchMoved(touch,event)
	self._isMove = true
	local location = touch:getLocation()
	if self:_hinTouch(touch) then
		self:_checkUpdateOffset(location)
	end
end

function M:onTouchEnded(touch,event)
	self:_onTouchEndCheckPage(touch)
end

function M:ctor(viewSize, delegate)
	assert(viewSize)
	_assertDelegate(delegate)
	self._isChange = false
	self._nowPageNumber = 0
	self:setContentSize(viewSize)
	self._delegate = delegate
	self:_createTableView(viewSize)
	self:_registerClickHandler()
	self:_createLeftButton()
	self:_createRightButton()
end

function M:_hinTouch(touch)
    return Touch:isTouchHitted(self, touch)
end

function M:_registerClickHandler()
	Touch:registerTouchOneByOne(self, false)
	self:registerScriptHandler(function(event)
		if "exit" == event then
			Touch:removeTouchOneByOne(self)
		end
	end)
end

function M:_checkUpdateOffset(location)
	local moveX = math.abs(location.x - self._reckonLocation.x)
	local moveDirection = location.x > self._reckonLocation.x
	if moveDirection ~= self._isChange then
		self._isChange = moveDirection
	end
	self:_updateOffset((location.x - self._reckonLocation.x) / self._cellSizeWidth)
	self._reckonLocation = location
end

function M:_getOffsetByPageNumber(pageNumber)
	local viewContentSize = self._tableView:getContentSize()
	local offSet = self._tableView:getContentOffset()
	local perOffsetx = viewContentSize.width / self._pageCount
	return cc.p(-perOffsetx * pageNumber, offSet.y)
end

function M:_getPageOffset(offSet, viewContentSize)
	local perOffsetx = viewContentSize.width / self._pageCount
	local offSetx = offSet.x
	local percentPage = _abs(offSetx / perOffsetx)
	local nowPage = 0
	local pageNumber = _getNumber(percentPage)
	self._nowPageNumber = pageNumber
	offSet = self:_getOffsetByPageNumber(pageNumber)
	return offSet
end
function M:_getMaxOffsetX(viewContentSize)
	local perOffsetx = viewContentSize.width / (self._pageCount)
	return viewContentSize.width - perOffsetx
end

function M:_getNearOffset(nowOffset, viewContentSize)
	local offSet = nowOffset
	local perOffsetx = viewContentSize.width / (self._pageCount)
	if nowOffset.x > 0 then
		offSet = cc.p(0, nowOffset.y)
	elseif _abs(offSet.x) >= self:_getMaxOffsetX(viewContentSize) then
		offSet = cc.p(-self:_getMaxOffsetX(viewContentSize), nowOffset.y)
	else
		offSet = self:_getPageOffset(offSet, viewContentSize)
	end
	return offSet
end

function M:_onTouchEndCheckPage(touch)
	local location = touch:getLocation()

	if self:_hinTouch(touch) then
		location = self._reckonLocation
	end

	if false == self._isMove and self:_hinTouch(touch) then
		local cell = self._tableView:cellAtIndex(self._nowPageNumber)
		if cell then
			self:onTableViewCellTouched(self._tableView, cell)
		end
	else
		self:_correctOffset(location)
	end
end

function M:_correctOffset(location)
	local viewContentSize = self._tableView:getContentSize()
	local nowOffset = self._tableView:getContentOffset()
	local offSet = self:_getNearOffset(nowOffset, viewContentSize)
	self._tableView:setContentOffset(offSet, true)
end

function M:_updatePage(direction)
	local movePage = 0
	if direction < 0 then
		movePage = self._nowPageNumber + 1
	else
		movePage = self._nowPageNumber - 1
	end
	if movePage >= self._pageCount then
		return
	elseif movePage < 0 then
		return
	end
	self._nowPageNumber = movePage
	local offSet = self:_getOffsetByPageNumber(self._nowPageNumber)
	self._tableView:setContentOffset(offSet, true)
end

function M:_updateOffset(key)
	local contentOffSet = self._tableView:getContentOffset()
	local tableViewContentSize = self._tableView:getContentSize()
	local offSet = cc.p(contentOffSet.x + (key * self._cellSizeWidth), contentOffSet.y)
	self._tableView:setContentOffset(offSet, false)
end

function M:_createLeftButton()
	local button = ButtonLongPress.new("ui/user-info/up-button.png")
	self:addChild(button)
	Layout:layout(button, self:getContentSize(), Layout.left_center)
	button:setRotation(270)
	button.onClicked = function()
		self:_updatePage(1)
	end
end

function M:_createRightButton()
	local button = ButtonLongPress.new("ui/user-info/up-button.png")
	button:setRotation(90)
	self:addChild(button)
	Layout:layout(button, self:getContentSize(), Layout.right_center)

	button.onClicked = function()
		self:_updatePage(-1)
	end
end

function M:_createTableView(viewSize)
	self._tableView = TableView.new(viewSize, self)
	Touch:removeTouchOneByOne(self._tableView)
	self._tableView:setDirection(cc.SCROLLVIEW_DIRECTION_HORIZONTAL)
	self:addChild(self._tableView)
	self._tableView:reloadData()
end

return M