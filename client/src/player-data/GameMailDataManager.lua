local GameMailData = require("ui.mail.data-manager.GameMailData")
local M = {}

local kMessageGameSend = "message_game_send"

function M:startMailListener()
    SocketManager:addObserver(self)
end

function M:stopMailListener()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kMessageGameSend then
        self:addGameMail(msgTable)
        Listener:postEvent(Listener.EventName.onListenMailGameChanged)
    end
end

function M:deleteGameMail(deletedMailData)
    local mailList = PlayerData:getGameMailList()
    for i, mailData in pairs(mailList) do
        if mailData == deletedMailData then
            mailList[i] = nil
            PlayerData:save()
            Listener:postEvent(Listener.EventName.onListenMailGameChanged)
            return
        end
    end
end
-- 批量删除
function M:batchDeleteGameMail(mailDataList)
    local mailList = PlayerData:getGameMailList()
    for i, mailData in pairs(mailDataList) do
        for j, localMailData in pairs(mailList) do
            if mailData == localMailData then
                mailList[j] = nil
            end
        end
    end
    PlayerData:save()
    Listener:postEvent(Listener.EventName.onListenMailGameChanged)
end

function M:updateMailType(mailData, mailType)
    GameMailData:updateMailType(mailData, Enum.MailType.Read)
    PlayerData:save()
end

function M:addGameMail(msgTable)
    local mailList = PlayerData:getGameMailList()
    local mailData = GameMailData:newGameMailData(msgTable)
    table.insert(mailList, mailData)
    PlayerData:save()
end

function M:getUnreadMailCount()
    local mailList = PlayerData:getGameMailList()
    local unreadCount = 0
    for _, mailData in pairs(mailList) do
        local mailType = GameMailData:getMailType(mailData)
        if mailType == Enum.MailType.UnRead then
            unreadCount = unreadCount + 1
        end
    end
    return unreadCount
end

return M
