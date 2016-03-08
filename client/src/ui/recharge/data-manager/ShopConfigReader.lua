local ShopConfig = require("config.ShopConfig")
local M = {}

local function _getConfigData(id)
    assert(id)
    return ShopConfig[id]
end

local function _getConverConfig(str)
    local tbl = Utils:formatStringToNumberTable(str)
    local list = {}
    for _, v in ipairs(tbl) do
        local data = {}
        data.id = v[1]
        data.count = v[2]
        table.insert(list, data)
    end
    return list
end

function M:getName(id)
    return _getConfigData(id).name
end

function M:getDesc(id)
    return _getConfigData(id).desc
end

function M:getIconId(id)
    return _getConfigData(id).icon
end

function M:getPrice(id)
    local priceStr = _getConfigData(id).price
    local configData = _getConverConfig(priceStr)
    local priceType = configData[1].id
    local priceCount = configData[1].count
    return priceType, priceCount
end

function M:getGoodsList()
    local goodsStr = _getConfigData(id).goods
    return _getConverConfig(goodsStr)
end

return M