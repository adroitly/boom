
local BattleUtils = require("ui.map.logic.BattleUtils")
local M = {}

local function _attackSameGuild(armyData)
    CommonUI:lightTips(__Localized("城池已经被同势力占领"))
    BattleUtils:setWaitStatus(armyData)
end

local function _moveActoin(armyData)
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

local function _attackBuildingFailed(armyData)
    local playerId = armyData:getPlayerId()
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
        print("待处理，stauts =", status)
    end
end

function M:action(msgTable)
    local code = msgTable.code
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    assert(code and playerId and armyId)
    if 0==code then 
        return
    end

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if not armyData then 
        return 
    end

    local errorTable = 
    {
        [ServerErrorCode.FAIL]  = function(armyData)
            CommonUI:lightTips("失去攻击目标")
            _moveActoin(armyData)
        end,
        [ServerErrorCode.BOX_FAIL] = function(armyData)
            CommonUI:lightTips("攻击目标不存在")
            _moveActoin(armyData)
        end,
        [ServerErrorCode.ATTACK_DISTANCE_FAIL] = function(armyData)
            CommonUI:lightTips("攻击军队与目标不一致")
            BattleUtils:setWaitStatus(armyData)
        end,
        [ServerErrorCode.ATTACK_TO_ARMY_DEATH] = function(armyData)
            CommonUI:lightTips("敌方军队已经死亡")
            BattleUtils:setWaitStatus(armyData)
        end,
        [ServerErrorCode.ATTACK_MY_ARMY_DEATH] = function(armyData)
            BattleUtils:armyDidDied(armyData:getPlayerId(), armyData:getArmyId())
        end, 
        [ServerErrorCode.ATTACK_BUILDING_FAIL] = function(armyData)
            _attackBuildingFailed(armyData)
        end, 
        [ServerErrorCode.ATTACK_MYSELF_BUILDING] = function(armyData)
            CommonUI:lightTips(__Localized("您已经攻下城池"))
            BattleUtils:setWaitStatus(armyData)
        end, 
        [ServerErrorCode.ATTACK_FRIEND_BUILDING] = function(armyData)
            _attackSameGuild(armyData)
        end, 
        [ServerErrorCode.GUILD_SAME] = function(armyData)
            _attackSameGuild(armyData)
        end, 
        [ServerErrorCode.GUILD_NOT_EXSITS] = function(armyData)
            CommonUI:lightTips(__Localized("请先加入势力"))
            BattleUtils:setWaitStatus(armyData)
        end, 
        [ServerErrorCode.SAME_COUNTRY] = function(armyData)
            CommonUI:lightTips(__Localized("不能攻击相同国家"))
            BattleUtils:setWaitStatus(armyData)
        end,
        
    }

    -- Print:Table2(msgTable, "attack code callback")
    local fun = errorTable[code]
    if fun then 
        fun(armyData)
    else
        CommonUI:lightTips(string.format("未知错误,code=%d", code))
    end
end

return M

