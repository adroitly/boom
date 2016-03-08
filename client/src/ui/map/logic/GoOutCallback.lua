local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
local MapConfig = require("ui.map.data-manager.MapConfig")
local TeamData = require("player-data.TeamData")
local TeamDataManager = require("player-data.TeamDataManager")
local M = {}

local function _changeViewCenter(goOutInfo)
    local twoDCoor = GoOutInfo:getTwoDCoor(goOutInfo)
    local localCoor = MapConfig:twoDToLocal(twoDCoor)
    local newPosition = MapConfig:getPositionFromCoordinate(localCoor)

    local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:changeViewCenterToPosition(newPosition)
end

local function _createArmyLead(armyId)
    local playerId = PlayerData:getPlayerId()

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if armyData then
        local armyLeadLayer = MapManager:getArmyLeadLayer()
        armyLeadLayer:createArmy(armyData)
        armyLeadLayer:resetPosition()
    end
end

local function _createArmy(armyId, msgTable)
    local teamData = TeamDataManager:getTeamData(armyId)
    if not teamData then 
        local text = string.format(__Localized("军队id=%d不存在了"), armyId)
        CommonUI:lightTips(text)
        return
    end
    
    if msgTable then 
        local outArmy = msgTable.army 
        local armyInfo = outArmy.army
        -- Print:Table(armyInfo, "go out =")
        teamData:updateTeamData(armyInfo)
    end
    
    local playerId = PlayerData:getPlayerId()
    local armyDataManager = MapManager:getArmyDataManager()
    if not armyDataManager:isArmyExist(playerId, armyId) then 
        local armyData = armyDataManager:addArmyWithTeamData(teamData)

        local armySpriteManager = MapManager:getArmySpriteManager()
        armySpriteManager:armyDidCreate(armyData)
    end
end

local function _getLocalCoor(goOutInfo)
    local twoDCoor = GoOutInfo:getTwoDCoor(goOutInfo)
    local localCoor = MapConfig:twoDToLocal(twoDCoor)
    return localCoor
end

local function _moveAction(armyId, goOutInfo)
    local playerId = PlayerData:getPlayerId()
    local toCoor = _getLocalCoor(goOutInfo)
    local armyDataManager = MapManager:getArmyDataManager()
    armyDataManager:moveArmy(playerId, armyId, toCoor.i, toCoor.j)
end

local function _attackBuilding(armyId, goOutInfo)
    local toCoor = _getLocalCoor(goOutInfo)
    local armyDataManager = MapManager:getArmyDataManager()
    local playerId = PlayerData:getPlayerId()
    armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.AttackBuilding, toCoor)
end

local function _occupyBuilding(armyId, goOutInfo)
    local toCoor = _getLocalCoor(goOutInfo)
    local armyDataManager = MapManager:getArmyDataManager()
    local playerId = PlayerData:getPlayerId()
    armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.OccupyBuilding, toCoor)
end

local function _attackArmy(armyId, goOutInfo)
    local playerId = PlayerData:getPlayerId()
    local armyDataManager = MapManager:getArmyDataManager()

    local toPlayerId = GoOutInfo:getToPlayerId(goOutInfo)
    local toArmyId = GoOutInfo:getToArmyId(goOutInfo)
    assert(toPlayerId and toArmyId)
    armyDataManager:attackArmy(playerId, armyId, toPlayerId, toArmyId)
end

local function _aid(armyId, goOutInfo)
    local toCoor = _getLocalCoor(goOutInfo)
    local armyDataManager = MapManager:getArmyDataManager()
    local playerId = PlayerData:getPlayerId()
    armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.Aid, toCoor)
end

local function _pickup(armyId, goOutInfo)
    local toCoor = _getLocalCoor(goOutInfo)
    local playerId = PlayerData:getPlayerId()
    local armyDataManager = MapManager:getArmyDataManager()
    armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.Pickup, toCoor)
end

local function _goOutAction(armyId, goOutInfo)
    local operations = 
    {
        [Enum.GoOutOperation.Move]              = _moveAction,
        [Enum.GoOutOperation.AttackBuilding]    = _attackBuilding,
        [Enum.GoOutOperation.OccupyBuilding]    = _occupyBuilding, 
        [Enum.GoOutOperation.AttackArmy]        = _attackArmy,
        [Enum.GoOutOperation.Aid]               = _aid,
        [Enum.GoOutOperation.Pickup]            = _pickup,
    }

    local operation = GoOutInfo:getOperation(goOutInfo)
    for key,fun in pairs(operations) do
        if key == operation then 
            fun(armyId, goOutInfo)
            return
        end
    end

    local text = string.format("有未处理的出征行为operation=%d", operation)
    CommonUI:lightTips(text)
end

-- 出征
function M:goOutCallback(armyId, goOutInfo, msgTable)
    assert(armyId and goOutInfo)

    -- 创建出征军队
    _createArmy(armyId, msgTable)

    -- 出征
    _goOutAction(armyId, goOutInfo)
    
    -- 跳转视图到目的地
    _changeViewCenter(goOutInfo)

    -- 主界面增加出征军队的Icon
    _createArmyLead(armyId)
end

return M