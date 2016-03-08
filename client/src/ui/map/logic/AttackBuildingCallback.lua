
local MapConfig = require("ui.map.data-manager.MapConfig")
local BattleUtils = require("ui.map.logic.BattleUtils")
local M = {}

local function _updateBuildingInfo(x, y, remainCityDef, garrisonNumber)
    local uniqueId = Utils:getUniqueId(x, y)
    local buildingDataManager = MapManager:getBuildingDataManager()
    local buildingData = buildingDataManager:findData(uniqueId)
    if not buildingData then 
        return
    end

    buildingData:updateCityDef(remainCityDef)
    buildingData:updateGarrisonNumber(garrisonNumber)

    local buildingSpriteManager = MapManager:getBuildingSpriteManager()
    buildingSpriteManager:updateCityDef(buildingData)
end

local function _continueAction(playerId, armyId)
    assert(playerId and armyId)
    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if not armyData then 
        return
    end

    -- 非玩家自己不做处理
    if not PlayerData:isOwner(playerId) then 
        return
    end

    local status = armyData:getStatus()
    if Enum.GoOutOperation.AttackBuilding == status then 
        BattleUtils:setWaitStatus(armyData)
        CommonUI:lightTips("建筑物可以占领了")
    elseif Enum.GoOutOperation.OccupyBuilding == status then
        local mapDataManager = MapManager:getMapDataManager()
        mapDataManager:occupyAction(armyData)
        BattleUtils:setWaitStatus(armyData)
    else 
        print("提示是否需要处理，stauts =", status)
    end
end 

local function _attackEffect(armyData, x, y)
    local uniqueId = Utils:getUniqueId(x, y)
    local buildingSpriteManager = MapManager:getBuildingSpriteManager()
    local buildingSpriteNode = buildingSpriteManager:findSpriteByUniqueId(uniqueId)
    if not buildingSpriteNode then 
        return
    end

    local animateSprite = BattleUtils:getAttackEffectAnimateSprite(armyData)
    local posx, posy = buildingSpriteNode:getPosition()
    local direction = BattleUtils:getDirectionScaleX(posx, armyData:getPosition().x)
    animateSprite:setScaleX(direction)

    buildingSpriteNode:addChild(animateSprite)
end


function M:action(msgTable)
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    local armyNumber = msgTable.army_number
    local skillIds = msgTable.skill_ids

    local x = msgTable.x 
    local y = msgTable.y 
    local remainCityDef = msgTable.remain_cityDef
    local garrisonNumber = msgTable.garrison_number
    assert(playerId and armyId and armyNumber and x and y and 
            garrisonNumber and skillIds and remainCityDef)

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if not armyData then 
        print("攻击的军队已经不存在")
        return
    end

    -- 刷新城堡血量
    _updateBuildingInfo(x, y, remainCityDef, garrisonNumber)

    -- 刷新军队数量
    armyData:setArmyCount(armyNumber)
    
    -- 刷新精灵军队数量
    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:updateArmyCount(armyData)

    -- 播放攻击动画
    local coor = MapConfig:coordinate(x, y)
    local pos = MapConfig:getPositionFromCoordinate(coor)
    armySpriteManager:playAttackAnimate(armyData, pos)

    -- 播放攻击特效
    _attackEffect(armyData, x, y)

    -- 删除军队和精灵军队
    if armyNumber <=0 then 
        BattleUtils:armyDidDied(playerId, armyId)
        return
    end

    -- 城堡是否已被攻破
    if remainCityDef>0 or garrisonNumber>0 then 
        return
    end

    _continueAction(playerId, armyId)
end

return M

