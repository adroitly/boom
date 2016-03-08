local M = class("ui.common.BackgroundLayer" , function()
	return cc.Layer:create()
end)

M.TitleHeight = 115
M.BottomHeight = 100
M.ReturnType =
{
    Button = 1,
    Keyboard = 2,
    TouchMove = 3,
}
function M:getTitleSize()
	return self._titleSize
end
-- 设置回调，回调包含一个回调类型
function M:setBackButtonCallback(callback)
	self._backCallback = callback
end

function M:ctor(parent, titlename)
	self:_createBackground()
	self:_createBackButton(parent)
	self:_createTitle(titlename)
	parent:addChild(self)
    self._touchSlide = require("ui.common.TouchSlideNode").new(self)
    Event:registerNodeEvent(self)
end

function M:removeTouchSlideNode()
    if self._touchSlide then
        self._touchSlide:removeFromParent()
        self._touchSlide = nil
    end
end

function M:onEnterTransitionFinish()
    Touch:registerTouchOneByOne(self, true)
    Touch:addKeyboardTouch(self)
end

function M:onExit()
    Touch:removeTouchOneByOne(self)
    Touch:removeKeyboardTouch(self)
end

function M:reloadLayer(titlename)
	self._titleLabel:setString(titlename)
end

function M:onKeyReleased(keyCode, event)
    if false == require("ui.common.LoadingLayer"):isHide() then
        return
    end
    if keyCode == cc.KeyCode.KEY_BACK then
        if self._backCallback then
            self._backCallback(M.ReturnType.Keyboard)
        end
    end
end

function M:onTouchSlideMoveRight()
    if false == require("ui.common.LoadingLayer"):isHide() then
        return
    end
    if self._backCallback then
        self._backCallback(M.ReturnType.TouchMove)
    end
end

function M:onTouchBegan(touch, event)
	return true
end

function M:_createBackground()
	local factor = cc.Director:getInstance():getContentScaleFactor()
	local backSprite = cc.Sprite:create("ui/common/BackgroundLayer.png")
	local backSpriteSize = backSprite:getContentSize()
	backSprite:setPosition(Screen.width / 2 , Screen.height / 2)
	self:addChild(backSprite)
end

function M:_createTitle(titlename)
	self._titleLabel =  CommonUI:createLabel(titlename , 40)
	local titleSprite = cc.Sprite:create("ui/team/ui-un-0003.png")
	local spriteSize = titleSprite:getContentSize()
	self._titleSize = spriteSize
	titleSprite:setPosition(Screen.width / 2 , Screen.height - spriteSize.height / 2)
	titleSprite:addChild(self._titleLabel)
	Layout:layout(self._titleLabel, spriteSize, Layout.center)
	self:addChild(titleSprite)
end

function M:_createBackButton(parent)
	local backButton = Button.new("ui/common/button-back.png")
	local backButtonSize = backButton:getContentSize()
	backButton:setPosition(cc.p(backButtonSize.width / 2 + 10, Screen.height - M.TitleHeight / 2))
	parent:addChild(backButton)
	backButton.onClicked = function()
		if self._backCallback then
			self._backCallback(M.ReturnType.Button)
		end
	end
	backButton:setLocalZOrder(1)
end

return M