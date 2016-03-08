local RichBase = require("ui.common.richlabel.ElementBase")
local M =  class("ui.common.richlabel.ElementText", function(config, parent)
	return RichBase.new(config, parent)
end)


function M:createLabel(text, fontSize, color, fontName, strokeColor, strokeSize)
	return M.new(self:_getLabelConfig(text, fontSize, color, fontName, strokeColor, strokeSize))
end

-- 是否有下划线
function M:setUnderLine(boolean)
	self.underline = boolean
end

function M:getUnderLine()
	return self.underline == true
end

function M:ctor(config, parent)
	self.parent = parent
	if nil ~= config then
		Table:copy(self, config)
	end
end

function M:_getLabelConfig(text, fontSize, color, fontName)
	return {
				richType = Enum.RichType.Label,
				text = text,
				fontSize = fontSize,
				color = color,
				fontName = fontName
			}
end

return M