local HeroGrowthConfig = require("config.HeroGrowthConfig")

local M = {}


local function _print(data, printName,name , value)
	if nil == data then
		print("HeroGrowthRead not find "..printName.." When "..name.."==="..value)
	end
end

local function _getData(level, key)
	local data = HeroGrowthConfig[level][key]
	_print(data, key, "heroLevel", level)
	return data
end

function M:getCommanderRatio(level)
	return _getData(level, "commanderRatio")
end

function M:getForceRatio(level)
	return _getData(level, "forceRatio")
end

function M:getBrainsRatio(level)
	return _getData(level, "brainsRatio")
end

function M:getCharmRatio(level)
	return _getData(level, "charmRatio")
end

function M:getConstitutionRatio(level)
	return _getData(level, "constitutionRatio")
end

function M:getTroopsRatio(level)
	return _getData(level, "troopsRatio")
end

function M:getEnergySpeed(level)
	return _getData(level, "energySpeed")
end


return M