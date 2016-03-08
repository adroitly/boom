local GuildLevelConfig = require("config.GuildLevelConfig")
local M = {}
function M:getNeedExp(level)
    return GuildLevelConfig[level].exp
end

function M:getMemberMax(level)
    return GuildLevelConfig[level].membermax
end

function M:getLevelMax()
    return table.getn(GuildLevelConfig)
end
return M