
local M = class("ui.common.PopBlood", function()
	return cc.Node:create()
end)

local function _getSize(size)
    if size.width < 1 then
    	size.width = 1
    end
	if size.height < 1 then
    	size.height = 1
    end
    return size
end

function M:_initWithNumber(number)
	local text = string.format("%d", number)
	local label = CommonUI:createLabel(text, 30)
	self:addChild(label)

	local callback = function()
		self:removeFromParent()
	end

	Action:Sequence().moveBy(0.6, cc.p(0, 60)).callFunc(callback).run(self)
end

function M:popBlood(withNode, number)
	assert(withNode)
	local node = M.new()
	withNode:addChild(node)
	local size = withNode:getContentSize()
	size = _getSize(size)
	node:setPosition(cc.p(math.random(size.width), math.random(size.height)))

	node:_initWithNumber(number)
end

return M