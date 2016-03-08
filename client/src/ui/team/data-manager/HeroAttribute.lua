local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local HeroGrowthConfigRead = require("ui.team.data-manager.HeroGrowthConfigRead")
local SkillConfigReader = require("config-reader.SkillConfigReader")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local M = {}

local function _getSkill(heroType)
	return HeroConfigRead:getSkill(heroType)
end

local m_allSoldierType = 0

local m_keyIndex = 
{
	Force        = 1, --   武力上限
	Brains       = 2, --   智力上限
	Commander    = 3, --   统率上限
	Constitution = 4, --   体质上限
}


local function _getSkillAdd(nomal, data, index)
	for key,skillData in pairs(data) do
		if key == index or key == m_allSoldierType then
			return nomal * skillData[2] / 1000 + skillData[1]
		end
	end
	return 0
end

local function _getSoldierAdd(heroType, level, soldierType, nomal)
	local skills = _getSkill(heroType)
	local soldierLimit1 = SkillConfigReader:getSoliderLimit(skills[1], level)
	local soldierLimit2 = SkillConfigReader:getSoliderLimit(skills[2], level)
	local addOne = _getSkillAdd(nomal, soldierLimit1, soldierType)
	local addTwo = _getSkillAdd(nomal, soldierLimit2, soldierType)
	return addOne + addTwo
end


local function _getDataValue(heroType, level, index, nomal)
	local skills = _getSkill(heroType)
	local data1 = SkillConfigReader:getAttributes(skills[1], level)
	local data2 = SkillConfigReader:getAttributes(skills[2], level)
	local addValue = _getSkillAdd(nomal, data1, index)
	addValue = addValue + _getSkillAdd(nomal, data2, index)
	return nomal + addValue
end

function M:getCommander(heroType, level)
	local nomal = HeroConfigRead:getCommander(heroType) * HeroGrowthConfigRead:getCommanderRatio(level)
	return _getDataValue(heroType, level, m_keyIndex.Commander, nomal)
end

function M:getForce(heroType, level)
	local nomal = HeroConfigRead:getForce(heroType) * HeroGrowthConfigRead:getForceRatio(level)
	return _getDataValue(heroType, level, m_keyIndex.Force, nomal)
end

function M:getBrains(heroType, level)
	local nomal = HeroConfigRead:getBrains(heroType) * HeroGrowthConfigRead:getBrainsRatio(level)
	return _getDataValue(heroType, level, m_keyIndex.Brains, nomal)
end

function M:getCharm(heroType, level)
	local nomal = HeroConfigRead:getCharm(heroType) * HeroGrowthConfigRead:getCharmRatio(level)
	return nomal
end

function M:getConstitution(heroType, level)
	local nomal = HeroConfigRead:getConstitution(heroType) * HeroGrowthConfigRead:getConstitutionRatio(level)
	return _getDataValue(heroType, level, m_keyIndex.Constitution, nomal)
end

function M:getTroops(heroType, level, soldierType)
	local nomal = HeroConfigRead:getTroops(heroType) * HeroGrowthConfigRead:getTroopsRatio(level)
	local addTroops = _getSoldierAdd(heroType, level, SoldierConfigReader:getType(soldierType), nomal)
	return nomal + addTroops
end

function M:getEnergySpeed(heroType, level)
	local nomal = HeroConfigRead:getEnergySpeed(heroType)
	return nomal
end

return M