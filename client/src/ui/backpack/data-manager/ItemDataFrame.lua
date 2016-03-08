local M = {}
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
--[[
根据Type创建Frame
]]
function M:getSpriteFrame(itemType, itemId)
    local packageName = ""
    local resId = itemId
    if itemType == Enum.ResourceTypeId.Item then
        packageName = "stage-icon"
    elseif itemType == Enum.ResourceTypeId.Soldier then
        packageName = "soldier"
        if 0 ~= itemId % 10 then
            resId = SoldierConfigReader:getType(itemId)
        end
    elseif itemType == Enum.ResourceTypeId.Hero then
        packageName = "hero-icon"
    end
    return CommonUI:createSpriteFrameTinyName(packageName, resId..".png")
end
return M
