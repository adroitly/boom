--[[
    * 描述：带文字显示按钮
    * 其他：参考Button
--]]
local SuperClass = require("libs.widget.Button")
local M = class("libs.widget.ButtonText", function(normalImageName, highligtedImageName, disabledImageName)
	return SuperClass.new(normalImageName, highligtedImageName, disabledImageName)
end)

--[[
    * 描述：统一创建文字按钮的默认参数配置，设置一次即可
    * 参数strokeColor：描边颜色
    * 参数strokeSize：描边大小，int类型
--]]
local m_fontName    = "STHeitiSC-Medium"
local m_textColor   = cc.c4b(255, 255, 255, 255)
local m_strokeColor = cc.c4b(0, 0, 0, 255)
local m_strokeSize  = 3
function M:setDefalutConfig(fontName, textColor, strokeColor, strokeSize)
    assert(fontName and textColor and strokeColor and strokeSize)
    m_fontName      = fontName
    m_textColor     = textColor
    m_strokeColor   = strokeColor
    m_strokeSize    = strokeSize
end

function M:setLabel(text, fontSize)
    if not self._textLabel then 
        local label = cc.Label:create()
        label:setSystemFontName(m_fontName)
        label:setTextColor(m_textColor)
        label:enableOutline(m_strokeColor, m_strokeSize)
        label:setHorizontalAlignment(1)
        local size = self:getContentSize()
        label:setPosition(cc.p(size.width/2, size.height/2))
        self:addChild(label)
        self._textLabel = label
        self._textLabel:setLocalZOrder(1)
    end

    self._textLabel:setString(text)
    self._textLabel:setSystemFontSize(fontSize and fontSize or 30)
end

function M:setContentSize(size)
    SuperClass.setContentSize(self, size)

    if self._textLabel then 
        self._textLabel:setPosition(cc.p(size.width/2, size.height/2))
    end
end

function M:getLabel()
    return self._textLabel
end

function M:getText()
    return self._textLabel:getString()
end

function M:setText(text)
    self._textLabel:setString(text)
end

function M:setTextColor(color)
    self._textLabel:setTextColor(color)
end

function M:setSystemFontSize(size)
    self._textLabel:setSystemFontSize(size)
end

return M


