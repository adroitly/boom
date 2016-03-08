local CastleConfig = require("config.CastleConfig")
local M = {}

function M:getResId(level)
    return CastleConfig[level].resId
end

function M:getMaxLevel()
    return table.getn(CastleConfig)
end

function M:getDepotConfine(level)
    return CastleConfig[level].depotConfine
end

function M:getDef(level)
    return CastleConfig[level].cityDef
end

function M:getCityAmount(level)
    return  CastleConfig[level].cityAmount
end

function M:getDefRestoreSpeed(level)
    return CastleConfig[level].cityDefSpeed
end

function M:getLevelCondition(level)
    return CastleConfig[level].officeCondition
end

function M:getSafeConfine(level)
    return CastleConfig[level].safeConfine
end

function M:getStorageConfine(level)
    return CastleConfig[level].storageConfine
end

function M:getUpgradeConditions(level)
    local condition = CastleConfig[level].upgradeCondition
    local formatTbl = Utils:formatStringToTable(condition)
    local tbl = {}
    for _, v in ipairs(formatTbl) do
        local data = {}
        data.id = tonumber(v[1])
        data.count = tonumber(v[2])
        table.insert(tbl, data)
    end
    return tbl
end

function M:getProduceResSpeed(level)
    local speed = CastleConfig[level].proResSpeed
    local formatTbl = Utils:formatStringToTable(speed)
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

function M:getProduceSoldierType(level)
    local typeSold = CastleConfig[level].typeSold
    local formatTbl = Utils:formatStringToTable(typeSold)
    local tbl = {}
    for _, v in ipairs(formatTbl) do
        table.insert(tbl, tonumber(v[1]))
    end
    return tbl
end

function M:getLevelMax()
    return CastleConfig[1].gradelimit
end

function M:getCityDefSpeed(level)
    return CastleConfig[level].cityDefSpeed
end

function M:getCityDefTime(level)
    return CastleConfig[level].cityDefTime
end


function M:getCityDefCondition(level)
    local str = CastleConfig[level].cityDefCondition
    local formatTbl = Utils:formatStringToNumberTable(str)
    local tbl = {}
    for _, v in ipairs(formatTbl) do
        local data = {}
        data.id = v[1]
        data.count = v[2]
        table.insert(tbl, data)
    end
    return tbl

end



return M