local ShareButton = require("share.FlaButton")

local M = class("share.ScrollButton", function(view, ...)
	return ShareButton:create(...)
end)

function M:ctor(view)
	self._view = view
	self._firstTouchPosition = nil
	self:setScaleRatio(1.002)

	Event:registerNodeEvent(self)
end

function M:setScrollView(scrollView)
	self._view = scrollView 
end

function M:onTouchBegan(touch, event)
	self._firstTouchPosition = touch:getLocation()

	if Touch:isTouchHitted(self._view, touch) and ShareButton.onTouchBegan(self, touch, event) then
		Function:safeCall(self._view, "onTouchBegan", self._view, touch, event)
		self._moved = false
		self._release = false
		return true
	end
	return false
end

function M:onTouchMoved(touch, event)
	if self._release then
		return
	end

	if not self._moved then
		-- 添加一定的范围，防止手指点击下去的时候有点滑动
		local position = touch:getLocation()
		local sensitivity = 20
		if cc.pDistanceSQ(position, self._firstTouchPosition) > sensitivity * sensitivity then 
			self._moved = true
		end
	end

	if self._moved then 
		self:setHighlighted(false)
		Function:safeCall(self._view, "onTouchMoved", self._view, touch, event)
	end

	self._touch = touch
end

function M:onTouchEnded(touch, event)
	if self._moved then 
		self:onTouchCancelled(touch, event)
		return 
	end 

	self._touch = nil
	self._release = true
    self:setHighlighted(false)
    ShareButton.onTouchEnded(self, touch, event)

    Function:safeCall(self._view, "onTouchCancelled", self._view, touch, event)
end

function M:onTouchCancelled(touch, event)
	self._touch = nil
	self._release = true
	self:setHighlighted(false)

	Function:safeCall(self._view, "onTouchEnded", self._view, touch, event) 
end

function M:onExit()
	if self._touch then
		self:onTouchEnded(self._touch, nil)
	end
end

return M