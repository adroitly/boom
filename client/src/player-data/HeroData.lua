local M = class("player-data.HeroData")

local function _isVaildMsgTable(msgTable)
    assert( msgTable.hero_type and msgTable.hero_id and
        msgTable.hero_level and msgTable.hero_state and
        msgTable.revive_time and msgTable.energy and
        msgTable.end_energy_time and msgTable.lock and
        msgTable.energy_reduce_count and msgTable.revive_reduce_count and msgTable.go_time)
end

-- 提示：heroType相当于配置表中的id, heroId则为当前英雄在服务端的标识符
function M:ctor(msgTable)
    _isVaildMsgTable(msgTable)
    Table:copy(self, msgTable)
end

function M:newHeroData(msgTable)
    return M.new(msgTable)
end

function M:updateHeroData(msgTable)
    _isVaildMsgTable(msgTable)
    Table:copy(self, msgTable)
end

function M:resetToNoneState()
    self.hero_state = Enum.HeroState.None
end

function M:resetToSurviceState()
    self.hero_state = Enum.HeroState.Survice
end

function M:getEndEnergyTime()
    return self.end_energy_time
end

function M:isLive()
    return PlayerData:getServerTime() - self.revive_time > 0
end

function M:getReviveTime()
    return self.revive_time
end

function M:getHeroEnergyOutside()
    local energy = math.floor(self.energy - (PlayerData:getServerTime() - self:getGotime()) / 60)
    return energy > 0 and energy or 0
end

function M:getHeroEnergy()
    local teamData = require("player-data.TeamDataManager"):getTeamDataByHeroId(self:getHeroId())
    if not teamData or Enum.TeamDataState.Outside ~= teamData:getState() then
        return self.energy
    else
        return self:getHeroEnergyOutside()
    end

end

function M:getHeroType()
    return self.hero_type
end

function M:getHeroId()
    return self.hero_id
end

function M:getHeroLevel()
    return self.hero_level
end

function M:getHeroState()
    return self.hero_state
end

-- 1表示上锁，不能出售，不能被吃 0表示没有上锁
function M:isLock()
    return self.lock == 1 and true or false
end
-- 是否使用了50%的加速训练
function M:getEnergyReduceCount()
    return self.energy_reduce_count
end

-- 是否使用了50%的疗伤
function M:getReviveReduceCount()
    return self.revive_reduce_count
end

function M:getGotime()
    return self.go_time or 0
end

return M