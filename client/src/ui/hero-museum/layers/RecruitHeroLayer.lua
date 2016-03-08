local BackgroundLayer = require("ui.common.BackgroundLayer")
local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.hero-museum.layers.RecruitHeroLayer",function()
	return cc.Layer:create()
end)

local SAVE_DEFULT_KEY = "RecruitHeroLayerOpinionValue"

-- 招贤的命令为hero-seek-3
local m_socketGetHeroKey = "hero_seek_3_get"
local m_socketChangeHeroKey = "hero_seek_3_change"
local m_socketConfirmHeroKey = "hero_seek_3"
local m_socketSeekHeroInfo = "hero_seek_3_info"

function M:ctor()
	self._buildingId = ResourcePointUtils:getCastleTag()
	self._buildingDatas = {}
	self:_getDataFromServer()
	self:_registerScriptHandler()
	self:_initData()
	self:_createPlaceButton()
	self:_createHeroInfoLayer()
	self:_createSearchNodes()
	self:_createConfirmNodes()
	self:_createPriceShow()
	self:_changeNowCoinLabel()
end

function M:updateBuildindId(buildingId)
	if nil ~= buildingId then
		self:_onPlaceCallBack(buildingId)
	end
end

function M:_initData()
	local priceData = PayRatioConfigReader:getRecruitConfirm()
	self._price = tonumber(priceData[1][2])
	self._priceName = BackpackConfigRead:getName(tonumber(priceData[1][1])) or __Localized("元气玉")
	self._nowCoin = self._price
	self._minCoin = self._price
	self._maxCoin = 20 * self._price
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	if m_socketGetHeroKey == cmd then
		CommonUI:showLoadingLayer(false)
		self:_reloadLayer(msgTable[m_socketSeekHeroInfo])
	end

	if m_socketChangeHeroKey == cmd then
		CommonUI:showLoadingLayer(false)
		if 0 == msgTable.code then
			self:_reloadLayer(msgTable[m_socketSeekHeroInfo])
		else
			CommonUI:errorAlertView(msgTable.code)
		end
	end

	if m_socketConfirmHeroKey == cmd then
		CommonUI:showLoadingLayer(false)
		if 0 == msgTable.code then
			self:_reloadLayer(msgTable[m_socketSeekHeroInfo])
			self:_showSuccessLayer(msgTable)
		else
			CommonUI:errorAlertView(msgTable.code)
		end
	end
		
end

function M:_showSuccessLayer(msgTable)
	if 0 == msgTable.hero_id then
		CommonUI:lightTips(__Localized("运气不佳,再接再厉"))
		return
	end
	local layer = require("ui.hero-museum.layers.ShowHerosLayer").new({msgTable.hero_id})
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
end

function M:_findBuildingData(buildingId)
	for key,buildingData in pairs(self._buildingDatas) do
		if buildingId == buildingData.buildingId then
			return key
		end
	end
end

function M:_updateBuildingData(buildingId, heroType)
	local key = self:_findBuildingData(buildingId)
	if nil == key then
		local buildingData = 
					{
						buildingId = buildingId,
						heroType = heroType,
					}
		table.insert(self._buildingDatas, buildingData)
	else
		self._buildingDatas[key] = 
					{
						buildingId = buildingId,
						heroType = heroType,
					}
	end
end

function M:_reloadLayer(heroSeekInfo)
	self._buildingId = heroSeekInfo.building_id
	local heroType = heroSeekInfo.hero_seek_type
	self._heroInfoLayer:reloadByHeroType(heroType)
	self:_updateBuildingData(self._buildingId, heroType)
end

function M:_getDataFromServer()
	local sendData = {building_id = self._buildingId}
	SocketManager:send(m_socketGetHeroKey, sendData)
	CommonUI:showLoadingLayer(true)
	
end

function M:_searchFromServer()
	local sendData = {building_id = self._buildingId}
	SocketManager:send(m_socketChangeHeroKey, sendData)
	CommonUI:showLoadingLayer(true)
end

function M:_registerScriptHandler()
	SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			SocketManager:removeObserver(self)
		end
    end)
end

function M:_changeNowCoinLabel()
	local percentage = math.floor(self._nowCoin / self._maxCoin * 100)
	self._heroInfoLayer:setProgressPercentage(percentage)

	self._nowCoinLabel:setString(string.format("%d/%d", self._nowCoin, self._maxCoin))
	self._confirmLabel:setString(string.format(__Localized("%d%s"), self._nowCoin, self._priceName))
end

function M:_subButtonClick()
	self._nowCoin = self._nowCoin - self._price

	if self._minCoin >= self._nowCoin then
		self._nowCoin = self._minCoin
	end
	self:_changeNowCoinLabel()
end

function M:_addButtonClick()

	self._nowCoin = self._nowCoin + self._price
	if self._maxCoin <= self._nowCoin then
		self._nowCoin = self._maxCoin
	end
	self:_changeNowCoinLabel()
end

