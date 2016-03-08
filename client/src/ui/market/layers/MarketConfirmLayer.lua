local M = class("ui.market.layers.MarketConfirmLayer", function()
	return cc.Layer:create()
end)

function M:createBuyConfirmLayer(func)
	local layer = M.new(func)
	layer:_init(__Localized("购买确认"))
	layer:_createSellUserName()
	layer._confirmButton:setLabel("购 买")
	return layer
end

function M:createSellConfirmLayer(func)
	local layer = M.new(func)
	layer:_init(__Localized("出售确认"))
	layer:_createBuyTipsLabel()
	layer._confirmButton:setLabel("出 售")
	return layer
end

function M:reload(marketData)
	self._marketData = marketData
	self:_reloadLables()
	self._goodsIcon:reloadByResoure(marketData:getResourceId(), marketData:getItemId(), marketData:getNumber(), marketData:getLevel())
end

function M:ctor(func)
	self._confirmFunc = func
	Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    require("ui.common.TouchSlideNode").new(self)
    Touch:addKeyboardTouch(self)
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
		self:removeFromParent()
    end
end

function M:onTouchSlideMoveRight()
    self:removeFromParent()
end

function M:_reloadLables()
	if self._userNameLabel then
		self._userNameLabel:setString(self:_getUserName())
	end
	self._priceLabel:setString(string.format(__Localized("单 价 : %d元宝"), self:_getPrice()))
	self._numberLabel:setString(string.format(__Localized("数 量 : %d"), self:_getNumber()))
	self._costLabel:setString(string.format(__Localized("总 价 : %d元宝"), self:_getCost()))
end

function M:onTouchBegan()
	return true
end

function M:_init(titlename)
	self:_createColorBackground()
	self:_createBackground()
	self:_registerScriptHandler()
	self:_createGoodIcon()
	self:_createPriceLabel()
	self:_createNumberLabel()
	self:_createCostLabel()
	self:_createTitleLabel(titlename)
	self:_createComfirmButton()
	self:_createCancelButton()
end

function M:_createSellUserName()
	self._userNameLabel = CommonUI:createLabel("我的名字六个字", 24)
	local goodsX , goodsY = self._goodsIcon:getPosition()
	local iconSize = self._goodsIcon:getContentSize()
	self._userNameLabel:setPosition(cc.p(Screen.width / 2, goodsY + iconSize.height))
	self:addChild(self._userNameLabel)
end

function M:_createBuyTipsLabel()
	local label = CommonUI:createLabel(__Localized("成功出售后，系统会收取出售总价的%5为手续费"), 24)
	local goodsX , goodsY = self._goodsIcon:getPosition()
	local iconSize = self._goodsIcon:getContentSize()
	label:setPosition(cc.p(Screen.width / 2, goodsY - iconSize.height * 2))
	self:addChild(label)
end

function M:_createComfirmButton()
	self._confirmButton = CommonUI:createTextButton(self, __Localized("确定"), "ui/login/login-button.png")
	self._confirmButton:setPosition(cc.p(Screen.width * 0.75, Screen.height / 4))
	self._confirmButton.onClicked = function()
		if self._confirmFunc then
			self._confirmFunc()
		end
		self:removeFromParent()
	end
end

function M:_createCancelButton()
	local button = CommonUI:createTextButton(self, __Localized("取 消"), "ui/login/login-button.png")
	button:setPosition(cc.p(Screen.width * 0.25, Screen.height / 4))
	button.onClicked = function()
		self:removeFromParent()
	end
end

function M:_createPriceLabel()
	self._priceLabel = CommonUI:createLabel(__Localized("单价:"), 24)
	self:addChild(self._priceLabel)
	self._priceLabel:setAnchorPoint(cc.p(0,0))
	self._priceLabel:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
end

function M:_createNumberLabel()
	self._numberLabel = CommonUI:createLabel(__Localized("数量:") , 24)
	self._numberLabel:setAnchorPoint(cc.p(0,1))
	self._numberLabel:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
	self:addChild(self._numberLabel)
end

function M:_createCostLabel()
	self._costLabel = CommonUI:createLabel(__Localized("总价:") , 30)
	local iconSize = self._goodsIcon:getContentSize()
	self._costLabel:setPosition(cc.p(Screen.width / 2, Screen.height / 2 - iconSize.height))
	self:addChild(self._costLabel)
end

function M:_createGoodIcon()
	self._goodsIcon = require("ui.backpack.layer-manager.ItemIconButton").new()
	self._goodsIcon:setPosition(cc.p(Screen.width / 4, Screen.height / 2))
	self:addChild(self._goodsIcon)
end

function M:_createTitleLabel(titlename)
	self._titleLabel = CommonUI:createLabel(titlename)
	self:addChild(self._titleLabel)
	self._titleLabel:setPosition(cc.p(Screen.width / 2, Screen.height * 0.75))
end
function M:_createColorBackground()
	local background = cc.LayerColor:create(cc.c4b(0, 0, 0, 160))
	self:addChild(background)
end
function M:_createBackground()
	local backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	backgroundSprite:setScaleY(3.5)
	local backSpriteSize = backgroundSprite:getContentSize()
	backgroundSprite:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
	self:addChild(backgroundSprite)
end

function M:_registerScriptHandler()
	Touch:registerTouchOneByOne(self, true)
end
function M:_getUserName()
	return self._marketData:getNickName()
end

function M:_getPrice()
	return self._marketData:getPrice()
end

function M:_getNumber()
	return self._marketData:getNumber()
end

function M:_getCost()
	return self:_getPrice() * self:_getNumber()
end

return M