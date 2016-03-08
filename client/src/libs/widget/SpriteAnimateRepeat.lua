--[[
    * 描述：精灵播放类
    * 参数plistPath：碎图纹理plist路径
    * 参数repeatCount：播放repeatCount次后自动删除
]]
local M = class("libs.widget.SpriteAnimateRepeat", function()
    return require("libs.widget.SpriteAnimate").new()
end)

function M:ctor(plistPath, repeatCount)
    assert(plistPath and repeatCount)
    self:init(plistPath)

    self._currentCount = 0
    self._repeatCount = repeatCount
    self:setFinishCallback(function()
        self:_onFinishCallback()
    end)

    self:_startAnimate()
end

function M:_onFinishCallback()
    self._currentCount = self._currentCount + 1
    if self._currentCount >= self._repeatCount then 
        self:_stopAnimate()
        self:removeFromParent() 
    end
end

function M:_startAnimate()
    Timer:addTimer(self)
    Event:registerNodeEvent(self)
end

function M:onUpdate(dt)
    self:update(dt)
end

function M:onExit()
    self:_stopAnimate()
end

function M:_stopAnimate()
    Timer:removeTimer(self)
end

return M 

