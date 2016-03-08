local M = class("ui.common.KeyboardTouchManager", function()
    return cc.Node:create()
end)

local m_keyBoardTouch = nil

function M:addKeyBoard(target)
    assert(target.onKeyReleased, "必须实现onKeyReleased方法")
    self:_init()
    if nil ~= self:_getIndexFromTarget(target) then
        return
    end
    table.insert(m_keyBoardTouch._targetList, target)
end

function M:removeKeyBoard(target)
    local index = self:_getIndexFromTarget(target)
    if index then
        table.remove(m_keyBoardTouch._targetList, index)
    end
end


--------------- 私有方法 ---------------

function M:_getIndexFromTarget(target)
    if nil == m_keyBoardTouch then
        return nil
    end
    for index, tempTarget in ipairs(m_keyBoardTouch._targetList) do
        if tempTarget == target then
            return index
        end
    end
    return nil
end

function M:ctor()
    Event:registerNodeEvent(self)
end

function M:onExit()
    m_keyBoardTouch = nil
end

function M:_init()
    if nil == m_keyBoardTouch then
        m_keyBoardTouch = M.new()
        m_keyBoardTouch._targetList = {}
        local gameScene = Director:getRunningScene()
        gameScene:addChild(m_keyBoardTouch)
        self:_createTouch(m_keyBoardTouch)
    end
end

function M:onKeyReleased(keyCode, event)
    local target = self:_getTopTarget()
    if target.onKeyReleased then
        target:onKeyReleased(keyCode, event)
    end
end

function M:onKeyPressed(keyCode, event)
    local target = self:_getTopTarget()
    if target.onKeyPressed then
        target:onKeyPressed(keyCode, event)
    end
end

function M:_getTopTarget()
    return m_keyBoardTouch._targetList[#m_keyBoardTouch._targetList]
end

function M:_createTouch(node)
    Touch:registerKeyboardTouch(node)
end

return M