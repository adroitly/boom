local M = class("ui.market.datas.FilterData")

function M:newBackpackFilerData(backpackType)
	local filterData = M.new(Enum.ResourceTypeId.Item)
	filterData:_updateBackpackType(backpackType)
	return filterData
end

function M:newHeroFilterData(heroLevel)
	local filterData = M.new(Enum.ResourceTypeId.Hero)
	filterData:_updateLevel(heroLevel)
	return filterData
end

function M:newNullFilterData()
	local filterData = M.new()
	return filterData
end

function M:ctor(resourceId)
	self.resourceId = resourceId
end

function M:getLevel()
	return self.level
end

function M:getResourceId()
	return self.resourceId
end

function M:getBackpackType()
	return self.backpackType
end

function M:_updateLevel(level)
	self.level = level
end

function M:_updateBackpackType(backpackType)
	self.backpackType = backpackType
end

return M