--[[
输入文本
输入中内嵌一个EditBox来解决Android的TextField部分机器无法输入中文
文本显示字体，颜色等显示信息参照Label设置
回调参照EditBox
]]
local SuperClass = cc.Label
local m_bgTag = 100008
local m_chCharLength = 2

local M = class("ui.common.InputUI", function()
    return SuperClass:create()
end)

function M:setPlaceHolder(placeHolder)
    self._placeHolder = placeHolder
    if self._isPlaceHolderShow then
        self:_showPlaceHolder()
    end
end

function M:setPlaceHolderColor(color)
    self._placeHolderColor = color
    if self._isPlaceHolderShow then
        self:_showPlaceHolder()
    end
end

-- 设置点击区域
function M:setTouchSize(size)
    assert(size)
    self._touchSize = size
end

--[[ 设置键盘监听，监听事件为EditBox事件
设置输入的回调
必须实现以下的方法中的一个或多个
onInsertBegan
onInsertEnd
onInsertChange
onInsertReturn
onInsertCancel
]]
function M:setListener(delegate)
    assert(delegate)
    assert(delegate.onInsertBegan or delegate.onInsertEnd or delegate.onInsertChange or delegate.onInsertReturn , "请注册回调函数")
    self._listener = delegate
end

-- 设置输入宽度，自动换行
function M:setTextWidth(textWidth)
    self:setWidth(textWidth)
end

-- 设置输入长度
function M:setMaxLength(maxLength)
    assert(maxLength)
    self._maxLength = maxLength
end

-- 设置输入框类型，参照EditBox的类型
function M:setInputMode(model)
    assert(model)
    self._inputModel = model
end

-- 设置是否可点击
function M:setTouchEnabled(enable)
    self._touchEnabled = enable
end
-- 打开键盘
function M:openKeyboard()
    self:_setEditBoxVisible(true)
    self._editBox:touchDownAction(self._editBox, ccui.TouchEventType.ended)
    self:_addTimer()
    self:onInsertBegan(self._editBox)
end

function M:getPlaceHolder()
    return self._placeHolder
end

function M:setString(text)
    self:_updateString(text)
end

function M:getString()
    return self._nowString
end

function M:setTextColor(color)
    if false == self._isPlaceHolderShow then
        SuperClass.setTextColor(self, color)
    end
    self._fontColor = color
end

----------- 内部接口 ----------

function M:_showPlaceHolder()
    self._isPlaceHolderShow = true
    SuperClass.setString(self, self._placeHolder)
    SuperClass.setTextColor(self, self._placeHolderColor)
end
function M:_hidePlaceHolder()
    self._isPlaceHolderShow = false
    SuperClass.setString(self, "")
    self:setTextColor(self._fontColor)
end

function M:_convertString(str)
    if not self._maxLength then
        return str
    end
    local realString = ""
    local charLength = 0
    for uchar in string.gfind(str,"[%z\1-\127\194-\244][\128-\191]*") do
        realString = realString .. uchar
        if 1 ~= string.len(uchar) then
            charLength = charLength + m_chCharLength
        else
            charLength = charLength + 1
        end
        if self._maxLength and self._maxLength < charLength then
            break
        end
    end
    return realString
end

function M:_updateString(text)
    local showString = self:_convertString(text)
    if 0 == string.len(showString) then
        self:_showPlaceHolder()
        self._nowString = ""
    else
        self:_hidePlaceHolder()
        SuperClass.setString(self, showString)
        self._nowString = showString
    end
end

function M:ctor(fontSize, fontColor)
    self._placeHolder = __Localized("请输入")
    self._placeHolderColor = cc.c4b(150, 150, 150, 255)
    self._nowString = ""
    local fontSize = fontSize or 24
    local fontColor = fontColor or cc.c4b(255, 255, 255, 255)
    self:setSystemFontSize(fontSize)
    self:setTextColor(fontColor)
    Touch:removeTouchOneByOne(self)
    Touch:registerTouchOneByOne(self, false)
    Event:registerNodeEvent(self)
    self:_showPlaceHolder()
