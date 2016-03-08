local M = class("ui.user-info.datas.OtherPlayerData")

local function _isValid(msgTable)
    assert(msgTable and msgTable.player_id and msgTable.nickname and msgTable.level and msgTable.level and msgTable.country and msgTable.guild_leader_name and msgTable.guild_name and msgTable.guild_title and msgTable.icon)
end

function M:ctor(msgTable)
    _isValid(msgTable)
    Table:copy(self, msgTable)
end

function M:getPlayerId()
    return self.player_id
end

function M:getNickname()
    return self.nickname
end

function M:getLevel()
    return self.level
end

function M:getCountry()
    return self.country
end

function M:getGuildLeaderName()
    return self.guild_leader_name
end

function M:getGuildName()
    return self.guild_name
end

function M:getGuildTitle()
    return self.guild_title
end

function M:getIcon()
    return self.icon
end

return M