local ArmyData = require("ui.map.data-manager.ArmyData")
local M = class("ui.map.army-status.Wait", function()
    return require("ui.map.army-status.Base").new()
end)

function M:update(armyData, dt)
    -- do nothing
end 

function M:onArmyIsNearDesination(armyData)
    -- do nothing
    return true
end

function M:onArmyDidAction(armyData)
    -- do nothing
end

return M