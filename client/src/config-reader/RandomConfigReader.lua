local RandomConfig = require("config.RandomConfig")

local M = {}

local function _getData(randomId, key)
    assert(RandomConfig[randomId] and RandomConfig[randomId][key])
    return RandomConfig[randomId][key]
end

function M:getDesc(randomId)
    return _getData(randomId, "desc")
end

function M:getName(randomId)
    return _getData(randomId, "name")
end

return M