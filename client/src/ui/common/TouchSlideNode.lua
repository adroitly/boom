local M = class("ui.common.TouchSlideNode", function()
    return cc.Node:create()
end)

local m_moveSkew = 200

local m_touchBegan = 80

local m_direction =
{
    Left = 1,
    Right = 2,
    Top = 3,
    Down = 4,
}


function M:setTouchBeganWidth(width)
    self._touchBeganWidth = width
end

--[[
 增加一个滑动的节点

 parent必须实现以下方法的一个或多个

 onTouchSlideMoveLeft
 onTouchSlideMoveRight
 onTouchSlideMoveTop
 onTouchSlideMoveDown
]]

function M:ctor(parent)
    self._touchBeganWidth = m_touchBegan
    assert(parent and "userdata" == type(parent))
    assert(parent.onTouchSlideMoveLeft or parent.onTouchSlideMoveRight or parent.onTouchSlideMoveTop or parent.onTouchSlideMoveDown, "请注册回调方法")
    self._parent = parent
    Touch:registerTouchOneByOne(self, false)
    self:setContentSize(cc.size(Screen.width, Screen.height))
    parent:addChild(self)
end

function M:onTouchBegan(touch, event)
    self._isMove = false
    self._beganLocation = touch:getLocation()
    return self:_isTouchStart(self._beganLocation)
end

function M:onTouchMoved(touch, event)
    self._isMove = true
end

function M:onTouchEnded(touch, event)
    if false == self._isMove or false == Touch:isTouchHitted(self, touch) then
        return
    end
    self._endLocation = touch:getLocation()
    self:_getDirection()
end

function M:onTouchCancelled(touch, event)
    self._isMove = Touch:isTouchHitted(self, touch)
end

function M:_isTouchStart(location)
    if self._parent.onTouchSlideMoveRight and location.x <= self._touchBeganWidth then
        return true
    elseif self._parent.onTouchSlideMoveLeft and location.x >= (Screen.width - self._touchBeganWidth) then
        return true
    elseif self._parent.onTouchSlideMoveTop and location.y <= self._touchBeganWidth then
        return true
    elseif self._parent.onTouchSlideMoveDown and location.y >= (Screen.height - self._touchBeganWidth) then
        return true
    end
    return false
end

function M:_getDirection()
    local x = math.abs(self._beganLocation.x - self._endLocation.x)
    local y = math.abs(self._beganLocation.y - self._endLocation.y)
    if x < m_moveSkew and y < m_moveSkew then
        return
    end
    if x > y then
        self:_getHorizontalDirection()
    else
        self:_getVerticalDirection()
    end
end

function M:_getHorizontalDirection()
    if self._beganLocation.x > self._endLocation.x then
        self:_touchSlideMoveDirection(m_direction.Left)
    else
        self:_touchSlideMoveDirection(m_direction.Right)
    end
end

function M:_getVerticalDirection()
    if self._beganLocation.y > self._endLocation.y then
        self:_touchSlideMoveDirection(m_direction.Down)
    else
        self:_touchSlideMoveDirection(m_direction.Top)
    end
end

function M:_touchSlideMoveDirection(direction)
    if m_direction.Left == direction and self._parent.onTouchSlideMoveLeft then
        self._parent:onTouchSlideMoveLeft()
    elseif m_direction.Right == direction and self._parent.onTouchSlideMoveRight then
        self._parent:onTouchSlideMoveRight()
    elseif m_direction.Top == direction and self._parent.onTouchSlideMoveTop then
        self._parent:onTouchSlideMoveTop()
    elseif m_direction.Down == direction and self._parent.onTouchSlideMoveDown then
        self._parent:onTouchSlideMoveDown()
    end
end

return M
