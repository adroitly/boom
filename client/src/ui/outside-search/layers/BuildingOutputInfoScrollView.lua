local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local CampConfigReader = require("ui.produce.data-manager.CampConfigReader")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local ResourcePointConfigReader = require("ui.produce.data-manager.ResourcePointConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local M = class("ui.outside-search.layers.BuildingOutputInfoScrollView", function()
	return cc.ScrollView:create()
end)

function M:ctor(buildingSearchData)
	self._buildingData = buildingSearchData:getBuildingData()
	self._otherPlayerData = buildingSearchData:getOtherPlayerData()
	self:_createProductLabel()
	self:_initScrollView()
	Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
	local minOffset = self:minContainerOffset()
	self:setContentOffset(cc.p(0, minOffset.y))
end

function M:_createProductLabel()
	local text = self:_getProductText(self._buildingData)
	local productLabel = CommonUI:createLabel(text, 24)
	self:addChild(productLabel)


	productLabel:setAnchorPoint(cc.p(0,0))
	local labelSize = productLabel:getContentSize()
	productLabel:setPosition(cc.p(Screen.width / 2 - labelSize.width / 2, 0))

	self:setContentSize(cc.size(Screen.width, labelSize.height))
end

function M:_getProductText()
	local buildingId = self._buildingData:getBuildingId()
	local buildingType = BuildingConfigReader:getBuildingType(buildingId)
	local text = ""
	if buildingType == Enum.BuildingType.FamousCity then
		text = self:_getFamousProductText(buildingId)
	elseif buildingType == Enum.BuildingType.ResourcePoint then
		text = self:_getResourceProductText(buildingId)
	elseif buildingType == Enum.BuildingType.Camp then
		text = self:_getSoldierProductText(buildingId)
	end
	return string.format(__Localized("产出:\n%s"), text)
end

function M:_getSoldierText(soldierList, isFamousCity)
	local text = ""
	for _,soldierTypeStr in pairs(soldierList) do
		local speed = ""
		if isFamousCity and self._otherPlayerData then
			local level = self._otherPlayerData:getLevel() or 1
			local soldierType = soldierTypeStr + level
			speed = string.format(__Localized("(%s秒/个)"), SoldierConfigReader:getProductionRate(soldierType))
		end
		text = string.format("%s%s%s\n",text, SoldierConfigReader:getNameByType(soldierTypeStr), speed)
	end
	return text
end

function M:_getResourceText(resourceList, isFamousCity)
	local text = ""
	for _,backpackTypeTable in pairs(resourceList) do
		local backpackType = backpackTypeTable.id
		local speed = ""
		if isFamousCity and self._otherPlayerData then
			speed = string.format(__Localized("(%s秒/个)"), backpackTypeTable.time)
		end
		text = string.format("%s%s%s\n", text, BackpackConfigRead:getName(backpackType), speed)
	end
	return text
end

function M:_getFamousProductText(buildingId)
	local isFamousCity = false
	local buildingType = BuildingConfigReader:getBuildingType(buildingId)
	if buildingType == Enum.BuildingType.FamousCity then
		isFamousCity = true
	end
	local soldierList = FamousCityConfigReader:getProduceSoldierType(buildingId)
	local resourceList = FamousCityConfigReader:getProduceResSpeed(buildingId)
	local text = string.format("%s", self:_getSoldierText(soldierList, isFamousCity))
	local productText = string.format("%s%s", text, self:_getResourceText(resourceList, isFamousCity))
	return productText
end

function M:_getSoldierProductText(buildingId)
	local soldierList = CampConfigReader:getProduceSoldierType(buildingId)
	return self:_getSoldierText(soldierList)
end

function M:_getResourceProductText(buildingId)
	local resourceList = ResourcePointConfigReader:getProduceResSpeed(buildingId)
	local text = self:_getResourceText(resourceList)
	return text
end

function M:_initScrollView()
	self:setViewSize(cc.size(Screen.width, Screen.height / 4))
	self:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
	self:setClippingToBounds(true)
end

return M