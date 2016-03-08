local HeroIcon = require("ui.common.HeroIcon")
local HeroDataManager = require("player-data.HeroDataManager")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.hero-museum.layers.ShowHerosLayer",function()
	return cc.Layer:create()
end)

function M:ctor(heroIdList)
	self:_createBackground()
	self:_createHeroIcons(heroIdList)
	self:_createScheduHandler()
	self:_createBottomButton()
end

function M:_createScheduHandler()
	self._index = 0
    TimerInterval:addTimer(self, 0.5)
    Event:registerNodeEvent(self)
end

function M:onUpdate()
	self._index = self._index + 1
	self:_heroIconAction(self._index)
	if table.getn(self._heroIconList) == self._index then
		TimerInterval:removeTimer(self)
	end
end

function M:onExit()
	TimerInterval:removeTimer(self)
end

function M:_heroIconAction(index)
	if nil == self._heroIconList[index] then
		return
	end
	self._heroIconList[index]:setVisible(true)
end

function M:_heroIconClick(heroIcon, heroData)
	local layer = require("ui.backpack.layer-manager.HeroIconClickLayer").new(heroData)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_createHeroIcons(heroIdList)
	self._heroIconList = {}
	local heroIdListLen = table.getn(heroIdList)
	local nodeLen = 5
	if 1 == heroIdListLen then
		nodeLen = 1
	end
	local buttonWidth = Screen.width / nodeLen
	local index = 1
	for key,heroId in pairs(heroIdList) do
		local heroData = HeroDataManager:getHeroDataById(heroId)
		local heroIcon = HeroIcon.new()

		heroIcon:setupClick(function()
			self:_heroIconClick(heroIcon, heroData)
		end)

		heroIcon:setVisible(false)
		heroIcon:reload(heroData)
		self:addChild(heroIcon)


		local heroIconSize = heroIcon:getContentSize()
		local posY = Screen.height - BackgroundLayer.TitleHeight - math.floor((key - 1) / 5 + 1) * heroIconSize.height
		heroIcon:setPosition(cc.p(buttonWidth * (index % 6 - 0.5), posY))
		index = index + 1
		if index > 5 then
			index = 1
		end

		table.insert(self._heroIconList, heroIcon)
	end
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("名将"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

function M:_createBottomButton()
	local button = CommonUI:createTextButton(self, __Localized("确定"), "ui/login/login-button.png")
	local buttonSize = button:getContentSize()
	button:setPosition(cc.p(Screen.width / 2, buttonSize.height / 2))
	button.onClicked = function()
		self:removeFromParent()
	end
end

return M