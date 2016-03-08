local M = class("ui.backpack.layer-manager.IconButton",  function(normalImageFile, highlightImageFile)
	return ButtonText.new(normalImageFile, highlightImageFile)
end)

function M:setupClick(callBack)
	self.onClicked = callBack
end

function M:newIconButton()
	local nomalName = "ui/backpack/uibtn.png"
	local highName = "ui/backpack/uibtn.png"
	local button = M.new(nomalName, highName)
	button.onClicked = function()
		button:_backpackItemDetail()
	end
	return button
end

-- 根据id reload
function M:reloadData(backpackId)
	self._backpackId = backpackId
	local nomalIcon = self:_getButtonNomalIcon(backpackId)
	local normalSprite = ccui.Scale9Sprite:create(nomalIcon)
	self:setBackgroundSpriteForState(normalSprite, cc.CONTROL_STATE_NORMAL)

	local highIcon = self:_getButtonHighIcon(backpackId)
	local highligtedSprite = ccui.Scale9Sprite:create(highIcon)
	self:setBackgroundSpriteForState(highligtedSprite, cc.CONTROL_STATE_HIGH_LIGHTED)
end

function M:_backpackItemDetail()
	local backpackDetailLayer = require("ui.backpack.layer-manager.GoodsDetailLayer").new()
	backpackDetailLayer:reloadData(self._backpackId)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(backpackDetailLayer)
end

function M:_getButtonNomalIcon(id)
	local iconName = "ui/backpack/uibtn.png"
	return iconName
end

function M:_getButtonHighIcon(id)
	local iconName = "ui/backpack/uibtn.png"
	return iconName
end

return M