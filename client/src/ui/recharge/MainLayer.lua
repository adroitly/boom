local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.recharge.MainLayer", function()
    return cc.Layer:create()
end)

local kInitTbl = {
    {title = "充值", Layer = require("ui.recharge.layer-manager.RechargeLayer")},
    {title = "VIP", Layer = require("ui.recharge.layer-manager.VipRightsLayer")},
    {title = "VIP礼包", Layer = require("ui.recharge.layer-manager.VipGiftsLayer")},
    {title = "商城", Layer = require("ui.recharge.layer-manager.ShopLayer")},
}

function M:ctor()
    self:_createBackground()
    self:_createTitleButtons()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("充值"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTitleButtons()
    local tempSprite = cc.Sprite:create("ui/mail/mail-title-bg.png")
    local tempSize = tempSprite:getContentSize()
    local buttonCount = table.getn(kInitTbl)
    local space = ((Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight) - tempSize.height * buttonCount) / (buttonCount + 1)
    for idx, value in ipairs(kInitTbl) do
        local button = CommonUI:createTextButton(self, value.title, "ui/mail/mail-title-bg.png")
        Layout:layout(button, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + space * idx + tempSize.height * (idx - 1)))
        button.onClicked = function()
            local layer = value.Layer.new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end
    end
    
end

return M