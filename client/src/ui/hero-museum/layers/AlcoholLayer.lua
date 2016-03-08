local BackgroundLayer = require("ui.common.BackgroundLayer")
local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.hero-museum.layers.AlcoholLayer", function()
	return cc.Layer:create()
end)

local m_socketConfirmKey = "hero_seek_1"
local m_socketGetCountKey = "hero_seek_count"

-- 1表示招贤令对酒一次，2表示元宝对酒一次，3表示元宝对酒十次
local m_sendDataType = {
	OneRecruit = 1,
	OneGoldIngot = 2,
	TenGoldIngot = 3,
}

local function _getOneRecruitData()
	return PayRatioConfigReader:getOneRecruitAlcohol()[1]
end

local function _getOneGoldData()
	return PayRatioConfigReader:getOneGoldAlcohol()[1]
end

local function _getTenGoldData()
	return PayRatioConfigReader:getTenAlcohol()[1]
end

local function _getOneRecruitName()
	local data = _getOneRecruitData()
	return BackpackConfigRead:getName(data[1])
end

local function _getOneRecruitPrice()
	local data = _getOneRecruitData()
	return data[2]
end

local function _checkOneRecruit()
	local data = _getOneRecruitData()
	return BackpackDataManager:checkBackpackEnough(data[1], _getOneRecruitPrice())
end

local function _getOneGoldName()
	local data = _getOneGoldData()
	return BackpackConfigRead:getName(data[1])
end

local function _getOneGoldPrice()
	local data = _getOneGoldData()
	return data[2]
end

local function _checkOneGold()
	local data = _getOneGoldData()
	return BackpackDataManager:checkBackpackEnough(data[1], _getOneGoldPrice())
end

local function _getTenGoldName()
	local data = _getTenGoldData()
	return BackpackConfigRead:getName(data[1])
end

local function _getTenGoldPrice()
	local data = _getTenGoldData()
	return data[2]
end

local function _checkTenGold()
	local data = _getTenGoldData()
	return BackpackDataManager:checkBackpackEnough(data[1], _getTenGoldPrice())
end

function M:ctor()
	self._recruitCount = 0
	self._sendType = m_sendDataType.OneRecruit
	self:_getRecruitCountFromServer()
	self:_registerScriptHandler()
	self:_createOneRecruitNodes()
	self:_createOnegoldIngotNodes()
	self:_createTenAlcolhoNodes()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if m_socketConfirmKey == cmd then
		assert(msgTable.code)
		self:_sendUnlock()
		if 0 == msgTable.code then
			self:_showSuccessLayer(msgTable)
			if m_sendDataType.OneRecruit == self._sendType then
				self:_updateRecruitCount(self._recruitCount - 1)
			end
		else
			CommonUI:errorAlertView(msgTable.code)
		end
	end
	if m_socketGetCountKey == cmd then
		self:_sendUnlock()
		assert(msgTable.hero_seek_1_2_count)
		self:_updateRecruitCount(msgTable.hero_seek_1_2_count)
	end
		
end

function M:_sendLock()
	self._isSendDataing = true
    CommonUI:showLoadingLayer(true)
end

function M:_sendUnlock()
	self._isSendDataing = false
	CommonUI:showLoadingLayer(false)
end

function M:_getRecruitCountFromServer()
	local sendData = {}
	SocketManager:send(m_socketGetCountKey, sendData)
	self:_sendLock()
end

function M:_updateRecruitCount(count)
	self._recruitCount = count
	self._recruitCountLabel:setString(string.format(__Localized("剩余次数:%d"),self._recruitCount))
end

function M:_showSuccessLayer(msgTable)
	local layer = require("ui.hero-museum.layers.ShowHerosLayer").new(msgTable.hero_ids)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_registerScriptHandler()
	SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			SocketManager:removeObserver(self)
		end
    end)
end

function M:_checkOneRecruitAlcolho()
	if self._isSendDataing then
		return
	end
	if _checkOneRecruit() then
		local sendData = {type = m_sendDataType.OneRecruit}
		SocketManager:send(m_socketConfirmKey, sendData)
		self._sendType = m_sendDataType.OneRecruit
		self:_sendLock()
	else
		CommonUI:lightTips(__Localized("资源不足，不能招贤"))
	end
