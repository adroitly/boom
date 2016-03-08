local M = {}

local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local BackpackDataManager = require("player-data.BackpackDataManager")

local m_produceType = 
{
    Soldier = 1,
    Resources = 2
}

function M:isCanUse(backpackId)
    if false == BackpackDataManager:checkBackpackEnough(backpackId, 1) then
        return false
    end
    
    local callbacks = {
        [Enum.CheckBackpackType.DoctorType] = function()
            return self:_checkHeroHasDie()
        end,
        [Enum.CheckBackpackType.OfficerType] = function()
            return self:_checkPlayerCanLevelUp()
        end,
        [Enum.CheckBackpackType.ProduceSoldierType] = function()
            return self:_checkHasProduceSolder()
        end,
        [Enum.CheckBackpackType.ProduceResourcesType] = function()
            return self:_checkHasProduceResource()
        end,
        [Enum.CheckBackpackType.PlayerSolderType] = function()
            return self:_checkHasHeroPlayering()
        end
  
    }
    local isCanUse = Function:safeCall(callbacks, backpackId)
    if nil ~= isCanUse then
        return isCanUse
    end
    return true
end

function M:_checkHeroHasDie()
    local heroDataList = PlayerData:getHeros()
    for _,heroData in pairs(heroDataList) do
        if false == heroData:isLive() then
            return true
        end
    end
    return false
end

function M:_checkPlayerCanLevelUp()
    local needTime = PlayerData:getUserInfoData():getLevelUpEndTime() - PlayerData:getServerTime()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    if 90 == currentLevel or needTime <= 0 then
        return false
    end
    return true
end

function M:_checkHasProduceSolder()
    return self:_checkHasProduce(m_produceType.Soldier)
end

function M:_checkHasProduceResource()
    return self:_checkHasProduce(m_produceType.Resources)
end

function M:_checkHasProduce(produceType)
    local produceList = ProduceBuildingDataManager:getProduceBuildingDataList()
    for _,produceData in pairs(produceList) do
        local buildProduceList = {}
        if m_produceType.Soldier == produceType then
            buildProduceList = produceData:getProduceSoliderDataList()
        else
            buildProduceList = produceData:getProduceResourceDataList()
        end
        for _,produceData in pairs(buildProduceList) do
            local endTime = produceData:getProduceEndTime()
            if endTime > PlayerData:getServerTime() then
                return true
            end
        end
    end
    return false
end

function M:_checkHasHeroPlayering()
        local heroDataList = PlayerData:getHeros()
    for _,heroData in pairs(heroDataList) do
        local endEnergyTime = heroData:getEndEnergyTime()
        if endEnergyTime > PlayerData:getServerTime() then
            return true
        end
    end
    return false
end

return M