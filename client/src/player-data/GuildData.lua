local M = class("player-data.GuildData")
local GuildSkillConfigRead = require("ui.guild.data-manager.GuildSkillConfigRead")
local GuildSkillData = require("ui.guild.data-manager.GuildSkillData")
local function _isVaild(msgTable)
    assert(msgTable and msgTable.guild_id and msgTable.flag and msgTable.name and msgTable.member_number and msgTable.level and msgTable.leader_name and msgTable.note and msgTable.guild_skill_infos and msgTable.exp and msgTable.donate and msgTable.setting_auto_join and msgTable.setting_limit_level and msgTable.custom_titles and msgTable.country)
end

function M:ctor(msgTable)
    self:_initSkillDataList()
    self:updateGuildData(msgTable)
end

function M:updateGuildData(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
    self:_updateSkillDataList()
end

function M:updateCustomTitleData(msgTable)
    for k, title_info in pairs(self.custom_titles) do
        if title_info.title == msgTable.title then
            title_info.name = msgTable.name
            return
        end
    end
end
function M:getTitleNameByTitle(title)
    for k, title_info in pairs(self.custom_titles) do
        if title_info.title == title then
            return title_info.name
        end
    end
end

function M:getCustomTitles()
    return self.custom_titles
end

function M:getGuildId()
    return self.guild_id
end

function M:getFlag()
    return self.flag
end

function M:getName()
    return self.name
end

function M:getLevel()
    return self.level
end

function M:getLeaderName()
    return self.leader_name
end

function M:getMemberNum()
    return self.member_number
end

function M:getNote()
    return self.note
end

function M:getGuildSkillDataList()
    return self._skillDataList
end

function M:getExp()
    return self.exp
end

function M:getDonate()
    return self.donate
end

function M:isAutoJoin()
    return self.setting_auto_join == Enum.GuildSetting.AutoOpen
end

function M:getJoinLevel()
    return self.setting_limit_level
end

function M:getCountryId()
    return self.country
end

-- 初始化技能列表
function M:_initSkillDataList()
    self._skillDataList = {}
    local t = GuildSkillConfigRead:getInitIdTable()
    for i, id in pairs(t) do
        local skillType = GuildSkillConfigRead:getSkillType(id)
        local skillLevel = GuildSkillConfigRead:getSkillLevel(id)
        local data = {}
        data.skill_type = skillType
        data.skill_level = skillLevel
        data.skill_exp = 0
        local guildSkillData = GuildSkillData.new(data)
        self._skillDataList[skillType] = guildSkillData
    end
end

function M:_updateSkillDataList()
    if not self.guild_skill_infos then
        return
    end
    for i, skillInfo in pairs(self.guild_skill_infos) do
        local skillType = skillInfo.skill_type
        self._skillDataList[skillType]:updateSkillData(skillInfo)
    end
end

return M