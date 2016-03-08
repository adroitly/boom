local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroDoctorCell = require("ui.hero-museum.layers.HeroDoctorCell")
local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.hero-museum.layers.HeroDoctorLayer",function()
	return cc.Layer:create()
end)


function M:ctor()
	self:_createAllUpSpeed()
	self:_initData()
	self:_createTableView()
	self:_registerScriptHandler()
end

function M:onHeroDoctorCellDidCallBack()
	self:onListenHeroDataChange()
end

function M:onListenHeroDataChange()
	self:_initData()
	self._tableView:reloadData()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if Command.ServiceUse == cmd then
		CommonUI:showLoadingLayer(false)
		if 0 == msgTable.code then
			CommonUI:lightTips("加速成功")
			self:onListenHeroDataChange()
		else
			CommonUI:lightTips("加速失败")
		end
	end
		
end

function M:_registerScriptHandler()
    self:registerScriptHandler(function(event)
	if event == "exit"then
			Listener:removeListener(self)
			SocketManager:removeObserver(self)
        end
    end)
    Listener:addListener(self)
    SocketManager:addObserver(self)
end

function M:_updateAllDoctorButton()
	local isCanClick = false
	for _,heroData in pairs(self._doctorHeroList) do
		if heroData:getReviveReduceCount() <= 0 then
			isCanClick = true
			break
		end
	end
	self._allUpSpeedButton:setEnabled(isCanClick)
end

function M:_initData()
	local heroDatas = PlayerData:getHeros()
	self._doctorHeroList = {}
	for _,heroData in pairs(heroDatas) do
		if false == heroData:isLive() then
			table.insert(self._doctorHeroList, heroData)
		end
	end
	self:_updateAllDoctorButton()
end

function M:onTableViewCellTouched(tableView, cell)
	-- body
end

function M:onTableViewCellSize(tableView, idx)
	return HeroDoctorCell.DoctorCellSize.width, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = HeroDoctorCell.new(self)
	end
	cell:reload(self._doctorHeroList[idx + 1])
	return cell
end

function M:onTableViewCellCount(tableView)
	return table.getn(self._doctorHeroList)
end

function M:_createTableView()
	local viewSize  = cc.size(
		Screen.width,
		Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight * 2)
	self._tableView = require("share.TableView").new(viewSize, self)
	self._tableView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
	self:addChild(self._tableView)
end

function M:_createAllUpSpeed()
	self._allUpSpeedButton = CommonUI:createTextButton(self, "全体加速", "ui/login/login-button.png")
	local buttonSize = self._allUpSpeedButton:getContentSize()
	self._allUpSpeedButton:setPosition(cc.p(Screen.width / 2, buttonSize.height / 2))
	self._allUpSpeedButton.onClicked = function()
		self:_allUpSpeedButtonClick()
	end
end

function M:_allUpSpeedButtonClick()
	local payNeed = PayRatioConfigReader:getAllDoctorSpeedUpPay()
	if BackpackDataManager:checkBackpackEnough(payNeed.id, payNeed.count) then
		self:_allUpSpeedAction()
	else
		CommonUI:alertRechargeLayer()
	end
end

function M:_allUpSpeedAction()
	if 0 == table.getn(self._doctorHeroList) then
		return
	end
	local socketData = {service_type = Enum.SpeedUpType.AllDoctorHero}
	SocketManager:send(Command.ServiceUse, socketData)
	CommonUI:showLoadingLayer(true)
end

return M