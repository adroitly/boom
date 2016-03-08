local GuildDonateRatioConfig = require("config.GuildDonateRatioConfig")
local M = {}

function M:getPersonalDonateRatio(id)
    return GuildDonateRatioConfig[id].personalDonate
end

function M:getGuildDonateRatio(id)
    return GuildDonateRatioConfig[id].guildDonate
end
return M