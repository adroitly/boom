SocketClient = require("libs.socket.SocketClient")
SocketError = require("socket-manager.SocketError")

local M = {}

local function _showAlertView(text, isReplaceScene)
	AlertView.new(text).onClicked = function(index)
		if isReplaceScene then 
			Director:replaceSceneWithClass(app.firstUILayer)
		end
	end
end

local function _serverCloseCallback(key)
	-- 登录账号服务器会立马断开链接，不需要处理
	if not key then 
		_showAlertView("与服务器断开链接", true)
	end
end 

function M:connect(ip, port, key)
	SocketClient.addObserver(M)
 	SocketClient.connect(ip, port, key)
end

function M:disconnect(key)
	SocketClient.disconnect(key)
end

function M:send(cmd, data, key)
	assert("table" ~= type(cmd), "请查看是否使用的是：号，而不是.号")
	SocketClient.send(cmd, data, key)
end

function M:addObserver(obs)
	SocketClient.addObserver(obs)
end

function M:removeObserver(obs)
	SocketClient.removeObserver(obs)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if ("StatusParseCmdError" == cmd) then 
		_showAlertView(string.format("%s错误，请与客服联系", msgTable.message), true)
	elseif ("StatusServerClose" == cmd) then 
		_serverCloseCallback(key)
	elseif ("StatusCheckCRCError" == cmd) then 
		_showAlertView("校验错误，数据不完整", true)
	elseif "SyntaxError" == cmd then
		_showAlertView(msgTable.message, true)
	elseif "error" == cmd then 
		SocketError:errorAction(msgTable, key)
	end 
end

return M 
