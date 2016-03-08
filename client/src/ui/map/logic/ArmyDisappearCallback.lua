local BattleUtils = require("ui.map.logic.BattleUtils")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = {}

function M:action(msgTable)
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    assert(playerId and armyId)

    if PlayerData:getPlayerId() ~= playerId then 
       BattleUtils:removeArmy(playerId, armyId) 
    end
end

return M