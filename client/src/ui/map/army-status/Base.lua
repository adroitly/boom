local MapConfig = require("ui.map.data-manager.MapConfig")
local ArmyData = require("ui.map.data-manager.ArmyData")
local BattleUtils = require("ui.map.logic.BattleUtils")

local M = class("ui.map.army-status.Base")
local const_max_record_walk_road = 10
local function _talkSeverToNextCoor(armyData)
	local playerId = armyData:getPlayerId()
	if not PlayerData:isOwner(playerId) then 
		return
	end

	local nextCoor = armyData.nextCoor
	local armyId = armyData:getArmyId()
	local curCoor = armyData:getFromCoordinate()
	local arriveData = {player_id=playerId, army_id=armyId, 
				to_x=nextCoor.i, to_y=nextCoor.j}
	SocketManager:send(Command.Arrive, arriveData)
end

local function _dealWithStop(armyData)
	local fromCoor = armyData:getFromCoordinate()
	armyData:setToCoordinate(fromCoor)

	BattleUtils:setWaitStatus(armyData)
	BattleUtils:resetArmyPosition(armyData)
end

local function _noWayToGo(armyData)
	_dealWithStop(armyData)
	CommonUI:lightTips("已经无路可走")
end

local function _coordinationHasBeOccupied(armyData)
	_dealWithStop(armyData)
	CommonUI:lightTips("目标据点已经被别人占领")
end

local function _isCoordinateOffset(armyData, newFromCoor)
	local nowFromCoor = armyData:getFromCoordinate()
	local len = MapConfig:getDistance(nowFromCoor, newFromCoor)
	return len > 2
end

local function _isNeighborCoor(coor1, coor2)
	local distance = MapConfig:getDistance(coor1, coor2)
	return distance==1
end

local function _forceFixCoordination(armyData, msgTable)
	local newFromCoor = MapConfig:coordinate(msgTable.from_x, msgTable.from_y)
	assert(armyData and newFromCoor.i and newFromCoor.j)
	if _isCoordinateOffset(armyData, newFromCoor) then 
		print("超过2个格子则强制移动当前坐标点")
		armyData:setFromCoordinate(newFromCoor)

		local pos = MapConfig:getPositionFromCoordinate(newFromCoor)
		armyData:setPosition(pos)
	end
end

local function _resetStartData(armyData)
	armyData._elapseTime = 0
	armyData._lock = true
	armyData._arrived = false 

	local pos = armyData:getPosition()
	armyData.startx = pos.x
	armyData.starty = pos.y
end

local function _resetNextData(armyData, nextCoor)
	armyData.nextCoor = nextCoor
	local nextPos = MapConfig:getPositionFromCoordinate(nextCoor)
	armyData.endx = nextPos.x
	armyData.endy = nextPos.y
end

local function _removeInvalidCoordinate(borderGrids)
	for key, girdCoor in pairs(borderGrids) do
		if not MapConfig:isValidCoordinate(girdCoor) then 
			borderGrids[key] = nil
		end
	end
end

local function _removeGridsByCoordinate( borderGrids, coor )
	for key, girdCoor in pairs(borderGrids) do
		if girdCoor.i==coor.i and girdCoor.j==coor.j then 
			borderGrids[key] = nil
			return
		end
	end
end

local function _removeGridsByExcludeCoors(borderGrids, excludeCoors)
	for _, exclude in pairs(excludeCoors) do
		_removeGridsByCoordinate(borderGrids, exclude)
	end
end

local function _getShortestCoordinate(armyData, borderGrids)
	local toCoor = armyData:getToCoordinate()
	local targetPos = MapConfig:getPositionFromCoordinate(toCoor)
	local tmpKey = nil
	local shortDistance = 10000000
	for key, girdCoor in pairs(borderGrids) do
		local girdPos = MapConfig:getPositionFromCoordinate(girdCoor)
		local tmpDistance = cc.pGetDistance(targetPos, girdPos)
		if tmpDistance < shortDistance then 
			tmpKey = key
			shortDistance = tmpDistance
		end
	end
	return borderGrids[tmpKey]
end

local function _removeArmyExistCoordinate(borderGrids)
	local armyDataManager = MapManager:getArmyDataManager()
	for key,coor in pairs(borderGrids) do
		if armyDataManager:isCoordinateExist(coor) then 
			borderGrids[key] = nil
		end
	end

end

local function _getNextCoor(armyData)
	local curCoor = armyData:getFromCoordinate()

	-- 获取临近的四个点
	local borderGrids = MapConfig:getBorderGrids(curCoor)

	-- 剔除无效的点
	_removeInvalidCoordinate(borderGrids)

	-- 剔除之前走过的点
	_removeGridsByExcludeCoors(borderGrids, armyData.excludeCoors)

	-- 剔除客户端军队已经存在的点
	_removeArmyExistCoordinate(borderGrids)

	-- 寻找最短路径
	return _getShortestCoordinate(armyData, borderGrids)
