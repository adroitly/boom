local RichBase = require("ui.common.richlabel.ElementBase")
local M = class("ui.common.richlabel.ElementSprite", function(config, parent)
	return RichBase.new(config, parent)
end)


function M:createSprite(fileName)
	return M.new(self:_getSpriteConfig(fileName))
end

function M:ctor(config, parent)
	self.parent = parent
	if nil ~= config then
		Table:copy(self, config)
	end
end

function M:getSpriteFile()
	return self.spriteFile
end

function M:_getSpriteConfig(fileName)
	return {
				richType = Enum.RichType.Image,
				spriteFile = fileName
			}
end

return M