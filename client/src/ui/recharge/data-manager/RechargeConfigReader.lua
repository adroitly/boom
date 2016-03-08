local RechargeConfig = require("config.RechargeConfig")
local M = {}

function M:getDesc(id)
    return RechargeConfig[id].desc
end

function M:getName(id)
    return RechargeConfig[id].name
end

function M:getIconId(id)
    return RechargeConfig[id].icon
end

function M:getPrice(id)
    return RechargeConfig[id].price
end

return M