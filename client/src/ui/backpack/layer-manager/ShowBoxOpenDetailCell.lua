local ItemDataFrame = require("ui.backpack.data-manager.ItemDataFrame")
local M = class("ui.backpack.layer-manager.ShowBoxOpenDetailCell", function()
	return GridViewCell.new()
end)

M.ShowBoxOpenDetailCellSize = cc.size(Screen.width, 200)

function M:ctor()
	self:_createSprite()
	self:_createNumberLabel()
end

function M:reload(packageItemData)
	self._packageItemData = packageItemData
	if nil == packageItemData then
		return
	end
	self:_updateSprite()
	self:_updateNumberLabel()
end

function M:_updateSprite()
	local resourceId = self._packageItemData:getResourceId()
	local itemType = self._packageItemData:getType()
	local spriteFrame = ItemDataFrame:getSpriteFrame(resourceId, itemType)
	self._sprite:setSpriteFrame(spriteFrame)
end

function M:_updateNumberLabel()
	local number = self._packageItemData:getNumber()
	local showText = string.format("X%d", number)
	self._numberLabel:setString(showText)
end

function M:_createSprite()
	self._sprite = cc.Sprite:create("ui/test.png")
	self:addChild(self._sprite)
	self._sprite:setPosition(cc.p(0, self._sprite:getContentSize().height / 2))
end

function M:_createNumberLabel()
	self._numberLabel = CommonUI:createLabel("X100", 24)
	self._sprite:addChild(self._numberLabel)
	Layout:layout(self._numberLabel, self._sprite:getContentSize(), Layout.center_bottom)
end

return M