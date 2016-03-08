
local BattleUtils = require("ui.map.logic.BattleUtils")

local M = class("ui.map.army-status.Pickup", function()
    return require("ui.map.army-status.Base").new()
end)

local function _sendPickupData(armyData)
    local toCoor = armyData:getToCoordinate()
    local sendData = {x=toCoor.i, y=toCoor.j}
    SocketManager:send(Command.RandPackageGet, sendData)
end

function M:onArmyIsNearDesination(armyData)
    if armyData:isFromEqualTo() then    
        _sendPickupData(armyData)
        BattleUtils:setWaitStatus(armyData)
        return true
    end 
    return false
end

function M:onArmyDidAction(armyData)
    -- do nothing
    
end

return M