local M = {}
-- 移到与GameMailDataManager相邻目录，PersonalMailData和SystemMailData一样处理
local function _isVaild(msgTable)
    assert(msgTable and msgTable.from_player_id and msgTable.to_player_id and msgTable.message and
     msgTable.message_type and msgTable.from_nickname and msgTable.time and msgTable.success)
end

function M:newGameMailData(msgTable)
    _isVaild(msgTable)
    return {
        fromPlayerId = msgTable.from_player_id,
        toPlayerId = msgTable.to_player_id,
        message = msgTable.message,
        mailType = msgTable.message_type,
        fromNickname = msgTable.from_nickname,
        time = msgTable.time,
        success = msgTable.success,
    }
end

function M:updateMailType(mailData, mailType)
    mailData.mailType = mailType
end

function M:getMessage(mailData)
    return mailData.message
end

function M:getMailType(mailData)
    return mailData.mailType
end

function M:getTime(mailData)
    return mailData.time
end

function M:getSuccess(mailData)
    return mailData.success
end


return M