local MapConfig = require("ui.map.data-manager.MapConfig")

local M = class("ui.map.data-manager.RandomResourceData")

local function _isVaild(msgTable)
	assert(msgTable.res_id and msgTable.x and msgTable.y and msgTable.pack)
end

function M:ctor(msgTable, uniqueId)
	_isVaild(msgTable)
	Table:copy(self, msgTable)
	
	assert(uniqueId)
	self._uniqueId = uniqueId
end

function M:refresh(msgTable)
	_isVaild(msgTable)
	Table:copy(self, msgTable)
end

function M:getUniqueId()
	return self._uniqueId
end


function M:getHomeCoor()
	return MapConfig:coordinate(self.x, self.y)
end

function M:getResourceId()
	return self.res_id
end

function M:getItems()
	-- 返回格式：com_package_item.proto
	return self.pack.items
end

return M