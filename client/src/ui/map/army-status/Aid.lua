local ArmyData = require("ui.map.data-manager.ArmyData")
local BattleUtils = require("ui.map.logic.BattleUtils")
local StatusUtils = require("ui.map.army-status.StatusUtils")

local M = class("ui.map.army-status.Wait", function()
    return require("ui.map.army-status.Base").new()
end)

function M:onArmyIsNearDesination(armyData)
    return StatusUtils:isRangeWithBuilding(armyData)
end

function M:onArmyDidAction(armyData)
   local mapDataManager = MapManager:getMapDataManager()
   mapDataManager:buildingGuardAction(armyData)
   BattleUtils:setWaitStatus(armyData)
end

return M