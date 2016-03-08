local MapConfig = require("ui.map.data-manager.MapConfig")
local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
local MapDataSocket = require("ui.map.data-manager.MapDataSocket")

local M = class("ui.map.data-manager.MapDataManager")

function M:ctor()
	self._heartBeat = require("ui.map.data-manager.HeartBeat").new()
	self._armyDataManager = require("ui.map.data-manager.ArmyDataManager").new()

	self._buildingDataManager = require("ui.map.data-manager.BuildingDataManager").new()
	self._randomResourceManager = require("ui.map.data-manager.BuildingDataManager").new()
end

function M:initUserInfo()
	self:_getViewDataByCoor(PlayerData:getHomeCoor())
end

function M:getArmyDataManager()
	return self._armyDataManager
end

function M:getBuildingDataManager()
	return self._buildingDataManager
end

function M:getRandomResourceManager()
	return self._randomResourceManager
end

function M:openSchedule()
	SocketManager:addObserver(self)
    Timer:addTimer(self)
end

function M:onUpdate(dt)
	self:_update(dt)
end

function M:stopSchedule()
	SocketManager:removeObserver(self)
	Timer:removeTimer(self)
end

function M:clean()
	self:stopSchedule()
end

function M:getSelfArmysData()
	return self._armyDataManager:getSelfArmysData()
end

function M:occupyAction(armyData)
	assert(armyData)
	local armyId = armyData:getArmyId()
	local fromCoor = armyData:getFromCoordinate()
	local toCoor = armyData:getToCoordinate()
	local sendData = { army_id=armyId, from_x=fromCoor.i, from_y=fromCoor.j,
						 to_x=toCoor.i, to_y=toCoor.j }
	
	SocketManager:send(Command.BuildingOccupy, sendData)
end

function M:buildingGuardAction(armyData)
	assert(armyData)

	local playerId = armyData:getPlayerId()
	local armyId = armyData:getArmyId()
	local fromCoor = armyData:getFromCoordinate()
	local toCoor = armyData:getToCoordinate()
	local sendData = { army_id=armyId, from_x=fromCoor.i, from_y=fromCoor.j,
						 to_x=toCoor.i, to_y=toCoor.j }
	-- Print:Table(sendData, "send building guard")
	SocketManager:send(Command.BuildingGuard, sendData)
end

------------ SocketManager delegate begin ------------
function M:onSocketClientDidCallback(cmd, msgTable, key)
	if ("StatusParseCmdError" == cmd) or 
		("StatusServerClose" == cmd) or 
		("StatusCheckCRCError" == cmd) then 
		self:stopSchedule()	
	end 
	
	MapDataSocket:socketCallback(cmd, msgTable)
end
------------ SocketManager delegate end ------------

function M:_getViewDataByCoor(viewCoor)
	local viewCenter = {x=viewCoor.i, y=viewCoor.j }
	SocketManager:send(Command.ViewDataGet, viewCenter)
end

function M:_update(dt)
	self._heartBeat:update(dt)
	
	self._armyDataManager:update(dt)
end

return M


