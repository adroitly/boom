
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = {}

local function _createArmy(msgTable)
    local playerId = msgTable.player_id
    local armyId = msgTable.army.army_id
    assert(playerId and armyId)

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if not armyData then 
        armyData = armyDataManager:addArmyData(msgTable)
        local armySpriteManager = MapManager:getArmySpriteManager()
        armySpriteManager:armyDidCreate(armyData)
    end
end

local function _moveArmy(msgTable)
    local armyInfo = msgTable.army 
    assert(armyInfo)

    local playerId = msgTable.player_id
    local armyId = armyInfo.army_id
    local fromx = armyInfo.from_x
    local fromy = armyInfo.from_y
    assert(playerId and armyId and fromx and fromy)

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    local newFromCoor = MapConfig:coordinate(fromx, fromy)
    local fromCoor = armyData:getFromCoordinate()
    if fromCoor.i==newFromCoor.i and fromCoor.j==newFromCoor.j then 
        return
    end

    if not PlayerData:isOwner(playerId) then 
        armyDataManager:moveArmy(playerId, armyId, newFromCoor.i, newFromCoor.j)
    end
end

local function _refreshData(msgTable)
    local playerId = msgTable.player_id
    local armyId = msgTable.army.army_id

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    armyData:refreshArmyData(msgTable)
end

function M:action(msgTable)    
    -- Print:Table2(msgTable, string.format("outside army id =", msgTable.army.army_id))

    -- 不存在则创建
    _createArmy(msgTable)
    
    -- 移动
    _moveArmy(msgTable)

    -- 刷新数据
    _refreshData(msgTable)
end

return M