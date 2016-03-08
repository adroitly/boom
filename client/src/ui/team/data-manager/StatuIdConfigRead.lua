local StatuIdConfig = require("config.StatuIdConfig")
local M = {}

function M:getNameById(statuId)
    return StatuIdConfig[statuId].name
end

return M