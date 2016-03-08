local SuperClass = ccui.TextField
local M = class("ui.common.TextInput", function()
    return SuperClass:create()
end)

-- 转换为中文占2，英文占1（在UTF8中中文占3，英文占1）
-- 根据限制长度返回最终字符串
local function _cutString(str, length)
    local realString = ""
    local realLength = 0
    local lenInByte = #str
    local i = 1
    while true do
        if i > lenInByte then
            realString = str
            break
        end
        local curByte = string.byte(str, i)
        local byteCount = 1
        -- 中文byte > 127， 并占3个字节
        if curByte > 0 and curByte <= 127 then
            byteCount = 1
            realLength = realLength + 1
        else
            byteCount = 3
            realLength = realLength + 2
        end
        if length ~= 0 and realLength > length then
            realString = string.sub(str, 1, i - 1)
            break
        end
        i = i + byteCount
    end
    return realString
end

local kShowLabelTag = 255
local kDefaultWidth = 90

function M:ctor(fontSize)
    self._maxLength = 0
    self._isAttach = false
    self:setFontSize(fontSize)
    self:setFontName("STHeitiSC-Medium")
    self:setTextColor(cc.c4b(0, 0, 0, 255))
    self:_setupListener()
    self:_createCursor()
    self:setPlaceHolder("请输入内容")
    self:setTouchEnabled(false)

    Touch:registerTouchOneByOne(self, true)
    Event:registerNodeEvent(self)   
end

function M:onExit()
    self:detachWithIME()
    if self:_isShowLabelShow() then
        self:_getShowLabel():setVisible(false)
    end
end

function M:setString(str)
    local cutString = _cutString(str, self._maxLength)
    local realString, size = self:_convertString(cutString)
    SuperClass.setString(self, realString)
    self:_updateCursorPosition(size.width, size.height * 0.5)
    if realString == "" then
        -- 当内容为空时，调整光标位置
        local realString, size = self:_convertString(" ")
        self:_updateCursorPosition(size.width, size.height * 0.5)
    end
    self:_setShowString(realString)
end

-- 中文占两个字符，英文占3个字符
function M:setMaxLength(maxLength)
    assert(maxLength)
    self._maxLength = maxLength
end

function M:setTextWidth(width)
    assert(width)
    self._textWidth = width
end

function M:setTouchSize(size)
    self._touchSize = size
end

function M:onTouchBegan(touch, event)
    if not self:isEnabled() then
        return false
    end
    local isHit = self:_isHitTest(touch)
    if isHit then
        self:attachWithIME()
    else
        self:detachWithIME()
    end
    return isHit
end

function M:onTouchMoved(touch,event)
end

function M:onTouchEnded(touch,event)
end

function M:onTouchCancelled(touch,event)
end

function M:setDetachIMECallback(callback)
    self._detachCallback = callback
end

function M:_isHitTest(touch)
    local pt = touch:getLocation()
    pt = self:getParent():convertToNodeSpace(pt)
    local posX, posY = self:getPosition()
    local anchorPoint = self:getAnchorPoint()
    local touchSize
    if self._touchSize then
        touchSize = self._touchSize
    else
        touchSize = self:getContentSize()
        touchSize.width = touchSize.width > kDefaultWidth and touchSize.width or kDefaultWidth
    end
    posX = posX - anchorPoint.x * touchSize.width
    posY = posY - anchorPoint.y * touchSize.height
    local rt = cc.rect(posX, posY, touchSize.width, touchSize.height)
    return cc.rectContainsPoint(rt, pt)
end

function M:onAttachWithIME()
    self._isAttach = true
    self:_updateString()
end

function M:onDetachWithIME()
    self:_getShowLabel():setVisible(false)
    self._isAttach = false
    if self._detachCallback then
        self._detachCallback()
    end
end

function M:onInsertText()
    self:_updateString()
end

function M:onDeleteBackward()
    self:_updateString()
end

function M:detachWithIME()
    self:didNotSelectSelf()
end

function M:_createCursor()
    local height = self:getFontSize()
    self._cursor = cc.DrawNode:create() 
    self._cursor:drawLine(cc.p(0, 0), cc.p(0, height), cc.c4f(1, 1, 1, 1))
    self._cursor:setContentSize(cc.size(2, height)) 
    self._cursor:setAnchorPoint(cc.p(0, 0.5))
    self:addChild(self._cursor) 
    -- 闪烁
    local seq = Action:Sequence()
        .delayTime(0.6)
        .callFunc(function()
            self._cursor:setVisible(self._isAttach)
        end)
        .delayTime(1) 
        .callFunc(function()
            self._cursor:setVisible(false)
        end)
    local rep = cc.RepeatForever:create(seq.raw)
    self._cursor:runAction(rep)
    self._cursor:setVisible(false)
end

function M:_updateCursorPosition(x, y)
    self._cursor:setPosition(cc.p(x, y))
end

function M:_updateString()
    self:setString(self:getString())
end

function M:_convertString(str)
    -- 移除换行符
    local convertStr = string.gsub(str, "\n", "")
    local realString = ""
    local fontSize = self:getFontSize()
    local fontName = self:getFontName()
    local tempLabel = cc.Label:create()
    tempLabel:setSystemFontSize(fontSize)
    tempLabel:setSystemFontName(fontName)
    local size = cc.size(0, 0)
    local tempStr = ""
    for uchar in string.gfind(convertStr,"[%z\1-\127\194-\244][\128-\191]*") do
        tempStr = tempStr .. uchar
        tempLabel:setString(tempStr)
        size = tempLabel:getContentSize()
        if self._textWidth and size.width > self._textWidth then
            tempLabel:setString(uchar)
            size = tempLabel:getContentSize()
            realString = realString .. "\n"
            tempStr = uchar
        end
        realString = realString .. uchar
    end
    return realString, size
end

function M:_setupListener()
    local event_types = {
        [ccui.TextFiledEventType.attach_with_ime] = "onAttachWithIME",
        [ccui.TextFiledEventType.detach_with_ime] = "onDetachWithIME",
        [ccui.TextFiledEventType.insert_text] = "onInsertText",
        [ccui.TextFiledEventType.delete_backward] = "onDeleteBackward",
    }
    local function eventHandler(textField, eventType)
        local funcName = event_types[eventType] 
        self[funcName](self) 
    end
    SuperClass.addEventListener(self, eventHandler)
end

function M:_setShowString(str)
    local label = self:_getShowLabel()
    label:setString(str)
    label:setVisible(true)
end

function M:_getShowLabel()
    local scene = cc.Director:getInstance():getRunningScene()
    local label = scene:getChildByTag(kShowLabelTag)
    if not label then
        label = CommonUI:createLabel("")
        scene:addChild(label, kShowLabelTag)
        label:setTag(kShowLabelTag)
        label:setPosition(cc.p(Screen.width / 2, Screen.height - 140))
    end
    return label
end

function M:_isShowLabelShow()
    local scene = cc.Director:getInstance():getRunningScene()
    local label = scene:getChildByTag(kShowLabelTag)
    return label and true or false
end

return M