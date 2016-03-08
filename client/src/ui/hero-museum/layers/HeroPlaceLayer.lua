local BackgroundLayer = require("ui.common.BackgroundLayer")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local M = class("ui.hero-museum.layers.HeroPlaceLayer", function()
	return cc.Layer:create()
end)

local kCityBuildingInfoGet = "city_building_info_get"

function M:ctor()
	self:_createBackground()
	self._buildingDataList = {}
	self:_createHomeBuildingButton()
	self:_createGridView()
	Event:registerNodeEvent(self)
end

function M:onClicked(func)
	self._callbackFunc = func
end

function M:getBuildingsId()
	return self._buildingDataList
end

function M:getBuildingDataList()
	return self._buildingDataList
end

function M:onHeroPlaceCellDidBack(buildingData)
	self._callbackFunc(buildingData)
	self:removeFromParent()
	CommonUI:showLoadingLayer(false)
end

function M:onExit()
	SocketManager:removeObserver(self)
end

function M:onEnterTransitionFinish()
	SocketManager:addObserver(self)
	self:_getBuildingsData()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if kCityBuildingInfoGet == cmd then
		assert(msgTable and msgTable.buildingInfos)
		CommonUI:showLoadingLayer(false)
		self:_reload(msgTable.buildingInfos)
	end
		
end

function M:_getBuildingsData()
	local guildId = PlayerData:getGuildId()
	if 0 == guildId then
		return
	end
	local sendData = {guild_id = guildId}
	SocketManager:send(kCityBuildingInfoGet, sendData)
	CommonUI:showLoadingLayer(true)
end

function M:_createHomeBuildingButton()
	local button = CommonUI:createTextButton(self, __Localized("主城"), "ui/login/login-button.png")
	local buttonSize = button:getContentSize()
	button:setPosition(cc.p(buttonSize.width / 2, Screen.height - BackgroundLayer.TitleHeight - buttonSize.height / 2))
	button.onClicked = function()
		local castleBuildingData = PlayerData:getCastleBuildingData()
		self:onHeroPlaceCellDidBack(castleBuildingData)
	end
end

function M:_reload(buildingDataList)
	local BuildingData = require("ui.map.data-manager.BuildingData")
	for _, value in pairs(buildingDataList) do
		local uniqueId = Utils:getUniqueId(value.x, value.y)
		local buildingData = BuildingData.new(value, uniqueId)
		table.insert(self._buildingDataList, buildingData)
	end
	self._gridView:reloadData()
end

function M:_createGridView()
	local pageViewSize = cc.size(
		Screen.width, 
		Screen.height - BackgroundLayer.TitleHeight * 2
		)
	self._gridView = GridView.new(pageViewSize, self, 3)
	self:addChild(self._gridView)
end


function M:onGridViewLineHeight(pageView)
	return 100
end

function M:onGridViewCellAtIndex(pageView, idx)
	local cell = pageView:dequeueCell()
	if not cell then
		cell = require("ui.hero-museum.layers.HeroPlaceLayerCell").new(self)
	end
	cell:reload(self._buildingDataList[idx + 1])
    return cell
end

function M:onGridViewCellCount(pageView)
	return table.getn(self._buildingDataList)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("名城选择"))
	background:setBackButtonCallback(function()
		CommonUI:showLoadingLayer(false)
		self:removeFromParent()
	end)
end

return M