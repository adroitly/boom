
local BattleUtils = require("ui.map.logic.BattleUtils")
local M = {}

function M:action(msgTable)
    BattleUtils:pickupRandomResource(msgTable.x, msgTable.y)
end

return M