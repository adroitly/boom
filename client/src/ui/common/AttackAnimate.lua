
local M = {}

function M:attackAnimate(node, attackPosition)
	local x, y = node:getPosition()

	local seq = Action:Sequence().moveTo(0.2, attackPosition).moveTo(0.2, cc.p(x, y) )
	seq.run(node)
end

return M

