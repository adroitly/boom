local ArmyData = require("ui.map.data-manager.ArmyData")
local StatusUtils = require("ui.map.army-status.StatusUtils")

local M = class("ui.map.army-status.OccupyBuilding", function()
    return require("ui.map.army-status.Base").new()
end)


function M:onArmyIsNearDesination(armyData)
    return StatusUtils:isRangeWithBuilding(armyData)
end

function M:onArmyDidAction(armyData)
    StatusUtils:attackBuilding(armyData)
end

return M


