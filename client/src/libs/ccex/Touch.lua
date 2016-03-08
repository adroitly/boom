local M = {}

function M:isTouchHitted(node, touch, miniSize)
    local pt = touch:getLocation()
    pt = node:getParent():convertToNodeSpace(pt);

    miniSize = miniSize or 50
    local rt = Layout:getFrame(node)
    if rt.width < miniSize then
        local offset = miniSize - rt.width
        rt.x = rt.x - offset * 0.5
        rt.width = rt.width + offset
    end

    if rt.height < miniSize then
        local offset = miniSize - rt.height
        rt.y = rt.y - offset * 0.5
        rt.height = rt.height + offset
    end

    return cc.rectContainsPoint(rt, pt)
end

function M:removeTouchOneByOne(node)
    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    dispatcher:removeEventListenersForTarget(node)
end

function M:registerTouchOneByOne(node, swallow)
    local events = {
        onTouchBegan = cc.Handler.EVENT_TOUCH_BEGAN,
        onTouchEnded = cc.Handler.EVENT_TOUCH_ENDED,
        onTouchMoved = cc.Handler.EVENT_TOUCH_MOVED,
        onTouchCancelled = cc.Handler.EVENT_TOUCH_CANCELLED,
    }

    local listener = nil
    for k, v in pairs(events) do
        if node[k] then
            listener = listener or cc.EventListenerTouchOneByOne:create()
            listener:registerScriptHandler(function(touch, event)
                return node[k](node, touch, event)
            end,
            v)
        end
    end

    if listener then
        if swallow then
            listener:setSwallowTouches(swallow)
        end

        local dispatcher = cc.Director:getInstance():getEventDispatcher()
        dispatcher:addEventListenerWithSceneGraphPriority(listener, node)
    end
end

function M:registerTouchAllAtOnce(node)
    local events = {
        onTouchesBegan = cc.Handler.EVENT_TOUCHES_BEGAN,
        onTouchesEnded = cc.Handler.EVENT_TOUCHES_ENDED,
        onTouchesMoved = cc.Handler.EVENT_TOUCHES_MOVED,
        onTouchesCancelled = cc.Handler.EVENT_TOUCHES_CANCELLED,
    }

    local listener = nil
    for k, v in pairs(events) do
        if node[k] then
            listener = listener or cc.EventListenerTouchAllAtOnce:create()
            listener:registerScriptHandler(function(touches, event)
                return node[k](node, touches, event)
            end,
            v)
        end
    end
end

--[[
    按键事件
    回调为:onKeyPressed,onKeyReleased
    其中:onKeyReleased为必须实现的回调
]]

function M:registerKeyboardTouch(node)
    local events = {
            onKeyPressed = cc.Handler.EVENT_KEYBOARD_PRESSED,
            onKeyReleased = cc.Handler.EVENT_KEYBOARD_RELEASED,
    }

    local listener = nil
    for k, v in pairs(events) do
        if node[k] then
            listener = listener or cc.EventListenerKeyboard:create()
            listener:registerScriptHandler(function(keyCode, event)
                return node[k](node, keyCode, event)
            end,
            v)
        end
    end

    if listener then
        local dispatcher = cc.Director:getInstance():getEventDispatcher()
        dispatcher:addEventListenerWithSceneGraphPriority(listener, node)
    end
end

local KeyboardTouchManager = require("ui.common.KeyboardTouchManager")

-- 这个是在管理器中添加，每次回调只会回调最后添加的一个
-- 这个方法的node必须实现onKeyReleased回调

function M:addKeyboardTouch(node)
    KeyboardTouchManager:addKeyBoard(node)
end

function M:removeKeyboardTouch(node)
    KeyboardTouchManager:removeKeyBoard(node)
end

return M