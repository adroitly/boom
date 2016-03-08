local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local M = class("ui.outside-search.layers.BuildingDefenceCell", function()
	return cc.TableViewCell:create()
end)

M.BuildingDefenceCellSize = cc.size(752, 193)
local kEmpty = 0
function M:ctor()
	self:_createBackground()
	self:_createHeroIcon()
	self:_createSoldierLabel()
	self:_createAddButton()
end

function M:reload(armyData)
	if armyData == kEmpty then
		self._addButton:setVisible(true)
		self._soldierInfoLabel:setString("")
		self._heroIcon:setVisible(false)
		return
	end
	self._addButton:setVisible(false)
	self._heroIcon:setVisible(true)
	self._armyData = armyData
	self._soldierInfoLabel:setString(self:_getSoldierInfoText())
	self._heroIcon:reload(armyData:getHeroData())
end

function M:setAddButtonCallback(callback)
	self._addButtonCallback = callback
end

function M:_createAddButton()
	self._addButton = CommonUI:createTextButton(self, "", "ui/team/button-add.png", "ui/team/button-add.png")
	Layout:layout(self._addButton, self:getContentSize(), Layout.left_center, cc.p(50, 0))
	self._addButton.onClicked = function()
		if self._addButtonCallback then
			self._addButtonCallback()
		end
	end
end

function M:_createHeroIcon()
	self._heroIcon = require("ui.common.HeroIcon").new()
	self:addChild(self._heroIcon)
	self._heroIcon:setPosition(cc.p(self._heroIcon:getContentSize().width, M.BuildingDefenceCellSize.height * 0.5))
end

function M:_createSoldierLabel()
	self._soldierInfoLabel = CommonUI:createLabel("", 24)
	self:addChild(self._soldierInfoLabel)
	Layout:layout(self._soldierInfoLabel, self:getContentSize(), Layout.center)
end

function M:_getSoldierInfoText()
	local soldierInfoText = ""
	soldierInfoText = string.format("%s\n%s\n%s", self:_getSoldierText(), self:_getFoodText(), self:_getMoraleText())
	return soldierInfoText
end


function M:_getFoodText()
	local food = self._armyData:getTeamData():getSoldierFood()
	return string.format(__Localized("粮食：%d"), food)
end

function M:_getSoldierText()
	local soldierType = self._armyData:getTeamData():getSoldierType()
	local soldierName = SoldierConfigReader:getName(soldierType)
	local soldierNumber = self._armyData:getTeamData():getSoldierNumber()
	return string.format(__Localized("%s：%d"), soldierName, soldierNumber)
end

function M:_getMoraleText()
	local text = __Localized("士气:10")
	return text
end

function M:_createBackground()
	local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
	self:addChild(background)
	self:setContentSize(background:getContentSize())
	background:setAnchorPoint(cc.p(0, 0))
end

return M