local MapConfig = require("ui.map.data-manager.MapConfig")

local M = class("player-data.TeamData")

local function _isVaildMsgTable(msgTable)
    assert(msgTable.army_state and msgTable.army_id and 
        msgTable.hero_id and msgTable.soldier_type and 
        msgTable.army_number and msgTable.food and 
        msgTable.from_x and msgTable.from_y and msgTable.statu_id)
end

function M:ctor(msgTable)
    _isVaildMsgTable(msgTable)
    Table:copy(self, msgTable)
end

function M:newTeamData(msgTable)
    return M.new(msgTable)
end

function M:updateTeamData(msgTable)
    _isVaildMsgTable(msgTable)
    Table:copy(self, msgTable)
end

function M:getState()
    local tmp = 
    {
        [1] = Enum.TeamDataState.Inside,
        [2] = Enum.TeamDataState.Outside,
        [3] = Enum.TeamDataState.Guard,
    }
    return tmp[self.army_state]
end

function M:setState(newState)
    assert(newState)
    self.army_state = newState
end

function M:getArmyId()
    return self.army_id
end

function M:getHeroId()
    return self.hero_id
end

function M:getSoldierType()
    return self.soldier_type
end

function M:getSoldierNumber()
    return self.army_number
end

function M:updateArmyNumber(number)
    assert(number)
    self.army_number = number
end

function M:getSoldierFood()
    return self.food
end

function M:getCooridnate()
    if self.from_x and self.from_y then 
        return MapConfig:coordinate(self.from_x, self.from_y)
    end
    return MapConfig:coordinate(0, 0)
end

function M:getStatuId()
    return self.statu_id
end

function M:updateCoor(i, j)
    assert(i and j)
    self.from_x = i 
    self.from_y = j
end

function M:updateCooridnate(newCoor)
    self:updateCoor(newCoor.i, newCoor.j)
end

return M