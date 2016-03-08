
local M = class("player-data.BackpackData")

local function _isVaildMsgTable(msgTable)
    assert(msgTable.item_type and msgTable.item_number)
end

function M:ctor(msgTable)
    _isVaildMsgTable(msgTable)
    Table:copy(self, msgTable)
end

function M:newBackData(msgTable)
    return M.new(msgTable)
end

function M:updataItemNumber(number)
    assert(number)
	self.item_number = number
end

function M:updateItemData(msgTable)
    _isVaildMsgTable(msgTable)
    Table:copy(self, msgTable)
end

function M:getItemType()
	return self.item_type
end


function M:getItemNumber()
	return self.item_number
end

return M