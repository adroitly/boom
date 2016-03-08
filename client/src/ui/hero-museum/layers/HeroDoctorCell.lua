local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.hero-museum.layers.HeroDoctorCell", function()
	return cc.TableViewCell:create()
end)

M.DoctorCellSize = cc.size(200, 0)

function M:ctor(delegate)
	self._delegate = delegate
	self:_createProgressTimer()
	self:_registerScriptHandler()
	self:_createHeroIcon()
	self:_createUpSpeedButton()
end
function M:reload(heroData)
	self._heroIcon:reload(heroData)
	self:_updateProgressPercentage()
	if heroData:getReviveReduceCount() <= 0 then
		self._speedButton:setEnabled(true)
	else
		self._speedButton:setEnabled(false)
	end
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if Command.ServiceUse == cmd then
		CommonUI:showLoadingLayer(false)
		if 0 == msgTable.code then
			CommonUi:lightTips("加速成功")
			self._delegate:onHeroDoctorCellDidCallBack()
		else
			CommonUi:lightTips("加速失败")
		end
	end
		
end

function M:_updateProgressPercentage()
	local heroData = self._heroIcon:getHeroData()
	local heroLevel = heroData:getHeroLevel()
	local heroType = heroData:getHeroType()
	local constitution = HeroConfigRead:getConstitution(heroType)
	local allLiveTime = 20 + heroLevel* 60 *(1 - constitution / (constitution + heroLevel *30))
	local liveTime = heroData:getReviveTime() - PlayerData:getServerTime()
	local seconds = math.floor(liveTime % 60)
	local minutes = math.floor(liveTime / 60 % 60)
	local hours = math.floor(liveTime / 60 / 60 % 24)
	local showText = string.format("%d:%d:%d",hours,minutes,seconds)
	self._progressLabel:setString(showText)
	self._progressTimer:setPercentage((1- liveTime / allLiveTime) * 100)
	if liveTime <= 0 then
		if self._delegate.onHeroDoctorCellDidCallBack then
			self._delegate:onHeroDoctorCellDidCallBack()
		end
	end
end


function M:_registerScriptHandler()
    SocketManager:addObserver(self)
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
	TimerInterval:addTimer(self, 1)
end

function M:onExit()
	SocketManager:removeObserver(self)
	TimerInterval:removeTimer(self)
end

function M:_createProgressTimer()
	self._progressTimer = ProgressBar.new("ui/hero-museum/progressbg.png","ui/hero-museum/progressup.png")
	self:addChild(self._progressTimer)
	local progressSize = self._progressTimer:getContentSize()
	self._progressTimer:setPosition(cc.p(Screen.width / 2 , BackgroundLayer.TitleHeight))
	self._progressLabel = CommonUI:createLabel("00:00:00", 24)
	self._progressLabel:setPosition(cc.p(0, 0))
	self._progressTimer:addChild(self._progressLabel)
end


function M:_createUpSpeedButton()
	self._speedButton = CommonUI:createTextButton(self, "加速", "ui/login/login-button.png")
	local buttonSize = self._speedButton:getContentSize()
	self._speedButton:setPosition(cc.p(Screen.width - buttonSize.width / 2,BackgroundLayer.TitleHeight))

	self._speedButton.onClicked = function()
		self:_speedButtonClick()
	end
end

function M:_speedButtonClick()
	local payNeed = PayRatioConfigReader:getOneDoctorSpeedUpPay()
	if BackpackDataManager:checkBackpackEnough(payNeed.id, payNeed.count) then
		self:_speedButonAction()
	else
		CommonUI:alertRechargeLayer()
	end
end

function M:_speedButonAction()
	AlertView.new(__Localized("确定加速?"), __Localized("取 消"), __Localized("加 速"))
	.onClicked = function(index)
		if 1==index then 
			local heroData = self._heroIcon:getHeroData()
			local heroId = heroData:getHeroId()
			local sendData = {service_type = Enum.SpeedUpType.OneDoctorHero ,id = heroId}
			SocketManager:send(Command.ServiceUse, sendData)
			CommonUI:showLoadingLayer(true)
		end
	end
end

function M:onUpdate()
	self:_updateProgressPercentage()
end


function M:_createHeroIcon()
	self._heroIcon = require("ui.common.HeroIcon").new()
	self:addChild(self._heroIcon)


	self._heroIconSize = self._heroIcon:getContentSize()
	self._heroIcon:setPosition(cc.p(self._heroIconSize.width , BackgroundLayer.TitleHeight))

	self._heroIcon:setupClick(function()
		local heroData = self._heroIcon:getHeroData()
		local scene = cc.Director:getInstance():getRunningScene()
		local layer = require("ui.team.layer-manager.HeroInfoLayer").new()
		layer:reloadLayerByHeroData(heroData)
		scene:addChild(layer)
	end)
end

return M