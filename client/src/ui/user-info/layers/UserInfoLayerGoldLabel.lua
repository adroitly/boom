local BackpackDataManager = require("player-data.BackpackDataManager")
local M = {}

local function _getGoldNumber()
    local backpackData = BackpackDataManager:getBackpackDataByType(Enum.ResourceType.Gold)
    local number = 0
    if backpackData then
        number = backpackData:getItemNumber()
    end
    return number
end

function M:createGoldNumerLabel()
    local number = _getGoldNumber()
    local label = CommonUI:createLabel(string.format(__Localized("元宝:%s"), number), 24)
    label:setAnchorPoint(cc.p(1, 0.5))
    return label
end

function M:updateGoldNumberLabel(label)
    local number = _getGoldNumber()
    label:setString(string.format(__Localized("元宝:%s"), number))
end

return M