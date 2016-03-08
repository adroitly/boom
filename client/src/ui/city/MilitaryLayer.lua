local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.city.MilitaryLayer", function()
    return cc.Layer:create()
end)

function M:onListenOpenAlertCoordinate()
    self:removeFromParent()
end

function M:ctor(buildingData)
    self._buildingData = buildingData
    self:_registerScriptHandler()
    self:_createBackground()
    self:_createRole()
    self:_createButtons()
end

function M:_registerScriptHandler()
    self:registerScriptHandler(function(event)
    if event == "exit"then
            Listener:removeListener(self)
        end
    end)
    Listener:addListener(self)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("军事"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createRole()
    local role = cc.Sprite:create("ui/city/inner-city-heromuseum.png")
    self:addChild(role)
    Layout:layout(role, Screen.size, Layout.center)
end

local function _getLayers()
    return {
                nil,
                require("ui.produce.layer-manager.ProduceSoldierLayer"),
                require("ui.outside-search.layers.BuildingGarrisonLayer"),
                require("ui.message-board.layer-manager.MessageBoardLayer"),
            }
end

local function _getButtonsCallbackTable()
    local nomal = "ui/login/login-up.png"
    local high = "ui/login/login-down.png"
    return {
        { nomal, high, high, "情报", },
        { nomal, high, high, "征兵", },
        { nomal, high, high, "驻守", },
        { nomal, high, high, "外交", },
    }
end


function M:_createButtons()
    local buttonsInfo = _getButtonsCallbackTable()
    local layers = _getLayers()
    local buttonSetLayer = ButtonSetLayer.new(buttonsInfo)
    buttonSetLayer:setLayout(cc.size(Screen.width, BackgroundLayer.TitleHeight))
    buttonSetLayer:setPosition(cc.p(0, BackgroundLayer.TitleHeight))
    buttonSetLayer.onClicked = function(node, index)
        index = index + 1
        local childLayer = layers[index]
        if childLayer then
            local layer = childLayer.new(self._buildingData)
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        else
            local mapLayer = MapManager:getMapMainLayer()
            mapLayer:onEnterMoreAlertLayer()
        end
    end
    self:addChild(buttonSetLayer)

    local TipsManager = require("ui.tips.TipsManager")
    local produceButton = buttonSetLayer:getButtonByIndex(2)
    TipsManager:addTipsListener(Enum.TipsType.ProduceSoldier, produceButton)
end

return M