local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.data-manager.BuildingData")

local function _isVaild(msgTable)
	assert(msgTable.owner_id and msgTable.x and msgTable.y
		and msgTable.city_amount and msgTable.garrison_number and msgTable.level and
		msgTable.building_id and msgTable.contry_id and msgTable.guild_id and msgTable.owner_name and msgTable.next_repair_time)
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

function M:getOwnerId()
	return self.owner_id
end

function M:getOwnerName()
	return self.owner_name
end

function M:changeOwnerId(newOwnerId)
	assert(newOwnerId)
	self.owner_id = newOwnerId
end

function M:getHomeCoor()
	return MapConfig:coordinate(self.x, self.y)
end

function M:getCityDef()
	return self.city_amount
end

function M:updateCityDef(newCityDef)
	assert(newCityDef)
	self.city_amount = newCityDef
end

function M:getGarrisonNumber()
	return self.garrison_number
end

function M:updateGarrisonNumber(newNumber)
	assert(newNumber)
	self.garrison_number = newNumber
end

function M:getLevel()
	return self.level
end

function M:getGuildId()
	return self.guild_id
end

function M:getCountryId()
	return self.contry_id
end

function M:getBuildingId()
	return self.building_id
end

function M:getNextRepairTime()
	return self.next_repair_time
end

return M