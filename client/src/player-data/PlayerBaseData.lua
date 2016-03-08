local M = class("player-data.PlayerBaseData")

local function _isVaild(msgTable)
    assert(msgTable.player_id and msgTable.nickname and msgTable.level and msgTable.pre_online_time)
end
function M:ctor(msgTable)
    _isVaild(msgTable)
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

function M:getPreOnlineTime()
    return self.pre_online_time
end

return M