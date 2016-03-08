local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.backpack.MainLayer", function()
	return cc.Layer:create()
end)

local function _getLayers()
	return {
				require("ui.backpack.layer-manager.BackpackLayer"),
				require("ui.backpack.layer-manager.BackpackHeroListLayer")
			}
end

local function _getButtonsInfos()
	local nomal = "ui/login/login-up.png"
	local high = "ui/login/login-down.png"
	local infos = {
					{ nomal, high, high, "道具"},
					{ nomal, high, high, "英雄"}
			}
	return infos
end

function M:ctor()
	self:_createBackground()
	self:_createButtons()
end

function M:_createButtons()
	local buttonsInfo = _getButtonsInfos()
	local layers = _getLayers()
	local buttonsLayer = ButtonRadioLayer.new(buttonsInfo)
	buttonsLayer:setLayout(cc.size(Screen.width, BackgroundLayer.TitleHeight))
	local loadLayers = {}
	local clickIndex = 0
	local contentSize = buttonsLayer:getContentSize()
	buttonsLayer:setPosition(cc.p(0, 0))
	buttonsLayer.onClicked = function(node, index)
		index = index + 1
		if nil ~= loadLayers[clickIndex] then
			loadLayers[clickIndex]:setVisible(false)
		end
		if nil ~= loadLayers[index] then
			loadLayers[index]:setVisible(true)
			clickIndex = index
		else
			clickIndex = index
			loadLayers[clickIndex] = layers[index].new()
			self:addChild(loadLayers[clickIndex])
		end
		
	end
	self:addChild(buttonsLayer)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("背包"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end


return M