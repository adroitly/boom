local M = {}

function M:onSocketClientDidCallback(cmd, msgTable, key)
end

function M:errorAction(msgTable, key)
	local str = string.format("code=%d, message=%s", msgTable.code, msgTable.message)
    AlertView.new(str)
end

return M