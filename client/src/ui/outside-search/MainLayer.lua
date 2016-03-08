local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local OtherPlayerData = require("ui.user-info.datas.OtherPlayerData")
local ArmyData = require("ui.map.data-manager.ArmyData")
local OtherPlayerCastleLayer = require("ui.outside-search.layers.OtherPlayerCastleLayer")
local BuildingSearchData = require("ui.outside-search.datas.BuildingSearchData")
local M = class("ui.outside-search.MainLayer", function()
	return cc.Layer:create()
end)

-- 玩家进入城池
local m_buildingInfos = {
		{ 
			buildingType = Enum.BuildingType.ResourcePoint, 
			layer = require("ui.outside-search.layers.SearchNotCastleLayer") 
		},
		{
			buildingType = Enum.BuildingType.Camp, 
			layer = require("ui.outside-search.layers.SearchNotCastleLayer") 
		},
		{ 
			buildingType = Enum.BuildingType.FamousCity, 
			layer = require("ui.outside-search.layers.SearchNotCastleLayer") 
		},
}

local m_buildingOwnweInfo = "building_owner_info"
local m_buildingGarrisonList ="building_garrison_list"

function M:createOtherCastleLayer(buildingData)
	self._buildingType = Enum.BuildingType.Castle
	self._buildingSearchData = BuildingSearchData.new(buildingData)
	self:_initgetBuildingData()
end

function M:createOtherBuildingLayer(buildingData)
	self._buildingSearchData = BuildingSearchData.new(buildingData)
	local buildingId = buildingData:getBuildingId()
	local buildingType = BuildingConfigReader:getBuildingType(buildingId)
	self._buildingType = buildingType
	self:_initgetBuildingData()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	local commons = 
	{
		[m_buildingOwnweInfo] = function(msgTable)
			assert(msgTable and msgTable.player_base_info2)
			local otherPlayerData = OtherPlayerData.new(msgTable.player_base_info2)
			self._buildingSearchData:setOtherPlayerData(otherPlayerData)

			self:_getBuildingDataFromServer(m_buildingGarrisonList)
		end,
		[m_buildingGarrisonList] = function(msgTable)
			self:_initArmyList(msgTable)
			self:_onServerCallBackFinish()
		end
	}

	Function:safeCall(commons, cmd, msgTable)
end

function M:_initArmyList(msgTable)
	assert(msgTable)
	local armyDataList = {}
	for _,msgTableArmyData in pairs(msgTable.armyInfos) do
		local armyData = ArmyData:newArmyDataWithInfo(msgTableArmyData)
		table.insert(armyDataList, armyData)
	end
	self._buildingSearchData:setArmyDataList(armyDataList)
end

-- 玩家城
function M:_onEnterCastle()
	local scene = cc.Director:getInstance():getRunningScene()
	local layer = OtherPlayerCastleLayer.new(self._buildingSearchData)
	scene:addChild(layer)
end

-- 进入非玩家城
function M:_onEnterNotCastle()
	local otherPlayerData = self._buildingSearchData:getOtherPlayerData()
	local playerId = 0
	if otherPlayerData then
		playerId = otherPlayerData:getPlayerId()
	end
	-- 无人占领
	if nil == otherPlayerData then
		local scene = cc.Director:getInstance():getRunningScene()
		local layer = require("ui.outside-search.layers.NoPlayerBuildingInfoLayer").new(self._buildingSearchData)
		scene:addChild(layer)
	else
		self:_createCheckBuildging()
	end
end

function M:_initgetBuildingData()
	CommonUI:showLoadingLayer(true)
	self:_addSocketDidCallBack()
	local ownerId = self._buildingSearchData:getBuildingData():getOwnerId()
	if ownerId <=0 then
		self:_onServerCallBackFinish()
	else
		self:_getBuildingDataFromServer(m_buildingOwnweInfo)
	end
end

function M:_getBuildingDataFromServer(commandKey)
	local homeCoor = self._buildingSearchData:getBuildingData():getHomeCoor()
	local sendData = {x = homeCoor.i, y = homeCoor.j}
	SocketManager:send(commandKey, sendData)
end

function M:_onServerCallBackFinish()
	CommonUI:showLoadingLayer(false)
	self:_removeSocketDidCallBack()
	if Enum.BuildingType.Castle == self._buildingType then
		self:_onEnterCastle()
	else
		self:_onEnterNotCastle()
	end
end

function M:_addSocketDidCallBack()
	SocketManager:addObserver(self)
end

function M:_removeSocketDidCallBack()
	SocketManager:removeObserver(self)
end

-- 根据类型进行进入城池
function M:_createCheckBuildging()
	local buildingId = self._buildingSearchData:getBuildingData():getBuildingId()
	local buildingType = BuildingConfigReader:getBuildingType(buildingId)
	local layer = nil
	local scene = cc.Director:getInstance():getRunningScene()
	for _,data in pairs(m_buildingInfos) do
		if buildingType == data.buildingType then
			layer = data.layer.new(self._buildingSearchData)
			break
		end
	end
	scene:addChild(layer)
end

return M