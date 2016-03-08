
local MapConfig = require("ui.map.data-manager.MapConfig")

local M = class("ui.map.layer-manager.BuildingSpritesManager", function()
    return require("ui.map.layer-manager.BaseSpritesManager").new()
end)

function M:cellPositionForData(buildingData)
    local coor = buildingData:getHomeCoor()
    return MapConfig:getResourcePointPosition(coor)
end

function M:cellUniqueIdForData(buildingData)
    return buildingData:getUniqueId()
end

function M:cellSpriteForData(buildingData)
    return require("ui.map.layer-manager.BuildingSpriteNode").new()
end

function M:cellReloadForData(buildingData, spriteNode)
    spriteNode:reloadData(buildingData)
end

function M:findBuldingData(point)
    return self:findDataByConditionFun(function(buildingData)
        local coor = buildingData:getHomeCoor()
        return MapConfig:isPointInBuildCoor(point, coor)
    end)
end

function M:updateCityDef(buildingData)
    local spriteNode = self:findSpriteByUniqueId(buildingData:getUniqueId())
    spriteNode:checkCityDef(buildingData)
end

return M