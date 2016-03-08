local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local CastleConfigReader = require("ui.city.king.CastleConfigReader")
local CampConfigReader = require("ui.produce.data-manager.CampConfigReader")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local ResourcePointConfigReader = require("ui.produce.data-manager.ResourcePointConfigReader")

local M = {}

function M:getProduceSoldierTypeList(id)
    local buildingType = BuildingConfigReader:getBuildingType(id)
    if buildingType == Enum.BuildingType.Castle then
        local level = self:_getCastleLevel()
        return CastleConfigReader:getProduceSoldierType(level)
    elseif buildingType == Enum.BuildingType.FamousCity then
        return FamousCityConfigReader:getProduceSoldierType(id)
    elseif buildingType == Enum.BuildingType.Camp then
        return CampConfigReader:getProduceSoldierType(id)
    end
end

function M:getProduceResourceConfigList(id)
    local buildingType = BuildingConfigReader:getBuildingType(id)
    if buildingType == Enum.BuildingType.Castle then
        local level = self:_getCastleLevel()
        return CastleConfigReader:getProduceResSpeed(level)
    elseif buildingType == Enum.BuildingType.FamousCity then
        return FamousCityConfigReader:getProduceResSpeed(id)
    elseif buildingType == Enum.BuildingType.ResourcePoint then
        return ResourcePointConfigReader:getProduceResSpeed(id)
    end
end

function M:_getCastleLevel()
    local level = PlayerData:getCastleLevel()
    return level
end

return M