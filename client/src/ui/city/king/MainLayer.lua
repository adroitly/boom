local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.city.king.MainLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createBackground()
    self:_createRole()
    self:_createButtons()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("君主"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createRole()
    local role = cc.Sprite:create("ui/city/inner-city-heromuseum.png")
    self:addChild(role)
    Layout:layout(role, Screen.size, Layout.center)
end

function M:_createButtons()
    local setInfo = {
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "排行榜", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "主城升级", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "官职", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "国战", 30},
    }
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    local btnSize = tempSprite:getContentSize()
    local buttonSetLayer = ButtonSetLayer.new(setInfo)
    buttonSetLayer:setLayout(cc.size(Screen.width, btnSize.height))
    self:addChild(buttonSetLayer)
    buttonSetLayer:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
    buttonSetLayer.onClicked = function(sender, index)
        self:_onTagSelected(sender, index)
    end

    -- tips
    local TipsManager = require("ui.tips.TipsManager")
    local playerLevelUpButton = buttonSetLayer:getButtonByIndex(3)
    TipsManager:addTipsListener(Enum.TipsType.LevelUp, playerLevelUpButton)
    local cityLevelUpButton = buttonSetLayer:getButtonByIndex(2)
    TipsManager:addTipsListener(Enum.TipsType.CityLevelUp, cityLevelUpButton)
    TipsManager:addTipsListener(Enum.TipsType.PickMoney, playerLevelUpButton)
    
end

function M:_onTagSelected(sender, index)
    local layerList = {
        {Layer = require("ui.rank.MainLayer")},
        {Layer = require("ui.city.king.CastleUpgradeLayer")},
        {Layer = require("ui.user-info.MainLayer")},
        {Layer = require("ui.country-war.MainLayer")}
    }
    local layer = layerList[index + 1].Layer.new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(layer)
end

return M