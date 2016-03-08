local MapConfig = require("ui.map.data-manager.MapConfig")
local TeamDataManager = require("player-data.TeamDataManager")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local M = {}

function M:setWaitStatus(armyData)
    if not armyData then 
        return
    end

    armyData:setStatus(Enum.GoOutOperation.Wait)
    
    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:playWaitAnimate(armyData)
end

function M:setArmyWaitStatus(playerId, armyId)
    assert(playerId and armyId)
    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    self:setWaitStatus(armyData)
end

function M:resetArmyPosition(armyData)
    assert(armyData)

    local coor = armyData:getFromCoordinate()
    local pos = MapConfig:getPositionFromCoordinate(coor)
    armyData:setPosition(pos)

    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:updateArmySpritePosition(armyData, pos)
end

-- 与armyDidDied区别，在于没有删除TeamDataManager
-- 比如驻守，删除军队但不会删除TeamDataManager
function M:removeArmy(playerId, armyId)
    assert(playerId and armyId)

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if not armyData then 
        return
    end

    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:removeArmySprite(armyData)

    armyDataManager:removeArmy(playerId, armyId)

    -- 删除主界面的军队Icon
    if PlayerData:isOwner(playerId) then 
        local armyLeadLayer = MapManager:getArmyLeadLayer()
        armyLeadLayer:deleteArmy(armyData)
        armyLeadLayer:resetPosition()
    end     
end

function M:armyDidDied(playerId, armyId)
    self:removeArmy(playerId, armyId)

    if PlayerData:isOwner(playerId) then 
        TeamDataManager:removeTeamData(armyId)
    end
end

function M:changeOutsideArmyState(msgTable)
    local outsideArmy = msgTable.army 

    local armyInfo = outsideArmy.army 
    local playerId = outsideArmy.player_id
    local armyId = armyInfo.army_id
    assert(armyInfo and playerId and armyId)

    if PlayerData:getPlayerId()==playerId then 
        TeamDataManager:updateTeamData(armyInfo)            
    end

    self:removeArmy(playerId, armyId)   
end

function M:pickupRandomResource(x, y)
    assert(x and y)
    local uniqueId = Utils:getUniqueId(x, y)
    local randomResSpriteManager = MapManager:getRandomResourceSpriteManager()
    randomResSpriteManager:removeSpriteDataByUniqueId(uniqueId)

    local randomResourceManager = MapManager:getRandomResourceManager()
    randomResourceManager:removeData(uniqueId)
end

function M:canAttackFamousCity(buildingData)
    local isFamousCity = ResourcePointUtils:isFamousCity(buildingData:getBuildingId())
    if isFamousCity and (not PlayerData:isHasGuild()) then 
        CommonUI:lightTips(__Localized("您需要先加入势力才能攻打名城"))
        return false
    end
    return true 
end

function M:getAttackEffectId(armyData)
    local teamData = armyData:getTeamData()
    local soldierType = teamData:getSoldierType()
    return SoldierConfigReader:getAttackEffectId(soldierType)
end

function M:getAttackEffectPath(armyData)
    local attackEffectId = self:getAttackEffectId(armyData)
    local id = attackEffectId and attackEffectId or 1
    return string.format("attack-effect/%d/%d.plist", id, id)
end

function M:getAttackEffectAnimateSprite(armyData)
    local resPath = self:getAttackEffectPath(armyData)
    local animateSprite = SpriteAnimateRepeat.new(resPath, 1)
    animateSprite:setFrameRate(0.1)
    return animateSprite
end

function M:getCityDefLostEffect(buildingData)
    return string.format("effect/war-fire/war-fire.plist")
end

function M:getCityDefLostEffectAnimateSprite(buildingData)
    local resPath = self:getCityDefLostEffect(buildingData)
    local animateSprite = SpriteAnimateRepeatForver.new(resPath)
    animateSprite:setFrameRate(0.1)
    return animateSprite
end

function M:getDirectionScaleX(x1, x2)
    return x1<x2 and 1.0 or -1.0 
end

return M

