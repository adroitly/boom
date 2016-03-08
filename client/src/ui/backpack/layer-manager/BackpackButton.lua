
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.backpack.layer-manager.BackpackButton", function(normalImageFile)
	return Button.new(normalImageFile)
end)

-- 新建一个空button
function M:newIconButton()
	local nomalName = "ui/backpack/uibtn.png"
	local button = M.new(nomalName)
	button:_createBackground()
	button:_createCountLabel()
	button:setSwallowTouches(false)
	button.onClicked = function()
		button:_buttonClick()
	end
	return button
end

-- 根据背包数据reload
function M:reloadData(backpackData)
	self._backpackData = backpackData

	if nil == backpackData then
		self._countLabel:setString("")
		self:setVisible(false)
		return
	end
	self:setVisible(true)
	local backpackId = self:_getBackPackItemType()
	self:_updateIcon(backpackId)
	local count = backpackData:getItemNumber()
	self._countLabel:setString(count)

end

function M:reloadByBackpackId(backpackId)
    self:_updateIcon(backpackId)
end

function M:_updateIcon(backpackId)
	local nomalIcon = self:_getButtonNomalIcon(backpackId)
	if nomalIcon then
		self:changeNormalSpriteWithFrame(nomalIcon)	
	else
		self:changeNormalSprite(self:_getNullIcon())
	end
end

function M:_getBackPackItemType()
	local itemID = self._backpackData:getItemType()
	return itemID
end

function M:_createCountLabel()
	self._countLabel = CommonUI:createLabel("1000", 26)
	local countLabelSize = self._countLabel:getContentSize()
	local buttonSize = self:getContentSize()
	self._countLabel:setPosition(buttonSize.width - countLabelSize.width / 2, countLabelSize.height / 2)
	self._countLabel:setString("")
	-- 记得设置这个最前面，不然重新设置背景图片会掩盖他
	self._countLabel:setLocalZOrder(1)
	self:addChild(self._countLabel)
end
function M:_buttonClick()
	if nil == self._backpackData then
		return
	end
	local layer = require("ui.backpack.layer-manager.BackpackDetailLayer").new(self:_getBackPackItemType())
	layer:setAllButtons()
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_createBackground()
	local background = cc.Sprite:create("ui/backpack/backpack-item-bg.png")
	local backgroundCheek = cc.Sprite:create("ui/backpack/backpack-item-cheek.png")
	backgroundCheek:setLocalZOrder(1)
	self:addChild(backgroundCheek)
	local contentSize = self:getContentSize()
	background:setPosition(cc.p(contentSize.width / 2, contentSize.height / 2))
	backgroundCheek:setPosition(cc.p(contentSize.width / 2, contentSize.height / 2))
	self:addChild(background)
end

function M:_getButtonNomalIcon(id)
	local iconName = string.format("%d.png", id)
	return CommonUI:createSpriteFrameTinyName("stage-icon",iconName)
end

function M:_getNullIcon()
	local iconName = "ui/backpack/uibtn.png"
	return iconName
end

function M:_getButtonHighIcon(id)
	local iconName = "ui/backpack/uibtn.png"
	return iconName
end

return M