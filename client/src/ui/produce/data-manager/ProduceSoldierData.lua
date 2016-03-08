local M = class("ui.produce.data-manager.ProduceSoldierData")
local function _isValid(msgTable)
    assert(msgTable and msgTable.id and msgTable.soldier_type and msgTable.soldier_number and msgTable.product_end_time and msgTable.x and msgTable.y and msgTable.reduce_count)
end
function M:ctor(msgTable)
    self:updateData(msgTable)
end

function M:updateData(msgTable)
    _isValid(msgTable)
    Table:copy(self, msgTable)
end

function M:getId()
    return self.id
end

function M:getLocalCoor()
    return self.x, self.y
end

function M:getSoldierType()
    return self.soldier_type
end

function M:getSoldierNumber()
    return self.soldier_number
end

function M:getProduceEndTime()
    return self.product_end_time
end

function M:getReduceCount()
    return self.reduce_count
end

function M:createEmptyDataByType(soldierType, x, y)
    local temp = {}
    temp.id = 0
    temp.soldier_type = soldierType
    temp.soldier_number = 0
    temp.product_end_time = 0
    temp.x = x
    temp.y = y
    temp.reduce_count = 0
    return M.new(temp)
end

return M