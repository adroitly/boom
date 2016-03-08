local BattleUtils = require("ui.map.logic.BattleUtils")
local TeamDataManager = require("player-data.TeamDataManager")

local M = {}

function M:action(msgTable)
    local code = msgTable.code
    assert(code)

    -- 驻守成功，刷新出征状态为驻守，删除军队
    if code == 0 then
        BattleUtils:changeOutsideArmyState(msgTable)
        return
    end

    local text = string.format("回城失败，错误码=%d", code)
    CommonUI:lightTips(text)
end

return M