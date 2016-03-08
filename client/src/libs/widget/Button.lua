--[[
    * 描述：统一按钮入口
    * 参数normalImageName：文件名
    * 参数：highligtedImageName和disabledImageName可以为空，为空时使用normalImageName加shader方式表现高亮和灰色
    * 点击事件：onClicked(button)
--]]
local GLProgram = require("libs.widget.GLProgram")
local M = class("libs.widget.Button", function(normalImageName, highligtedImageName, disabledImageName)
	return cc.ControlButton:create()
end)

function M:ctor(normalImageName, highligtedImageName, disabledImageName)
    if normalImageName then
        self:changeNormalSprite(normalImageName, highligtedImageName, disabledImageName)
    end
    
    self:registerControlEventHandler(function()
        if self.onClicked then
            self.onClicked(self)
        end
    end, cc.CONTROL_EVENTTYPE_TOUCH_UP_INSIDE)
end

function M:setContentSize(size)
    local sprite = self:getBackgroundSpriteForState(cc.CONTROL_STATE_NORMAL) 
    sprite:setScale9Enabled(true)
    self:setPreferredSize(size) 
end

function M:changeNormalSprite(normalImageName, highligtedImageName, disabledImageName)
    assert(normalImageName)
    local normalSprite = ccui.Scale9Sprite:create(normalImageName)
    self:_setNormalSprite(normalSprite)
    
    local highlightImage = highligtedImageName and highligtedImageName or normalImageName
    local highlightSprite = ccui.Scale9Sprite:create(highlightImage)
    self:_setHighlightedSprite(highlightSprite, nil==highligtedImageName)

    local disabledImage = disabledImageName and disabledImageName or normalImageName
    local disabledSprite = ccui.Scale9Sprite:create(disabledImage)
    self:_setDisalbeSprite(disabledSprite, nil==disabledImageName)
end

function M:changeNormalSpriteWithFrame(normalSpriteFrame, highlightdSpriteFrame, disableSpriteFrame)
    assert(normalSpriteFrame)
    local normalSprite = ccui.Scale9Sprite:createWithSpriteFrame(normalSpriteFrame)
    self:_setNormalSprite(normalSprite)

    local highlightImage = highlightdSpriteFrame and highlightdSpriteFrame or normalSpriteFrame
    local highlightSprite = ccui.Scale9Sprite:createWithSpriteFrame(highlightImage)
    self:_setHighlightedSprite(highlightSprite, nil==highlightdSpriteFrame)

    local disabledImage = disableSpriteFrame and disableSpriteFrame or normalSpriteFrame
    local disabledSprite = ccui.Scale9Sprite:createWithSpriteFrame(disabledImage)
    self:_setDisalbeSprite(disabledSprite, nil==disableSpriteFrame)
end

--[[
    * 描述：触发点击事件后是否截住事件，true事件不会往下传递，false事件往下传递
           主要用于滚动视图，点击按钮后还可以拖动视图
--]]
function M:setSwallowTouches(enable)
    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    dispatcher:removeEventListenersForTarget(self)
    self._isHightlight = false 
    Touch:registerTouchOneByOne(self, enable)
end

-------------------------------- 接口分割线 --------------------------------

function M:_setNormalSprite(normalSprite)
    normalSprite:setScale9Enabled(false)
    self:setPreferredSize(normalSprite:getContentSize())
    self:setBackgroundSpriteForState(normalSprite, cc.CONTROL_STATE_NORMAL)
end

function M:_setHighlightedSprite(highlightSprite, useGLProgram)
    self:setBackgroundSpriteForState(highlightSprite, cc.CONTROL_STATE_HIGH_LIGHTED)
    if useGLProgram then 
        highlightSprite:setScale9Enabled(false)
        highlightSprite:getSprite():setGLProgramState(GLProgram:getHighlightButtonState())
    end
end

function M:_setDisalbeSprite(disabledSprite, useGLProgram)
    self:setBackgroundSpriteForState(disabledSprite, cc.CONTROL_STATE_DISABLED)
    if useGLProgram then 
        disabledSprite:setScale9Enabled(false)
        disabledSprite:getSprite():setGLProgramState(GLProgram:getGray())
    end
end

function M:onTouchBegan(touch, event)
    local hidden = Node:findParent(self, function(parent)
        return not parent:isVisible()
    end, true)

    if hidden then 
        return false
    end

    if not self:isEnabled() then 
        return false
    end

    if Touch:isTouchHitted(self, touch) then 
        self._isHightlight = true 
        self:setHighlighted(true)
        return true
    end

    return false
end

function M:onTouchMoved(touch, event)
    local hitTest = Touch:isTouchHitted(self, touch)
    if hitTest ~= self._isHightlight then
        self._isHightlight = hitTest
        self:setHighlighted(hitTest)
    end
end 

function M:onTouchEnded(touch, event)
    self._isHightlight = false
    self:setHighlighted(false)
    if Touch:isTouchHitted(self, touch) then
        if self.onClicked then
            self.onClicked(self)
        end
    end
end

function M:onTouchCancelled(touch, event)
    self:onTouchEnded(touch, event)
end

return M


