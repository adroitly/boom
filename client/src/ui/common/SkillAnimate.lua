local SkillConfigReader = require("config-reader.SkillConfigReader")
local M = class("ui.common.SkillAnimate", function()
	return cc.Node:create()
end)

function M:_initWithSkillId(skillId)
	local name = SkillConfigReader:getName(skillId)

	local label = CommonUI:createLabel(name, 40)
	self:addChild(label)
	
	local callback = function()
		self:removeFromParent()
	end

	Action:Sequence().moveBy(1.0, cc.p(0, 100)).callFunc(callback).run(self)
end

function M:action(parent, skillId)
	assert(parent)
	local node = M.new()
	parent:addChild(node)
	local size = parent:getContentSize()
	node:setPosition(cc.p(size.width/2, size.height/2))

	node:_initWithSkillId(skillId)
end

return M