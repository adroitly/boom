local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local HeroDataManager = require("player-data.HeroDataManager")
local M = class("ui.hero-museum.layers.UpgradeHeroLayer",function()
	return cc.Layer:create()
end)

local m_socketSendKey = "hero_upgrade"

local function _checkReloadStuff(heroData, oldHeroData, selectList)
	if nil == oldHeroData then
		return true
	end
	if oldHeroData:getHeroLevel() ~= heroData:getHeroLevel() then
		return true
	end
	for _,data in pairs(selectList) do
		if data.heroId == heroData:getHeroId() and Enum.UpgradeHeroType.Target ~= data.dataType then
			return true
		end
	end
	return false
end


local function _getInfoNames()
	local infoNames = {"星级:", "武力:", "统帅:", "智力:", "体质"}
	return infoNames
end


local function _getInfoDatas(len, heroType, level)
	local infoDatas = {}
	if nil == heroType then
		for key=1,len do
			infoDatas[key] = 000
		end
	else
		local force = HeroAttribute:getForce(heroType, level)
		local commander = HeroAttribute:getCommander(heroType, level)
		local brains = HeroAttribute:getBrains(heroType, level)
		local constitution = HeroAttribute:getConstitution(heroType, level)
		infoDatas[1] = level
		infoDatas[2] = force
		infoDatas[3] = commander
		infoDatas[4] = brains
		infoDatas[5] = constitution
	end
	return infoDatas
end

local function _getInfoLabelText(heroType, level)
	local infoNames = _getInfoNames()
	local infoDatas = _getInfoDatas(table.getn(infoNames), heroType, level)
	local infoLabelText = ""
	for key,value in pairs(infoNames) do
		infoLabelText = string.format("%s%s%s\n", infoLabelText, infoNames[key], infoDatas[key])
	end
	return infoLabelText
end

function M:ctor(hasBackground)
	if hasBackground then
		self:_createBackground()
	end
	self._heroSelectList = {}
	self:_registerHandler()
	self:_createStuffsButton()
	self:_createTargetButton()
	self:_createChangeButton()
	self:_createConfirmButton()
	self:_createInfoLabel()
end

function M:getHeroSelectList()
	return self._heroSelectList
end

function M:onSelectHeroListLayerDidCallBack(dataType, heroData)
	self:reload(dataType, heroData)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if m_socketSendKey == cmd then
		CommonUI:showLoadingLayer(false)
		assert(msgTable and msgTable.code)
		if 0 == msgTable.code then
			self:_upgradeSuccess()
		else
			CommonUI:lightTips(__Localized("升星失败,code==")..msgTable.code)
		end
	end
		
end

function M:reload(dataType, heroData)
	if dataType == Enum.UpgradeHeroType.Target then

		local oldHeroData = self:_getTargetHeroData()
		self._targetButton:reload(heroData)

		if true == _checkReloadStuff(heroData, oldHeroData, self._heroSelectList) then
			self:_reloadStuffButton()
		end
		self:_changeInfoLabel()
		

	elseif dataType == Enum.UpgradeHeroType.StuffOne then

		self._stuffButtonList[dataType]:reload(heroData)

	elseif dataType == Enum.UpgradeHeroType.StuffTwo then

		self._stuffButtonList[dataType]:reload(heroData)

	end
	self:_checkHeroData(dataType, heroData)
end

function M:_upgradeSuccess()
	CommonUI:lightTips(__Localized("升星成功"))
	self._heroSelectList = {}
	for _,heroIcon in pairs(self._stuffButtonList) do
		heroIcon:reload()
	end
	local heroList = HeroDataManager:getBackpackHeroList()
	local targetHeroId = self:_getTargetHeroData():getHeroId()
	for _,heroData in pairs(heroList) do
		if targetHeroId == heroData:getHeroId() then
			self._targetButton:reload(heroData)
			self:_checkHeroData(Enum.UpgradeHeroType.Target, heroData)
			self:_changeInfoLabel()
			return
		end
	end
