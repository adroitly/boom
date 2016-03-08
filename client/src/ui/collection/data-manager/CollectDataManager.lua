local CollectData = require("ui.collection.data-manager.CollectData")
local M = {}

local kCollectInfoGet       = "collect_info_get"
local kCollectInfoAdd       = "collect_info_add"
local kCollectInfoDelete    = "collect_info_delete"

function M:getDataListByType(collectType)
    local list = {}
    if not self._collectDataList then
        return list
    end
    for _, collectData in pairs(self._collectDataList) do
        if collectData:getCollectType() == collectType then
            table.insert(list, collectData)
        end
    end
    return list
end

function M:isDataCollected(coor)
    if not self._collectDataList then
        return false
    end
    for _, collectData in pairs(self._collectDataList) do
        local collectCoor = collectData:getCoor()
        if collectCoor.i == coor.i and collectCoor.j == coor.j then
            return true
        end
    end
    return false
end

function M:isCollectDataListEmpty()
    if not self._collectDataList then
        return true
    end
    return table.getn(self._collectDataList) == 0
end

function M:collectInfoGetRequest()
    SocketManager:send(kCollectInfoGet, {})
end

function M:startDataListener()
    SocketManager:addObserver(self)
end

function M:stopDataListener()
    self._collectDataList = {}
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local callbacks = {
        [kCollectInfoGet] = function(msgTable)
            for _, collectInfo in ipairs(msgTable.collect_info_list) do
                self:_addCollectData(collectInfo)
            end
            Listener:postEvent(Listener.EventName.onListenCollectDataChanged)
        end,
        [kCollectInfoAdd] = function(msgTable)
            if msgTable.code == 0 then
                self:_addCollectData(msgTable.collect_info)
                Listener:postEvent(Listener.EventName.onListenCollectDataChanged)
            end
        end,
        [kCollectInfoDelete] = function(msgTable)
            if msgTable.code == 0 then
                self:_delectDataById(msgTable.id)
                Listener:postEvent(Listener.EventName.onListenCollectDataChanged)
            end
        end,
    }
    Function:safeCall(callbacks, cmd, msgTable)
end

function M:_addCollectData(collectInfo)
    if not self._collectDataList then
        self._collectDataList = {}
    end
    local collectData = CollectData.new(collectInfo)
    self._collectDataList[collectData:getId()] = collectData
end

function M:_delectDataById(id)
    self._collectDataList[id] = nil
end
return M