function M:_createPriceShow()
	local searchButtonSize = self._searchButton:getContentSize()
	local subButton = ButtonLongPress.new("ui/team/button-sub.png")
	self:addChild(subButton)
	subButton.onClicked = function()
		self:_subButtonClick()
	end

	self._nowCoinLabel = CommonUI:createLabel(string.format("%d/%d", self._nowCoin, self._maxCoin), 24)
	self:addChild(self._nowCoinLabel)

	local priceLabel = CommonUI:createLabel(string.format(__Localized("每%d%s增加5好感度"), self._price, self._priceName), 30)
	self:addChild(priceLabel)

	local labelSize = priceLabel:getContentSize()

	priceLabel:setPosition(cc.p(Screen.width / 2 , searchButtonSize.height + labelSize.height * 1.5))
	self._nowCoinLabel:setPosition(cc.p(Screen.width / 2 , searchButtonSize.height + labelSize.height * 2.5))

	local addButton = ButtonLongPress.new( "ui/team/button-add.png")
	self:addChild(addButton)
	addButton.onClicked = function()
		self:_addButtonClick()
	end
	
	subButton:setPosition(cc.p(searchButtonSize.width * 1.5, searchButtonSize.height + labelSize.height * 2.5))
	addButton:setPosition(cc.p(Screen.width - searchButtonSize.width * 1.5, searchButtonSize.height + labelSize.height * 2.5))
end

function M:_createHeroInfoLayer()
	self._heroInfoLayer = require("ui.hero-museum.layers.TrickHeroInfoLayer").new()
	self:addChild(self._heroInfoLayer)
	local progressValue = cc.UserDefault:getInstance():getIntegerForKey(SAVE_DEFULT_KEY)
	progressValue = progressValue > 0 and progressValue or 5
	self._nowCoin =  progressValue * self._maxCoin / 100
	self._heroInfoLayer:setProgressPercentage(progressValue)
end

function M:_onPlaceCallBack(buildingId)
	local placeName = "主城"
	if ResourcePointUtils:getCastleTag() ~= buildingId then
		placeName = FamousCityConfigReader:getName(buildingId)
	end

	self._placeButton:setText(placeName)
	self._buildingId = buildingId
	local key = self:_findBuildingData(buildingId)
	if nil == key then
		self:_getDataFromServer()
	else
		local heroType = self._buildingDatas[key].heroType
		self._heroInfoLayer:reloadByHeroType(heroType)
	end
end

function M:_createPlaceButton()
	self._placeButton = CommonUI:createTextButton(self, "主城", "ui/login/login-up.png")
	local buttonSize = self._placeButton:getContentSize()
	self._placeButton:setPosition(cc.p(buttonSize.width / 2, Screen.height - BackgroundLayer.TitleHeight - buttonSize.height * 1.5))
	self._placeButton.onClicked = function()
		local scene = cc.Director:getInstance():getRunningScene()
		local layer = require("ui.hero-museum.layers.HeroPlaceLayer").new()
		layer:onClicked(function(buildingData)
			self:_onPlaceCallBack(buildingData:getBuildingId())
		end)
		scene:addChild(layer)
	end
end

function M:_onComfirmButtonClick()
	local recruitData = PayRatioConfigReader:getRecruitConfirm()
	if BackpackDataManager:checkBackpackEnough(recruitData[1][1], self._nowCoin) then
		local progressValue = self._heroInfoLayer:getProgressValue()
		local sendData = {building_id = self._buildingId,hero_seek_luck = progressValue}
		SocketManager:send(m_socketConfirmHeroKey, sendData)
		CommonUI:showLoadingLayer(true)
	else
		self:_createRechargeView()
	end
end


function M:_createConfirmNodes()
	local recruitData = PayRatioConfigReader:getRecruitConfirm()
	self._confirmLabel = CommonUI:createLabel(string.format("%s%s", recruitData[1][1], recruitData[1][2]), 30)
	self:addChild(self._confirmLabel)
	self._confirmButton = CommonUI:createTextButton(self, __Localized("招揽"), "ui/login/login-up.png")
	local buttonSize = self._confirmButton:getContentSize()
	local labelSize = self._confirmLabel:getContentSize()
	self._confirmButton.onClicked = function()
		local progressValue = self._heroInfoLayer:getProgressValue()
		cc.UserDefault:getInstance():setIntegerForKey(SAVE_DEFULT_KEY, progressValue)
		cc.UserDefault:getInstance():flush()
		self:_onComfirmButtonClick()
	end

	self._confirmButton:setPosition(cc.p(Screen.width - buttonSize.width, buttonSize.height / 2))
	self._confirmLabel:setPosition(cc.p(Screen.width - buttonSize.width, buttonSize.height + labelSize.height / 2))
end

function M:_onSearchButtonClick()
	local searchData = PayRatioConfigReader:getRecruitSearch()
	if BackpackDataManager:checkBackpackEnough(searchData[1][1], searchData[1][2]) then
		self:_confirmSearch()
	else
		self:_createRechargeView()
	end
end

function M:_confirmSearch()
	local searchData = PayRatioConfigReader:getRecruitSearch()
	local searchAlertText = string.format(__Localized("确定花费%d%s搜索一次?"),searchData[1][2], 
		BackpackConfigRead:getName(searchData[1][1]))
	local alertView = AlertView.new(searchAlertText, __Localized("取 消"), __Localized("搜 索"))
	alertView.onClicked = function(index)
			if 1==index then 
				self:_searchFromServer()
			end
		end
end

function M:_createSearchNodes()
	self._searchButton = CommonUI:createTextButton(self, __Localized("搜索"), "ui/login/login-up.png")
	local buttonSize = self._searchButton:getContentSize()
	self._searchButton.onClicked = function()
		self:_onSearchButtonClick()
	end
	self._searchButton:setPosition(cc.p(buttonSize.width, buttonSize.height / 2))


end

function M:_createRechargeView()
	CommonUI:alertRechargeLayer()
end

return M