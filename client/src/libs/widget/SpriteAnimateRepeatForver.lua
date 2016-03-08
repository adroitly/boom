--[[
    * 描述：精灵无限循环播放类
    * 参数plistPath：碎图纹理plist路径
]]
local M = class("libs.widget.SpriteAnimateRepeatForver", function()
    return require("libs.widget.SpriteAnimate").new()
end)

function M:ctor(plistPath)
    assert(plistPath)
    self:init(plistPath)
    self:_startAnimate()
end

function M:_startAnimate()
    Timer:addTimer(self)
    Event:registerNodeEvent(self)
end

function M:onExit()
    self:_stopAnimate()
end

function M:onUpdate(dt)
    self:update(dt)
end

function M:_stopAnimate()
    Timer:removeTimer(self)
end

return M 

