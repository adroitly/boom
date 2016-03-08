local M = {}

--[[
    * 描述：获取账号服务器地址，该地址需要根据不同的发行商修改
--]]
function M:getServerAccountIp()
    return "120.196.143.123"
end

function M:getServerAccountPort()
    return 20000
end

--[[
    * 描述：获取服务器列表
--]]
function M:getServerList()
    return string.format("http://120.196.143.123:21000/?type=server_list&channel_id=%d&platform_id=%d", 
        Platform:getChannelId(), Platform:getPlatformId())
end

--[[
    * 描述：获取评论地址，引导用户去评论
--]]
function M:getCommentUrl()
    local urlTable = 
    {
        ["PatgameOutnet:outnet"] = "itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=1064366640",
        ["PatgameInnet:innet"] = "itms-apps://itunes.apple.com/cn/app/pa-pa-feng-bao-mo-huanq-ban/id1064366640?mt=8", 
    }

    local platfrom = c_BridgeSDK:getChannelName()
    return urlTable[platfrom]
end

-------------------------------------------------------------------- 

function M:setServerIp(ip, port)
    assert(ip and port)
    self._serverIp = ip 
    self._serverPort = port
end

function M:getServerIp()
    return self._serverIp
end

function M:getServerPort()
    return self._serverPort
end

function M:setServerAccountId(accountId)
    assert(accountId)
    self._accountId = accountId
end

function M:getServerAccountId()
    return self._accountId
end

return M