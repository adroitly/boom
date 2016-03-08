local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.city.MainLayer", function()
	return cc.Layer:create()
end)

local kImageKey = 
{
    King = "king",
    Heromuseum = "heromuseum",
    Military = "military",
    Produce = "produce",
    Market = "market",
}

local function _getFileName(key)
    return string.format("ui/city/inner-city-%s.png", key)
end

function M:ctor(buildingData)
    self._buildingData = buildingData
	self:_registerClickHandler()
	self:_initUserLayer()
    self:_checkBuildingType()
end

function M:onListenOpenAlertCoordinate()
	self:removeFromParent()
end

function M:_initUserLayer()
	self:_createBackground()
    self:_createHeroMuseum()
    self:_createProduce()
    self:_createFamousCity()
	self:_createKing()
    self:_createMarket()
    self:_createMilitary()
end

function M:_checkBuildingType()
    self:_updateButtonsByBuildingType(false)
    local buildingType = self:_getBuildingType()
    if buildingType == Enum.BuildingType.Castle then
        self:_updateButtonsByBuildingType(true)
    elseif buildingType == Enum.BuildingType.ResourcePoint then
        self._militaryButton:setVisible(true)
        self._produceButton:setVisible(true)
    elseif buildingType == Enum.BuildingType.Camp then
        self._militaryButton:setVisible(true)
    elseif buildingType == Enum.BuildingType.FamousCity then
        self:_updateButtonsByBuildingType(true)
        self._kingButton:setVisible(false)
    end
end

function M:_updateButtonsByBuildingType(visible)
	self._kingButton:setVisible(visible)
	self._marketButton:setVisible(visible)
	self._militaryButton:setVisible(visible)
    self._heroMuseumButton:setVisible(visible)
    self._produceButton:setVisible(visible)
end

function M:_createFamousCity()
	local famousCityButton = CommonUI:createTextButton(self, __Localized("已占领"), "ui/city/famous-button.png")
	local buttonSize = famousCityButton:getContentSize()
	famousCityButton:setPosition(cc.p(buttonSize.width / 2, Screen.height * 0.75))
	famousCityButton.onClicked = function()
		local scene = cc.Director:getInstance():getRunningScene()
		local layer = require("ui.hero-museum.layers.HeroPlaceLayer").new()
		layer:onClicked(function(buildingData)
			self:_onFamousCityButtonClick(buildingData)
		end)
		scene:addChild(layer)
	end
end

function M:_onFamousCityButtonClick(buildingData)
	self._buildingData = buildingData
	self:_checkBuildingType()
	self:_mapViewChangeToBuilding(self:_getBuildingId())
end

function M:_mapViewChangeToBuilding(buildingId)
    local mapLayerManager = MapManager:getMapLayerManager()
    if ResourcePointUtils:isCastleType(buildingId) then
        local position = MapConfig:getPositionFromCoordinate(PlayerData:getHomeCoor())
        mapLayerManager:changeViewCenterToPosition(position)
    else
        local twoDCoorTable = FamousCityConfigReader:getCoordinate(buildingId)
        mapLayerManager:changeViewCenterByTwoDCoor(twoDCoorTable[1], twoDCoorTable[2])
    end
end

function M:_createHeroMuseum()
	self._heroMuseumButton = CommonUI:createTextButton(self, __Localized("招贤馆"), _getFileName(kImageKey.Heromuseum))
	local buttonSize = self._heroMuseumButton:getContentSize()

	self._heroMuseumButton:setPosition(cc.p(Screen.width - buttonSize.width / 2, Screen.height / 4))

	self._heroMuseumButton.onClicked = function()
		local layer = require("ui.hero-museum.MainLayer").new()
		layer:updateBuildindId(self:_getBuildingId())
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(layer)
	end
end

function M:_createKing()
    local iconId = PlayerData:getUserInfoData():getIcon()
    local imageName = string.format("ui/city/inner-city-king-%d.png", iconId)
	self._kingButton = CommonUI:createTextButton(self, __Localized("君主"), imageName)
    self._kingButton.onClicked = function()
        local layer = require("ui.city.king.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end

	self._kingButton:setPosition(cc.p(Screen.width / 2, Screen.height * 0.6))
end

function M:_createProduce()
	self._produceButton = CommonUI:createTextButton(self, __Localized("生产"), _getFileName(kImageKey.Produce))
    self._produceButton.onClicked = function()
        local layer = require("ui.produce.layer-manager.ProduceResourcesLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
	local buttonSize = self._produceButton:getContentSize()
	self._produceButton:setPosition(cc.p(buttonSize.width / 2, Screen.height / 4))
    
    local TipsManager = require("ui.tips.TipsManager")
    TipsManager:addTipsListener(Enum.TipsType.ProduceResources, self._produceButton, cc.p(buttonSize.width - 50, buttonSize.height - 20))
end

function M:_createMilitary()
	self._militaryButton = CommonUI:createTextButton(self, __Localized("军事"), _getFileName(kImageKey.Military))
	local buttonSize = self._militaryButton:getContentSize()
	self._militaryButton:setPosition(cc.p(buttonSize.width, Screen.height * 0.5))
    self._militaryButton.onClicked = function()
        local layer = require("ui.city.MilitaryLayer").new(self._buildingData)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createMarket()
	self._marketButton = CommonUI:createTextButton(self, __Localized("集市"), _getFileName(kImageKey.Market))

	local buttonSize = self._marketButton:getContentSize()

	self._marketButton:setPosition(cc.p(Screen.width - buttonSize.width, Screen.height * 0.5))
	self._marketButton.onClicked = function()
		local layer = require("ui.market.MainLayer").new()
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(layer)
	end
end


function M:_registerClickHandler()
    Touch:registerTouchOneByOne(self, true)
    Event:registerNodeEvent(self)
    Listener:addListener(self)
end

function M:onExit()
    Listener:removeListener(self)
end

function M:_getBuildingType()
	if nil == self:_getBuildingId() then
		return nil
	end
	local buildType = BuildingConfigReader:getBuildingType(self:_getBuildingId())
	return buildType
end

function M:_getBuildingId()
    if self._buildingData then
        return self._buildingData:getBuildingId()
    end
    local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
    return ResourcePointUtils:getCastleTag()
end

function M:onTouchBegan(touch, event)
	return true
end


function M:_createBackground()
	local background = cc.Sprite:create("ui/city/inner-city-bg.png")
	background:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
	self:addChild(background)
end

return M