
local MapConfig = require("ui.map.data-manager.MapConfig")
local StatusUtils = require("ui.map.army-status.StatusUtils")
local BattleUtils = require("ui.map.logic.BattleUtils")

local M = class("ui.map.army-status.GoHome", function()
    return require("ui.map.army-status.Base").new()
end)

function M:onArmyIsNearDesination(armyData)
    return StatusUtils:isRangeWithBuilding(armyData)
end

function M:onArmyDidAction(armyData)    
    BattleUtils:setWaitStatus(armyData)

    local fromCoor = armyData:getFromCoordinate()
    local armyId = armyData:getArmyId()
    local sendData = {army_id=armyId}
    SocketManager:send(Command.ArmyGoBack, sendData)
end

return M