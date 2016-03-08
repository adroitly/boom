
local ArmyData = require("ui.map.data-manager.ArmyData")
local MapConfig = require("ui.map.data-manager.MapConfig")


local GoOutInfo = require("ui.map.data-manager.GoOutInfo")

local M = class("ui.map.data-manager.ArmyDataManager")

local function _isVaildAttackData(armyData, toArmyData)
	if nil==armyData then
		print("attack error: my army not exist") 
		return false 
	end

	if nil==toArmyData then 
		print("attack error: attack army not exist")
		return false
	end

	if not PlayerData:isOwner( armyData:getPlayerId() ) then 
		print("attack error: armyData not owner")
		return false 
	end

	return true
end

local function _canRecoveryArmyDataInCenterCoor(armyData, centerCoor)
	if PlayerData:isOwner( armyData:getPlayerId() ) then 
		return false 
	end

	local curCoor = armyData:getFromCoordinate()
	return MapConfig:canRecoveryInCenterCoor(curCoor, centerCoor)
end


function M:ctor()
	self._dataManager = {}

	self:_initStatus()
end

function M:addArmyData(msgTable)
	local data = ArmyData:newArmyDataWithInfo(msgTable)
	table.insert(self._dataManager, data)
	return data
end

function M:safeAddArmyData(msgTable)
	local playerId = msgTable.player_id
	local armyId = msgTable.army_id
	if not self:isArmyExist(playerId, armyId) then
		return self:addArmyData(msgTable)
	end
end

function M:addArmyWithTeamData(teamData)
	assert(teamData)
	local armyData = ArmyData:newArmyDataWithTeamData(teamData)
	table.insert(self._dataManager, armyData)
	return armyData
end

function M:removeArmy(playerId, armyId)
	assert(playerId and armyId)
	for key, armyData in pairs(self._dataManager) do
		if armyData:getPlayerId()==playerId and 
			armyData:getArmyId()==armyId then 
			self._dataManager[key] = nil 
			return
		end
	end
end

function M:findArmyData(playerId, armyId)
	assert(playerId and armyId)
	for _, armyData in pairs(self._dataManager) do
		if armyData:getPlayerId()==playerId and 
			armyData:getArmyId()==armyId then 
			return armyData
		end
	end
	return nil
end

function M:findArmyDataSelected()
	for _, armyData in pairs(self._dataManager) do
		if armyData:isSelected() then
			return armyData
		end
	end
end

function M:updateArmyCount(playerId, armyId, armyCount)
	assert(playerId and armyId)
	local armyData = self:findArmyData(playerId, armyId)
	if armyData then
		armyData:setArmyCount(armyCount)
	end
end

function M:isArmyExist(playerId, armyId)
	local value = self:findArmyData(playerId, armyId)
	return value ~= nil
end

function M:changeStatus(playerId, armyId, newStatus, toCoor)
	assert(playerId and armyId and newStatus and toCoor.i)
	local armyData = self:findArmyData(playerId, armyId)
	if nil==armyData then 
		print("error : can't find army ", playerId, armyId)
		return
	end

	armyData:setStatus(newStatus)
	self._status[newStatus]:begin(armyData, toCoor)
end

function M:moveArmy(playerId, armyId, tarcoori, tarcoorj)
	local status = Enum.GoOutOperation.Move
	local toCoor = MapConfig:coordinate(tarcoori, tarcoorj)
	self:changeStatus(playerId, armyId, status, toCoor)
end

function M:attackArmyWithArmyData(armyData, toArmyData)
	if not _isVaildAttackData(armyData, toArmyData) then 
		return
	end

	local status = Enum.GoOutOperation.AttackArmy
	armyData:setStatus(status)
	self._status[status]:beginAttack(armyData, toArmyData)
end

function M:attackArmy(playerId, armyId, toPlayerId, toArmyId)
	local armyData = self:findArmyData(playerId, armyId)
	local toArmyData = self:findArmyData(toPlayerId, toArmyId)
	self:attackArmyWithArmyData(armyData, toArmyData)
end

function M:isCoordinateExist(coor)
	for _, armyData in pairs(self._dataManager) do
		local armyCoor = armyData:getFromCoordinate()
		if armyCoor.i==coor.i and armyCoor.j==coor.j then 
			return true
		end
	end
end

function M:update(dt)
	for _, armyData in pairs(self._dataManager) do
		local status = armyData:getStatus()
		local fun = self._status[status]
		if fun then 
			fun:update(armyData, dt)
		end
	end
end

function M:getSelfArmysData()
	local armys = {}
	for _, armyData in pairs(self._dataManager) do
		local playerId = armyData:getPlayerId()
		if PlayerData:isOwner(playerId) then 
			table.insert(armys, armyData)
		end
	end
	return armys
end

function M:arriveCommonCallback(msgTable)
	local playerId = msgTable.player_id
	local armyId = msgTable.army_id
	assert(playerId and armyId)
	
	local armyData = self:findArmyData(playerId, armyId)
	if not armyData then 
		return
	end

	local status = armyData:getStatus()
	local fun = self._status[status]
	if fun then 
		fun:arriveCallback(armyData, msgTable)
		return
	end

	CCLog("未处理status=%d", status)
end

function M:recoveryDataInCenterCoor(centerCoor, recoverSpriteFun)
	assert(recoverSpriteFun)
	for key, armyData in pairs(self._dataManager) do
		if _canRecoveryArmyDataInCenterCoor(armyData, centerCoor) then 
			recoverSpriteFun(armyData)
			self._dataManager[key] = nil
		end
	end 
end

function M:_initStatus()
	local statusTable = 
	{
		[Enum.GoOutOperation.Move] = require("ui.map.army-status.Move").new(),
		[Enum.GoOutOperation.Wait] = require("ui.map.army-status.Wait").new(),
		[Enum.GoOutOperation.AttackArmy] 	 = require("ui.map.army-status.AttackArmy").new(),
		[Enum.GoOutOperation.AttackBuilding] = require("ui.map.army-status.AttackBuilding").new(),
		[Enum.GoOutOperation.OccupyBuilding] = require("ui.map.army-status.OccupyBuilding").new(), 
		[Enum.GoOutOperation.GoHome]		 = require("ui.map.army-status.GoHome").new(),
		[Enum.GoOutOperation.Aid]			 = require("ui.map.army-status.Aid").new(),
		[Enum.GoOutOperation.Pickup]		 = require("ui.map.army-status.Pickup").new(),
	}

	self._status = {}
	for k,v in pairs(statusTable) do
		self._status[k] = v
	end
end


return M

