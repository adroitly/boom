local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local HeroDataManager = require("player-data.HeroDataManager")
local SoldierDataManager = require("player-data.SoldierDataManager")
local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.team.layer-manager.EditTeamLayerCell", function ()
	return cc.TableViewCell:new()
end)

local m_socketSendKey = "army_set"
M.TableViewCellSize = cc.size(200,0)

function M:getSoldierCount()
	return self._selectSoldierCount
end

function M:setSelect(isSelect)
	self._slider:setVisible(isSelect)
	self._confirmButton:setVisible(isSelect)
	local backSpriteName = {"ui/team/ui-un-0012b.png", "ui/team/ui-un-0012a.png"}
	self._backgroundSprite:setTexture(isSelect and backSpriteName[1] or backSpriteName[2])
	local soldierCount = self:_getSoldierCount()
	self._soldierCountLabel:setString(string.format("%s/%s", soldierCount, self:_getTroopsMaxCount()))
	local grainCount = self:_getGrainCount() * soldierCount
    self._grainSprite:setText(__Localized("粮食")..grainCount)
	self._slider:setValue(soldierCount)
end

-- 设置剩余兵力
function M:setSurplusSoldierCount(value)
	if value < 0 then
		value = 0
	end
	self._surplusSprite:setText(__Localized("剩余兵力")..value)
	-- 滚动条最长的为剩余的加现有的
	self._sliderMaxValue = value + math.floor(self._slider:getValue())
end


function M:reload(teamData)
	self._teamData = teamData
	self:_updateNodes()
end

function M:ctor(delegate)
	self._sliderMaxValue = 1
	self:_createTimer()
	self:_createBackGround()
	self:_createHeroIcon()
	self:_createSoldier()
	self:_createSurplusSoldierSprite()
	self:_createSoldierNameSprite()
	self:_createSoldierSlider(delegate)
	self:_createGrain()
	self:_createEnergy()
	self:_createPlayButton()
	self:_createConfirmButton(delegate)
end


function M:_updateNodes()
	local heroId = self:_getHeroType()
	local heroData = self:_getHeroData()
	local soldierCount = self:_getSoldierCount()
	local soldierName = self:_getSoldierName()
	local grainCount = self:_getGrainCount() * soldierCount
	self._heroIcon:reload(heroData)

	self._slider:setMaximumValue(self:_getTroopsMaxCount())
	self._slider:setValue(soldierCount)
	self._soldierCountLabel:setString(string.format("%s/%s", soldierCount, self:_getTroopsMaxCount()))
	self._soldierNameSprite:setText(__Localized("兵种"..soldierName))
	self._grainSprite:setText(__Localized("粮食")..grainCount)
	self:_updateHeroEnergy()
	self:setSelect(false)
	if self:_canAccelerate() then
		self._playButton:setEnabled(true)
	else
		self._playButton:setEnabled(false)
	end
end

function M:_createTimer()
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
	TimerInterval:addTimer(self, 1)
end

function M:onExit()
	TimerInterval:removeTimer(self)
end

function M:onUpdate()
	self:_updateHeroEnergy()
end

function M:_updateHeroEnergy()
	local energyCount = self:_getEnergyCount()
	self._energySprite:setText(__Localized("士气")..energyCount)
	local endEnergyTime = self:_getEndEnergyTime()
	if PlayerData:getServerTime() > endEnergyTime then
		self._playButton:setText(__Localized("训练"))
		return
	end
	local targetTime = endEnergyTime - PlayerData:getServerTime()
	local timeLabelText = Function:timeToDateString(targetTime)
	self._playButton:setText(__Localized("加速")..timeLabelText)
end

function M:_getSoldierBackCount()
	local soldierList = PlayerData:getSoldiers()
	local selectSoldierType = self._teamData:getSoldierType()
	local soldierData = soldierList[selectSoldierType]
	local soldierBackCount = soldierData:getSoldierNumber()
	return soldierBackCount
end

function M:_getHeroData()
	local heroIdData = self:_getHeroTypeData()
	return HeroDataManager:getHeroDataById(heroIdData)
end

function M:_getHeroTypeData()
	return self._teamData:getHeroId()
end

function M:_getHeroType()
	local heroData = self:_getHeroTypeData()
	return HeroDataManager:getHeroTypeById(heroData)
end

function M:_getHeroLevel()
	local heroIdData = self:_getHeroTypeData()
	local heroData = HeroDataManager:getHeroDataById(heroIdData)
	return heroData:getHeroLevel()
end

function M:_getState()
	return self._teamData:getState()
end

function M:_getSoldierId()
	local soliderTypeData = self._teamData:getSoldierType()
	local soldierData = SoldierDataManager:getSoldierDataByType(soliderTypeData)
	return soldierData:getSoldierType()
end

function M:_getSoldierCount()
	return self._teamData:getSoldierNumber() or 0
end

function M:_getTroopsMaxCount()
	local heroLevel = self:_getHeroLevel()
	local heroId = self:_getHeroType()
	return HeroAttribute:getTroops(heroId, heroLevel, self:_getSoldierId())
end

