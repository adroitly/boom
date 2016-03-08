local M = class("player-data.GuildMemberData")
local PlayerBaseData = require("player-data.PlayerBaseData")
local function _isVaild(msgTable)
    assert(msgTable and msgTable.player_id and msgTable.player_base_info and msgTable.title and msgTable.donate)
end

function M:ctor(msgTable)
    self:updateMemberData(msgTable)
end

function M:updateMemberData(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:getPreOnlineTime()
    return self.player_base_info.pre_online_time
end

function M:getLevel()
    return self.player_base_info.level
end

function M:getPlayerId()
    return self.player_base_info.player_id
end

function M:getNickname()
    return self.player_base_info.nickname
end

function M:getTitle()
    return self.title
end

function M:getTotalDonate()
    return self.donate
end


return M