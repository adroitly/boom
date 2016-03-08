local OfficerConfig = require("config.OfficerConfig")
local M = {}

function M:getDataByKey(level, key)
	return OfficerConfig[level][key]
end

function M:getOfficerName(level)
    return OfficerConfig[level].officer
end

function M:getMaxLevel()
    return OfficerConfig[1].levelMax
end

function M:getNextExp(level)
    return OfficerConfig[level].nextExp
end

function M:getGrowthRate(level)
    return OfficerConfig[level].growthRate
end

function M:getCostTime(level)
    return OfficerConfig[level].costTime
end

function M:isCanAppoint(level)
	return OfficerConfig[level].appointPower
end

function M:getAppointMax(level)
	return OfficerConfig[level].appointMax
end

function M:getProRes(level)
	return OfficerConfig[level].proRes
end

function M:getLaborage(level)
	return OfficerConfig[level].laborage
end

function M:getOffDonation(level)
	return OfficerConfig[level].offDonation
end

function M:getProvinceType(level)
	return OfficerConfig[level].provinceType
end

function M:getSpeedCost(level)
	return OfficerConfig[level].speedCost
end

function M:getMinLevelHasAppointPower()
    for level,_ in ipairs(OfficerConfig) do
        if 1 == self:isCanAppoint(level) then
            return level
        end
    end
end

return M