
local BattleUtils = require("ui.map.logic.BattleUtils")
local BaseSpritesManagerUtils = require("ui.map.layer-manager.BaseSpritesManagerUtils")
local SkillAnimate = require("ui.common.SkillAnimate")
local M = {}

local function _setWaitStatusWhenBeAttack(toPlayerId, toArmyData)
    if not toArmyData then 
        return
    end

    -- 如果被攻击则停止移动状态
    if PlayerData:isOwner(toPlayerId) then 
        local status = toArmyData:getStatus()
        if Enum.GoOutOperation.Move == status or 
            Enum.GoOutOperation.GoHome == status then 
            BattleUtils:setWaitStatus(toArmyData)
        end
    end
end

local function _updateArmyCount(armyData, nowArmyCount)
    if armyData then 
        armyData:setArmyCount(nowArmyCount)
    end
end

local function _setMoveWhenTargetDied(armyData, toArmyCount)
    if toArmyCount>0 then
        return
    end

    if not armyData then 
        return
    end

    local armyCount = armyData:getArmyCount()
    if armyCount<=0 then 
        return
    end

    local playerId = armyData:getPlayerId()
    local armyId = armyData:getArmyId()
    local toCoor = armyData:getToCoordinate()
    local armyDataManager = MapManager:getArmyDataManager()
    if PlayerData:isOwner(playerId) then 
        armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.Move, toCoor)
    else 
        BattleUtils:setWaitStatus(armyData)
    end
end


local function _removeArmyWithNowArmyCount(playerId, armyId, nowArmyCount)
    if nowArmyCount <=0 then 
        BattleUtils:armyDidDied(playerId, armyId)
    end
end

local function _showAnimate(armyData, toArmyData)
    local armySpriteManager = MapManager:getArmySpriteManager()

    if armyData and toArmyData then 
        local pos = toArmyData:getPosition()
        armySpriteManager:playAttackAnimate(armyData, pos)

        local toPos = armyData:getPosition()
        armySpriteManager:playAttackAnimate(toArmyData, toPos)
    end
    
    armySpriteManager:updateArmyCount(armyData)
    armySpriteManager:updateArmyCount(toArmyData)
end

local function _attackAnimate(armyData, toArmyData)
    local pos = toArmyData:getPosition()
    local toPos = armyData:getPosition()
    local direction = BattleUtils:getDirectionScaleX(pos.x, toPos.x)

    local animateSprite = BattleUtils:getAttackEffectAnimateSprite(armyData)
    animateSprite:setScaleX(direction)

    local armySpriteManager = MapManager:getArmySpriteManager()
    local armySpriteNode = armySpriteManager:findArmySpriteNode(toArmyData)
    armySpriteNode:addChild(animateSprite)
    local size = armySpriteNode:getContentSizeCache()
    animateSprite:setPosition(Point:centerBySize(size))
end

local function _showAttackAnimate(armyData, toArmyData)
    if armyData and toArmyData then 
        _attackAnimate(armyData, toArmyData)

        _attackAnimate(toArmyData, armyData)
    end 
end

local function _skillAnimate(armyData, skillId)
    local armySpriteManager = MapManager:getArmySpriteManager()
    local armySpriteNode = armySpriteManager:findArmySpriteNode(armyData)
    if not armySpriteNode then 
        return
    end

    SkillAnimate:action(armySpriteNode, skillId)
end

local function _showSkillAnimate(armyData, skillIds)
    if not armyData then 
        return 
    end

    for _, skillId in pairs(skillIds) do
        _skillAnimate(armyData, skillId)
    end
end

function M:action(msgTable)
    -- Print:Table2(msgTable, "attack army callback")
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    local skillIds = msgTable.skill_ids

    local toPlayerId = msgTable.to_player_id
    local toArmyId = msgTable.to_army_id
    local toSkillIds = msgTable.to_skill_ids
    assert(playerId and armyId and skillIds and 
        toPlayerId and toArmyId and toSkillIds)

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    local toArmyData = armyDataManager:findArmyData(toPlayerId, toArmyId)

    -- 被攻击则停止移动状态
    _setWaitStatusWhenBeAttack(toPlayerId, toArmyData)

    -- 刷新士兵数量
    -- _updateArmyCount(armyData, armyNumber)
    -- _updateArmyCount(toArmyData, toArmyNumber)

    -- 显示攻击动画
    _showAnimate(armyData, toArmyData)

    -- 显示攻击特效
    _showAttackAnimate(armyData, toArmyData)

    -- 技能特效
    _showSkillAnimate(armyData, skillIds)
    _showSkillAnimate(toArmyData, toSkillIds)

    -- 目标死亡则移动到目标点
    -- _setMoveWhenTargetDied(armyData, toArmyNumber)

    -- 删除军队
    -- _removeArmyWithNowArmyCount(playerId, armyId, armyNumber)
    -- _removeArmyWithNowArmyCount(toPlayerId, toArmyId, toArmyNumber)

end

return M

