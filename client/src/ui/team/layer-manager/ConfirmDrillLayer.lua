local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.team.layer-manager.ConfirmDrillLayer", function()
	return cc.Layer:create()
end)

function M:ctor(teamData)
	self._teamData = teamData
	self:_createScript()
	self:_createDialog()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if cmd == Command.ArmyPromote then
		CommonUI:showLoadingLayer(false)
		if 0 == msgTable.code then
			self:removeFromParent()
		else
			CommonUI:lightTips("训练失败")
			self:removeFromParent()
		end
	end
end

function M:_createScript()
	SocketManager:addObserver(self)
	self:registerScriptHandler(function(event)
		if "exit" == event then
			SocketManager:removeObserver(self)
		end
	end)
end

function M:_sendToServer()
	local armyId = self._teamData:getArmyId()
	local armySetData = {army_id = armyId}
	SocketManager:send(Command.ArmyPromote, armySetData)
	CommonUI:showLoadingLayer(true)
end

function M:_createDialog()
    AlertView.new(__Localized("确认训练?"), __Localized("取 消"), __Localized("确 定"))
    .onClicked = function(index)
        if 1 == index then
			self:_sendToServer()
		else
			self:removeFromParent()
        end
    end
end


return M