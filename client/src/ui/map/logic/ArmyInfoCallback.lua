
local TeamDataManager = require("player-data.TeamDataManager")
local M = {}

local function _deleteArmy(msgTable)
    local armyId = msgTable.army_id
    assert(armyId)
    teamData = TeamDataManager:getTeamData(armyId)
    local soldierNumber = teamData:getSoldierNumber()
    if soldierNumber <=0 then 
        -- print("remove team", armyId)
        TeamDataManager:removeTeamData(armyId)
    end
end

-- 背包军队的增、删、改
function M:action(msgTable)
    -- Print:Table(msgTable, "army info callback")
    TeamDataManager:updateTeamData(msgTable)

    -- 与服务器协商如何判断删除军队
    _deleteArmy(msgTable)
end

return M