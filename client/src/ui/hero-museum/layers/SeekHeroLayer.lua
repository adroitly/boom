local BackgroundLayer = require("ui.common.BackgroundLayer")
local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.hero-museum.layers.SeekHeroLayer",function()
	return cc.Layer:create()
end)

local m_socketGetHeroKey = "hero_seek_2_get"
local m_socketChangeHeroKey = "hero_seek_2_change"
local m_socketConfirmHeroKey = "hero_seek_2"

local m_socketSeekHeroInfo = "hero_seek_2_info"


local function _checkBackpackEnough(data)
	assert(data)
	local backpackType = data[1][1]
	local needNumber = data[1][2]
	return BackpackDataManager:checkBackpackEnough(backpackType, needNumber)
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
			-- CommonUI:lightTips(string.format("Code = %s",msgTable.code))
			CommonUI:errorAlertView(msgTable.code)
		end
	end

	if m_socketConfirmHeroKey == cmd then
		CommonUI:showLoadingLayer(false)
		if 0 == msgTable.code then
			self:_reloadLayer(msgTable[m_socketSeekHeroInfo])
			self:_showSuccessLayer(msgTable)
		else
			-- CommonUI:lightTips(string.format("Code = %s",msgTable.code))
			CommonUI:errorAlertView(msgTable.code)
		end
	end
end

function M:ctor()
	self._buildingId = ResourcePointUtils:getCastleTag()
	self._buildingDatas = {}
	self:_getDataFromServer()
	self:_registerScriptHandler()
	self:_createPlaceButton()
	self:_createHeroInfoLayer()
	self:_createSearchNodes()
	self:_createConfirmNodes()
	self:_createPriceLabel()
end

function M:updateBuildindId(buildingId)
	if nil ~= buildingId then
		self:_onPlaceCallBack(buildingId)
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

function M:_findBuildDataKey(buildingId)
	for key,buildingData in pairs(self._buildingDatas) do
		if buildingId == buildingData.buildingId then
			return key
		end
	end
end

function M:_updateBuildingData(buildingId, heroType, heroLuck)
	local key = self:_findBuildDataKey(buildingId)
	if nil == key then
		local buildingData = 
					{
						buildingId = buildingId,
						heroType = heroType,
						heroLuck = heroLuck
					}
		table.insert(self._buildingDatas, buildingData)
	else
		self._buildingDatas[key] = 
					{
						buildingId = buildingId,
						heroType = heroType,
						heroLuck = heroLuck
					}
	end
end

function M:_reloadLayer(heroSeekInfo)
	self._buildingId = heroSeekInfo.building_id
	local heroType = heroSeekInfo.hero_seek_type
	self._heroInfoLayer:reloadByHeroType(heroType)
	local heroLuck = heroSeekInfo.hero_seek_luck
	self._heroInfoLayer:setProgressPercentage(heroLuck)
	self:_updateBuildingData(self._buildingId, heroType, heroLuck)
end

function M:_registerScriptHandler()
	SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			SocketManager:removeObserver(self)
		end
    end)
end

function M:_createPriceLabel()
	local priceLabel =  CommonUI:createLabel(__Localized("每次招揽需要300元气玉"), 30)
	self:addChild(priceLabel)

	local labelSize = priceLabel:getContentSize()
	priceLabel:setPosition(cc.p(Screen.width / 2, BackgroundLayer.BottomHeight + labelSize.height * 1.5))
end

function M:_createHeroInfoLayer()
	self._heroInfoLayer = require("ui.hero-museum.layers.TrickHeroInfoLayer").new()
	self:addChild(self._heroInfoLayer)
end

function M:_onPlaceCallBack(buildingId)
	local placeName = "主城"
	if not ResourcePointUtils:isCastleType(buildingId) then
		placeName = FamousCityConfigReader:getName(buildingId)
	end
	self._placeButton:setText(placeName)
	self._buildingId = buildingId
	local key = self:_findBuildDataKey(buildingId)
	if nil == key then
		self:_getDataFromServer()
	else
		local heroType = self._buildingDatas[key].heroType
		local heroLuck = self._buildingDatas[key].heroLuck
		self._heroInfoLayer:reloadByHeroType(heroType)
		self._heroInfoLayer:setProgressPercentage(heroLuck)
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
	local seekData = PayRatioConfigReader:getSeekConfirm()
	if _checkBackpackEnough(seekData) then
		CommonUI:showLoadingLayer(true)
		local sendData = {building_id = self._buildingId}
		SocketManager:send(m_socketConfirmHeroKey, sendData)
	else
		self:_createRechargeView()
	end
end

function M:_createConfirmNodes()
	local seekData = PayRatioConfigReader:getSeekConfirm()
	self._confirmLabel = CommonUI:createLabel(string.format("%s%s", seekData[1][2],BackpackConfigRead:getName(seekData[1][1])), 30)
	self:addChild(self._confirmLabel)
	self._confirmButton = CommonUI:createTextButton(self, __Localized("招揽"), "ui/login/login-up.png")
	self._confirmButton.onClicked = function()
		self:_onComfirmButtonClick()
	end
	local buttonSize = self._confirmButton:getContentSize()
	local labelSize = self._confirmLabel:getContentSize()
	self._confirmButton:setPosition(cc.p(Screen.width - buttonSize.width, buttonSize.height / 2))
	self._confirmLabel:setPosition(cc.p(Screen.width - buttonSize.width, buttonSize.height + labelSize.height / 2))
end

function M:_onSearchButtonClick()
	local searchData = PayRatioConfigReader:getSeekSearch()
	if _checkBackpackEnough(searchData) then
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
	self._searchButton.onClicked = function()
		self:_onSearchButtonClick()
	end

	local buttonSize = self._searchButton:getContentSize()
	self._searchButton:setPosition(cc.p(buttonSize.width, buttonSize.height / 2))
	
end

function M:_createRechargeView()
	local seekData = PayRatioConfigReader:getSeekConfirm()
	CommonUI:lightTips(string.format(__Localized("%s不足"), BackpackConfigRead:getName(seekData[1][1])))
end

return M