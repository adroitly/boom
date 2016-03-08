local ResourcePointConfig = require("config.ResourcePointConfig")
local M = {}
function M:getProduceResSpeed(id)
    local proResSpeedType = self:_getConfigDataById(id).proResSpeed
    local formatTbl = Utils:formatStringToTable(proResSpeedType)
    local tbl = {}
    for _, v in ipairs(formatTbl) do
        local data = {}
        data.id = tonumber(v[1])
        data.limit = tonumber(v[2])
        data.time = tonumber(v[3])
        table.insert(tbl, data)
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
    return ResourcePointConfig[id]
end

return M