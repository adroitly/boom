
local MapConfig = require("ui.map.data-manager.MapConfig")

local M = class("ui.map.layer-manager.RandomResSpritesManager", function()
    return require("ui.map.layer-manager.BaseSpritesManager").new()
end)

function M:cellPositionForData(randomResourceData)
    local coor = randomResourceData:getHomeCoor()
    return MapConfig:getPositionFromCoordinate(coor) 
end

function M:cellUniqueIdForData(randomResourceData)
    return randomResourceData:getUniqueId()
end

function M:cellSpriteForData(randomResourceData)
    return require("ui.map.layer-manager.RandomResSpriteNode").new()
end

function M:cellReloadForData(randomResourceData, randomResSpriteNode)
    randomResSpriteNode:reloadData(randomResourceData)
end

function M:findRandomResourceData(point)
    local curCoor = MapConfig:getCoordinateFromPosition(point)
    return self:findDataByConditionFun(function(randomResourceData)
        local homeCoor = randomResourceData:getHomeCoor()
        return curCoor.i==homeCoor.i and curCoor.j==homeCoor.j
    end)
end

return M