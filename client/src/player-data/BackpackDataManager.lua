
local BackpackData = require("player-data.BackpackData")

local M = {}

function M:initBackpackData(msgTables)
	local dataList = {}
	for _, value in pairs(msgTables) do
		local itemType = value.item_type
        local data = BackpackData:newBackData(value)
        table.insert(dataList, data)
    end
    return dataList
end

local function findItem(itemList, itemType)
	for _,data in pairs(itemList) do
		if data.item_type == itemType then
			return data
		end
	end
	return nil
end

local function _postEvent(itemType)
	Listener:postEvent(Listener.EventName.onListenBackpackDataChange, itemType)
end

function M:updateBackpackData(msgTable)
	local itemType = msgTable.item_type
	local itemList = PlayerData:getBackpackItemList()
	local item = {}
	local backpackData = findItem(itemList, itemType)
	if nil == backpackData then
		item = BackpackData:newBackData(msgTable)
		table.insert(itemList, item)
	else
		backpackData:updateItemData(msgTable)
	end
	_postEvent(itemType)
end

function M:getBackpackDataByType(itemType)
    local itemList = PlayerData:getBackpackItemList()
    return findItem(itemList, itemType)
end

function M:updateBackpackDataNumber(itemType, number)
	local itemList = PlayerData:getBackpackItemList()
    local backpackData = findItem(itemList, findItem)
    BackpackData:updataItemNumber(backpackData, number)
end

function M:checkBackpackEnough(backpackType , needNumber)
    local backpackData = self:getBackpackDataByType(backpackType)
    if nil == backpackData then
        return false
    elseif backpackData:getItemNumber() >= needNumber then
        return true
    else
        return false
    end
end

return M