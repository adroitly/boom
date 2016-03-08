local SkillConfig = require("config.SkillConfig")
local M = {}

local SkillEffectType =
{
    PlusAttributes  = 1,
    Damage          = 2,
    SoliderLimit    = 3,
    PlusSolider     = 4,
    IntervalDamage  = 5,
    DurationBuff    = 6,
}

local function _getSkillValue(skillId)
    local value = SkillConfig[skillId]
    assert(value, string.format("错误提示：SkillConfig配置表id=%d不存在", skillId))
    return value
end

local function _checkActionUpVaild(actionUpTable, originData, skillId)
    for i,v in ipairs(actionUpTable) do
        assert(#v==3, string.format("错误提示：actionup=%s必须有3个参数skillId = %s", originData, skillId))
    end
end

local function _checkActionTable(actionTable, originData, skillId)
    local assertTable =
    {
        [SkillEffectType.PlusAttributes] = function(value)
            assert(#value==5, string.format("错误提示，属性加成类型必须有5个参数, value=%s skillId = %s", originData, skillId))
        end,
        [SkillEffectType.Damage] = function(value)
            assert(#value==5, string.format("错误提示，技能伤害型必须有5个参数, value=%s skillId = %s", originData, skillId))
        end,
        [SkillEffectType.SoliderLimit] = function(value)
            assert(#value==5, string.format("错误提示，携带士兵上限型必须有5个参数, value=%s skillId = %s", originData, skillId))
        end,
        [SkillEffectType.PlusSolider] = function(value)
            assert(#value==5, string.format("错误提示，恢复兵力型必须有5个参数, value=%s skillId = %s", originData, skillId))
        end,
        [SkillEffectType.IntervalDamage] = function(value)
            assert(#value==7, string.format("错误提示，持续伤害型必须有7个参数, value=%s skillId = %s", originData, skillId))
        end,
        [SkillEffectType.DurationBuff] = function(value)
            assert(#value==6, string.format("错误提示，持续buff型必须有6个参数, value=%s skillId = %s", originData, skillId))
        end,
    }

    for i,v in ipairs(actionTable) do
        Function:safeCall(assertTable, v[2], v)
    end
end

-- 获取技能的成长属性
local function _getActionTable(skillValue, skillLevel, skillId)
    local actionTable = Utils:formatStringToNumberTable(skillValue.action)
    _checkActionTable(actionTable, skillValue.action, skillId)

    local actionUpTable = Utils:formatStringToNumberTable(skillValue.actionup)
    _checkActionUpVaild(actionUpTable, skillValue.actionup, skillId)

    for _,actionUpValue in ipairs(actionUpTable) do
        local upIndex = actionUpValue[1]
        local indexValue = actionTable[upIndex]
        local upRow = actionUpValue[2]
        local upValue = actionUpValue[3]

        assert(#indexValue>=upRow, string.format("错误提示：参数的index大于配置的个数 skillId = %s", skillId))
        indexValue[upRow] = indexValue[upRow] + upValue*(skillLevel-1)
    end

    return actionTable
end

local function _getTargetValueByContentTable(contentTable, skillValue, skillLevel, skillId)
    local content = contentTable[1]
    if content == "pro" then
        local lastValue = skillValue.pro + skillValue.proup*(skillLevel - 1)
        local divide = contentTable[3] and contentTable[3] or 1
        lastValue = math.floor(lastValue / divide)
        return lastValue
    elseif content == "action" then
        assert(#contentTable>=3, string.format("错误提示：解析(%s)必须要>3个参数 skillId = %s", content, skillId))

        local toIndex = tonumber(contentTable[2])
        local toValue = tonumber(contentTable[3])
        local actionTable = _getActionTable(skillValue, skillLevel, skillId)
        local divide = contentTable[4] and contentTable[4] or 1
        local lastValue = actionTable[toIndex][toValue] / divide
        return lastValue
    end

    assert(false, string.format("错误提示：未定义的解析对象%s", content))
end

local function _changeValueToRichFormat(value)
    return string.format("<b>color=[255-255-255-255],text=%s</b>", math.abs(value))
end

local function _getSkillDescription(skillValue, skillLevel, skillId)
    local desc = skillValue.desc
    local parseTable = String:findSubs(desc, "<", ">")

    for _,value in ipairs(parseTable) do
        local contentTable = String:split(value, ".")
        local number = _getTargetValueByContentTable(contentTable, skillValue, skillLevel, skillId)
        local richFormat = _changeValueToRichFormat(number)

        local replaceString = string.format("<%s>", value)
        desc = string.gsub(desc, replaceString, richFormat)
    end

    return desc
end

local function _getAttributeByType(skillId, skillLevel, skillEffectType)
    assert(skillId and skillLevel)
    local skillValue = _getSkillValue(skillId)
    local actionTable = _getActionTable(skillValue, skillLevel, skillId)

    local attributes = {}
    for _,actionValue in ipairs(actionTable) do
        if skillEffectType == actionValue[2] then
            local attributeIndex = actionValue[3]
            local attributeValue = attributes[attributeIndex] and attributes[attributeIndex] or {}

            -- 直接加成
            local curRealValue = attributeValue[1] and attributeValue[1] or 0
            local realValue = curRealValue + actionValue[4]
            attributeValue[1] = realValue

            -- 千分比加成
            local curPercentValue = attributeValue[2] and attributeValue[2] or 0
            local percentValue = curPercentValue + actionValue[5]
            attributeValue[2] = percentValue

            attributes[attributeIndex] = attributeValue
        end
    end
    return attributes
end

---------------------------------- 接口入口 ----------------------------------

function M:getName(skillId)
    return _getSkillValue(skillId).name
end

function M:getMaxLevel(skillId)
    return _getSkillValue(skillId).maxlv
end

function M:getDescription(skillId, skillLevel)
    assert(skillId and skillLevel)
    local skillValue = _getSkillValue(skillId)
    return _getSkillDescription(skillValue, skillLevel, skillId)
end

--[[
    * 描述：获取被动技能属性加成
    * 结果：{ [属性类型] = [直接加成值，千分比加成], ... }，属性类型表参考文件底部
    * 例子：{ [1]=[10, 100],[2]=[30, 0] }, 增加武力10，提高10%武力值，增加智力30
--]]
function M:getAttributes(skillId, skillLevel)
    return _getAttributeByType(skillId, skillLevel, SkillEffectType.PlusAttributes)
end

--[[
    * 描述：获取士兵上限
    * 结果：{ [兵种ID]=[直接加成，千分比加成], ... }
    * 例子：{ [18000]=[1000, 100] }，携带大刀兵增加1000士兵，并提高10%携带
--]]
function M:getSoliderLimit(skillId, skillLevel)
    return _getAttributeByType(skillId, skillLevel, SkillEffectType.SoliderLimit)
end

--[[
    * 属性值索引
     1   武力上限
     2   智力上限
     3   统率上限
     4   体质上限
     5   士兵生命
     6   部队攻击
     7   部队防御
     8   士兵命中
     9   士兵闪避
     10  士气
     11  破甲系数
     12  反弹伤害千分比
     13  减伤系数
     -- 14  出征兵力上限  已废弃
     15  免疫debuff机率
     16  免疫持续伤害buff机率
--]]

return M

