
local M = class("ui.common.LightTips", function(text)
	return cc.Layer:create()
end)

function M:ctor(text)
	local background = cc.Sprite:create("ui/mail/mail-input.png")
	background:setPosition(Screen.center)
	self:addChild(background)
	
	local label = CommonUI:createLabel(text, 30)
	label:setPosition(Screen.center)
	label:setTextColor(cc.c4b(0, 0, 0, 255))
	self:addChild(label)

	Action:Sequence().fadeOut(1.5).callFunc(function()
		self:removeFromParent()
	end).run(self)
end

function M:lightTips(text)
	local node = M.new(text)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(node)
end

return M