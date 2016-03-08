local M = class("test-layer.TestLabel", function()
    return cc.Label:create()
end)

function M:ctor()
    Touch:registerTouchOneByOne(self, true)
    self._isHighlighted = false
    self._enable = true 
end 

function M:setEnable(enable)
    self._enable = enable
end

--------------------------- 接口分割线 ---------------------------

function M:onTouchBegan(touch, event)
    if not self._enable then 
        return false
    end

    local isHit = Touch:isTouchHitted(self, touch)
    if isHit then
        self:_setHighlighted(true)
    end
    return isHit
end

function M:onTouchEnded(touch, event)
    local isHit = Touch:isTouchHitted(self, touch)
    self:_setHighlighted(false)
    if isHit and self.onClicked then
        self:onClicked()
    end
end

function M:onTouchMoved(touch, event)
    local isHit = Touch:isTouchHitted(self, touch)
    self:_setHighlighted(isHit) 
end

function M:onTouchCancelled(touch, event)
end

function M:_setHighlighted(value)
    if self._isHighlighted == value then
        return
    end

    self._isHighlighted = value
    if self._isHighlighted then
        self:setScale(1.2)
    else
        self:setScale(1.0)
    end
end

return M
