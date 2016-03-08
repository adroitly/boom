--[[
    * 描述：长按按钮
    * 点击事件：onClicked(button)
    * 长按事件：同上
--]]
local SuperClass = require("libs.widget.Button")
local M = class("libs.widget.ButtonLongPress", function(normalImageName, highligtedImageName, disabledImageName)
	return require("libs.widget.ButtonText").new(normalImageName, highligtedImageName, disabledImageName)
end)

function M:ctor()
    self:registerControlEventHandler(function()
        self:_beganTouch()
    end, cc.CONTROL_EVENTTYPE_TOUCH_DOWN)

    self:registerControlEventHandler(function()
        self:_cancelTouch()
    end, cc.CONTROL_EVENTTYPE_TOUCH_CANCEL)

    self:registerControlEventHandler(function()
        self:_cancelTouch()
    end, cc.CONTROL_EVENTTYPE_TOUCH_UP_OUTSIDE)

    self:registerControlEventHandler(function()
        self:_cancelTouch()
        self:_endTouch()
    end, cc.CONTROL_EVENTTYPE_TOUCH_UP_INSIDE)

    self:_reset()
end

function M:onTouchBegan(touch, event)
    if not self:isEnabled() then
        return false
    end
    SuperClass.onTouchBegan(self, touch, event)
    local isInside = Touch:isTouchHitted(self, touch, 0)
    if isInside then
        self:_beganTouch()
    end
    return isInside
end

function M:onTouchCancelled(touch, event)
    SuperClass.onTouchCancelled(self, touch, event)
    self:_cancelTouch()
end

function M:onTouchEnded(touch, event)
    SuperClass.onTouchEnded(self, touch, event)
    local isInside = Touch:isTouchHitted(self, touch, 0)
    self:_cancelTouch()
end

function M:_beganTouch()
    if not self._handle then
        self:_reset()
        Timer:addTimer(self)
        self._handle = true
    end
end

function M:_endTouch()
    if self._handle then
        return
    end
    if self.onClicked then
        self.onClicked(self)
    end
end

function M:_cancelTouch()
    if self._handle then
        Timer:removeTimer(self)
        self._handle = nil
    end
end

function M:_reset()
    self._currentTime = 0
    self._stepTime = 0
end

function M:onUpdate(dt)
    self._currentTime = self._currentTime + dt + self._stepTime
    if self._currentTime > 0.5 then
        self._currentTime = 0
        self._stepTime = self._stepTime + 0.02

        if self.onClicked then
            self.onClicked(self)
        end
    end
end

return M


