local M = class("ui.outside-search.layers.SearchArmyLayer", function()
	return cc.Layer:create()
end)

local m_getOtherPalyerData = "player_base_info2"

function M:createArmySearch(armyData)
	self._armyData = armyData
	self:_getOtherUserDataFromServer()
end

function M:_removeObserver()
	SocketManager:removeObserver(self)
end

function M:_getOtherUserDataFromServer()
	SocketManager:addObserver(self)
	local playerId = self._armyData:getPlayerId()
	local sendData = {target_id = playerId}
	SocketManager:send(m_getOtherPalyerData,  sendData)
	CommonUI:showLoadingLayer(true)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	local commons = 
	{
		[m_getOtherPalyerData] = function(msgTable)
			assert(msgTable)	
			self:_searchArmyFinish(msgTable)
		end,
	}

	Function:safeCall(commons, cmd, msgTable)
end

function M:_searchArmyFinish(msgTable)
	CommonUI:showLoadingLayer(false)
	local heroInfoLayer = require("ui.team.layer-manager.HeroInfoLayer").new()
	heroInfoLayer:reloadLayerByArmyData(self._armyData)
	local otherPlayerData = require("ui.user-info.datas.OtherPlayerData").new(msgTable)
	heroInfoLayer:reloadOtherPlayerData(otherPlayerData)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(heroInfoLayer)
	self:_removeObserver()
end

return M