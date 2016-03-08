-- ProduceBuildingData
local M = class("ui.produce.data-manager.ProduceBuildingData")

local function _isVaild(msgTable)
    assert(msgTable and msgTable.building_id and msgTable.x and msgTable.y)
end

function M:ctor(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
    self._soldierDataList = {}
    self._resourceDataList = {}
end

function M:getBuildingId()
    return self.building_id
end

function M:getUniqueId()
    return Utils:getUniqueId(self.x, self.y)
end

function M:getLocalCoor()
    return self.x, self.y
end

function M:addProduceSoldierData(data)
    local soldierType = data:getSoldierType()
    self._soldierDataList[soldierType] = data
end

function M:getProduceSoliderData(soldierType)
    return self._soldierDataList[soldierType]
end

function M:getProduceSoliderDataList()
    return self._soldierDataList
end

function M:addProduceResourceData(data)
    local itemType = data:getItemType()
    self._resourceDataList[itemType] = data
end

function M:getProduceResourceDataList()
    return self._resourceDataList
end

function M:getProduceResourceData(itemType)
    return self._resourceDataList[itemType]
end


return M