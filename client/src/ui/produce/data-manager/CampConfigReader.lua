local CampConfig = require("config.CampConfig")
local M = {}
function M:getProduceSoldierType(id)
    local soldierTypeStr = self:_getConfigDataById(id).productionType
    local formatTbl = Utils:formatStringToTable(soldierTypeStr)
    local tbl = {}
    for _, v in ipairs(formatTbl) do
        table.insert(tbl, tonumber(v[1]))
    end
    return tbl
end

function M:getCityDef(id)
    return self:_getConfigDataById(id).cityDef
end

function M:getCityAmount(id)
    return self:_getConfigDataById(id).cityAmount
end

function M:_getConfigDataById(id)
    return CampConfig[id]
end

return M