end

local function _clearExcludeCoor( armyData )
	armyData.excludeCoors = {}
end

local function _addExcludeCoor( armyData, i, j )
	assert(armyData and i and j)
	if table.getn(armyData.excludeCoors) > const_max_record_walk_road then 
		table.remove(armyData.excludeCoors, 1)
	end

	local coor = MapConfig:coordinate(i, j)
	table.insert(armyData.excludeCoors, coor)
end

local function _isTargetHasBeOccupied(armyData)
	local fromCoor = armyData:getFromCoordinate()
	local toCoor = armyData:getToCoordinate()
	if _isNeighborCoor(fromCoor, toCoor) then
		local armyDataManager = MapManager:getArmyDataManager()
		if armyDataManager:isCoordinateExist(toCoor) then 
			_coordinationHasBeOccupied(armyData)
			return true
		end
	end
	return false
end

local function _goToNext(armyData)
	_resetStartData(armyData)

	-- 目标是否已经被军队占领
	if _isTargetHasBeOccupied(armyData) then 
		_coordinationHasBeOccupied(armyData)
		return
	end

	local nextCoor = _getNextCoor(armyData)
	if nil==nextCoor then 
		_noWayToGo(armyData)
		return
	end

	_resetNextData(armyData, nextCoor)
	_talkSeverToNextCoor(armyData)
end

function M:arriveCallback(armyData, msgTable)
	local code = msgTable.code
	local fromx = msgTable.from_x
	local fromy = msgTable.from_y
	assert(armyData and code and fromx and fromy)
	armyData._lock = false

	_forceFixCoordination(armyData, msgTable)

	local code = msgTable.code
	-- 占位成功
	if 0==code then 
		local fromCoor = armyData:getFromCoordinate()
		_addExcludeCoor(armyData, fromCoor.i, fromCoor.j)
		armyData:setFromCoordinate(armyData.nextCoor) 
		self:_arrivedAction(armyData)
		return
	end
	
	-- 占位失败，重新计算	
	local newFromCoor = MapConfig:coordinate(fromx, fromy)
	armyData:setFromCoordinate(newFromCoor)
	BattleUtils:resetArmyPosition(armyData)

	-- 目标点已经被人占领
	local toCoor = armyData:getToCoordinate()
	if _isNeighborCoor(newFromCoor, toCoor) then
		_coordinationHasBeOccupied(armyData)
		return
	end

	local nextCoor = armyData.nextCoor
	_addExcludeCoor(armyData, nextCoor.i, nextCoor.j)
	_goToNext(armyData)
end

function M:update(armyData, dt)
	armyData._elapseTime = armyData._elapseTime + dt
	if armyData._isMoveing then 
		local ratio = armyData._elapseTime / armyData:getSpeedTime()
		ratio = math.min(ratio, 1)

		local space = cc.p(armyData.endx-armyData.startx, armyData.endy-armyData.starty)
		local newPosition = cc.p(armyData.startx + space.x*ratio,  armyData.starty + space.y*ratio)
		armyData:setPosition(newPosition)

		local armySpriteManager = MapManager:getArmySpriteManager()
		armySpriteManager:armyDidMove(armyData)

		if ratio >= 1 then 
			self:_moveEnd(armyData)
			return
		end
	else 
		if armyData._elapseTime > armyData:getSpeedTime() then 
			armyData._elapseTime = 0
			self:onArmyDidAction(armyData)
		end
	end
end

function M:begin(armyData, toCoor)
	assert(armyData and toCoor.i and toCoor.j)
	armyData:setToCoordinate(toCoor)
	armyData._isMoveing = true
	armyData._elapseTime = armyData._elapseTime or 0
	
	if self:onArmyIsNearDesination(armyData) then
		armyData._isMoveing = false
		return
	end

	local fromCoor = armyData:getFromCoordinate()
	_clearExcludeCoor(armyData)
	_goToNext(armyData)
end

------------------------ 分割线 ------------------------
function M:onArmyIsNearDesination(armyData)
	assert(false, "请继承使用")
end

function M:onArmyDidAction(armyData)
	assert(false, "请继承使用")
end

function M:_arrivedAction(armyData)
	if false==armyData._lock and true==armyData._arrived then 
		if self:onArmyIsNearDesination(armyData) then
			armyData._isMoveing = false
			_clearExcludeCoor(armyData)
		else 
			_goToNext(armyData)
		end
	end
end

function M:_moveEnd(armyData)
	local playerId = armyData:getPlayerId()
	if PlayerData:isOwner(playerId) then 
		armyData._arrived = true
		self:_arrivedAction(armyData)
	else 
		BattleUtils:setWaitStatus(armyData)	
	end	
end

return M