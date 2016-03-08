local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.guild.layer-manager.ResourceHouseLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createBackground()
    self:_createSaveButton()
    self:_createTakeButton()
    self:_createRecordButton()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("仓库"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createSaveButton()
    local button = self:_createButton(__Localized("存入资源"))
    Layout:layout(button, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
    button.onClicked = function()
        local layer = require("ui.guild.layer-manager.ResourceSaveLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
    end
end

function M:_createTakeButton()
    local button = self:_createButton(__Localized("取出资源"))
    Layout:layout(button, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + button:getContentSize().height))
    button.onClicked = function()
        local layer = require("ui.guild.layer-manager.ResourceTakeLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createRecordButton()
    local button = self:_createButton(__Localized("存取记录"))
    Layout:layout(button, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + button:getContentSize().height * 2))
    button.onClicked = function()
        local layer = require("ui.guild.layer-manager.ResourceRecordLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
    end
end

function M:_createButton(title)
    local button = CommonUI:createTextButton(self, title, "ui/team/ui-un-0012a.png")
    button:setSystemFontSize(40)
    return button
end


return M