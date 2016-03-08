local SoldierData = require("player-data.SoldierData")

local M = {}

-- 登录时的初始化数据
function M:initSoldiersListFromServer(msgTable)
    local list = {}
    for _, value in pairs(msgTable) do
        local soldierType = value.soldier_type
        list[soldierType] = SoldierData:newSoldierData(value)
    end
    return list
end

function M:updateSoldierNumber(soldierType, soldierNumber)
    local soldiersList = PlayerData:getSoldiers()
    local soldierData = soldiersList[soldierType]
    soldierData:updateSoldierNumber(soldierNumber)
end

function M:getSoldierNumber(soldierType)
    local soldiersList = PlayerData:getSoldiers()
    local soldierData = soldiersList[soldierType]
    return soldierData:getSoldierNumber()
end

-- 更新或添加单个士兵数据
function M:updateSoldierData(msgTable)
    local soldierType = msgTable.soldier_type
    local soldiersList = PlayerData:getSoldiers()
    if not soldiersList[soldierType] then
        soldiersList[soldierType] = SoldierData:newSoldierData(msgTable)
    else
        soldiersList[soldierType]:updateSoldierData(msgTable)
    end
    Listener:postEvent(Listener.EventName.onListenSoldierDataUpdate)
end

function M:getSoldierDataByType(soldierType)
    local soldiersList = PlayerData:getSoldiers()
    local soldierData = soldiersList[soldierType]
    return soldierData
end

return M