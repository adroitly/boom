local function _getClass(sprite)
    local scaleSprite = sprite
    if "string" == type(sprite) then
        scaleSprite = ccui.Scale9Sprite:create(sprite)
    end
    local fontSize = scaleSprite:getContentSize()
    return ccui.EditBox:create(fontSize, sprite)
end
--[[
EditBox类
isFollow设置是否跟随背景图大小设定
isFollow设置为true则fontSize设置无效
]]
local M = class("ui.common.EditBox", function(fontSize, sprite, isFollow)
    if isFollow then
        return _getClass(sprite)
    else
        return ccui.EditBox:create(fontSize, sprite)
    end
end)

function M:setString(text)
    self:setText(text)
end

function M:getString(text)
    return self:getText()
end

function M:setTextColor(color)
    self:setFontColor(color)
end

--[[
设置输入的回调
必须实现以下的方法中的一个或多个
onInsertBegan
onInsertEnd
onInsertChange
onInsertReturn
onInsertCancel
]]

function M:setListener(delegate)
    assert(delegate, "请检查delegate")
    assert(delegate.onInsertBegan or delegate.onInsertEnd or delegate.onInsertChange or delegate.onInsertReturn or delegate.onInsertCancel, "请注册回调函数")
    local function editboxEventHandler(eventType)
        if eventType == "began" then
            if delegate.onInsertBegan then
                delegate:onInsertBegan(self)
            end
        elseif eventType == "ended" then
            if delegate.onInsertEnd then
                delegate:onInsertEnd(self)
            end
        elseif eventType == "changed" then
            if delegate.onInsertChange then
                delegate:onInsertChange(self)
            end
        elseif eventType == "return" then
            if delegate.onInsertReturn then
                delegate:onInsertReturn(self)
            end
        end
    end
    self._delegate = delegate
    self:registerScriptEditBoxHandler(editboxEventHandler)
end

-- 这个不知道为什么EditBox不开放这个接口出来
function M:setVisible(visible)
    cc.Node.setVisible(self, visible)
    if false == visible then
        Touch:removeKeyboardTouch(self)
    else
        Touch:addKeyboardTouch(self)
    end
end

function M:ctor()
    Touch:addKeyboardTouch(self)
    Event:registerNodeEvent(self)
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        if self._delegate.onInsertCancel then
            self._delegate:onInsertCancel(self)
        end
    end
end

return M
