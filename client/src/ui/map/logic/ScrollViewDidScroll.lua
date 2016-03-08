
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.logic.cc.ScrollViewDidScroll")

local function _updateCoordinateLayer(viewCoor)
    local twoDCoor = MapConfig:localTo2D(viewCoor)

    local coordinateLayer = MapManager:getCoordinateLayer()
    coordinateLayer:showCoordinate(twoDCoor)
end

local function _updateCastleArrowPointLayer(centerPosition)
    local castlePointArrowLayer = MapManager:getCastlePointArrowLayer()
    castlePointArrowLayer:showCastlePointArrow(centerPosition)
end

local function _getViewData(coor)
    assert(coor.i and coor.j)
    local viewChangeData = {player_id=PlayerData:getPlayerId(), x=coor.i, y=coor.j}
    local to2d = MapConfig:localTo2D(coor)
    SocketManager:send(Command.ViewChange, viewChangeData)
end

local function _recoverArmy(viewCoor)
    local armySpriteManager = MapManager:getArmySpriteManager()
    local armyDataManager = MapManager:getArmyDataManager()
    armyDataManager:recoveryDataInCenterCoor(viewCoor, function(armyData)
        local uniqueId = armyData:getUniqueId()
        armySpriteManager:removeSpriteDataByUniqueId(uniqueId)
    end)
end

local function _recoverBuilding(viewCoor)
    assert(viewCoor.i)

    local buildingDataManager = MapManager:getBuildingDataManager()
    local buildingSpriteManager = MapManager:getBuildingSpriteManager()
    buildingDataManager:recoveryDataInCenterCoor(viewCoor, function(buildingData)
        local uniqueId = buildingData:getUniqueId()
        buildingSpriteManager:removeSpriteDataByUniqueId(uniqueId)
    end)
end

local function _recoverRandomResource(viewCoor)
    local randomResourceManager = MapManager:getRandomResourceManager()
    local randomResSpriteManager = MapManager:getRandomResourceSpriteManager()
    randomResourceManager:recoveryDataInCenterCoor(viewCoor, function(buildingData)
        local uniqueId = buildingData:getUniqueId()
        randomResSpriteManager:removeSpriteDataByUniqueId(uniqueId)
    end)
end

function M:ctor()
    self._viewCenterPosition = cc.p(0, 0)
    self._viewCoordimate = MapConfig:coordinate(0, 0)
end

function M:_isFastMove(centerPosition)
    local sub = cc.pSub(self._viewCenterPosition, centerPosition)
    local max = math.max(math.abs(sub.x), math.abs(sub.y))
    return max > 25
end

function M:_refreshView(centerPosition)
    self._viewCenterPosition = centerPosition

    local viewCoor = MapConfig:getCoordinateFromPosition(centerPosition)
    local distance = MapConfig:getDistance(self._viewCoordimate, viewCoor)
    if distance > 0 then 
        _recoverArmy(viewCoor)
        _recoverBuilding(viewCoor)
        _recoverRandomResource(viewCoor)
        
        self._viewCoordimate = viewCoor
        _getViewData(viewCoor)

        _updateCoordinateLayer(viewCoor)
    end
end

function M:didScroll(centerPosition)
    _updateCastleArrowPointLayer(centerPosition)

    if self:_isFastMove(centerPosition) then 
        self._viewCenterPosition = centerPosition
        return
    end
    
    self:_refreshView(centerPosition)
end

function M:changeViewCenter(centerPosition)
    self:_refreshView(centerPosition)
end

return M