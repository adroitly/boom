local ArmyData = require("ui.map.data-manager.ArmyData")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.army-status.AttackArmy", function()
    return require("ui.map.army-status.Base").new()
end)

local function _getAttackPlayerId( armyData )
    assert(armyData)
    return armyData.attackPlayerId
end

local function _setAttackPlayerId( armyData, toPlayerId )
    assert(armyData and toPlayerId)
    armyData.attackPlayerId = toPlayerId
end

local function _getAttackArmyId( armyData )
    assert(armyData)
    return armyData.attackArmyId
end

local function _setAttackArmyId( armyData, toArmyId )
    assert(toArmyId and armyData)
    armyData.attackArmyId = toArmyId
end

function M:onArmyIsNearDesination(armyData)
    local toCoor = armyData:getToCoordinate()
    local fromCoor = armyData:getFromCoordinate()
    local distance = MapConfig:getDistance(fromCoor, toCoor)
    return armyData:getRange() >= distance
end

function M:onArmyDidAction(armyData)
    local toPlayerId = _getAttackPlayerId(armyData)
    local toArmyId = _getAttackArmyId(armyData)
    local toCoor = armyData:getToCoordinate()

    local fromCoor = armyData:getFromCoordinate()
    local armyId = armyData:getArmyId()

    local sendData = {from_x=fromCoor.i, from_y=fromCoor.j, army_id=armyId, 
            to_x=toCoor.i, to_y=toCoor.j, to_player_id=toPlayerId, to_army_id=toArmyId}
    SocketManager:send(Command.AttackArmy, sendData)
end


function M:beginAttack(armyData, toArmyData)    
    assert(armyData and toArmyData)
    
    _setAttackPlayerId(armyData, toArmyData:getPlayerId())
    _setAttackArmyId(armyData, toArmyData:getArmyId())

    local targetCoor = toArmyData:getFromCoordinate()
    self:begin(armyData, targetCoor)
end

return M