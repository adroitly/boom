local SoldierConfig = require("config.SoldierConfig")
local M = {}

-- 根据兵种类型
function M:getNameByType(stype)
    for _,soldierData in pairs(SoldierConfig) do
        local soldierType = soldierData.id
        local tempType = self:getType(soldierType)
        if tempType == stype then
            return self:getName(soldierType)
        end
    end
end

function M:getRestraindesc(soldierType)
    return self:_getConfigData(soldierType).restraindesc
end

function M:getRestrain(soldierType)
    return self:_getConfigData(soldierType).restrain
end

function M:getType(soldierType)
    return self:_getConfigData(soldierType).category
end

function M:getName(soldierType)
    return self:_getConfigData(soldierType).name
end

function M:getLevel(soldierType)
    return self:_getConfigData(soldierType).level
end

function M:getHP(soldierType)
    return self:_getConfigData(soldierType).HP
end

function M:getAttack(soldierType)
    return self:_getConfigData(soldierType).attack
end

function M:getDefense(soldierType)
    return self:_getConfigData(soldierType).defense
end

function M:getHitRatio(soldierType)
    return self:_getConfigData(soldierType).hitRatio
end

function M:getDodge(soldierType)
    return self:_getConfigData(soldierType).dodge
end

function M:getSpeed(soldierType)
    return self:_getConfigData(soldierType).speed
end

function M:getAttackDistance(soldierType)
    return self:_getConfigData(soldierType).attackDistance
end

function M:getCapacity(soldierType)
    return self:_getConfigData(soldierType).capacity
end

function M:getProductionRate(soldierType)
    return self:_getConfigData(soldierType).productionRate
end

function M:getAttackEffectId(soldierType)
    return self:_getConfigData(soldierType).attackEffectId
end

function M:getResources(soldierType)
    local resources = self:_getConfigData(soldierType).resources
    local formatTbl = Utils:formatStringToNumberTable(resources)
    local tbl = {}
    for _, t in ipairs(formatTbl) do
        table.insert(tbl, {id = t[1], count = t[2]})
    end
    return tbl
end

function M:getFood(soldierType)
    return self:_getConfigData(soldierType).food
end

function M:getWood(soldierType)
    local tbl = self:getResources(soldierType)
    for k, v in ipairs(tbl) do
        if v.id == Enum.ResourceType.Wood then
            return v.count
        end
    end
    return 0
end

function M:getStone(soldierType)
    local tbl = self:getResources(soldierType)
    for k, v in ipairs(tbl) do
        if v.id == Enum.ResourceType.Stone then
            return v.count
        end
    end
    return 0
end

function M:getCoin(soldierType)
    local tbl = self:getResources(soldierType)
    for k, v in ipairs(tbl) do
        if v.id == Enum.ResourceType.Coin then
            return v.count
        end
    end
    return 0
end

function M:isHasConfigData(soldierType)
    return SoldierConfig[soldierType] and true or false
end

function M:_getConfigData(soldierType)
    local data = SoldierConfig[soldierType]
    assert(data, string.format("SoldierConfig找不到相应数据，id=%d", soldierType))
    return data
end



return M