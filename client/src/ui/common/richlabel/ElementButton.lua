local RichBase = require("ui.common.richlabel.ElementBase")
local M = class("ui.common.richlabel.ElementButton", function(config, parent)
	return RichBase.new(config, parent)
end)

function M:createButton(nomal, high)
	return M.new(self:_getButtonConfig(nomal, height))
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

function M:_getButtonConfig(nomal, high)
	return {
				richType = Enum.RichType.Button,
				nomal = nomal,
				height = height
			}
end

return M