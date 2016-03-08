local RichBase = require("ui.common.richlabel.ElementBase")
local M = class("ui.common.richlabel.ElementTextButton", function(config, parent)
	return RichBase.new(config, parent)
end)


function M:createTextButton(richBaseLabel, nomal, height)
	return M.new(self:_getTextButtonConfig(richBaseLabel, nomal, height))
end

function M:ctor(config, parent)
	self.parent = parent
	if nil ~= config then
		Table:copy(self, config)
	end
end
function M:getNomal()
	return self.nomal
end

function M:getHigh()
	return self.high
end

function M:_getTextButtonConfig(richBaseLabel, nomal, height)
	local base = M.new()
	Table:copy(base, richBaseLabel)
	base.richType = Enum.RichType.TextButton
	base.nomal = nomal
	base.height = height
	return base
end

return M