local GuildSkillConfig = require("config.GuildSkillConfig")
local M = {}

function M:getSkillName(id)
    return GuildSkillConfig[id].name
end

function M:getSkillType(id)
    return GuildSkillConfig[id].skilltype
end

function M:getSkillDesc(id)
    return GuildSkillConfig[id].desc
end

function M:getSkillLevel(id)
    return GuildSkillConfig[id].lv
end

function M:getSkillUpgradeExp(id)
    return GuildSkillConfig[id].exp
end

function M:getFoodValue(id)
    return GuildSkillConfig[id].foodvalue or 0
end

function M:getFoodPro(id)
    return GuildSkillConfig[id].foodpro or 0
end

function M:getWoodValue(id)
    return GuildSkillConfig[id].woodvalue or 0
end

function M:getWoodPro(id)
    return GuildSkillConfig[id].woodpro or 0
end

function M:getStoneValue(id)
    return GuildSkillConfig[id].stonevalue or 0
end

function M:getStonePro(id)
    return GuildSkillConfig[id].stonepro or 0
end

function M:getCoinValue(id)
    return GuildSkillConfig[id].coinvalue or 0
end

function M:getCoinPro(id)
    return GuildSkillConfig[id].coinpro or 0
end

-- 获取0级的技能的标志ID，用作技能列表初始化显示用
function M:getInitIdTable()
    local t = {}
    for _, v in pairs(GuildSkillConfig) do
        if v.lv == 0 then
            table.insert(t, v.id)
        end
    end
    return t
end

function M:getSkillLevelMax(id)
    return GuildSkillConfig[id].lvmax
end

function M:getIcon(id)
    return GuildSkillConfig[id].icon
end

return M