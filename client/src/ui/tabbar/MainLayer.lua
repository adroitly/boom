local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.tabbar.MainLayer", function()
    return cc.Layer:create()
end)

M.TabbarLayerSize = cc.size(Screen.width, 109)

function M:onEnterInnerCityAction(buildingData)
    local innerLayer = require("ui.city.MainLayer").new(buildingData)
    innerLayer:setTag(Enum.Tag.InnertCityLayer)
    MapManager:getMapMainLayer():addChild(innerLayer)
    self:_homeButtonChange(Enum.HomeButtonFileName.InnertCityLayer)
end

function M:_exitInnerCityAction()
    local innertCityLayer = MapManager:getMapMainLayer():getChildByTag(Enum.Tag.InnertCityLayer)
    innertCityLayer:removeFromParent()
    self:_homeButtonChange(Enum.HomeButtonFileName.MapLayer)
end

function M:ctor()
    self:_changeViewToHomeCoor()
    self:_createBackground()
    self:_createHomeButton()
    self:_createMailButton()
    self:_createBackpackButton()
    self:_createGuildButton()
    if app.openTestFunction then
        require("ui.cheat.MainLayer"):createButton(self)
    end
    require("ui.tabbar.TeamButtonLayer"):createLayer(self)
end

function M:_homeButtonChange(imageFile)
     self._homeButton:changeNormalSprite(imageFile)
end

function M:_createGuildButton()
    local button = Button.new("ui/main-page/main-button03.png")
    self:addChild(button)
    Layout:layout(button, Screen.size, Layout.center_bottom, cc.p(-button:getContentSize().width * 2, 0))
    button.onClicked = function()
        local layer = require("ui.guild.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createMailButton()
    local mailButton = Button.new("ui/main-page/main-button06.png")
    self:addChild(mailButton)
    Layout:layout(mailButton, Screen.size, Layout.center_bottom, cc.p(-mailButton:getContentSize().width, 0))
    mailButton.onClicked = function()
        local mailLayer = require("ui.mail.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(mailLayer)
    end

    local buttonSize = mailButton:getContentSize()
    local TipsManager = require("ui.tips.TipsManager")
    TipsManager:addTipsListener(Enum.TipsType.Email, mailButton, cc.p(buttonSize.width - 20, buttonSize.height - 20))
end

function M:_createBackpackButton()
    local backpackButton = Button.new("ui/main-page/main-button05.png")
    self:addChild(backpackButton)
    Layout:layout(backpackButton, Screen.size, Layout.center_bottom, cc.p(backpackButton:getContentSize().width, 0))
    backpackButton.onClicked = function()
        local mailLayer = require("ui.backpack.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(mailLayer)
    end
end

function M:_createBackground()
    local downBackground = cc.Sprite:create("ui/main-page/bg-maintop.png")
    self:addChild(downBackground)
    self:setLocalZOrder(1)
    Layout:layout(downBackground, Screen.size, Layout.left_bottom)
end

function M:_changeViewToHomeCoor()
    local mapLayerManager = MapManager:getMapLayerManager()
    local position = MapConfig:getPositionFromCoordinate(PlayerData:getHomeCoor())
    mapLayerManager:changeViewCenterToPosition(position)
end

function M:_createHomeButton()
    -- 返回主城按钮
    self._homeButton = Button.new(Enum.HomeButtonFileName.MapLayer)
    self:addChild(self._homeButton)
    Layout:layout(self._homeButton, Screen.size, Layout.left_bottom)
    self._homeButton.onClicked = function()
        if MapManager:getMapMainLayer():getChildByTag(Enum.Tag.InnertCityLayer) then
            self:_exitInnerCityAction()
        else
            self:_changeViewToHomeCoor()
            self:onEnterInnerCityAction(PlayerData:getCastleBuildingData())
        end
    end
end

return M