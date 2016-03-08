local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.data-manager.BuildingDataManager")

function M:ctor()
	self._dataManager = {}
end

function M:getOwnBuildingData()
	local homeCoor = PlayerData:getHomeCoor()
    local uniqueId = Utils:getUniqueId(homeCoor.i, homeCoor.j)
    local BuildingDataManager = MapManager:getBuildingDataManager()
    local buildingData = BuildingDataManager:findData(uniqueId)
    return buildingData
end

function M:addData(buildingData, uniqueId)
	assert(buildingData and uniqueId)
	self._dataManager[uniqueId] = buildingData
end

function M:findData(uniqueId)
	assert(uniqueId)
	return self._dataManager[uniqueId]
end

function M:removeData(uniqueId)
	self._dataManager[uniqueId] = nil 
end

function M:recoveryDataInCenterCoor(centerCoor, recoverSpriteFun)
	assert(centerCoor.i and centerCoor.j and recoverSpriteFun)
	for key, buildingData in pairs(self._dataManager) do
		local curCoor = buildingData:getHomeCoor()
		if MapConfig:canRecoveryInCenterCoor(curCoor, centerCoor) then 
			recoverSpriteFun(buildingData)
			self._dataManager[key] = nil 
		end
	end 
end

return M