end

function M:onExit()
    if self._editBox  then
        self:_setEditBoxVisible(false)
    end
    self:_removeEditBox()
    self._background = nil
end

function M:onTouchBegan(touch, event)
    if self:_isOpenKeyBoard(touch) then
        self:openKeyboard()
    end
    return true
end

function M:onInsertBegan(editBox)
    self:_addTimer()
    local text = self:getString()
    editBox:setText(text)
    if self._listener and self._listener.onInsertBegan then
        self._listener:onInsertBegan(editBox)
    end
end

function M:onInsertEnd(editBox)
    self:_updateString(editBox:getText())
    self:_setEditBoxVisible(false)
    if self._listener and self._listener.onInsertEnd then
        self._listener:onInsertEnd(editBox)
    end
end

function M:onInsertChange(editBox)
    self:_setEditBoxVisible(true)
    if self._listener and self._listener.onInsertChange then
        self._listener:onInsertChange(editBox)
    end
end

function M:onInsertReturn(editBox)
    self:_updateString(editBox:getText())
    self:_setEditBoxVisible(false)
    if self._listener and self._listener.onInsertReturn then
        self._listener:onInsertReturn(editBox)
    end
end

function M:onInsertCancel(editBox)
    self:_setEditBoxVisible(false)
    if self._listener and self._listener.onInsertCancel then
        self._listener:onInsertCancel(editBox)
    end
end

function M:_addTimer()
    -- 如果同一界面出现多个的时候可能出现不弹出背景,加延迟操作即可
    TimerDelay:addTimer(self, 0.1, function()
        TimerDelay:removeTimer(self)
        self:_setEditBoxVisible(true)
    end)
end

function M:_isOpenKeyBoard(touch)
    if false == self._touchEnabled then
        return false
    end
    local pt = touch:getLocation()
    pt = self:getParent():convertToNodeSpace(pt)
    local posX, posY = self:getPosition()
    local anchorPoint = self:getAnchorPoint()
    local touchSize
    if self._touchSize then
        touchSize = self._touchSize
    else
        touchSize = self:getContentSize()
    end
    posX = posX - anchorPoint.x * touchSize.width
    posY = posY - anchorPoint.y * touchSize.height
    local rt = cc.rect(posX, posY, touchSize.width, touchSize.height)
    return cc.rectContainsPoint(rt, pt)
end

function M:_createEditBox()
    local bg = self:_createEditBoxBg()
    self._editBox = require("ui.common.EditBox").new(cc.size(Screen.width, 50), "ui/common/bg-input.png")
    self._editBox:setInputMode(self._inputModel or cc.EDITBOX_INPUT_MODE_SINGLELINE)
    self._editBox:setListener(self)
    self._editBox:setFontSize(30)
    self._editBox:setPlaceholderFontSize(30)
    self._editBox:setPlaceHolder(self:getPlaceHolder())
    self._editBox:setPlaceholderFontColor(cc.c4b(255, 255, 255, 255))
    self._editBox:setPosition(Screen.width / 2, Screen.height / 2)
    if self._maxLength then
        self._editBox:setMaxLength(self._maxLength)
    end
    bg:addChild(self._editBox)
end

function M:_createEditBoxBg()
    if self._background then
        return self._background
    end
    local sceneBg = Director:getRunningScene():getChildByTag(m_bgTag)
    if sceneBg then
        self._background = sceneBg
        return sceneBg
    end
    self._background = cc.LayerColor:create(cc.c4b(188, 135, 24, 100))
    Director:getRunningScene():addChild(self._background)
    self._background:setLocalZOrder(1)
    self._background:setTag(m_bgTag)
    return self._background
end

function M:_removeEditBox()
    if self._editBox then
        self._editBox:removeFromParent()
        self._editBox = nil
    end
end

function M:_setEditBoxVisible(visible)
    if not self._editBox then
        self:_createEditBox()
    end
    if visible == self._background.visible then
        return
    end
    self._background.visible = visible
    self._background:setVisible(visible)
    self._editBox:setVisible(visible)
end

return M
