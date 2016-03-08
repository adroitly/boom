local M = class("ui.country-war.data-manager.CountryWarData")

local function _isValid(msgTable)
    assert(msgTable and msgTable.country_id and msgTable.relation and msgTable.player_count and msgTable.fighting and msgTable.score)
end

function M:ctor(msgTable)
    _isValid(msgTable)
    Table:copy(self, msgTable)
end

function M:getCountryId()
    return self.country_id
end

function M:getRelation()
    return self.relation
end

function M:getPlayerCount()
    return self.player_count
end

function M:getFighting()
    return self.fighting
end

function M:getScore()
    return self.score
end

return M