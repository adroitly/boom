
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local PackageItemData = require("ui.backpack.data-manager.PackageItemData")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.backpack.layer-manager.EditGoodsLayer", function()
	return cc.Layer:create()
end)

local testmarket = "auction_add"

local m_maxUseCount = 100

local m_commads = 
		{
			OpenBox = "open_box",
			UseItem = "item_use",
			ArmyPromoteUseItem = "army_promote_use_item"
		}

local m_useInfos = 
		{
			{itemType = 1, command = m_commads.UseItem, hasNumber = false},
			{itemType = 3, command = m_commads.OpenBox, hasNumber = true},
		}
local m_userItemSpeed = 
{
	{backpackId = 50301, command = m_}
}
local function _getSendCommand(backpackId)
	local itemType = BackpackConfigRead:getItemType(backpackId)
	for _,data in pairs(m_useInfos) do
		if itemType == data.itemType then
			return data.command
		end
	end
	return nil
end

local function _hasUseNumber(backpackId)
	local itemType = BackpackConfigRead:getItemType(backpackId)
	for _,data in pairs(m_useInfos) do
		if itemType == data.itemType then
			return data.hasNumber
		end
	end
	return false
end


--[[
backpackData  背包物品数据
]]
function M:reload(backpackData)
	self._backpackData = backpackData
	local packID = backpackData:getItemType()
	local packName = BackpackConfigRead:getName(packID)
	local buttonName = ""
	local showName = ""
	buttonName = __Localized("使用")
	showName = __Localized("主公，您确定使用")..packName..__Localized("道具?")
	self._backgroundLayer:reloadLayer(buttonName)
	self._editButton:setText(buttonName)
	self._showLabel:setString(showName)
	self:_updateSilder(backpackData)
end

function M:getContentSize()
	return self._contentSize
end

function M:ctor()
	self._useBackpackId = nil
	self:_createBackground()
	self:_createShowLabel()
	self:_createEditButton()
	self:_createSilider()
	self:_setupEventHandler()

end

function M:onTouchBegan(touch, event)
	return true
end

function M:_checkMaxCount()
	if false == _hasUseNumber(self:_getBackpackDataID()) then
		self._maxCount = 1
	end
	self._maxCount = (self._maxCount > m_maxUseCount) and m_maxUseCount or self._maxCount
end

function M:_updateSilder(backpackData)
	self._maxCount = backpackData:getItemNumber()
	self:_checkMaxCount()
	self._slider:setMinimumValue(1)
    self._slider:setMaximumValue(self._maxCount)
    self._sliderLabel:setString("1".." / "..self._maxCount)
end

function M:_setupEventHandler()
	SocketManager:addObserver(self)
   
    Event:registerNodeEvent(self)
    Touch:registerTouchOneByOne(self, true)
end

function M:onExit()
	SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
	local commons = 
	{
		[m_commads.OpenBox] = function(msgTable)
			self:_checkOpenBox(msgTable)
		end,
		[m_commads.UseItem] = function(msgTable)
			self:_checkUseItem(msgTable)
		end
	}

	local fun = commons[cmd]
	if fun then 
		fun(msgTable)
		CommonUI:showLoadingLayer(false)
	end
end

function M:_checkUseItem(msgTable)
	assert(msgTable and msgTable.code)
	local name = BackpackConfigRead:getName(self._useBackpackId)
	local showText = string.format(__Localized("使用%s%s"), name, (0 == msgTable.code) and "成功" or "失败")
	CommonUI:lightTips(showText)
	self:removeFromParent()
end

function M:_checkOpenBox(msgTable)
	assert(msgTable and msgTable.code)
	if 0 ~= msgTable.code then
		CommonUI:lightTips(__Localized("开启失败"))
		return
	end
	local packageItemDataList = PackageItemData:getItemList(msgTable)
	local showDetailLayer = require("ui.backpack.layer-manager.ShowBoxOpenDetailLayer").new(packageItemDataList)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(showDetailLayer)
	self:removeFromParent()
end

function M:_getBackpackDataID()
	return self._backpackData:getItemType()
end

function M:_createShowLabel()
	self._showLabel = CommonUI:createLabel(__Localized("主公，您确定使用")..__Localized("道具?") , 30)
	local labelSize = self._showLabel:getContentSize()
	self._showLabel:setAnchorPoint(0, 0.5)
	self._showLabel:setPosition(0, self._contentSize.height / 2 - labelSize.height)
	self:addChild(self._showLabel)
end

function M:_subButtonClick()
	local value = math.floor(self._slider:getValue())
	if value <= 1 then
		return
	end
	self._slider:setValue(value - 1)
end

function M:_addButtonClick()
	local value = math.floor(self._slider:getValue())
	if value >= self._maxCount then
		return
	end
	self._slider:setValue(value + 1)
end

function M:_createSilider()
	local subButton = ButtonLongPress.new("ui/team/button-sub.png", "ui/team/button-sub.png")
	local subButtonSize = subButton:getContentSize()
	local PosiX = subButtonSize.width / 2
	local PosiY = Screen.height / 2 - subButtonSize.height * 2
	subButton:setPosition(PosiX, PosiY)
	self:addChild(subButton)
	subButton.onClicked = function()
		self:_subButtonClick()
	end
	self._slider = ControlSlider.new("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
	self._slider:setMinimumValue(0)
    self._slider:setMaximumValue(30)
    local sliderSize = self._slider:getContentSize()
    self._slider:setPosition(subButtonSize.width + sliderSize.width / 2, PosiY)
    self:addChild(self._slider)
    self._slider.onValueChanged = function(sender, currentValue)
	local value = math.floor(currentValue)
        self:_sliderChange(value)
    end
  
    local addButton = ButtonLongPress.new("ui/team/button-add.png", "ui/team/button-add.png")
    addButton:setPosition(subButtonSize.width * 1.5 + sliderSize.width, PosiY)
    self:addChild(addButton)
    addButton.onClicked = function()
    	self:_addButtonClick()
    end

    self._sliderLabel = CommonUI:createLabel("0 / 0")
    local labelSize = self._sliderLabel:getContentSize()
    self._sliderLabel:setPosition(subButtonSize.width * 1.5 + sliderSize.width * 1.5 + labelSize.width /2, PosiY)
    self:addChild(self._sliderLabel)
end

function M:_sliderChange(value)
	self._sliderLabel:setString(value.." / "..self._maxCount)
end

function M:_createEditButton()
	self._editButton = CommonUI:createTextButton(self, __Localized("使用"), "ui/team/ui-but-0004a.png", "ui/team/ui-but-0004a.png")
	local buttonSize = self._editButton:getContentSize()
	local PosiX = self._contentSize.width - buttonSize.width 
	local PosiY = buttonSize.height + 100
	self._editButton:setPosition(PosiX, PosiY)
	self._editButton.onClicked = function()
		self:_editButtonClick()
	end
end

function M:_editButtonClick()
	local useCount = math.floor(self._slider:getValue())
	local backpackId = self:_getBackpackDataID()
	local command = _getSendCommand(backpackId)
	local itemData = {item_type = backpackId, item_number = useCount}
	if false == _hasUseNumber(backpackId) then
		itemData = {item_type = backpackId}
	end
	assert(command)
	SocketManager:send(command, itemData)
	CommonUI:showLoadingLayer(true)
	self._useBackpackId = backpackId
	
end

function M:_createBackground()
	self._backgroundLayer = require("ui.common.BackgroundLayer").new(self, "")
	self._contentSize = cc.size(Screen.width, Screen.height)
	self._backgroundLayer:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M