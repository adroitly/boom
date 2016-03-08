local M = class("ui.message-board.data-manager.MessageBoardData")

local function _isValid(msgTable)
    assert(msgTable and msgTable.id and msgTable.player_id and msgTable.nickname and msgTable.content and msgTable.time and msgTable.country)
end

function M:ctor(msgTable)
    _isValid(msgTable)
    Table:copy(self, msgTable)
end

function M:getId()
    return self.id
end

function M:getPlayerId()
    return self.player_id
end

function M:getNickname()
    return self.nickname
end

function M:getContent()
    return self.content
end

function M:getTime()
    return self.time
end

function M:getCountryId()
    return self.country
end

return M