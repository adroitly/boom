local BattleUtils = require("ui.map.logic.BattleUtils")
local BaseSpritesManagerUtils = require("ui.map.layer-manager.BaseSpritesManagerUtils")
local M = {}

local function _showLostHpAnimate(armyData, lostHp)
    local uniqueId = armyData:getUniqueId()
    local armySpriteManager = MapManager:getArmySpriteManager()
    BaseSpritesManagerUtils:showLostHpAnimate(armySpriteManager, uniqueId, lostHp)
end

local function _showBuff(armyData, skillId)
    if skillId > 0 then 
        print("警告：显示军队Buff动画未处理")
    end
end

local function _armyDeadAction(armyNumber, playerId, armyId)
    if armyNumber <=0 then 
        BattleUtils:armyDidDied(playerId, armyId)
    end
end

function M:action(msgTable)
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    local armyNumber = msgTable.army_number
    local armyLostNumber = msgTable.army_lost_number
    local skillId = msgTable.skill_id
    assert(playerId and armyId and armyNumber and armyLostNumber and skillId)

    -- Print:Table2(msgTable, "army lost callback")
    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId) 
    if not armyData then 
        -- 驻守人员被打死了
        _armyDeadAction(armyNumber, playerId, armyId)
        return
    end

    -- 播放buff
    _showBuff(armyData, skillId)

    -- 扣血动画
    _showLostHpAnimate(armyData, armyLostNumber)

    -- 刷新军队
    armyData:setArmyCount(armyNumber)

    -- 刷新地图军队数量
    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:updateArmyCount(armyData)

    -- 军队死亡
    _armyDeadAction(armyNumber, playerId, armyId)
end

return M

