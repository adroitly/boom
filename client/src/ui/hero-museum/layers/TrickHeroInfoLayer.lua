local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local SkillConfigReader = require("config-reader.SkillConfigReader")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.hero-museum.layers.TriceHeroInfoLayer", function()
	return cc.Layer:create()
end)

local function _getHeroInfoNames()
	local infoNames = {"", "国家:", "兵种:", "武力:", "智力:", "统帅:", "体质:"}
	return infoNames
end

local function _getHeroInfoDatas(heroType)
	local heroName = HeroConfigRead:getName(heroType)
	local heroForce = HeroAttribute:getForce(heroType, 1)
	local heroBrains = HeroAttribute:getBrains(heroType, 1)
	local heroCommander = HeroAttribute:getCommander(heroType, 1)
	local heroConstitution = HeroAttribute:getConstitution(heroType, 1)
	local recommendSoldierId = HeroConfigRead:getRecommendSoldier(heroType)
	local soldierName = SoldierConfigReader:getNameByType(recommendSoldierId)
	local countryId = HeroConfigRead:getCountry(heroType)
	local countryName = CountryConfigReader:getCountryName(countryId)
	local infoDatas = {heroName, countryName, soldierName, heroForce, heroBrains, heroCommander, heroConstitution}
	return infoDatas
end

local function _getHeroInfoLabelTexts(heroType)
	local infoNames = _getHeroInfoNames()
	local infoDatas = {}
	if nil == heroType then
		for k,v in pairs(infoNames) do
			infoDatas[k] = "00"
		end
	else
		infoDatas = _getHeroInfoDatas(heroType)
	end
	local labelTexts = {}
	for i=1,3 do
		local labelText = ""
		for j=1,3 do
			local key = 3 * (j- 1) + i
			local name = infoNames[key]
			local vaule = infoDatas[key]
			local textEnd = "\n"
			if nil == name then
				break
			end
			if 3 == j then
				textEnd = ""
			end
			labelText = string.format("%s%s%s%s", labelText,name,vaule,textEnd)
		end
		table.insert(labelTexts, labelText)
	end
	return labelTexts
end

function M:ctor()
	self:_registerTimerHandler()
	self:_createTimeLabel()
	self:_createHeroIconSripte()
	self:_createHeroInfoLabels()
	self:_createSkillsLayer()
	self:_createProgressTimer()
	self:_createFileLabel()
end

function M:reloadByHeroType(heroType)
	self._heroType = heroType
	local heroType = self:_getHeroType()
	local spriteFrame = CommonUI:createSpriteFrameTinyName("hero-icon", heroType..".png")
	self._heroIconSprite:setSpriteFrame(spriteFrame)
	self:_changeHeroInfoLabels()
	local heroSkills = HeroConfigRead:getSkill(heroType)
	self._skillsLayer:reload(heroSkills)
end

function M:setProgressPercentage(percentage)
	self._progressTimer:setPercentage(percentage)
	self._progressLabel:setString(string.format("%d/100", percentage))
end

function M:getProgressValue()
	return self._progressTimer:getPercentage()
end

function M:_createSkillsLayer()
	self._skillsLayer = require("ui.team.layer-manager.UserSkillLayer").new()
	self:addChild(self._skillsLayer)
	self._skillsLayer:setPosition(cc.p(0, Screen.height / 2))
end

function M:_createFileLabel()
	local fileLabel = CommonUI:createLabel(__Localized("每次失败增加5好感度"), 30)
	self:addChild(fileLabel)


	local progressSize = self._progressTimer:getContentSize()
	local labelSize = fileLabel:getContentSize()

	local PosiX = Screen.width / 2
	local PosiY = Screen.height / 4 - progressSize.height + labelSize.height / 2

	fileLabel:setPosition(cc.p(PosiX, PosiY))
end


function M:_createProgressTimer()
	local opinionLabel = CommonUI:createLabel(__Localized("好感度:"), 30)
	opinionLabel:setAlignment(0)
	self:addChild(opinionLabel)
	local opinionLabelSize = opinionLabel:getContentSize()

	local PosiX = Screen.width / 4
	local PosiY = Screen.height / 4 + opinionLabelSize.height

	opinionLabel:setPosition(PosiX, PosiY)

	self._progressTimer = ProgressBar.new("ui/hero-museum/progressbg.png", "ui/hero-museum/progressup.png")
	self:addChild(self._progressTimer)
	local progressSize = self._progressTimer:getContentSize()
	self._progressTimer:setPosition(cc.p(PosiX + opinionLabelSize.width/2 + progressSize.width / 2, PosiY))

	self._progressLabel = CommonUI:createLabel("00/100", 36)
	self._progressLabel:setPosition(cc.p(0, 0))
	self._progressTimer:addChild(self._progressLabel)
end


function M:_changeHeroInfoLabels()
	local heroType = self:_getHeroType()
	local infoNames = _getHeroInfoNames()
	local labelTexts = _getHeroInfoLabelTexts(heroType)
	for key,value in pairs(labelTexts) do
		self._heroInfoLabels[key]:setString(value)
	end
end

function M:_createHeroInfoLabels()
	self._heroInfoLabels = {}
	local infoNames = _getHeroInfoNames()
	local labelTexts = _getHeroInfoLabelTexts()
	local heroSpriteX, heroSpriteY = self._heroIconSprite:getPosition()
	local heroSpriteSize = self._heroIconSprite:getContentSize()
	for key,value in pairs(labelTexts) do
		local label = CommonUI:createLabel(value,30)
		local labelSize = label:getContentSize()
		label:setAlignment(0)
		label:setPosition(cc.p(heroSpriteX + labelSize.width + (Screen.width / 4 * (key - 1)), heroSpriteY))
		self:addChild(label)
		table.insert(self._heroInfoLabels, label)
	end
	
end

function M:_createHeroIconSripte()
	self._heroIconSprite = cc.Sprite:create("ui/army-select.png")
	local spriteSize = self._heroIconSprite:getContentSize()
	local PosiX = spriteSize.width
	local PosiY = Screen.height - BackgroundLayer.TitleHeight * 3.5 + spriteSize.height / 2
	self._heroIconSprite:setPosition(cc.p(PosiX, PosiY))

	self:addChild(self._heroIconSprite)
end

function M:_getHeroType()
	return self._heroType
end


function M:_registerTimerHandler()
    TimerInterval:addTimer(self, 1)
    Event:registerNodeEvent(self)	
end

function M:onUpdate()
	self:_changeTimeLabel()
end

function M:onExit()
	TimerInterval:removeTimer(self)
end

function M:_createTimeLabel()
	self._timeLabel = CommonUI:createLabel(__Localized("刷新倒计时:00:00:00"), 30)
	self:addChild(self._timeLabel)

	local labelSize = self._timeLabel:getContentSize()
	self._timeLabel:setPosition(cc.p(Screen.width / 2, Screen.height - BackgroundLayer.TitleHeight * 2 - labelSize.height / 2))

	self:_changeTimeLabel()
end

function M:_changeTimeLabel()
	local serverTime = PlayerData:getServerTime()
	local nowH = os.date("%H", serverTime)
	local nowM = os.date("%M", serverTime)
	local nowS = os.date("%S", serverTime)
	local nowTime = nowH * 3600 + nowM * 60 + nowS
	local targetTime = 24 * 3600 - nowTime
	local timText = Function:timeToDateString(targetTime)
	local timeLabelText = string.format(__Localized("刷新倒计时:%s"), timText)
	self._timeLabel:setString(timeLabelText)
end

return M