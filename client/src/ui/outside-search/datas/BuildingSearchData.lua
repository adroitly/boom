local M = class("ui.outside-search.datas.BuildingSearchData")

function M:ctor(buildingData)
	self._buildingData = buildingData
end

function M:setOtherPlayerData(otherPlayerData)
	self._otherPlayerData = otherPlayerData
end

function M:setArmyDataList(armyDataList)
	self._armyDataList = armyDataList
end

function M:getBuildingData()
	return self._buildingData
end
function M:getOtherPlayerData()
	return self._otherPlayerData
end

function M:getArmyDataList()
	return self._armyDataList
end

return M