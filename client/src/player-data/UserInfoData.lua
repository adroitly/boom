local M = class("player-data.UserInfo")

local function _isVaild(msgTable)
    assert(msgTable and msgTable.player_id and msgTable.nickname and
     msgTable.home_x and msgTable.home_y and msgTable.message_system_number 
     and msgTable.server_time and msgTable.guild_id and msgTable.level 
     and msgTable.level_up_end_time and msgTable.salary_receive_time 
     and msgTable.level_up_reduce_50 and msgTable.country and msgTable.item_50706 and msgTable.message_board_count and msgTable.rmb and msgTable.vip and msgTable.vip_reward_receive_time and msgTable.vip_gift_recevie_lv and msgTable.icon and msgTable.sex)
end

function M:ctor(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:updateData(msgTable)
    _isVaild(msgTable)
    Table:copy(self, msgTable)
end

function M:getPlayerId()
    return self.player_id
end

function M:getNickname()
    return self.nickname
end

function M:getSalaryReceiveTime()
    return self.salary_receive_time
end

function M:getHomePos()
    return {x = self.home_x, y = self.home_y}
end

function M:setMessageSystemNumber(num)
    self.message_system_number = num
end

function M:getMessageSystemNumber()
    return self.message_system_number
end

function M:getServerTime()
    return self.server_time
end

function M:getGuildId()
    return self.guild_id
end

function M:getLevel()
    return self.level
end

function M:getCountryId()
    return self.country
end

function M:getLevelUpEndTime()
    return self.level_up_end_time
end

-- 是否使用过50%的道具
function M:isInFiftyAccelerate()
    return self.level == self.level_up_reduce_50
end

function M:getHeroGetawayTime()
    return self.item_50706
end

function M:getMessageBoardCount()
    return self.message_board_count
end

function M:getVip()
    return self.vip
end

function M:getRMB()
    return self.rmb
end

function M:getVipRewardReceiveTime()
    return self.vip_reward_receive_time
end

function M:getVipGiftRecevieLevel()
    return self.vip_gift_recevie_lv
end

function M:getIcon()
    return self.icon
end

function M:getSex()
    return self.sex
end

return M