
-- 心跳
local M = class("ui.map.data-manager.HeartBeat")

function M:ctor()
    self._elapseTime = 0    
end

function M:update(dt)
	self._elapseTime = self._elapseTime + dt
	if self._elapseTime > 5 then 
		self._elapseTime = 0
		SocketManager:send("heartbeat", {}) 
	end 
end

return M 
