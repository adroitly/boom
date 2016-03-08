local GuildData = require("player-data.GuildData")
local GuildMemberData = require("player-data.GuildMemberData")
local GuildSkillData = class("ui.guild.data-manager.GuildSkillData")
local M = {}

local kGuildCreate          = "guild_create"
local kGuildOwnInfo         = "guild_own_info"
local kGuildSkillInfo       = "guild_skill_info"
local kGuildInfo            = "guild_info"
local kGuildMemberInfo      = "guild_member_info"
local kGuildCustomTitleInfo = "guild_custom_title_info"

function M:startDataListener()
    SocketManager:addObserver(self)
end

function M:stopDataListener()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildOwnInfo then
        self:updateOwnGuildData(msgTable)
    end
    if cmd == kGuildSkillInfo then
        self:updateGuildSkillData(msgTable)
    end
    if cmd == kGuildInfo then
        PlayerData:getGuildData():updateGuildData(msgTable)
    end
    if cmd == kGuildMemberInfo then
        if PlayerData:isOwner(msgTable.player_id) then
            PlayerData:getGuildMemberData():updateMemberData(msgTable)
        end
    end
    if cmd == kGuildCustomTitleInfo then
        local guildData = PlayerData:getGuildData()
        guildData:updateCustomTitleData(msgTable)
    end
end

function M:resetOwnGuildData()
    local defaultGuildOwnData = {}
    default(kGuildOwnInfo, defaultGuildOwnData)
    self:initGuildData(defaultGuildOwnData)
end

function M:initGuildData(guildOwnInfo)
    local guildData = GuildData.new(guildOwnInfo.guild_info)
    local guildMemberData = GuildMemberData.new(guildOwnInfo.guild_member_info)
    PlayerData:resetGuildData(guildData)
    PlayerData:resetGuildMemberData(guildMemberData)
end

function M:updateOwnGuildData(guildOwnInfo)
    PlayerData:getGuildData():updateGuildData(guildOwnInfo.guild_info)
    PlayerData:getGuildMemberData():updateMemberData(guildOwnInfo.guild_member_info)
end

function M:updateGuildSkillData(skillInfo)
    local skillType = skillInfo.skill_type
    local skillExp = skillInfo.skill_exp
    local guildData = PlayerData:getGuildData()
    local skillDataList = guildData:getGuildSkillDataList()
    local skillData = skillDataList[skillType]
    skillData:updateSkillData(skillInfo)
end
return M