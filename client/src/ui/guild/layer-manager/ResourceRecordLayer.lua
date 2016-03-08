local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.guild.layer-manager.ResourceRecordLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createBackground()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "存取记录")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

return M