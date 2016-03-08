local BackgroundLayer = require("ui.common.BackgroundLayer")
local IconButton = require("ui.backpack.layer-manager.IconButton")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")

local M = class("ui.backpack.layer-manager.GoodsDetailLayer", function()
	return cc.Layer:create()
end)

function M:reloadData(backpackId)
	local name = BackpackConfigRead:getName(backpackId)
	local desc = BackpackConfigRead:getDesc(backpackId)

	local button = IconButton:newIconButton()
	button:reloadData(backpackId)
	button:setupClick(nil)
	local buttonSize = button:getContentSize()
	local PosiX = Screen.width / 2
	local PosiY = Screen.height - BackgroundLayer.TitleHeight - buttonSize.height / 2
	button:setPosition(PosiX, PosiY)
	self:addChild(button)

	self._dataDescLabel:setString(desc)
	self._dataNameLabel:setString(name)
end

function M:ctor()
	self:_createBackground()
	self:_createDataNameLabel()
	self:_createDataDescLabel()
end

function M:_createDataNameLabel()
	self._dataNameLabel = CommonUI:createLabel("TEST")
	self._dataNameLabel:setPosition(Screen.width / 2, Screen.height / 2)
	self:addChild(self._dataNameLabel)
end

function M:_createDataDescLabel()
	self._dataDescLabel = CommonUI:createLabel("TEST")
	self._dataDescLabel:setDimensions(Screen.width,100)
	self._dataDescLabel:setAnchorPoint(0, 0.5)
	local labelSize = self._dataDescLabel:getContentSize()
	self._dataDescLabel:setPosition(0, Screen.height / 2 - labelSize.height)
	self:addChild(self._dataDescLabel)
end

function M:_createBackground()
	local backgroundLayer = BackgroundLayer.new(self, __Localized("物品详情"))
	backgroundLayer:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end


return M