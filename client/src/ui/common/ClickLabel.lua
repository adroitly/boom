local M = class("ui.common.ClickLabel.ClickLabel", function()
	return cc.Label:create()
end)

local m_fontName    = "STHeitiSC-Medium"
local m_textColor   = cc.c4b(255, 255, 255, 255)
local m_strokeColor = cc.c4b(0, 0, 0, 255)
local m_strokeSize  = 3

function M:ctor(text, fontSize)
	self:setSystemFontName(m_fontName)
	self:setSystemFontSize(fontSize or 24)
	self:setString(text)
	self:registerTouchOneByOne(false)
	self:setHorizontalAlignment(1)
	self._contentSize = self:getContentSize()
    self:enableOutline(m_strokeColor, m_strokeSize)
end

function M:setFontName(fontName)
	assert(fontName)
	self:setSystemFontName(fontName)
end

function M:setFontSize(fontSize)
	assert(fontSize)
	self:setSystemFontSize(fontSize)
end

function M:registerTouchOneByOne(swallow)
	Touch:removeTouchOneByOne(self)
	Touch:registerTouchOneByOne(self,swallow)
end

function M:onTouchBegan(touch, event)
	local hitt = Touch:isTouchHitted(self, touch, 0)
	return hitt
end

function M:onTouchEnded(touch, event)
	local hitt = Touch:isTouchHitted(self, touch, self._contentSize.height * 0.5)
	if hitt and self.onClicked then
		self:onClicked()
	end
end

function M:onTouchMoved(touch, event)
end

function M:onTouchCancelled(touch, event)
end

return M