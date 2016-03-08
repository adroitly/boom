local M = {}
local function _isVaild(msgTable)
    assert(msgTable and msgTable.to_player_id and msgTable.from_player_id and
         msgTable.message and msgTable.message_type and msgTable.from_nickname and msgTable.to_nickname and msgTable.time and msgTable.icon)
end

-- 每个玩家的邮件数据
function M:newMailData(player_id, nickname)
    return {
        playerId = player_id,
        nickname = nickname,
        unreadCount = 0,
        isRead = true,
        mailList = {}
    }
end

-- 每条邮件的数据
function M:newPersonalMailData(msgTable)
    _isVaild(msgTable)
    return {
        toPlayerId = msgTable.to_player_id,
        fromPlayerId = msgTable.from_player_id,
        message = msgTable.message,
        time = msgTable.time,
        mailType = msgTable.message_type,
        toNickname = msgTable.to_nickname,
        fromNickname = msgTable.from_nickname,
        icon = msgTable.icon
    }
end

function M:isRead(mailData)
    return mailData.isRead
end

function M:updateUnReadMailCount(mailData, count)
    mailData.unreadCount = count
    self:_setReadState(mailData, count == 0)
end

function M:getPersonalMailDataList(mailData)
    return mailData.mailList
end

function M:getUnreadMailCount(mailData)
    return mailData.unreadCount
end

function M:getPlayerId(mailData)
    return mailData.playerId
end

function M:getNickname(mailData)
    return mailData.nickname
end

function M:getToNickname(mailData)
    return mailData.toNickname
end

function M:getFromNickName(mailData)
    return mailData.fromNickname
end

function M:getMessage(personlaMailData)
    return personlaMailData.message
end

function M:getTime(personlaMailData)
    return personlaMailData.time
end

function M:getFromPlayerId(personalMailData)
    return personalMailData.fromPlayerId
end

function M:getMailType(personlaMailData)
    return personlaMailData.mailType
end

function M:getIcon(personlaMailData)
    return personlaMailData.icon
end

function M:_setReadState(mailData, isRead)
    mailData.isRead = isRead
end

return M