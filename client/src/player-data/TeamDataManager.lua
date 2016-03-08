local TeamData = require("player-data.TeamData")
local SoldierDataManager = require("player-data.SoldierDataManager")
local HeroDataManager = require("player-data.HeroDataManager")

local M = {}
local TeamState = 
{
    All     = 0,
    Ready   = 1, 
    GoOut   = 2,
    Guard   = 3,    
}

local kArmyCreate = "army_create"

local function _postEvent()
    Listener:postEvent(Listener.EventName.onListenTeamDataChange)
end

function M:startMailListener()
    SocketManager:addObserver(self)
end

function M:stopMailListener()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kArmyCreate then
        if msgTable.code == 0 then
            TeamDataManager:createTeamData(msgTable.army)
        end
    end
end

-- 登录时的初始化数据
function M:initTeamListFromServer(msgTable)
    local list = {}
    for _, value in pairs(msgTable) do
        local armyId = value.army_id
        list[armyId] = TeamData:newTeamData(value)
    end
    return list
end

-- 获取军队数据
function M:getTeamData(armyId)
    local teamList = PlayerData:getTeamList()
    return teamList[armyId]
end

function M:getTeamDataByHeroId(heroId)
    local teamList = PlayerData:getTeamList()
    for _,teamData in pairs(teamList) do
        if heroId == teamData:getHeroId() then
            return teamData
        end
    end
    return nil
end

-- 创建军队
-- 对士兵的数量，武将的状态进行处理
function M:createTeamData(msgTable)
    Print:Table(msgTable, "create team data")
    local armyId = msgTable.army_id
    assert(armyId)

    local teamList = PlayerData:getTeamList()
    local teamData = TeamData:newTeamData(msgTable)
    teamList[armyId] = teamData
    return teamData
end

function M:updateTeamData(msgTable)
    local armyId = msgTable.army_id
    assert(armyId)
    
    local teamList = PlayerData:getTeamList()
    local teamData = teamList[armyId]
    if teamData then
        teamData:updateTeamData(msgTable)
    else 
        teamData = self:createTeamData(msgTable)
        teamList[armyId] = teamData
    end
    _postEvent()
    return teamData
end

function M:updateTeamSoldierNumber(msgTable)
    Print:Table(msgTable)
    local armyId = msgTable.army_id
    local armyNumber = msgTable.army_number
    local soldierNumber = msgTable.soldier_number
    assert(armyId)
    
    local teamList = PlayerData:getTeamList()
    if nil == teamList[armyId] then
        return
    end

    local teamData = teamList[armyId]
    local soldierType = teamData:getSoldierType()
    SoldierDataManager:updateSoldierNumber(soldierType, soldierNumber)
    
    teamData:updateArmyNumber(armyNumber)
end

function M:removeTeamData(armyId)
    assert(armyId)
    local teamList = PlayerData:getTeamList()
    teamList[armyId] = nil
    _postEvent()
end

function M:setState(armyId, newState)
    assert(armyId and newState)
    local teamList = PlayerData:getTeamList()
    local teamData = teamList[armyId]
    if teamData then 
        teamData:setState(newState)
    end
end

function M:updateCooridnate(armyId, i, j)
    assert(armyId and i and j)
    local teamList = PlayerData:getTeamList()
    local teamData = teamList[armyId]
    if teamData then 
        teamData:updateCoor(i, j)
    end
end

function M:getReadyTeamList()
    return self:_getTeamList(TeamState.Ready)
end

function M:getGoOutTeamList()
    return self:_getTeamList(TeamState.GoOut)
end

function M:getGuardTeamList()
    return self:_getTeamList(TeamState.Guard)
end

function M:_getTeamList(state)
    local teamList = PlayerData:getTeamList()
    if TeamState.All == state then 
        return teamList
    end

    local tmpList = {}
    for _,teamData in pairs(teamList) do
        if state == teamData:getState() then
            table.insert(tmpList, teamData)
        end
    end
    return tmpList
end

return M