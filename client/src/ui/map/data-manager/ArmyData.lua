local MapConfig = require("ui.map.data-manager.MapConfig")
local TeamData = require("player-data.TeamData")
local HeroData = require("player-data.HeroData")
local HeroDataManager = require("player-data.HeroDataManager")

local M = class("ui.map.data-manager.ArmyData")

function M:newArmyDataWithTeamData(teamData, msgTable)
	local playerId = PlayerData:getPlayerId()
	local contryId = PlayerData:getUserInfoData():getCountryId()
	local guildId  = PlayerData:getGuildId()

	local heroId = teamData:getHeroId()
	local heroData = HeroDataManager:getHeroDataById(heroId)
	return M.new(playerId, contryId, guildId, teamData, heroData)
end

function M:newArmyDataWithInfo(msgInfo)
	local playerId = msgInfo.player_id
	local contryId = msgInfo.contry_id
	local guildId  = msgInfo.guild_id
	local armyInfo = msgInfo.army
	local heroInfo = msgInfo.hero
	assert(playerId and contryId and guildId and armyInfo and heroInfo)
	local teamData = TeamData:newTeamData(armyInfo)
	local heroData = HeroData.new(heroInfo)

	return M.new(playerId, contryId, guildId, teamData, heroData)
end

function M:ctor(playerId, contryId, guildId, teamData, heroData)
	self._playerId = playerId
	self._contryId = contryId
	self._guildId  = guildId
	self._teamData = teamData
	self._heroData = heroData

	self._status  	= Enum.GoOutOperation.Wait

	local coor 		= teamData:getCooridnate()
	local pos 		= MapConfig:getPositionFromCoordinate(coor)
	self._position 	= pos
	self._toCoor 	= coor

	self._speedTime  = 2
	self._range 	 = 1
	self._isSelected = false
end

function M:refreshArmyData(msgTable)
	assert(msgTable)
	self._teamData:updateTeamData(msgTable.army)
	self._heroData:updateHeroData(msgTable.hero)
end

function M:getTeamData()
	return self._teamData
end

function M:getPlayerId()
	return self._playerId
end

function M:getArmyId()
	return self._teamData:getArmyId()
end

function M:getUniqueId()
	return self:getPlayerId() .. self:getArmyId()
end

function M:getCountryId()
	return self._contryId
end

function M:getGuildId()
	return self._guildId
end

function M:setStatus(newStatus)
	assert(newStatus)
	self._status = newStatus
end

function M:getStatus()
	return self._status
end

function M:getPosition()
	return self._position
end

function M:getFromCoordinate()
	return self._teamData:getCooridnate()
end

function M:setFromCoordinate(coor)
	assert(coor.i)
	self._teamData:updateCooridnate(coor)
end

function M:setPosition(pos)
	assert(pos.x and pos.y)
	self._position = cc.p(pos.x, pos.y)
end

function M:getToCoordinate()
	return self._toCoor
end

function M:setToCoordinate(coor)
	assert(coor.i and coor.j)
	self._toCoor = MapConfig:coordinate(coor.i, coor.j)
end

function M:getSpeedTime()
	return self._speedTime
end

function M:isFromEqualTo()
	local fromCoor = self._teamData:getCooridnate()
	local toCoor = self:getToCoordinate()
	return fromCoor.i==toCoor.i and
			fromCoor.j==toCoor.j
end

function M:getRange()
	return self._range
end

function M:getArmyCount()
	return self._teamData:getSoldierNumber()
end

function M:setArmyCount(newNumber)
	self._teamData:updateArmyNumber(newNumber)
end

function M:setSelected(isSelected)
	self._isSelected = isSelected
end

function M:isSelected()
	return self._isSelected
end

function M:getHeroData()
	return self._heroData
end

return M