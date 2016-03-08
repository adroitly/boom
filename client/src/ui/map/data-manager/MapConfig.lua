
local M = {}

-- 共有几列几行的背景图
M.mapRow = 100     -- 列
M.mapLine = 50    -- 行

-- 每个背景图宽和高有多少个格子
M.mapWidthCount = 10
M.mapHeightCount = 20

-- 每个格子的宽高
M.tileWidth = 204.8
M.tileHeight = 102.4

local function _getMapWidthCount()
	return M.mapRow * M.mapWidthCount
end

local function _getMapHeightCount()
	return M.mapLine * M.mapHeightCount
end

-- 本地坐标转为正数的本地坐标
local function _localToPlusLocal(localCoor)
	local i = (localCoor.j - localCoor.i)
	local j = (localCoor.j + localCoor.i) 
	return M:coordinate(i, j)
end

local function _plusLocalToLocal(plusLocal)
	local i = (plusLocal.j - plusLocal.i) / 2
	local j = (plusLocal.i + plusLocal.j) / 2
	return M:coordinate(i, j) 
end

-- 四舍五入
local function _roundUp(value)
	return math.floor(value + 0.5)
end

local function _coordinateFromPosition(position)
	-- 这个公式是从上面getPositionFromCoordinate()换算得到
	local i = _roundUp(position.y/M.tileHeight - position.x/M.tileWidth)
	local j = _roundUp(position.y/M.tileHeight + position.x/M.tileWidth)
    return M:coordinate(i, j)
end

local function _length(coor, position)
	local pos = M:getPositionFromCoordinate(coor)
	return cc.pGetDistance(pos, position)
end

local function _isInCoordinate(myLength, coordinate, touchPosition)
	local len = _length(coordinate, touchPosition)
	return len < myLength
end



function M:coordinate(_i, _j)
	return {i=_i, j=_j}
end

function M:getPositionFromCoordinate(coordinate)
	local x = (coordinate.j - coordinate.i) * M.tileWidth * 0.5
	local y = (coordinate.j + coordinate.i) * M.tileHeight * 0.5
	return cc.p(x, y)
end

function M:getRectWithPosition(pos)
	return cc.rect(pos.x-M.tileWidth/2, pos.y-M.tileHeight/2, M.tileWidth, M.tileHeight )
end

function M:getRectWithCoordinate(coor)
	local pos = self:getPositionFromCoordinate(coor)
	return self:getRectWithPosition(pos)
end

-- 获取当前相邻格子数
function M:getBorderGrids(coor)
	return { M:coordinate(coor.i+1, coor.j), 
			 M:coordinate(coor.i, coor.j+1),
			 M:coordinate(coor.i, coor.j-1),
			 M:coordinate(coor.i-1, coor.j)  }
end

function M:getCoordinateFromPosition(position)
	local coor = _coordinateFromPosition(position)
	-- 因为是地图是菱形，所以需要判断点是否落到4个边角
	-- 判断position离哪个coor的中心点最近
	local selfLength = _length(coor, position)

	local cornerTable = self:getBorderGrids(coor)
	for _,value in pairs(cornerTable) do
		if _isInCoordinate(selfLength, value, position) then 
			return value 
		end 
	end
	return coor
end

-- 坐标点是否超出屏幕
function M:isValidCoordinate(localCoor)
	local newCoor = _localToPlusLocal(localCoor)
	newCoor.i = newCoor.i / 2
	newCoor.j = newCoor.j / 2
	return (newCoor.i>0 and newCoor.i<_getMapWidthCount()) and 
			(newCoor.j>0 and newCoor.j<_getMapHeightCount())
end

-- 本地坐标转2维数组坐标
function M:localTo2D(localCoor)
	local newCoor = _localToPlusLocal(localCoor) 

	newCoor.i = math.floor(newCoor.i / 2)
	if(newCoor.j%2 == 0) then 
		newCoor.i = newCoor.i - 1
	end 
	newCoor.j = newCoor.j - 1
	return newCoor
end

function M:twoDToLocal(twoD)
	local x = twoD.i 
	local y = twoD.j + 1

	x = math.floor(x * 2)
	if y%2 ~= 0 then 
		x = x + 1
	else 
		x = x + 2
	end

	return _plusLocalToLocal(self:coordinate(x, y))
end

function M:getDistance(startCoor, endCoor)
 	assert(startCoor and endCoor)
	return math.abs(startCoor.i-endCoor.i) + math.abs(startCoor.j-endCoor.j)
end

-- TWO_D_W和TWO_D_H以及算法必须与服务器一致，用于回收数据
function M:canRecoveryInCenterCoor(curCoor, centerCoor)
	local twoDViewCoor = self:localTo2D(centerCoor)

	local TWO_D_W = 4
	local TWO_D_H = 15

	local from2DCoor = self:localTo2D(curCoor)
	if (from2DCoor.i>=twoDViewCoor.i-TWO_D_W and from2DCoor.i<twoDViewCoor.i+TWO_D_W) and 
		(from2DCoor.j>=twoDViewCoor.j-TWO_D_H and from2DCoor.j<twoDViewCoor.j+TWO_D_H)   then 
		return false
	end
	return true
end

-- 获取资源点（占4个格子）的坐标点
function M:getResourcePointPosition(coordinate)
	local x = (coordinate.j - coordinate.i) * M.tileWidth * 0.5
	local y = (coordinate.j + coordinate.i) * M.tileHeight * 0.5
	return cc.p(x + M.tileWidth/2, y)
end

-- 屏幕坐标点是否落在建筑物点内
function M:isPointInBuildCoor(point, coor)
	local curCoor = self:getCoordinateFromPosition(point)
	local buildCoors = self:getBuildCoors(coor)
	for _,buildCoor in pairs(buildCoors) do
		if curCoor.i==buildCoor.i and 
		    curCoor.j==buildCoor.j then 
			return true
		end
	end
end

-- 建筑物(城堡、农田、兵营、名城)的坐标点占4个格子
function M:getBuildCoors(coor)
	return { coor, 
			 M:coordinate(coor.i, coor.j+1),
			 M:coordinate(coor.i-1, coor.j+1),
			 M:coordinate(coor.i-1, coor.j)  }
end

return M

