local BackpackConfig = require("config.BackpackConfig")
local M = {}

local function _print(data, id, key)
	if nil == data then
		CCLog("BackpackConfig配置表id=%s, key=%s不存在", id, key)
	end
end

local function _getData(id, key)
	local numberId = tonumber(id)
	local configTable = BackpackConfig[numberId]
	_print(configTable, id, key)
	local data = configTable[key]
	_print(data, id, key)
	return data
end

function M:getName(id)
	return _getData(id, "name")
end

function M:getDesc(id)
	return _getData(id, "desc")
end

function M:getItemType(id)
	return _getData(id, "itemType")
end

function M:isBind(id)
	return 0 ~= _getData(id, "isbind")
end

function M:getMaxCount(id)
	return _getData(id, "maxCount") 
end

function M:getPrice(id)
	return _getData(id, "price")
end

function M:getMinGovernmentLevel(id)
	return _getData(id, "minGovernmentLevel")
end

function M:getMinCityLevel(id)
	return _getData(id, "minCityLevel")
end

function M:getEffect(id)
	return _getData(id, "effect")
end

function M:isUse(id)
	return _getData(id, "isuse")
end

function M:getChestItems(id)
	return 0
end

function M:getAllConfig()
	local config = {}
	for backpackType, _ in pairs(BackpackConfig) do
		table.insert(config, backpackType)
	end
	table.sort(config, function(a, b)
		return a < b
	end)
	return config
end

return M

