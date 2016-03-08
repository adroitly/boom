local M = class("ui.produce.data-manager.ProduceResourceData")

local function _isValid(msgTable)
    assert(msgTable and msgTable.id and msgTable.item_type and msgTable.item_number and msgTable.product_end_time and msgTable.x and msgTable.y and msgTable.reduce_count)
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

function M:getItemType()
    return self.item_type
end

function M:getItemNumber()
    return self.item_number
end

function M:getProduceEndTime()
    return self.product_end_time
end

function M:setProduceTime(time)
    self._produceTime = time
end

function M:getProduceTime()
    return self._produceTime
end

function M:setProduceLimit(limit)
    self._produceLimit = limit
end

function M:getProduceLimit()
    return self._produceLimit
end

function M:getReduceCount()
    return self.reduce_count
end

function M:createEmptyDataByType(itemType, limit, time, x, y)
    local temp = {}
    temp.id = 0
    temp.item_type = itemType
    temp.item_number = 0
    temp.product_end_time = 0
    temp.x = x
    temp.y = y
    temp.reduce_count = 0
    local data = M.new(temp)
    data:setProduceLimit(limit)
    data:setProduceTime(time)
    return data
end

return M