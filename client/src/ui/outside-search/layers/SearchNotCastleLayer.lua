local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.outside-search.layers.SearchNotCastleLayer", function()
	return cc.Layer:create()
end)

function M:ctor(buildingSearchData)
	self:_createBackground(buildingSearchData)
	self:_createUserInfoLayer(buildingSearchData)
	self:_createBuildingOutputInfoNode(buildingSearchData)
	self:_createBuildingDefenceNodes(buildingSearchData)
	self:_createDefenceCityInfoScrolView(buildingSearchData)
end

function M:_createUserInfoLayer(buildingSearchData)
	local userInfoLayer = require("ui.outside-search.layers.HeroInfosLayer").new(buildingSearchData)
	self:addChild(userInfoLayer)
	userInfoLayer:setPosition(cc.p(0, Screen.height - userInfoLayer:getContentSize().height -  BackgroundLayer.TitleHeight))
end

function M:_createBuildingOutputInfoNode(buildingSearchData)
	local buildingOutputInfo = require("ui.outside-search.layers.BuildingOutputInfoScrollView").new(buildingSearchData)
	buildingOutputInfo:setPosition(cc.p(0, Screen.height * 0.5))
	self:addChild(buildingOutputInfo)
end

function M:_createBuildingDefenceNodes(buildingSearchData)
	local defenceSprite = CommonUI:createTextSprite(self, "ui/team/ui-un-0015.png", __Localized("驻扎部队"), 24)
	local spriteSize = defenceSprite:getContentSize()
	defenceSprite:setPosition(cc.p(Screen.width / 2, Screen.height / 2 - spriteSize.height))
	
	self._buildingDefenceLayer = require("ui.outside-search.layers.BuildingDefenceLayer").new(buildingSearchData)
	self:addChild(self._buildingDefenceLayer)
end

function M:_createDefenceCityInfoScrolView(buildingSearchData)
	local cityInfoScrollView = require("ui.outside-search.layers.CityInfoScrollView").new(buildingSearchData)
	self:addChild(cityInfoScrollView)

	local defenceX, defenceY = self._buildingDefenceLayer:getPosition()
	local defenceSize = self._buildingDefenceLayer:getContentSize()
	local cityInfoScrollViewSize = cityInfoScrollView:getContentSize()
	cityInfoScrollView:setPosition(cc.p(defenceX, defenceY + defenceSize.height / 2 + cityInfoScrollViewSize.height / 2))
end

function M:_createBackground(buildingSearchData)
	local buildingData = buildingSearchData:getBuildingData()
	local buildingId = buildingData:getBuildingId()
	local homeCoor = buildingData:getHomeCoor()
	local twoCoor = MapConfig:localTo2D(homeCoor)
	local buildingName = BuildingConfigReader:getName(buildingId)
	local text = string.format("%s(%d,%d)", buildingName, twoCoor.i, twoCoor.j)
	local background = BackgroundLayer.new(self, text)
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M