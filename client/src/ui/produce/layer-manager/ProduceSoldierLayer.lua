local ProduceSoldierNode = require("ui.produce.layer-manager.ProduceSoldierNode")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local CastleConfigReader = require("ui.city.king.CastleConfigReader")
local ProduceBuildingData = require("ui.produce.data-manager.ProduceBuildingData")
local ProduceSoldierData = require("ui.produce.data-manager.ProduceSoldierData")
local ProduceConfigReader = require("ui.produce.data-manager.ProduceConfigReader")
local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local OccupiedBuildingView = require("ui.produce.layer-manager.OccupiedBuildingView")
local M = class("ui.produce.layer-manager.ProduceSoldierLayer", function ()
    return cc.Layer:create()
end)

local kCastleProductSoldier = "castle_product_soldier"
local kCastleProductSoldierReceive = "castle_product_soldier_receive"
local kCastleProductSoldierGet = "castle_product_soldier_get"
local kCastleProductSoldierInfo = "castle_product_soldier_info"
local kProduceBuildingInfoGet = "produce_building_info_get"
local kServiceUse = "service_use"

function M:ctor()
    self:_createBackground()
    self:_createSpeedUpButton()
    self:_createOneKeyButton()
    self:_checkFinishList()
    self:setTag(Enum.LayerTag.ProduceSoldier)

    Event:registerNodeEvent(self)
end

function M:onExit()
    TimerInterval:removeTimer(self)
    SocketManager:removeObserver(self)
    Listener:removeListener(self)
end

function M:onEnterTransitionFinish()
    SocketManager:addObserver(self)
    Listener:addListener(self)
    CommonUI:showLoadingLayer(true)
    ProduceBuildingDataManager:getProduceBuildingInfo()
end

function M:onProduceSoldierReceived(msgTable)
    CommonUI:showLoadingLayer(false)
    if not CommonUI:errorAlertView(msgTable.code) then
        CommonUI:lightTipsFormat("获取成功")
        self._occupiedBuildingView:updateView()
    end
end

function M:onProduceBuildingInfoGet()
    CommonUI:showLoadingLayer(false)
    self:_createOccupiedBuildingView()
    self:_checkTotalSpeedUpState()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local cmdTable = {
        [kCastleProductSoldier] = function()
            CommonUI:showLoadingLayer(false)
            if not CommonUI:errorAlertView(msgTable.code) then
                CommonUI:lightTipsFormat("开始生产")
                self._occupiedBuildingView:updateView()
            end
            self:_checkTotalSpeedUpState()
        end,
        [kServiceUse] = function()
            CommonUI:showLoadingLayer(false)
            if not CommonUI:errorAlertView(msgTable.code) then
                CommonUI:lightTipsFormat("成功开启加速服务")
                self._occupiedBuildingView:updateView()
            end
            self:_checkTotalSpeedUpState()
        end,
    }
    Function:safeCall(cmdTable, cmd)
end

function M:_checkTotalSpeedUpState()
    local isUsed = ProduceBuildingDataManager:isTotalProduceSoldierSpeedUpUsed()
    self._speedUpButton:setEnabled(not isUsed)
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "征兵")
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createSpeedUpButton()
    self._speedUpButton = CommonUI:createTextButton(self, "全体加速", "ui/login/login-up.png")
    Layout:layout(self._speedUpButton, Screen.size, Layout.center_bottom, cc.p(100, 0))
    self._speedUpButton.onClicked = function()
        local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
        local onePayTbl = PayRatioConfigReader:getTotalProduceSoldierSpeedUpPay()
        local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
        local name = BackpackConfigRead:getName(onePayTbl.id)
        local str = string.format(__Localized("您是否花费%d%s开启全体征兵加速50%%服务?"), onePayTbl.count, name)
        AlertView.new(str, __Localized("取 消"), __Localized("确 定"))
        .onClicked = function(index)
           if 1==index then
                CommonUI:showLoadingLayer(true)
                local serviceType = Enum.SpeedUpType.TotalProduceSoldier
                SocketManager:send(kServiceUse, {service_type = serviceType})
            end 
        end
    end
    self._speedUpButton:setEnabled(false)
end

function M:_createOneKeyButton()
    self._oneKeyButton = CommonUI:createTextButton(self, "一键完成", "ui/login/login-up.png")
    Layout:layout(self._oneKeyButton, Screen.size, Layout.center_bottom, cc.p(-100, 0))
    self._oneKeyButton.onClicked = function()
        self._oneKeyButton:setEnabled(false)
        ProduceBuildingDataManager:sendAllProduceSoldierReceived()
    end
    self._oneKeyButton:setEnabled(false)
end

function M:_getFinishProduceList()
    return ProduceBuildingDataManager:getFinishProduceSoldierList()
end

function M:_checkFinishList()
    TimerInterval:addTimer(self, 2)
end

function M:onUpdate()
    local list = self:_getFinishProduceList()
    self._oneKeyButton:setEnabled(table.getn(list) > 0)
    self:_checkTotalSpeedUpState()
end

function M:_createOccupiedBuildingView()
    local height = Screen.size.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight
    self._occupiedBuildingView = OccupiedBuildingView.new(cc.size(Screen.width, height), Enum.ProduceType.Soldier)
    self._occupiedBuildingView:setPosition(cc.p(0, Screen.height - height - BackgroundLayer.TitleHeight))
    self:addChild(self._occupiedBuildingView)
end

function M:_sendBuildingInfoRequest()
    SocketManager:send(kProduceBuildingInfoGet, {})
end

function M:_sendProduceSoldierInfoRequest()
    SocketManager:send(kCastleProductSoldierGet, {})
end


return M