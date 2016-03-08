local PersonalMailData = require("ui.mail.data-manager.PersonalMailData")
local M = {}

local kMaxMailCount = 50
local kMessagePersonalInfo = "message_personal_info"

function M:startMailListener()
    SocketManager:addObserver(self)
end

function M:stopMailListener()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kMessagePersonalInfo then
        self:addPersonalMail(msgTable)
        Listener:postEvent(Listener.EventName.onListenMailPersonalChanged, msgTable)
    end
end

function M:deletePersonalMail(playerId)
    local list = PlayerData:getPersonalMailList()
    list[playerId] = nil
    PlayerData:save()
    Listener:postEvent(Listener.EventName.onListenMailPersonalChanged)
end

-- 批量删除
function M:batchDeletePersonalMail(playerIdList)
    local mailList = PlayerData:getPersonalMailList()
    for i, playerId in pairs(playerIdList) do
        mailList[playerId] = nil
    end
    PlayerData:save()
    Listener:postEvent(Listener.EventName.onListenMailPersonalChanged)
end

function M:addPersonalMail(msgTable)
    local toPlayerId = msgTable.to_player_id
    local fromPlayerId = msgTable.from_player_id
    local playerId = fromPlayerId
    local nickname = msgTable.from_nickname
    -- 如果是自己向别人发的邮件
    local isOwner = PlayerData:isOwner(fromPlayerId)
    if isOwner then
        playerId = toPlayerId
        nickname = msgTable.to_nickname
    end
    local list = PlayerData:getPersonalMailList()
    if not list[playerId] then
        list[playerId] = PersonalMailData:newMailData(playerId, nickname)
    end
    local unreadCount = PersonalMailData:getUnreadMailCount(list[playerId])
    -- 未读邮件增加1
    if not isOwner then
        PersonalMailData:updateUnReadMailCount(list[playerId], unreadCount + 1)
    end
    local mailData = PersonalMailData:newPersonalMailData(msgTable)
    -- 插入列表头部
    table.insert(list[playerId].mailList, 1, mailData)
    -- 限制长度
    if table.getn(list[playerId].mailList) > kMaxMailCount then
        table.remove(list[playerId].mailList)
    end
    PlayerData:save()
end
-- 当前玩家的未读聊天信息设为0
function M:resetMailCount(playerId)
    local list = PlayerData:getPersonalMailList()
    PersonalMailData:updateUnReadMailCount(list[playerId], 0)
end

function M:getUnreadMailCount()
    local list = PlayerData:getPersonalMailList()
    local unreadMailCount = 0
    for _, mailData in pairs(list) do
        local count = PersonalMailData:getUnreadMailCount(mailData)
        unreadMailCount = unreadMailCount + count
    end
    return unreadMailCount
end

function M:getNewestPersonalMailData(playerId)
    local list = PlayerData:getPersonalMailList()
    local playerMailList = PersonalMailData:getPersonalMailDataList(list[playerId])
    -- 第一条为最新
    return playerMailList[1]
end

return M