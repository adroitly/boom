local M = class("ui.guild.data-manager.GuildSkillData")

local function _isVaild(msgTable)
    assert(msgTable and msgTable.skill_type and msgTable.skill_level and msgTable.skill_exp)
end

function M:ctor(msgTable)
    self:updateSkillData(msgTable)
end

function M:updateSkillData(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:getSkillType()
    return self.skill_type
end

function M:getSkillLevel()
    return self.skill_level
end

function M:getSkillExp()
    return self.skill_exp
end

function M:getSkillId()
    return self.skill_type + self.skill_level
end

return M