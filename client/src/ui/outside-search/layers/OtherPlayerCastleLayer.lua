local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.outside-search.layers.OtherPlayerCastleLayer", function()
	return cc.Layer:create()
end)

function M:ctor(buildingSearchData)
	self:_createBackground(buildingSearchData)
	self:_createUserInfoLayer(buildingSearchData)
	self:_createBuildingDefenceLayer(buildingSearchData)
	self:_createCityInfoScrollView(buildingSearchData)
end

function M:_createUserInfoLayer(buildingSearchData)
	local userInfoLayer = require("ui.outside-search.layers.HeroInfosLayer").new(buildingSearchData)
	self:addChild(userInfoLayer)
	userInfoLayer:setPosition(cc.p(0, Screen.height - userInfoLayer:getContentSize().height -  BackgroundLayer.TitleHeight))
end

function M:_createBuildingDefenceLayer(buildingSearchData)
	local buildingDefenceLayer = require("ui.outside-search.layers.BuildingDefenceLayer").new(buildingSearchData)
	self:addChild(buildingDefenceLayer)
	buildingDefenceLayer:setPosition(cc.p(0,BackgroundLayer.BottomHeight))
end

function M:_createCityInfoScrollView(buildingSearchData)
	local cityInfoScrollView = require("ui.outside-search.layers.CityInfoScrollView").new(buildingSearchData)
	cityInfoScrollView:setPosition(cc.p(0, Screen.height * 0.5))
	self:addChild(cityInfoScrollView)
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