local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local AnchorPointConfigReader = require("config-reader.AnchorPointConfigReader")
local M = {}

function M:getCastleTag()
	return 14000
end

function M:isCastleType(buildingId)
    assert("number" == type(buildingId))
    return self:getCastleTag() == buildingId
end

function M:isFamousCity(buildingId)
    assert("number" == type(buildingId))
    local buildingType = BuildingConfigReader:getBuildingType(buildingId)
    return buildingType == Enum.BuildingType.FamousCity
end

function M:getBuildingNameWithId(buildingId)
	local buildingTag =
	{
		[14000] = __Localized("城堡"),
		[10001] = __Localized("粮田"),
		[10021] = __Localized("石矿厂"),
		[10041] = __Localized("玉矿厂"),
		[10061] = __Localized("铸币厂"),
		[10081] = __Localized("木材厂"),
		[10101] = __Localized("战略要地"),

		[12001] = __Localized("近程兵营"),
		[12011] = __Localized("中程兵营"),
		[12021] = __Localized("远程兵营"),
		[12031] = __Localized("通用兵营"),
	}

	return buildingTag[buildingId]
end

function M:getBuildingResourceId(buildingId, buildingLevel)
	-- 城堡需要算等级
    if self:isCastleType(buildingId) then
        return buildingLevel + self:getCastleTag() - 1
    end

  	-- 名城Id需读配置表
    local isFamousCity = self:isFamousCity(buildingId)
    if isFamousCity then
		return FamousCityConfigReader:getResId(buildingId)
    end

    return buildingId
end

function M:getBuildingResourceIdByBuildingData(buildingData)
    local buildingId = buildingData:getBuildingId()
    local buildingLevel = buildingData:getLevel()
    return self:getBuildingResourceId(buildingId, buildingLevel)
end

function M:getBuildingAnchorPoint(buildingId, buildingLevel)
    local anchorPointId = buildingId
    local isFamousCity = self:isFamousCity(buildingId)
    if isFamousCity then
        anchorPointId = FamousCityConfigReader:getResId(buildingId)
    else
        anchorPointId = buildingId + buildingLevel - 1
    end
    return AnchorPointConfigReader:getAnchorPoint(anchorPointId)
end

function M:getBuildingAnchorPointByBuildingData(buildingData)
    local buildingId = buildingData:getBuildingId()
    local buildingLevel = buildingData:getLevel()
    return self:getBuildingAnchorPoint(buildingId, buildingLevel)
end

-- 是否是我自己的主城
function M:isMyHomeCastle(buildingData)
    assert(buildingData)
    local buildingId = buildingData:getBuildingId()
    if self:getCastleTag()==buildingId and
            PlayerData:isOwner(buildingData:getOwnerId()) then
        return true
    end
    return false
end

return M
