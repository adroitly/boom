local BattleUtils = require("ui.map.logic.BattleUtils")

local M = {}

local function _changeBuildingOwner(msgTable)
    local x = msgTable.x 
    local y = msgTable.y
    assert(x and y)
    
    local newOwnerId = msgTable.owner_id
    local uniqueId = Utils:getUniqueId(x, y)
    local buildingDataManager = MapManager:getBuildingDataManager()
    local buildingData = buildingDataManager:findData(uniqueId)
    if buildingData then 
        buildingData:changeOwnerId(newOwnerId)
    end
end

function M:action(msgTable)
    -- Print:Table(msgTable, "building occupy callback")
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    local code = msgTable.code
    assert(code and playerId and armyId)

    if code == 0 then
        _changeBuildingOwner(msgTable)

        local armyDataManager = MapManager:getArmyDataManager()
        local armyData = armyDataManager:findArmyData(playerId, armyId)
        if not armyData then 
            return
        end
        
        local mapDataManager = MapManager:getMapDataManager()
        mapDataManager:buildingGuardAction(armyData)
        BattleUtils:setWaitStatus(armyData)
        return
    end

    -- 停止军队
    BattleUtils:setArmyWaitStatus(playerId, armyId)
    if ServerErrorCode.BUILDING_HP == code then 
        CommonUI:lightTips("城墙的血量大于0，需要先攻破城墙")
    elseif ServerErrorCode.BUILDING_GARRISONS_SIZE == code then
        CommonUI:lightTips("已经有人驻守，无法占领")
    else
        local text = string.format("占领失败，错误码=%d", code)
        CommonUI:lightTips(text)
    end

end

return M