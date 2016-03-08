local BackpackButton = require("ui.backpack.layer-manager.BackpackButton")
local ShowBoxOpenDetailCell = require("ui.backpack.layer-manager.ShowBoxOpenDetailCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.backpack.layer-manager.ShowBoxOpenDetailLayer", function()
	return cc.Layer:create()
end)

function M:ctor(packageItemDataList)
	self._packageItemDataList = packageItemDataList
	self:_init()
end

function M:_init()
	self:_createBackground()
	self:_createGridView()
	self:_createExitButton()
end

function M:onGridViewCellCount()
	return table.getn(self._packageItemDataList)
end

function M:onGridViewLineHeight()
	return ShowBoxOpenDetailCell.ShowBoxOpenDetailCellSize.height
end

function M:onGridViewCellAtIndex(pageView, idx)
	local cell = pageView:dequeueCell()
	if nil == cell then
		cell = ShowBoxOpenDetailCell.new()
	end

	cell:reload(self._packageItemDataList[idx + 1])
	return cell
end

function M:_createGridView()
	local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
	local gridView = GridView.new(viewSize, self, 4)
	self:addChild(gridView)
	gridView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
end

function M:_showDetail(index, resourceFileName)
	local packageItemData = self._packageItemDataList[index]
	local sprite = self:_createSprite(index, resourceFileName,packageItemData:getType())
	self:_createNumberLabel(sprite, packageItemData:getNumber())
end

function M:_createExitButton()
	local button = CommonUI:createTextButton(self, "确定", "ui/login/login-button.png")
	Layout:layout(button, Screen.size, Layout.center_bottom)
	button.onClicked = function()
		self:removeFromParent()
	end
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("恭喜获得"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M