function M:_getSoldierName()
	local soldierId = self:_getSoldierId()
	return SoldierConfigReader:getName(soldierId)
end

function M:_getGrainCount()
	local soldierId = self:_getSoldierId()
	return SoldierConfigReader:getFood(soldierId)
end

function M:_getEnergyCount()
	local endEnergyTime = self:_getEndEnergyTime()
	local targetTime = endEnergyTime - PlayerData:getServerTime()
	local heroData = self:_getHeroData()
	local energyCount = heroData:getHeroEnergy()
	local heroType = self:_getHeroType()
	local energySpeed = HeroConfigRead:getEnergySpeed(heroType)
	local count = energyCount - (math.floor(targetTime / (energySpeed)))
	if count < 0 then
		count = 0
	end
	return count > energyCount and energyCount or count
end

function M:_getEndEnergyTime()
	local heroData = self:_getHeroData()
	return heroData:getEndEnergyTime()
end


function M:_canAccelerate()
	local heroData = self:_getHeroData()
	local energyReduceCount = heroData:getEnergyReduceCount()
	if tonumber(energyReduceCount) > 0 then
		return false
	end
	return true
end

function M:_createBackGround()
	self._backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	local backSpriteSize = self._backgroundSprite:getContentSize()
	self._backgroundSprite:setPosition(cc.p(Screen.width / 2 , 100))
	self:addChild(self._backgroundSprite)
end


-- 粮食
function M:_createGrain()
	local spriteName = "ui/login/login-bt.png"
	self._grainSprite = CommonUI:createTextSprite(self, spriteName, "" ,24)
	local spriteSize = self._grainSprite:getContentSize()
	self._grainSprite:setPosition(cc.p(self._heroIconSize.width + spriteSize.width - 10, self._heroIconSize.height + spriteSize.height / 4))
end

-- 士气
function M:_createEnergy()
	local spriteName = "ui/login/login-bt.png"
	self._energySprite = CommonUI:createTextSprite(self, spriteName, "" ,24)
	local spriteSize = self._energySprite:getContentSize()
	local PosiX = self._heroIconSize.width + spriteSize.width * 2
	local PosiY = self._heroIconSize.height + spriteSize.height / 4
	self._energySprite:setPosition(cc.p(PosiX, PosiY))
end

function M:_createConfirmButton(delegate)
	self._confirmButton = CommonUI:createTextButton(self, __Localized("确定"), "ui/login/register-bt.png")
	local buttonSize = self._confirmButton:getContentSize()
	local posiY = buttonSize.height 
	self._confirmButton:setPosition(cc.p(Screen.width - buttonSize.width / 1.5 , posiY))
	self._confirmButton.onClicked = function()
		local armyCount = math.floor(self._slider:getValue())
		if armyCount == self:_getSoldierCount() then
			delegate:onCellCloseSelect(self)
			return
		end
		local armyId = self._teamData:getArmyId()
		local armySetData = {army_id = armyId, army_number = armyCount}
		SocketManager:send(m_socketSendKey, armySetData)
		CommonUI:showLoadingLayer(true)
	end
	self._confirmButton:setVisible(false)
end

function M:_checkCanPaySpeed()
	local oneEngrySpeedPay = PayRatioConfigReader:getOneHeroEnergySpeed()
	local backpackType = oneEngrySpeedPay.id
	local cost = oneEngrySpeedPay.count
	return BackpackDataManager:checkBackpackEnough(backpackType, cost)
end

function M:_onPlayButtonClick()
	if self:_getEnergyCount() >= HeroConfigRead:getEnergyMax(self:_getHeroType()) then
		CommonUI:lightTips(__Localized("士气已满，无需训练"))
		return
	elseif Enum.TeamDataState.Outside == self._teamData:getState() then
		CommonUI:lightTips(__Localized("部队在外城，不能训练"))
		return
	end
	local layer = nil
	local endEnergyTime = self:_getEndEnergyTime()
	local scene = cc.Director:getInstance():getRunningScene()
	if PlayerData:getServerTime() > endEnergyTime then
		layer = require("ui.team.layer-manager.ConfirmDrillLayer").new(self._teamData)

	else
		local canPaySpeed = self:_checkCanPaySpeed()
		if self:_canAccelerate() and canPaySpeed then
			layer = require("ui.team.layer-manager.ConfirmSpeedupLayer").new(self._teamData)
		elseif false == canPaySpeed  then
			CommonUI:alertRechargeLayer()
			return
		else
			CommonUI:lightTips(__Localized("已经使用过50%加速"))
			return
		end
	end
	scene:addChild(layer)
end


-- 训练按钮
function M:_createPlayButton()
	self._playButton = CommonUI:createTextButton(self, __Localized("训练"), "ui/login/register-bt.png")
	local buttonSize = self._playButton:getContentSize()
	local posiY = self._heroIconSize.height + buttonSize.height / 4
	self._playButton:setPosition(cc.p(Screen.width - buttonSize.width / 1.5 , posiY))
	self._playButton.onClicked = function ()
		self:_onPlayButtonClick()
	end
end

