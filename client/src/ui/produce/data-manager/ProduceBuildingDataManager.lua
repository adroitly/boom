local ProduceBuildingData = require("ui.produce.data-manager.ProduceBuildingData")
local ProduceSoldierData = require("ui.produce.data-manager.ProduceSoldierData")
local ProduceResourceData = require("ui.produce.data-manager.ProduceResourceData")
local ProduceConfigReader = require("ui.produce.data-manager.ProduceConfigReader")
local M = {}

local kCastleProductSoldierReceive = "castle_product_soldier_receive"
local kCastleProductSoldierInfo = "castle_product_soldier_info"
local kCastleProductSoldierGet = "castle_product_soldier_get"
local kProduceBuildingInfoGet = "produce_building_info_get"
local kCastleProductItemReceive = "castle_product_item_receive"
local kCastleProductItemInfo = "castle_product_item_info"
local kCastleProduceItemGet = "castle_product_item_get"
local kGuildQuit = "guild_quit"

M.ProduceType = 
{
    Soldier = 1,
    Resources = 2,
}

function M:startDataListener()
    self._isNeedInit = false
    self._buildingDataList = {}
    SocketManager:addObserver(self)
end

function M:stopDataListener()
    SocketManager:removeObserver(self)
    self._buildingDataList = {}
end

function M:produceInfoRequest()
    self:getProduceBuildingInfo()
    self._isNeedInit = true
end

function M:getProduceBuildingInfo()
    SocketManager:send(kProduceBuildingInfoGet, {})
end

function M:getProduceSoldierInfo()
    SocketManager:send(kCastleProductSoldierGet, {})
end

function M:getProduceResourceInfo()
    SocketManager:send(kCastleProduceItemGet, {})
end

function M:sendAllProduceSoldierReceived()
    local list = self:getFinishProduceSoldierList()
    for _, produceData in pairs(list) do
        local id = produceData:getId()
        SocketManager:send(kCastleProductSoldierReceive, {id = id})
    end
end

function M:sendAllProduceResourcesReceived()
    local list = self:getFinishProduceResourcesList()
    for _, produceData in pairs(list) do
        if not self:_isLimit(produceData) then
            local id = produceData:getId()
            SocketManager:send(kCastleProductItemReceive, {id = id})
        else
            return false
        end
    end
    return true
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local cmdTbl = {
        [kCastleProductSoldierReceive] = function(msgTable)
            if msgTable.code == 0 then
                self:setProduceSoldierDataToDefault(msgTable.id)
            end
            Listener:postEvent(Listener.EventName.onProduceSoldierReceived, msgTable)
        end,
        [kCastleProductSoldierInfo] = function(msgTable)
            self:updateProduceSoldierDataToBuilding(msgTable)
        end,
        [kCastleProductSoldierGet] = function(msgTable)
            for k, v in pairs(msgTable.soldiers) do
                self:updateProduceSoldierDataToBuilding(v)
            end
        end,
        [kProduceBuildingInfoGet] = function(msgTable)
            local msgBuildingDataList = msgTable.building_info_list
            for _, v in ipairs(msgBuildingDataList) do
                self:addProduceBuildingData(v)
            end
            self:_checkProduceBuildingDataList(msgBuildingDataList)
            if self._isNeedInit then
                self:getProduceSoldierInfo()
                self:getProduceResourceInfo()
                self._isNeedInit = false
            end
            Listener:postEvent(Listener.EventName.onProduceBuildingInfoGet)
        end,
        [kCastleProductItemReceive] = function(msgTable)
            if msgTable.code == 0 then
                self:setProduceResourceDataToDefault(msgTable.id)
            end
            Listener:postEvent(Listener.EventName.onProduceResourceReceived, msgTable)
        end,
        [kCastleProductItemInfo] = function(msgTable)
            self:updateProduceResourceDataToBuilding(msgTable)
        end,
        [kCastleProduceItemGet] = function(msgTable)
            for k, v in pairs(msgTable.items) do
                self:updateProduceResourceDataToBuilding(v)
            end
        end,
        [kGuildQuit] = function(msgTable)
            if msgTable.code ~= 0 then
                return
            end
            self._buildingDataList = {}
            self:produceInfoRequest()
        end,
    }
    Function:safeCall(cmdTbl, cmd, msgTable)
