local BattleUtils = require("ui.map.logic.BattleUtils")
local TeamDataManager = require("player-data.TeamDataManager")

local M = {}

local function _errorAction(msgTable)
    local code = msgTable.code

    local outsideArmy = msgTable.army 
    local armyInfo = outsideArmy.army 
    local playerId = outsideArmy.player_id
    local armyId = armyInfo.army_id
    assert(armyInfo and playerId and armyId)

    -- 停止军队
    BattleUtils:setArmyWaitStatus(playerId, armyId)
    if ServerErrorCode.ARMY_DEATH == code then 
        CommonUI:lightTips("驻守的时候，军队被人打死了")
    else 
        local text = string.format("驻守失败，错误码=%d", code)
        CommonUI:lightTips(text)
    end
end

function M:action(msgTable)
    -- Print:Table(msgTable.army.army, "building guard callback")

    local code = msgTable.code
    assert(code)

    -- 驻守成功，刷新出征状态为驻守，删除军队
    if code == 0 then
        BattleUtils:changeOutsideArmyState(msgTable)
        return
    end

    _errorAction(msgTable)
end

return M