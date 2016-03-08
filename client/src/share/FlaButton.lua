-- local AudioUtils = require("share.AudioUtils")
local GLProgram = require("libs.widget.GLProgram")
local SharedScheduler = cc.Director:getInstance():getScheduler()  

local M = class("share.FlaButton", function(normalName, highligtedName, disabledName)
    return cc.ControlButton:create()
end)

function M:_getScale9SpriteWithName(fileName)
    assert(fileName)
    return  ccui.Scale9Sprite:create(fileName)
end

-- 设置normal状态下的精灵
function M:setNormalSprite(normalName)
    local normalSprite = self:_getScale9SpriteWithName(normalName)
    normalSprite:setScale9Enabled(false)

    self:setPreferredSize(normalSprite:getContentSize())
    self:setBackgroundSpriteForState(normalSprite, cc.CONTROL_STATE_NORMAL)

    return normalSprite
end

-- 包含变量
-- hasHighligtedImage, 按钮是否有高亮图片
-- noramlGLProgramState,   按钮普通状态下的glprogram
-- onClicked 外部设置的回调函数
-- onLongTouch 外部长按回调函数
function M:ctor(normalName, highligtedName, disabledName)
    -- self.audioResourcePath = "res/music/button.mp3" -- 默认按钮声音

    local normalSprite = self:setNormalSprite(normalName)
    self._disabledName = disabledName

    if disabledName then
        local highligtedSprite = self:_getScale9SpriteWithName(disabledName)
        self:setBackgroundSpriteForState(highligtedSprite, cc.CONTROL_STATE_DISABLED)
        self.hasDisabledImage = true
    end

    if highligtedName then
        local highligtedSprite = self:_getScale9SpriteWithName(highligtedName)
        self:setBackgroundSpriteForState(highligtedSprite, cc.CONTROL_STATE_HIGH_LIGHTED)
        self.hasHighligtedImage = true
    end
    self.noramlGLProgramState = normalSprite:getSprite():getGLProgramState()
    self:setupEventHandler()
end

function M:create(normalName, highligtedName)
    return M.new(normalName, highligtedName)
end

function M:setHighlighted(highlight)
    cc.Control.setHighlighted(self, highlight)

    if self.hasHighligtedImage then
        return
    end

    local normalSprite = self:getBackgroundSpriteForState(cc.CONTROL_STATE_NORMAL)
    local sprite = normalSprite:getSprite()

    local glState = highlight and GLProgram:getHighlightButtonState() or self.noramlGLProgramState
    sprite:setGLProgramState(glState)
    Function:safeCall(self, "onHighlighted", glState, highlight)
end

function M:hitTest(touch)
    return Touch:isTouchHitted(self, touch)
end

function M:onTouchBegan(touch, event)
    self._isLongTouch = false

    local hidden = Node:findParent(self, function(parent)
        return not parent:isVisible()
    end, true)

    if hidden == nil and self:hitTest(touch) then
        if self:isEnabled() then
            self:setHighlighted(true)
            -- if self.audioResourcePath ~= nil then 
            --     AudioUtils.playEffect(self.audioResourcePath)
            -- end
            if self.onLongTouch then
                self:_checkLongTouch()
                self._touchIng = true
            end
        end
        return true
    end
    return false
end

function M:onTouchMoved(touch,event)
    if not self:isEnabled() then
        return
    end

    local hitTest = self:hitTest(touch)
    local isHighlited = self:isHighlighted()
    if hitTest ~= isHighlited then
        self:setHighlighted(hitTest)
    end
end


function M:onTouchEnded(touch,event)
    if not self:isEnabled() then
        return
    end
    self:setHighlighted(false)
    if self:isEnabled() and self:hitTest(touch) then
        if self.onClicked and false == self._isLongTouch then
            self:onClicked(self)
        end
    end
    self._touchIng = false
    if nil ~= self._handle then
        SharedScheduler:unscheduleScriptEntry(self._handle)
    end
end

function M:onTouchCancelled(touch,event)
    self:setHighlighted(false)
end

function M:_checkLongTouch()
    local handler
    -- 定时器缓冲
    handler = SharedScheduler:scheduleScriptFunc(function()
        SharedScheduler:unscheduleScriptEntry(handler)
        if self._touchIng then
            self:_startHandle()
        end
    end, 1, false)

end

function M:_startHandle()
    if nil ~= self._handle then
        SharedScheduler:unscheduleScriptEntry(self._handle)
    end
    -- 创建一个定时器，每隔0.1秒钟时运行
    self._handle = SharedScheduler:scheduleScriptFunc(function(time)
        self:onLongTouch()
        self._isLongTouch = true
    end,0.1,false)
end

function M:_registerScriptHandler()
    self:registerScriptHandler(function(event)
        if "exit" == event then
            if nil ~= self._handle then
                SharedScheduler:unscheduleScriptEntry(self._handle)
            end
        end
    end)
end

function M:setupEventHandler()
    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    dispatcher:removeEventListenersForTarget(self)

    Touch:registerTouchOneByOne(self, true)
    self:_registerScriptHandler()
end

function M:setEnabled(enabled, disColor)
    local normalSprite = self:getBackgroundSpriteForState(cc.CONTROL_STATE_NORMAL)
    local sprite = normalSprite:getSprite()
    local glState = enabled and self.noramlGLProgramState or GLProgram:getGray()
    sprite:setGLProgramState(glState)
    cc.Control.setEnabled(self, enabled)
end

function M:setScale9ContentSize(size)
    local sprite = self:getBackgroundSpriteForState(cc.CONTROL_STATE_NORMAL) 
    sprite:setScale9Enabled(true)
    self:setPreferredSize(size) 
end

return M

