local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroDataManager = require("player-data.HeroDataManager")
local M = class("ui.hero-museum.layers.SelectHeroListLayer", function()
	return cc.Layer:create()
end)

local m_heroMaxLevel = 10

function M:ctor(delegate, dataType)
	self._delegate = delegate
	self._heroSelectList = delegate:getHeroSelectList()
	self._dataType = dataType
	self:_registerHandler()
	self:_createBackground()
	self:_initData()
	self:_createPageView()
end

function M:_onHeroIconClicked(heroData)
	self._delegate:onSelectHeroListLayerDidCallBack(self._dataType, heroData)
	self:removeFromParent()
end


function M:_registerHandler()
	Listener:addListener(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			Listener:removeListener(self)
		end
    end)
end

function M:_getTargetLevel()
	for _,heroSelectData in pairs(self._heroSelectList) do
		if Enum.UpgradeHeroType.Target == heroSelectData.dataType then
			return heroSelectData.heroLevel
		end
	end
end

function M:_checkHeroData(heroData)
	if m_heroMaxLevel == heroData:getHeroLevel() then
		return true
	end
	if Enum.UpgradeHeroType.Target ~= self._dataType and true == heroData:isLock() then
		return true
	end
	local heroId = heroData:getHeroId()
	for k,data in pairs(self._heroSelectList) do
		if heroId == data.heroId then
			return true
		end
	end
	return false
end

function M:_initData()
	local heroList = {}
	self._showHeroList = {}
	if Enum.UpgradeHeroType.Target == self._dataType then
		heroList = HeroDataManager:getBackpackHeroList()
	else
		heroList = HeroDataManager:getBackpackHeroNoTeamList(self:_getTargetLevel())
	end
	for _,heroData in pairs(heroList) do
		if false == self:_checkHeroData(heroData) then
			table.insert(self._showHeroList, heroData)
		end
	end
	if table.getn(self._showHeroList) == 0 then
		self:_createNoneHeroSelectLabel()
	end
end

function M:onPageViewCellTouched(pageView, cell)
	-- body
end

function M:onPageViewCellSize(pageView, idx)
	return 50, 0
end

function M:_heroIconDetail(heroIcon, idx)
	if self._showHeroList[idx + 1] then
		heroIcon:setVisible(true)
	else
		heroIcon:setVisible(false)
	end
	heroIcon:reload(self._showHeroList[idx + 1])
	heroIcon:setupClick(function()
		local heroData = heroIcon:getHeroData()
		self:_onHeroIconClicked(heroData)
	end)
end

function M:onPageViewCellAtIndex(pageView, idx)
	local heroIcon = pageView:dequeueCell()
	if nil == heroIcon then
		heroIcon = require("ui.common.HeroIcon").new()
		local heroIconSize = heroIcon:getContentSize()
		heroIcon:setPosition(cc.p(0, heroIconSize.height))
	end
	self:_heroIconDetail(heroIcon, idx)

    return heroIcon
end

function M:onPageViewCellCount(pageView)
	return table.getn(self._showHeroList)
end

function M:_createPageView()
	local pageViewSize = cc.size(
		Screen.width, 
		Screen.height - BackgroundLayer.TitleHeight * 2
		)
	local pageView = require("share.PageView").new(pageViewSize, self, 4)
	pageView:setPosition(0, BackgroundLayer.TitleHeight)
	self:addChild(pageView)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("选择武将"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

function M:_createNoneHeroSelectLabel()
	local label = CommonUI:createLabel(__Localized("没有当前等级的武将选择，请选择其他等级武将") , 30)
	self:addChild(label)
	Layout:layout(label, Screen.size, Layout.center)
end


return M