end

function M:_createOneRecruitNodes()
	local recruitButtonText = string.format(__Localized("%s对酒一次"), _getOneRecruitName())
	local recruitLabelText = string.format("%d%s",_getOneRecruitPrice(), _getOneRecruitName())
	local recruitButton = CommonUI:createTextButton(self, recruitButtonText, "ui/login/login-up.png")
	recruitButton.onClicked = function()
		if self._recruitCount ~= 0 then
			self:_checkOneRecruitAlcolho()
		elseif self._recruitCount <= 0 then
			CommonUI:lightTips(__Localized("招贤次数不够"))
		end
	end

	local recruitLabel = CommonUI:createLabel(recruitLabelText, 24)
	self:addChild(recruitLabel)


	self._recruitCountLabel = CommonUI:createLabel(__Localized("剩余次数:0"), 24)
	self:addChild(self._recruitCountLabel)
	local buttonSize = recruitButton:getContentSize()
	local buttonWidth = Screen.width / 2
	self._recruitCountLabel:setPosition(cc.p(buttonWidth * 0.5, Screen.height / 2 + buttonSize.height / 4))
	recruitLabel:setPosition(cc.p(buttonWidth * 0.5, Screen.height / 2))
	recruitButton:setPosition(cc.p(buttonWidth * 0.5, Screen.height / 2 - buttonSize.height / 2))
end

function M:_checkOneGoldAlcolho()
	if self._isSendDataing then
		return 
	end
	if _checkOneGold() then
		self:_sendLock()
		local sendData = {type = m_sendDataType.OneGoldIngot}
		SocketManager:send(m_socketConfirmKey, sendData)
		self._sendType = m_sendDataType.OneGoldIngot
	else
		self:_createAlertView()
	end
end

function M:_createOnegoldIngotNodes()
	local goldIngotButtonText = string.format(__Localized("%s对酒一次"), _getOneGoldName())
	local goldIngotLabelText = string.format("%d%s",_getOneGoldPrice(), _getOneGoldName())

	local goldIngotButton = CommonUI:createTextButton(self, goldIngotButtonText, "ui/login/login-up.png")
	goldIngotButton.onClicked = function()
			self:_checkOneGoldAlcolho()
		end
	local goldIngotLabel = CommonUI:createLabel(goldIngotLabelText, 24)
	self:addChild(goldIngotLabel)

	local buttonSize = goldIngotButton:getContentSize()
	local buttonWidth = Screen.width / 2
	goldIngotLabel:setPosition(cc.p(buttonWidth * 1.5, Screen.height / 2))
	goldIngotButton:setPosition(cc.p(buttonWidth * 1.5, Screen.height / 2 - buttonSize.height / 2))
end

function M:_checkTenAlcolho()
	if self._isSendDataing then
		return 
	end
	if _checkTenGold() then
		self:_sendLock()
		local sendData = {type = m_sendDataType.TenGoldIngot}
		SocketManager:send(m_socketConfirmKey, sendData)
		self._sendType = m_sendDataType.TenGoldIngot
	else
		self:_createAlertView()
	end
end

function M:_createTenAlcolhoNodes()
	local tenGoldIngotButton = CommonUI:createTextButton(self, __Localized("元宝对酒二十次"), "ui/login/login-up.png")
	local buttonSize = tenGoldIngotButton:getContentSize()
	tenGoldIngotButton:setPosition(cc.p(Screen.width / 2 ,buttonSize.height / 2))
	tenGoldIngotButton.onClicked = function()
		self:_checkTenAlcolho()
	end
	local text = string.format("%d%s", _getTenGoldPrice(), _getTenGoldName())
	local tenGOldIngotLabel = CommonUI:createLabel(text, 24)
	self:addChild(tenGOldIngotLabel)

	local labelSize = tenGOldIngotLabel:getContentSize()
	tenGOldIngotLabel:setPosition(cc.p(Screen.width / 2 ,buttonSize.height + labelSize.height / 2))
end

function M:_createAlertView()
	CommonUI:alertRechargeLayer()
	
end

return M