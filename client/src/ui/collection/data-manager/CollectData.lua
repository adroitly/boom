local MapConfig = require("ui.map.data-manager.MapConfig")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local CollectConfig = require("ui.collection.data-manager.CollectConfig")
local M = class("ui.collection.data-manager.CollectData")

function M:ctor(msgTable)
    assert(msgTable and msgTable.id and msgTable.info)
    Table:copy(self, msgTable)
    local data = CollectConfig:decodeToData(msgTable.info)
    Table:copy(self, data)
end

function M:getId()
    return self.id
end

function M:getCollectType()
    return self.collectType
end

function M:getPlayerName()
    return self.playerName
end

function M:getBuildingName()

    return BuildingConfigReader:getName(self.buildingId)
end

function M:getBuildingId()
    return self.buildingId
end

function M:getBuildingLevel()
    return self.buildingLevel
end

function M:getCoor()
    return MapConfig:coordinate(self.i, self.j)
end


return M