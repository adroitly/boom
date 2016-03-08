local MapConfig = require("ui.map.data-manager.MapConfig")

local M = {}

local function _palyAttackAnimate(armyData)
    local toCoor = armyData:getToCoordinate()
    local pos = MapConfig:getPositionFromCoordinate(toCoor)

    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:playAttackAnimate(armyData, pos)
end

local function _sendAttackBuildingToServer(armyData)
    local toCoor = armyData:getToCoordinate()
    local fromCoor = armyData:getFromCoordinate()
    local armyId = armyData:getArmyId()
    local sendData = {from_x=fromCoor.i, from_y=fromCoor.j, army_id=armyId, 
            to_x=toCoor.i, to_y=toCoor.j}
    SocketManager:send(Command.AttackBuilding, sendData)
end

function M:isRangeWithBuilding(armyData)
    -- 攻击建筑物八面方位
    local toCoor = armyData:getToCoordinate()
    local fromCoor = armyData:getFromCoordinate()
    local buildCoors = MapConfig:getBuildCoors(toCoor)
    for _,coor in pairs(buildCoors) do
        local distance = MapConfig:getDistance(fromCoor, coor)
        if armyData:getRange() >= distance then
            return true
        end
    end
    return false
end

function M:attackBuilding(armyData)
    _palyAttackAnimate(armyData)

    _sendAttackBuildingToServer(armyData)
end

return M