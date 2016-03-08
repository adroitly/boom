local WikiConfig = require("config.WikiConfig")
local M = {}

function M:getId(id)
    return WikiConfig[id].id
end

function M:getH1Title(id)
    return WikiConfig[id].h1
end

function M:getH2Title(id)
    return WikiConfig[id].h2
end

function M:getForm(id)
    return WikiConfig[id].form
end

function M:getDesc(id)
    return WikiConfig[id].desc
end

return M