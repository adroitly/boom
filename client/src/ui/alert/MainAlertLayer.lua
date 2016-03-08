local AlertData = require("ui.alert.AlertData")
local KAttackAlert = "attack_alert"
local M = class("ui.alert.MainAlertLayer", function()
	return cc.Layer:create()
end)

function M:onEnterMoreAlertLayer()
	self._moreLayer = require("ui.alert.MoreAlertLayer").new()
	self._moreLayer:reloadData(self._alertList)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(self._moreLayer)
end

function M:ctor()
	self._alertList = {}
	self:_createShowLine()
	self:_scriptHandler()
end

function M:_scriptHandler(  )
	self:registerScriptHandler(function(event)
        if event == "exit" then
        	TimerRepeat:removeTimer(self)
        	SocketManager:removeObserver(self)
        end
    end)
    SocketManager:addObserver(self)
end

-- 更新列表
function M:_updateAlertList(alertData)
	local listSize = table.getn(self._alertList)
	-- 10个了就删除一个
	if listSize >= 10 then
		table.remove(self._alertList, 1)
	end
	table.insert(self._alertList, alertData)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if cmd == KAttackAlert then
		local alertData = AlertData:newAlertData(msgTable)
		self:_updateAlertList(alertData)
		self:_reloadData(alertData)
		if self._moreLayer and self._moreLayer.reloadData then
			self._moreLayer:reloadData(self._alertList)
		end
	end
end

function M:_reloadData(alertData)
	self:_schedulerChange()
	local showText = alertData:getAlertMessage()
	self._showLineLabel:setString(showText)
end

function M:_createShowLine()
	local nomalName = "ui/main-page/button-news.png"
	self._moreAlertButton = Button.new(nomalName, nomalName)
	self:addChild(self._moreAlertButton)
	self._moreAlertButton.onClicked = function()
		self:onEnterMoreAlertLayer()
	end
	self._moreAlertButton:setAnchorPoint(0, 0.5)
	self._moreAlertButton:setPosition(cc.p(0, 200))
	local buttonSize = self._moreAlertButton:getContentSize()
	self._showLineLabel = CommonUI:createLabel("", 20)
	self._showLineLabel:setAnchorPoint(0, 0.5)
	self._showLineLabel:setPosition(cc.p(buttonSize.width, 200))
	self:addChild(self._showLineLabel)
	self._showLineLabel:setVisible(false)
	self._moreAlertButton:setVisible(false)
end
function M:_stopHandler()
	TimerRepeat:removeTimer(self)
end

function M:_schedulerChange()
	self._showLineLabel:setVisible(true)
    self._moreAlertButton:setVisible(true)
	self:_stopHandler()

	TimerRepeat:addTimer(self, 5, 1)
end

function M:onUpdate()
	self._showLineLabel:setVisible(false)
end

return M