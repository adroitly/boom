
local BattleUtils = require("ui.map.logic.BattleUtils")
local TeamDataManager = require("player-data.TeamDataManager")

local M = {}

function M:action(msgTable)
    Print:Table(msgTable, "army info update = ")
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    local armyNumber = msgTable.army_number
    assert(playerId and armyId and armyNumber)

    if PlayerData:isOwner(playerId) then
        local teamData = TeamDataManager:getTeamData(armyId)
        teamData:updateSoldierNumber(armyNumber)
    end

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if armyData then 
        armyData:setArmyCount(armyNumber)
    end

    -- 死亡处理
    if armyNumber <= 0 then
        BattleUtils:armyDidDied(playerId, armyId)
    end
end

return M