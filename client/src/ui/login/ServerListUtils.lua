local M = {}

local kLastLoginServerId = "LastLoginServerId"
function M:getRecommendServer(list)
    for i,v in ipairs(list) do
        if Enum.ServerListState.Recommend==v.state then
            return v
        end
    end

    return list[1]
end

function M:findServerWithId(list, id)
    for i,v in ipairs(list) do
        if v.id == id then
            return v 
        end
    end
end

function M:getLastLoginServerId(list)
    local lastId = cc.UserDefault:getInstance():getIntegerForKey(kLastLoginServerId)
    if nil == list then
        return lastId
    end
    if lastId and self:findServerWithId(list, lastId) then
        return lastId
    end

    local recommendServer = self:getRecommendServer(list)
    return recommendServer.id
end

function M:saveServerIdForLastLogin(id)
    cc.UserDefault:getInstance():setIntegerForKey(kLastLoginServerId, id)
end

return M


