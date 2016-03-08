
local BattleUtils = require("ui.map.logic.BattleUtils")
local M = {}

function M:action(msgTable)
    Print:Table(msgTable, "rand package get =")

    local code = msgTable.code 
    assert(code)
    if 0==code then 
        BattleUtils:pickupRandomResource(msgTable.x, msgTable.y)
        
        CommonUI:lightTipsFormat(__Localized("捡取成功"))
        return
    end

    CommonUI:lightTipsFormat(__Localized("捡取失败，code=%d", code))
end

return M