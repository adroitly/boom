local BuildingConfig = require("config.BuildingConfig")
local M = {}

function M:getName(id)
    return self:_getConfigDataById(id).name
end

function M:getBuildingType(id)
    return self:_getConfigDataById(id).cityType
end

function M:_getConfigDataById(id)
    return BuildingConfig[id]
end

return M