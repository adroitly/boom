
local BattleUtils = require("ui.map.logic.BattleUtils")
local M = class("ui.map.army-status.Move", function()
    return require("ui.map.army-status.Base").new()
end)

function M:onArmyIsNearDesination(armyData)
    if armyData:isFromEqualTo() then    
         local text = string.format("军队id=%d已经抵达目的地", armyData:getArmyId() )
         CommonUI:lightTips(text)
         BattleUtils:setWaitStatus(armyData)
         return true
    end
    
    return false
end

function M:onArmyDidAction(armyData)
end

return M