end

function M:_registerHandler()
	Listener:addListener(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			Listener:removeListener(self)
			SocketManager:removeObserver(self)
		end
    end)
    SocketManager:addObserver(self)
end



function M:_getTargetHeroData()
	return self._targetButton:getHeroData()
end

function M:_checkHeroData(dataType, heroData)
	for key,data in pairs(self._heroSelectList) do
		if dataType == data.dataType then
			self._heroSelectList[key] = nil
		end
	end
	if nil == heroData then
		return 
	end
	local heroId = heroData:getHeroId()
	local heroLevel = heroData:getHeroLevel()
	local selectHeroData = {
							heroId = heroId, 
							dataType = dataType,
							heroLevel = heroLevel,
						}
	table.insert(self._heroSelectList, selectHeroData)
end

function M:_getStuffHeroList()
	local targetHeroData = self:_getTargetHeroData()
	local heroLevel = targetHeroData:getHeroLevel()
	local heroId = targetHeroData:getHeroId()
	local heroList = HeroDataManager:getBackpackHeroNoTeamList(heroLevel)
	local stuffHeroList = {}
	for _,tempHeroData in pairs(heroList) do
		local tempId = tempHeroData:getHeroId()
		if tempId ~= heroId and false == tempHeroData:isLock() then
			table.insert(stuffHeroList, tempHeroData)
		end
	end
	return stuffHeroList
end

function M:_reloadStuffButton()
	local stuffHeroList = self:_getStuffHeroList()
	local selectList = {}
	for key,node in pairs(self._stuffButtonList) do
		if table.getn(stuffHeroList) <= table.getn(self._stuffButtonList) then
			node:reload(stuffHeroList[key])
			self:_checkHeroData(key,stuffHeroList[key])
		else
			local stuffKey = math.random(table.getn(stuffHeroList))
			while nil ~= selectList[stuffKey] do
				stuffKey = math.random(table.getn(stuffHeroList))
			end
			selectList[stuffKey] = 1
			node:reload(stuffHeroList[stuffKey])
			self:_checkHeroData(key, stuffHeroList[stuffKey])

		end

	end
end

function M:_changeInfoLabel()
	local heroData = self._targetButton:getHeroData()
	local heroType = heroData:getHeroType()
	local heroLevel = heroData:getHeroLevel()
	local heroMaxLevel = HeroConfigRead:getStarmax(heroType)
	local oldInfoLabelText = _getInfoLabelText(heroType, heroLevel)
	local newInfoLabelText = ""
	if heroLevel >= heroMaxLevel then
		newInfoLabelText = _getInfoLabelText(heroType, heroLevel)
		CommonUI:lightTips(__Localized("武将已满星，无需升星"))
	else
		newInfoLabelText = _getInfoLabelText(heroType, heroLevel + 1)
	end
	self._oldInfoLabel:setString(oldInfoLabelText)
	self._newInfoLabel:setString(newInfoLabelText)
end

function M:_createInfoLabel()

	local oldInfoLabelText = _getInfoLabelText()
	local newInfoLabelText = _getInfoLabelText()

	self._oldInfoLabel = CommonUI:createLabel(__Localized(oldInfoLabelText), 36)
	self:addChild(self._oldInfoLabel)

	self._newInfoLabel = CommonUI:createLabel(__Localized(newInfoLabelText), 36)
	self:addChild(self._newInfoLabel)

	local infoLabelSize = self._newInfoLabel:getContentSize()

	self._oldInfoLabel:setPosition(cc.p(0, infoLabelSize.height / 2))
	self._oldInfoLabel:setAnchorPoint(0,0.5)
	self._oldInfoLabel:setAlignment(0)

	self._newInfoLabel:setPosition(cc.p(infoLabelSize.width * 2, infoLabelSize.height / 2))
	self._newInfoLabel:setAnchorPoint(0,0.5)
	self._newInfoLabel:setAlignment(0)
