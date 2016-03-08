local M = class("ui.outside-search.layers.CityInfoScrollView", function()
	return cc.ScrollView:create()
end)

function M:ctor(buildingSearchData)
	self._buildingData = buildingSearchData:getBuildingData()
	self._armyDataList = buildingSearchData:getArmyDataList()
	self:_initScrollView()
	self:_createDefenceLabel()
	Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
	local minOffset = self:minContainerOffset()
	self:setContentOffset(cc.p(0, minOffset.y))
end

function M:_createDefenceLabel()
	local defenceLabel = CommonUI:createLabel(self:_getDefenceText(), 24)
	defenceLabel:setAnchorPoint(cc.p(0,0))
	-- defenceLabel:setPosition(cc.p(0, Screen.height / 8))
	self:addChild(defenceLabel)
	self:setContentSize(cc.size(Screen.width, defenceLabel:getContentSize().height))
end

function M:_initScrollView()
	self:setViewSize(cc.size(Screen.width, Screen.height / 4))
	self:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
	self:setClippingToBounds(true)
end

function M:_getDefenceText()
	local HPText = string.format(__Localized("城     防:%d"), self._buildingData:getCityDef())
	local soldierNumber = 0
	for _,armyData in pairs(self._armyDataList) do
		soldierNumber = soldierNumber + armyData:getArmyCount()
	end
	local soldierText = string.format(__Localized("驻守兵力:%d"), soldierNumber)
	local text = string.format("%s\n%s", HPText, soldierText)
	return text
end

return M