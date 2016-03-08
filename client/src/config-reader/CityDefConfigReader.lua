local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local CastleConfigReader = require("ui.city.king.CastleConfigReader")
local CampConfigReader = require("ui.produce.data-manager.CampConfigReader")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local ResourcePointConfigReader = require("ui.produce.data-manager.ResourcePointConfigReader")

local M = {}

function M:getCityAmount(buildingId)
    local buildingType = BuildingConfigReader:getBuildingType(buildingId)
    if buildingType == Enum.BuildingType.Castle then
        local level = PlayerData:getCastleLevel()
        return CastleConfigReader:getCityAmount(level)
    elseif buildingType == Enum.BuildingType.FamousCity then
        return FamousCityConfigReader:getCityAmount(buildingId)
    elseif buildingType == Enum.BuildingType.Camp then
        return CampConfigReader:getCityAmount(buildingId)
    elseif buildingType == Enum.BuildingType.ResourcePoint then
        return ResourcePointConfigReader:getCityAmount(buildingId)
    end
end

function M:getCityDef(buildingId)
    local buildingType = BuildingConfigReader:getBuildingType(buildingId)
    if buildingType == Enum.BuildingType.Castle then
        local level = PlayerData:getCastleLevel()
        return CastleConfigReader:getDef(level)
    elseif buildingType == Enum.BuildingType.FamousCity then
        return FamousCityConfigReader:getCityDef(buildingId)
    elseif buildingType == Enum.BuildingType.Camp then
        return CampConfigReader:getCityDef(buildingId)
    elseif buildingType == Enum.BuildingType.ResourcePoint then
        return ResourcePointConfigReader:getCityDef(buildingId)
    end
end

return M