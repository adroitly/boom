local M = class("ui.backpack.data-manager.PackageItemData")
local function _assertMsgTable(msgTable)
	assert(msgTable and msgTable.code and msgTable.items)
end
local function _assertPackageItem(packageItem)
	assert(packageItem and packageItem.resource_id and packageItem.type and packageItem.number)
end
function M:ctor(packageItem)
	_assertPackageItem(packageItem)
	Table:copy(self, packageItem)
end

function M:getItemList(msgTable)
	_assertMsgTable(msgTable)
	local packageItemList = {}
	for _,item in pairs(msgTable.items) do
		table.insert(packageItemList, M.new(item))
	end
	return packageItemList
end

function M:getResourceId()
	return self.resource_id
end

function M:getType()
	return self.type
end

function M:getNumber()
	return self.number
end


function M:updateNumber(number)
	self.number = number
end
return M