-- 兵
function M:_createSoldier()
	self._soldierCountLabel = CommonUI:createLabel("0000/0000" ,24)
	local labelSize = self._soldierCountLabel:getContentSize()
	local posiX = self._heroIconSize.width + labelSize.width * 2.5
	local posiY = self._heroIconSize.height - labelSize.height * 3
	self._soldierCountLabel:setPosition(cc.p(posiX, posiY))
	self:addChild(self._soldierCountLabel)
end

-- 剩余兵力
function M:_createSurplusSoldierSprite()
	local spriteName = "ui/login/login-bt.png"
	self._surplusSprite = CommonUI:createTextSprite(self, spriteName, "" ,24)
	local spriteSize = self._surplusSprite:getContentSize()
	local posiX = self._heroIconSize.width + spriteSize.width * 3.5 - 50
	local posiY = self._heroIconSize.height + spriteSize.height / 4
	self._surplusSprite:setPosition(cc.p(posiX, posiY))
end

-- 兵种名称
function M:_createSoldierNameSprite()
	self._soldierNameSprite = CommonUI:createTextSprite(self, "ui/login/login-bt.png", __Localized("兵种") ,24)
	local spriteSize = self._soldierNameSprite:getContentSize()
	local posiX = self._heroIconSize.width + spriteSize.width - 10
	local posiY = self._heroIconSize.height - spriteSize.height
	self._soldierNameSprite:setPosition(cc.p(posiX, posiY))
end

function M:_addButtonClick()
	if false == self._isSelect then
		return
	end
	local value = math.floor(self._slider:getValue())
	if value > self._sliderMaxValue - 1 then
		return
	end
	value = value + 1
	self._slider:setValue(value)
end
-- 减少士兵数量回调
function M:_subButtonClick()
	local value = math.floor(self._slider:getValue())
	if value < 2 then
		return 
	end
	value = value - 1
	self._slider:setValue(value)
end

-- 
function M:_createSoldierSlider(delegate)
	local spriteSize = self._soldierNameSprite:getContentSize()

	local subButton = ButtonLongPress.new("ui/team/button-sub.png", "ui/team/button-sub.png")
	local buttonSize = subButton:getContentSize()
	local subButtonPosiX = self._heroIconSize.width + spriteSize.width * 1.5
	local posiY = self._heroIconSize.height - spriteSize.height / 1.5
	subButton:setPosition(cc.p(subButtonPosiX, posiY))
	subButton.onClicked = function()
		self:_subButtonClick()
	end
	self:addChild(subButton)

	self._slider = ControlSlider.new("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
	self._slider:setSwallowTouches(false)
    self._slider:setMinimumValue(1)
    self._slider:setValue(1)
    local sliderSize = self._slider:getContentSize()
    local sliderPosiX = self._heroIconSize.width + spriteSize.width * 1.5 + sliderSize.width / 2 + buttonSize.width
    self._slider:setPosition(cc.p(sliderPosiX, posiY))
    self:addChild(self._slider)
    self._slider.onValueChanged = function(sender, currentValue)
	local value = math.floor(currentValue)
		self:_sliderValueChang(delegate, value)
    end
    
    local addButtonPosiX = sliderPosiX + sliderSize.width / 2 + buttonSize.width
    local addButton = ButtonLongPress.new("ui/team/button-add.png", "ui/team/button-add.png")
	addButton:setPosition(cc.p(addButtonPosiX, posiY))
	addButton.onClicked = function()
		self:_addButtonClick()
	end
    self:addChild(addButton)

    -- TESTTEST
	subButton:setVisible(false)
	addButton:setVisible(false)
end

function M:_sliderValueChang(delegate, value)
    if value > self._sliderMaxValue then
		self._slider:setValue(self._sliderMaxValue)
		self._selectSoldierCount = value
		value = self._sliderMaxValue
    end
    self._selectSoldierCount = value
    local grainCount = self:_getGrainCount() * value
    self._soldierCountLabel:setString(string.format("%s/%s", value, self:_getTroopsMaxCount()))
    self._grainSprite:setText(__Localized("粮食")..grainCount)
    local soldierId = self:_getSoldierId()
    local soldierBackCount = SoldierDataManager:getSoldierNumber(soldierId)
    local teamSolcierCount = self:_getSoldierCount()
    self:setSurplusSoldierCount(soldierBackCount - (value - teamSolcierCount))
    if delegate.onCellSoldierNumberChange then
		delegate:onCellSoldierNumberChange(soldierId, soldierBackCount - (value - teamSolcierCount))
	end
end

function M:_createHeroIcon()
	self._heroIcon = require("ui.common.HeroIcon").new(nil, function ()
		local heroInfoLayer = require("ui.team.layer-manager.HeroInfoLayer").new()
		heroInfoLayer:reloadLayerByTeamData(self._teamData)
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(heroInfoLayer)
	end)
	self._heroIconSize = self._heroIcon:getContentSize()
	self._heroIcon:setPosition(cc.p(self._heroIconSize.width , self._heroIconSize.height - M.TableViewCellSize.width / 10))
	self:addChild(self._heroIcon)
end

return M

