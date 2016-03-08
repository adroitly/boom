local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.hero-museum.MainLayer", function()
	return cc.Layer:create()
end)


local m_buttonEnum = {
	Nomal = 1,
	High  = 2
}
local function _getLayers()
	return {
				require("ui.hero-museum.layers.AlcoholLayer"),
				require("ui.hero-museum.layers.SeekHeroLayer"),
				require("ui.hero-museum.layers.RecruitHeroLayer"),
				require("ui.hero-museum.layers.HeroDoctorLayer"),
				require("ui.hero-museum.layers.UpgradeHeroLayer"),
}
end

local function _getButtonsInfo()
	local nomal = "ui/login/login-up.png"
	local high = "ui/login/login-down.png"
	local infos = {
				{ nomal, high, high, "对酒", },
				{ nomal, high, high, "求贤", },
				{ nomal, high, high, "招将", },
				{ nomal, high, high, "医馆", },
				{ nomal, high, high, "升星", },
			}
	return infos
end

function M:ctor()
	self:_createBackground()
	self:_createButtons()
end

function M:updateBuildindId(buildingId)
	self._buildingId = buildingId
end

function M:_checkUpdateLayerBuildingId(layer)
	if self._buildingId and layer.updateBuildindId then
		layer:updateBuildindId(self._buildingId)
	end
end

function M:_createButtons()
	local buttonsInfo = _getButtonsInfo()
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
			local layer = layers[index].new()
			layer:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
			loadLayers[clickIndex] = layer
			self:_checkUpdateLayerBuildingId(layer)
			self:addChild(loadLayers[clickIndex])
		end
	end
	self:addChild(buttonsLayer)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("名将"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
		CommonUI:showLoadingLayer(false)
	end)
end

return M