end

function M:_createChangeButton()
	local changeButton = CommonUI:createTextButton(self, __Localized("更换材料"), "ui/login/login-up.png")
	local changeButtonSize = changeButton:getContentSize()
	changeButton:setPosition(cc.p(Screen.width - changeButtonSize.width * 1.5, changeButtonSize.height * 2))

	changeButton.onClicked = function()
		if nil == self:_getTargetHeroData() then
			CommonUI:lightTips(__Localized("没有选择目标"))
			return
		end
		self:_reloadStuffButton()
	end
end

function M:_upgradeHeroAction()
	local targetHeroData = self:_getTargetHeroData()
	if nil == targetHeroData then
			return
	end
	local targetHeroLevel = targetHeroData:getHeroLevel()
	local targetHeroMaxLevel = HeroConfigRead:getStarmax(targetHeroData:getHeroType()) or 10
	if targetHeroLevel >= targetHeroMaxLevel then
		CommonUI:lightTips(__Localized("武将已经满星,不能升星"))
		return
	end
	local targetHeroId = targetHeroData:getHeroId()
	local stuffHeroIds = {}
	for _,stuffButton in pairs(self._stuffButtonList) do
		local heroData = stuffButton:getHeroData()
		if nil == heroData then
			break
		end
		local heroId = heroData:getHeroId()
		table.insert(stuffHeroIds, heroId)
	end
	if table.getn(stuffHeroIds) < 2 then
		CommonUI:lightTips(__Localized("材料不足，无法升星"))
		return
	end
	local heroUpdateData = {hero_id = targetHeroId, stuff_hero_ids = stuffHeroIds}
	SocketManager:send(m_socketSendKey, heroUpdateData)
	CommonUI:showLoadingLayer(true)
end

function M:_createConfirmButton()
	local confirmButton = CommonUI:createTextButton(self, __Localized("升星"), "ui/login/login-up.png")
	local confirmButtonSize = confirmButton:getContentSize()
	confirmButton:setPosition(Screen.width - confirmButtonSize.width / 2, confirmButtonSize.height * 2)

	confirmButton.onClicked = function()
		self:_upgradeHeroAction()
	end
end

function M:_createTargetButton()
	self._targetButton = require("ui.common.HeroIcon").new()
	local buttonSize = self._targetButton:getContentSize()
	self._targetButton:setPosition(Screen.width / 2, Screen.height / 2 - buttonSize.height)
	self:addChild(self._targetButton)
	local heroList = PlayerData:getHeros()
	self._targetButton:setupClick(function()
		local scene = cc.Director:getInstance():getRunningScene()
		local layer = require("ui.hero-museum.layers.SelectHeroListLayer").new(self, Enum.UpgradeHeroType.Target)
		scene:addChild(layer)
	end)
end

function M:_createStuffsButton()
	self._stuffButtonList = {}
	local stuffButtonWidth = Screen.width / 2
	for key = 1,2 do
		local stuffButton = require("ui.common.HeroIcon").new()
		self:addChild(stuffButton)

		local buttonSize = stuffButton:getContentSize()
		stuffButton:setPosition(stuffButtonWidth * (key - 0.5), Screen.height / 2 + buttonSize.height)

		stuffButton:setupClick(function(stuffButton)
			if nil == self:_getTargetHeroData() then
				CommonUI:lightTips(__Localized("没有选择目标"))
				return 
			end
			local scene = cc.Director:getInstance():getRunningScene()
			local layer = require("ui.hero-museum.layers.SelectHeroListLayer").new(self, key)
			scene:addChild(layer)
		end)
		table.insert(self._stuffButtonList, stuffButton)
	end
end

function M:_createBackground()
	local background = require("ui.common.BackgroundLayer").new(self, __Localized("升星"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M