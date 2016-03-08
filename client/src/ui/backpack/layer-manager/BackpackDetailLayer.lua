local MarketData = require("ui.market.datas.MarketData")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.backpack.layer-manager.BackpackDetailLayer", function()
	return cc.Layer:create()
end)


function M:ctor(backpackId)
	self._backpackId = backpackId
	self._buttonsInfo = {}
	self:_createBackground()
	self:_createShowLabel()
	self:_setEventHandler()
	self:_reloadData()
	self:_createBackpackIcon(backpackId)
	Event:registerNodeEvent(self)
end

function M:setLookOverState()
	self:setButtonNumber(1)
	self:createGainButtonByIndex(1)
end

function M:setButtonNumber(number)
	self._buttonNumber = number
	self:_createBackButton()
end

function M:createGainButtonByIndex(index)
	local gainButton = CommonUI:createTextButton(self, __Localized("去获取"), "ui/login/login-button.png")
	self:_updatePosition(gainButton, index)

	gainButton.onClicked = function()
		self:_gainButtonClick()
	end
end

function M:createMarketButtonByIndex(index)
	local marketButton = CommonUI:createTextButton(self, __Localized("放市场"), "ui/login/login-button.png")
	self:_updatePosition(marketButton, index)

	marketButton.onClicked = function()
		self:_marketButtonClick()
	end
end

function M:createUseButtonByIndex(index)
	local useButton = CommonUI:createTextButton(self, __Localized("使用"), "ui/login/login-button.png")
	self:_updatePosition(useButton, index)

	local isCanUse = require("ui.backpack.layer-manager.CheckBackpackItemCanUse"):isCanUse(self:_getBackpackDataID())
	if false == isCanUse then
		useButton:setEnabled(false)
	end

	useButton.onClicked = function()
		self:_userButtonClick()
	end
end

function M:setAllButtons()
	local backpackId = self:_getBackpackDataID()
	local isUse = BackpackConfigRead:isUse(backpackId)
	if 0 == isUse then
		self:setButtonNumber(2)
		self:createGainButtonByIndex(1)
		self:createMarketButtonByIndex(2)
	else
		self:setButtonNumber(3)
		self:createGainButtonByIndex(1)
		self:createMarketButtonByIndex(2)
		self:createUseButtonByIndex(3)
	end
end

function M:onEnterTransitionFinish()
	Touch:registerTouchOneByOne(self, true)
	Touch:addKeyboardTouch(self)
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:_createBackButton()
    local button = CommonUI:createTextButton(self, __Localized("返回"), "ui/login/login-button.png")
    self:_updatePosition(button, 0)
    button.onClicked = function()
        self:removeFromParent()
    end
end

function M:_updatePosition(node, index)
	local buttonHeight = Screen.height / (self._buttonNumber + 2) / 2
	node:setPosition(cc.p(Screen.width * 0.5, buttonHeight * (index + 0.5)))
end

function M:onTouchBegan(touch, event)
	return true
end

function M:_setEventHandler()
    Touch:registerTouchOneByOne(self, true)
end

function M:getContentSize()
	return self._contentSize
end

function M:_reloadData()
	local backpackId = self:_getBackpackDataID()
	local backName = BackpackConfigRead:getName(backpackId)
	local backDesc = BackpackConfigRead:getDesc(backpackId)
	self._showNameLabel:setString(backName)
	self._showDescLabel:setString(backDesc)
end

function M:_getBackpackData()
	return BackpackDataManager:getBackpackDataByType(self:_getBackpackDataID())
end

function M:_getBackpackDataID()
	return self._backpackId
end

function M:_isBind()
	local itemType = self:_getBackpackDataID()
	return BackpackConfigRead:isBind(itemType)
end

function M:_createShowLabel()
	self._showNameLabel = CommonUI:createLabel("Test", 26)
	local labelSize = self._showNameLabel:getContentSize()
	self._showNameLabel:setPosition(labelSize.width, self._contentSize.height/2 + labelSize.height)
	self._showNameLabel:setAnchorPoint(0, 0.5)
	self:addChild(self._showNameLabel)

	self._showDescLabel = CommonUI:createLabel("Test", 26)
	self._showDescLabel:setAlignment(0)
	self._showDescLabel:setWidth(Screen.width)
	self._showDescLabel:setPosition(labelSize.width, self._contentSize.height/2 - labelSize.height)
	self._showDescLabel:setAnchorPoint(0, 0.5)
	self:addChild(self._showDescLabel)
end

function M:onTouchCancelled(touch,event)
end

function M:_gainButtonClick()
	local searchGoodsLayer = require("ui.backpack.layer-manager.SearchGoodsLayer").new()
	searchGoodsLayer:reloadByBackpackId(self._backpackId)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(searchGoodsLayer)
	self:removeFromParent()
end
function M:_marketButtonClick()
	local isBind = self:_isBind()
	if isBind then
		AlertView.new(__Localized("当前物品已被绑定，不能投放市场"))
		return
	end
	local marketData = require("ui.market.datas.MarketData"):newMarketDataByBackpackData(self:_getBackpackData())
	local layer = require("ui.market.layers.ConfirmGoodsSetToMarketLayer").new()
	layer:reload(marketData)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(layer)
	self:removeFromParent()
end


function M:_userButtonClick()
	local editGoodsLayer = require("ui.backpack.layer-manager.EditGoodsLayer").new()
	local backpackData = self:_getBackpackData()
	editGoodsLayer:reload(backpackData)
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(editGoodsLayer)
	self:removeFromParent()
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchSlideMoveRight()
    self:removeFromParent()
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
		self:removeFromParent()
    end
end

function M:_createBackpackIcon(backpackId)
    local button = require("ui.backpack.layer-manager.BackpackButton"):newIconButton()
    button:reloadByBackpackId(backpackId)
    self:addChild(button)
    button:setPosition(cc.p(Screen.width / 2, Screen.height * 0.6))
end

function M:_createBackground()
	local backgroundLayer = cc.LayerColor:create(cc.c4b(0, 0, 0, 160))
	self:addChild(backgroundLayer)
	self._contentSize = cc.size(Screen.width, Screen.height)
end

return M