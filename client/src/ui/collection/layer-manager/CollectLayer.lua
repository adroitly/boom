local BackgroundLayer = require("ui.common.BackgroundLayer")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.collection.layer-manager.CollectLayer", function()
    return cc.Layer:create()
end)

local kCollectInfoAdd = "collect_info_add"

function M:ctor(buildingData)
    self._buildingData = buildingData
    self:_createBackground(buildingData)
    self:_createButtonLayer()

    Event:registerNodeEvent(self)
end

function M:onEnter()
    SocketManager:addObserver(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kCollectInfoAdd then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips("添加成功")
        end
    end
end

function M:_createBackground(buildingData)
    local localCoor = self._buildingData:getHomeCoor()
    local twoDCoor = MapConfig:localTo2D(localCoor)
    local titleStr = string.format("收藏坐标：X%d,Y%d", twoDCoor.i, twoDCoor.j)
    local background = BackgroundLayer.new(self, titleStr)
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createButtonLayer()
    local setInfo = {
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "朋友", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "敌人", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "资源", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "标记", 30},
    }
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    local btnSize = tempSprite:getContentSize()
    local buttonSetLayer = ButtonSetLayer.new(setInfo)
    buttonSetLayer:setLayout(cc.size(Screen.width, btnSize.height * 2), buttonSetLayer.FromTopToBottom, 2)
    self:addChild(buttonSetLayer)
    buttonSetLayer:setPosition(cc.p(0, Screen.height - BackgroundLayer.TitleHeight - btnSize.height * 2))
    buttonSetLayer.onClicked = function(sender, index)
        self:_onTagSelected(sender, index)
    end
end

function M:_onTagSelected(sender, index)
    local localCoor = self._buildingData:getHomeCoor()
    local buildingId = self._buildingData:getBuildingId()
    local level = self._buildingData:getLevel()
    local ownerName = self._buildingData:getOwnerName()
    ownerName = ownerName == "" and " " or ownerName
    local twoDCoor = MapConfig:localTo2D(localCoor)
    local CollectConfig = require("ui.collection.data-manager.CollectConfig")
    local collectInfo = CollectConfig:encodeToString(index + 1, ownerName, buildingId, level, twoDCoor)
    SocketManager:send(kCollectInfoAdd, {info = collectInfo})
    CommonUI:showLoadingLayer(true)
end

return M