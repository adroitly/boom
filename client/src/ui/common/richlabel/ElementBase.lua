local M = class("ui.common.richlabel.ElementBase")

local m_fontName    = "STHeitiSC-Medium"
local m_textColor   = cc.c4b(255, 255, 255, 255)
local m_strokeColor = cc.c4b(0, 0, 0, 255)
local m_strokeSize  = 3

function M:ctor(config, parent)
	self.parent = parent
	if nil ~= config then
		Table:copy(self, config)
	end
end

function M:getRichType()
	return self.richType
end

function M:getStrokeColor()
	return self.strokeColor or m_strokeColor
end

function M:getStrokeSize()
	return self.strokeSize or m_strokeSize
end

function M:getColor()
	return self.color or m_textColor
end

function M:getText()
	return self.text
end
function M:getFontName()
	return self.fontName or m_fontName
end

function M:getFontSize()
	return self.fontSize or 24
end

function M:updateText(text)
	self.text = text
end

function M:getParent()
	return self.parent
end

return M