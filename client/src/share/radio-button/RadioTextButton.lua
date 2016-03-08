local RadioButton = require("share.radio-button.RadioButton")
local M = class("share.radio-button.RadioTextButton", RadioButton)

function M:ctor(text, normalName, selectedName)
    RadioButton.init(self, normalName, selectedName)
    self:_initWithText(text)
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

function M:_initWithText(text)
    self._textLabel = CommonUI:createLabel(text, 30)
    self._textLabel:setLocalZOrder(1)
    self:addChild(self._textLabel)
    Layout:layout(self._textLabel, self:getContentSize(), Layout.center)
end

return M