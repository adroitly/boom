local M = class("player-data.SoldierData")

local function _isVaild(msgTable)
    assert(msgTable.soldier_type and msgTable.soldier_number)
end

-- 提示：soldier_type相当于配置表中的id
function M:ctor(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:newSoldierData(msgTable)
    return M.new(msgTable)
end

function M:updateSoldierData(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:updateSoldierNumber(soldierNumber)
    self.soldier_number =  soldierNumber
end

function M:getSoldierType()
    return self.soldier_type
end

-- 获取的是未编队的士兵的数量
function M:getSoldierNumber()
    return self.soldier_number
end

return M