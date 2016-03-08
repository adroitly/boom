local M = class("ui.rank.data-manager.RankData")

local function _isVaild(msgTable)
    assert(msgTable and msgTable.rank and msgTable.id and msgTable.name and msgTable.guild_name and msgTable.level and msgTable.country and msgTable.value and msgTable.icon)
end

function M:ctor(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:getRank()
    return self.rank
end

function M:getId()
    return self.id
end

function M:getName()
    return self.name
end

function M:getGuildName()
    return self.guild_name
end

function M:getLevel()
    return self.level
end

function M:getCountry()
    return self.country
end

function M:getValue()
    return self.value
end

function M:getIcon()
    return self.icon
end

return M