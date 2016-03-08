local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local ResourcePointConfigReader = require("ui.produce.data-manager.ResourcePointConfigReader")
local CampConfigReader = require("ui.produce.data-manager.CampConfigReader")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local MapConfig = require("ui.map.data-manager.MapConfig")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.outside-search.layers.NoPlayerBuildingInfoLayer", function()
	return cc.Layer:create()
end)

function M:ctor(buildingSearchData)
	local buildingData = buildingSearchData:getBuildingData()
	self:_createBackground(buildingData)
	self:_createProductNode(buildingSearchData)
	self:_checkIsFamous(buildingData)
end

function M:_checkIsFamous(buildingData)
	local buildingId = buildingData:getBuildingId()
	local buildingType = BuildingConfigReader:getBuildingType(buildingId)
	if buildingType == Enum.BuildingType.FamousCity then
		self:_createDefenseLabel(buildingData)
	else
		self._buildingOutputInfo:setPosition(cc.p(0, Screen.height / 2))
	end
end

function M:_createDefenseLabel(buildingData)
	local showText = string.format(__Localized("城 防:%d"), buildingData:getCityDef())
	self._defenseLabel = CommonUI:createLabel(showText, 24)
	self:addChild(self._defenseLabel)
	self._defenseLabel:setPosition(cc.p(Screen.width / 2, Screen.height * 0.75))
end

function M:_createProductNode(buildingSearchData)
	self._buildingOutputInfo = require("ui.outside-search.layers.BuildingOutputInfoScrollView").new(buildingSearchData)
	self._buildingOutputInfo:setPosition(cc.p(0, Screen.height / 4))
	self:addChild(self._buildingOutputInfo)
end


function M:_createBackground(buildingData)
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