end

function M:addProduceBuildingData(msgTable)
    local uniqueId = Utils:getUniqueId(msgTable.x, msgTable.y)
    if self._buildingDataList[uniqueId] then
        return
    end
    local buildingData = ProduceBuildingData.new(msgTable)
    self._buildingDataList[uniqueId] = buildingData
    self:_initProduceSoldierData(buildingData)
    self:_initProduceResourceData(buildingData)
end

-- 检测是否和服务端一直，（主要处理当前生产的建筑被别人占领）
function M:_checkProduceBuildingDataList(msgBuildingDataList)
    for uid, _ in pairs(self._buildingDataList) do
        local hasData = false
        for _, v in ipairs(msgBuildingDataList) do
            local uniqueId = Utils:getUniqueId(v.x, v.y)
            if uid == uniqueId then
                hasData = true
                break
            end
        end
        if not hasData then
            self._buildingDataList[uid] = nil
        end
    end
end

function M:removeAllBuildingData()
    self._buildingDataList = {}
end

function M:getProduceBuildingDataList()
    return self._buildingDataList
end

function M:getProduceBuildingData(uniqueId)
    return self._buildingDataList[uniqueId]
end

function M:getFinishProduceSoldierList()
    return self:_getFinishProduceList(M.ProduceType.Soldier)
end

function M:getFinishProduceResourcesList()
    return self:_getFinishProduceList(M.ProduceType.Resources)
end

function M:updateProduceSoldierDataToBuilding(msgTable)
    local buildingData = self:_getBuildingDataByCoor({x = msgTable.x, y = msgTable.y})
    local soldierData = buildingData:getProduceSoliderData(msgTable.soldier_type)
    soldierData:updateData(msgTable)
end

function M:updateProduceResourceDataToBuilding(msgTable)
    local buildingData = self:_getBuildingDataByCoor({x = msgTable.x, y = msgTable.y})
    local resourceData = buildingData:getProduceResourceData(msgTable.item_type)
    resourceData:updateData(msgTable)
end

-- function M:_initMsgData()
-- end

function M:_getBuildingDataByCoor(coor)
    local uniqueId = Utils:getUniqueId(coor.x, coor.y)
    local buildingData = self._buildingDataList[uniqueId]
    return buildingData
end

function M:_initProduceSoldierData(buildingData)
    local buildingId = buildingData:getBuildingId()
    local list = ProduceConfigReader:getProduceSoldierTypeList(buildingId)
    if not list then
        return
    end
    local localX, localY = buildingData:getLocalCoor()
    local level = PlayerData:getCastleLevel()
    for k, v in ipairs(list) do
        local soldierType = v + level
        local soldierData = ProduceSoldierData:createEmptyDataByType(soldierType, localX, localY)
        buildingData:addProduceSoldierData(soldierData)
    end
end

function M:_initProduceResourceData(buildingData)
    local buildingId = buildingData:getBuildingId()
    local list = ProduceConfigReader:getProduceResourceConfigList(buildingId)
    if not list then
        return
    end
    local localX, localY = buildingData:getLocalCoor()
    for k, v in ipairs(list) do
        local resourceData = ProduceResourceData:createEmptyDataByType(v.id, v.limit, v.time, localX, localY)
        buildingData:addProduceResourceData(resourceData)
    end
end

function M:setProduceSoldierDataToDefault(produceId)
    for _, buildingData in pairs(self._buildingDataList) do
        local soldierDataList = buildingData:getProduceSoliderDataList()
        for __, soldierData in pairs(soldierDataList) do
            if soldierData:getId() == produceId then
                local defaultData = self:_soldierDataToDefault(buildingData, soldierData)
                buildingData:addProduceSoldierData(defaultData)
            end
        end
    end
