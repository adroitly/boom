local M = {}

local kUserInfo = "user_info"

function M:startDataListener()
    SocketManager:addObserver(self)
end

function M:stopDataListener()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kUserInfo then
        PlayerData:getUserInfoData():updateData(msgTable)
        Listener:postEvent(Listener.EventName.onListenUserInfoDataChange)
    end
end
return M