local HeroConfig = require("config.HeroConfig")

local M = {}

local function _print(data, printName,name , value)
	if nil == data then
		print("HeroConfigRead not find "..printName.." When "..name.."==="..value)
	end
end

local function _getData(heroType, key)
	local heroConfigData = HeroConfig[heroType]
	_print(heroConfigData, key, "heroType", heroType)
	local data = heroConfigData[key]
	_print(data, key, "heroType", heroType)
	return data
end

function M:getName(heroType)
	return _getData(heroType, "name")
end
-- 武将类型
function M:getHeroTypeName(heroType)
	return _getData(heroType, "heroType")
end

function M:getStarmax(heroType)
	return _getData(heroType, "starmax")
end

function M:getSex(heroType)
	return _getData(heroType, "sex")
end

function M:getCommander(heroType)
	return _getData(heroType, "commander")
end

function M:getForce(heroType)
	return _getData(heroType, "force")
end

function M:getBrains(heroType)
	return _getData(heroType, "brains")
end

function M:getCharm(heroType)
	return _getData(heroType, "charm")
end

function M:getConstitution(heroType)
	return _getData(heroType, "constitution")
end

function M:getTroops(heroType)
	return _getData(heroType, "troops")
end

function M:getDesc(heroType)
	return _getData(heroType, "desc")
end

function M:getRecommendSoldier(heroType)
	-- return 18001
	return _getData(heroType, "recommendSoldier")
end

function M:getSkill(heroType)
	local skill = _getData(heroType, "skillID")
	local skillTable = Utils:formatStringToNumberTable(skill)
	return {skillTable[1][1], skillTable[2][1]}
end

function M:getEnergy(heroType)
	return _getData(heroType, "energy")
end

-- 获取一级的速度
function M:getEnergySpeed(heroType)
	return _getData(heroType, "energySpeed")
end

function M:getEnergyMax(heroType)
	return _getData(heroType, "energymax")
end

function M:getPrice(heroType)
	return _getData(heroType, "price")
end

-- 是否可以交易的
function M:isBind(heroType)
	return 0 ~= _getData(heroType, "isbind")
end

function M:getCountry(heroType)
	return _getData(heroType, "country")
end

return M