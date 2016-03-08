local SystemMailData = require("ui.mail.data-manager.SystemMailData")
local M = {}

local kMaxMailCount = 50

local kLogin = "login"
local kMessageSystemGet = "message_system_get"
local kMessageSystemSend = "message_system_send"
local kMessageSystemSet = "message_system_set"

function M:startMailListener()
    SocketManager:addObserver(self)
end

function M:stopMailListener()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local callbacks = {
        [kMessageSystemGet] = function(msgTable)
            for k, v in pairs(msgTable.messages) do
                self:_addSystemMail(v)
            end
            Listener:postEvent(Listener.EventName.onListenMailSystemChanged)
        end,
        [kMessageSystemSend] = function(msgTable)
            PlayerData:getUserInfoData():setMessageSystemNumber(msgTable.message_system_number)
        end,
        [kMessageSystemSet] = function(msgTable)
            PlayerData:getUserInfoData():setMessageSystemNumber(msgTable.message_system_number)
            self:_setMailType(msgTable)
            Listener:postEvent(Listener.EventName.onListenMailSystemChanged)
        end,
    }
    
    if callbacks[cmd] then
        callbacks[cmd](msgTable)
    end
end

function M:sendSystemMailGetRequest()
    local mailId = self:getTheMaxMailId()
    SocketManager:send(kMessageSystemGet, {id = mailId})
end

function M:getUnreadMailCount()
    return PlayerData:getUserInfoData():getMessageSystemNumber()
end

-- 获取最大的邮件ID
function M:getTheMaxMailId()
    local mailList = PlayerData:getSystemMailList()
    local maxMailId = 0
    for mailId, mailData in pairs(mailList) do
        maxMailId = maxMailId < mailId and mailId or maxMailId
    end
    return maxMailId
end

function M:_addSystemMail(msgTable)
    local mailList = PlayerData:getSystemMailList()
    local mailData = SystemMailData:newSystemMailData(msgTable)
    local mailId = SystemMailData:getMailId(msgTable)
    mailList[mailId] = mailData
end

function M:_setMailType(msgTable)
    local mailList = PlayerData:getSystemMailList()
    local mailType = msgTable.message_type
    local mailId = msgTable.id
    if mailType == Enum.MailType.Deleted then
        mailList[mailId] = nil
        return
    end
    SystemMailData:updateMailType(mailList[mailId], mailType)
end

return M