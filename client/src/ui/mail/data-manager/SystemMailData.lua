local PackageItemData = require("ui.backpack.data-manager.PackageItemData")
local M = {}

local function _isVaild(msgTable)
    assert(msgTable and msgTable.id and msgTable.from_player_id and msgTable.to_player_id and 
        msgTable.message and msgTable.message_type and msgTable.from_nickname and msgTable.time and msgTable.guild_id and msgTable.title and msgTable.items)
end

function M:newSystemMailData(msgTable)
    _isVaild(msgTable)
    local itemsList = {}
    for _, item in ipairs(msgTable.items) do
        local data = {}
        data.resource_id = item.resource_id
        data.type = item.type
        data.number = item.number
        table.insert(itemsList, data)
    end
    return {
        id = msgTable.id,
        fromPlayerId = msgTable.from_player_id,
        toPlayerId = msgTable.to_player_id,
        message = msgTable.message,
        mailType = msgTable.message_type,
        fromNickname = msgTable.from_nickname,
        time = msgTable.time,
        guildId = msgTable.guild_id,
        title = msgTable.title,
        itemsList = itemsList
    }
end

function M:updateMailType(mailData, mailType)
    mailData.mailType = mailType
end

function M:getMailId(mailData)
    return mailData.id
end

function M:getMailTitle(mailData)
    return mailData.title
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

function M:getGuildId(mailData)
    return mailData.guildId
end

function M:getItemDataList(mailData)
    local itemList = {}
    for _, item in ipairs(mailData.itemsList) do
        local itemData = PackageItemData.new(item)
        table.insert(itemList, itemData)
    end
    return itemList
end

return M