end

function M:_soldierDataToDefault(buildingData, soldierData)
    local soldierType = soldierData:getSoldierType()
    local coorX, coorY = buildingData:getLocalCoor()
    local defaultData = ProduceSoldierData:createEmptyDataByType(soldierType, coorX, coorY)
    return defaultData
end

function M:setProduceResourceDataToDefault(produceId)
    for _, buildingData in pairs(self._buildingDataList) do
        local resourceDataList = buildingData:getProduceResourceDataList()
        for __, resourceData in pairs(resourceDataList) do
            if resourceData:getId() == produceId then
                local defauleData = self:_resourceDataToDefaule(buildingData, resourceData)
                buildingData:addProduceResourceData(defauleData)
            end
        end
    end
end

function M:_resourceDataToDefaule(buildingData, resourceData)
    local itemType = resourceData:getItemType()
    local limit = resourceData:getProduceLimit()
    local time = resourceData:getProduceTime()
    local coorX, coorY = buildingData:getLocalCoor()
    local defaultData = ProduceResourceData:createEmptyDataByType(itemType, limit, time, coorX, coorY)
    return defaultData
end

-- 全体征兵加速是否已被使用过
function M:isTotalProduceSoldierSpeedUpUsed()
    local usedCount = 0
    local produceCount = 0
    for _, buildingData in pairs(self._buildingDataList) do
        local soldierDataList = buildingData:getProduceSoliderDataList()
        usedCount, produceCount = self:_checkTotalSpeedUpUsed(soldierDataList)
    end
    return usedCount == produceCount
end

-- 全体生产加速是否已被使用过
function M:isTotalProduceResourceSpeedUpUsed()
    local usedCount = 0
    local produceCount = 0
    for _, buildingData in pairs(self._buildingDataList) do
        local resourceDataList = buildingData:getProduceResourceDataList()
        usedCount, produceCount = self:_checkTotalSpeedUpUsed(resourceDataList)
    end
    return usedCount == produceCount
end

function M:_checkTotalSpeedUpUsed(produceDataList)
    local usedCount = 0         -- 已用过加速的生产数量
    local produceCount = 0      -- 正在生产的数量
    local nowTime = PlayerData:getServerTime()
    for __, produceData in pairs(produceDataList) do
        if produceData:getId() ~= 0 then
            local endTime = produceData:getProduceEndTime()
            if nowTime < endTime then
                produceCount = produceCount + 1
                if produceData:getReduceCount() > 0 then
                    usedCount = usedCount + 1
                end
            end
        end
    end
    return usedCount, produceCount
end

function M:_getFinishProduceList(produceType)
    local list = {}
    local dataList = self:getProduceBuildingDataList()
    if not dataList then
        return list
    end
    for _, buildingData in pairs(dataList) do
        local produceList
        if produceType == M.ProduceType.Soldier then
            produceList = buildingData:getProduceSoliderDataList()
        elseif produceType == M.ProduceType.Resources then
            produceList = buildingData:getProduceResourceDataList()
        end
        for __, produceData in pairs(produceList) do
            local id = produceData:getId()
            local endTime = produceData:getProduceEndTime()
            local nowTime = PlayerData:getServerTime()
            local diffTime = endTime - nowTime
            if id ~= 0 and endTime > 0 and diffTime <= 0 then
                table.insert(list, produceData)
            end
        end
    end
    return list
end

function M:_isLimit(resourceData)
    local BackpackDataManager = require("player-data.BackpackDataManager")
    local itemType = resourceData:getItemType()
    local backpackData = BackpackDataManager:getBackpackDataByType(itemType)
    local itemNumber = 0
    if backpackData then
        itemNumber = backpackData:getItemNumber()
    end
    local CastleConfigReader = require("ui.city.king.CastleConfigReader")
    local limit = CastleConfigReader:getStorageConfine(PlayerData:getCastleLevel())
    if itemNumber >= limit then
        return true
    end
    return false
end

return M