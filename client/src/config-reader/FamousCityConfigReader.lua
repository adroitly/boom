local FamousCityConfig = require("config.FamousCityConfig")
local M = {}

local function _print(value, id, key)
    if nil == value then
        local text = string.format("FamousCityConfigReader配置表错误：id=%d, key=%s不存在", id, key)
        print(text)
    end
end

local function _getValue(id, key)
    assert(id and key)
    local configData = FamousCityConfig[id]
    local value = configData[key]
    _print(value, id, key)
    return value
end

function M:getName(id)
    return _getValue(id, "name")
end

function M:getCityAtk(id)
    return _getValue(id, "cityAtk")
end

function M:getCityDef(id)
    return _getValue(id, "cityDef")
end

function M:getCityDefSpeed(id)
    return _getValue(id, "cityDefSpeed")
end

function M:getCityAmount(id)
    return _getValue(id, "cityAmount")
end

function M:getProExp(id)
    return _getValue(id, "proExp")
end

-- 返回的是string，需要用common的Utils解析
function M:getProResSpeed(id)
    return _getValue(id, "proResSpeed")
end

-- 返回的是无key坐标x,y
function M:getCoordinate(id)
    local value = _getValue(id, "coordinate")
    return Utils:formatStringToNumberTable(value)[1]
end

-- 资源Icon Id
function M:getResId(id)
    return _getValue(id, "resId")
end

function M:getProduceSoldierType(id)
    local soldierTypeStr = self:_getConfigDataById(id).typeSold
    local formatTbl = Utils:formatStringToTable(soldierTypeStr)
    local tbl = {}
    for _, v in ipairs(formatTbl) do
        table.insert(tbl, tonumber(v[1]))
    end
    return tbl
end

function M:getProduceResSpeed(id)
    local speed = self:_getConfigDataById(id).proResSpeed
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

function M:_getConfigDataById(id)
    return FamousCityConfig[id]
end

return M