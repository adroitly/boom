local BackgroundLayer = require("ui.common.BackgroundLayer")
local ProduceResourceNode = require("ui.produce.layer-manager.ProduceResourceNode")
local CastleConfigReader = require("ui.city.king.CastleConfigReader")
local OccupiedBuildingView = require("ui.produce.layer-manager.OccupiedBuildingView")
local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local M = class("ui.produce.layer-manager.ProduceResourcesLayer", function ()
    return cc.Layer:create()
end)

local kCastleProductItem = "castle_product_item"
local kCastleProductItemReceive = "castle_product_item_receive"
local kCastleProductItemInfo = "castle_product_item_info"
local kServiceUse = "service_use"

function M:ctor()
    self:_createBackground()
    self:_createSpeedUpButton()
    self:_createOneKeyButton()
    self:_checkFinishList()
    self:setTag(Enum.LayerTag.ProduceResources)
    
    SocketManager:addObserver(self)
    Event:registerNodeEvent(self)
end

function M:onExit()
    TimerInterval:removeTimer(self)
    SocketManager:removeObserver(self)
    Listener:removeListener(self)
end

function M:onEnterTransitionFinish()
    Listener:addListener(self)
    CommonUI:showLoadingLayer(true)
    ProduceBuildingDataManager:getProduceBuildingInfo()
end

function M:onProduceResourceReceived(msgTable)
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
        [kCastleProductItem] = function()
            CommonUI:showLoadingLayer(false)
            if not CommonUI:errorAlertView(msgTable.code) then
                CommonUI:lightTipsFormat("开始生产")
                self._occupiedBuildingView:updateView()
                self:_checkTotalSpeedUpState()
            end
        end,
        [kServiceUse] = function()
            CommonUI:showLoadingLayer(false)
            if not CommonUI:errorAlertView(msgTable.code) then
                CommonUI:lightTipsFormat("成功开启加速服务")
                self._occupiedBuildingView:updateView()
                self:_checkTotalSpeedUpState()
            end
        end,
    }

    Function:safeCall(cmdTable, cmd)
end

function M:_checkTotalSpeedUpState()
    local isUsed = ProduceBuildingDataManager:isTotalProduceResourceSpeedUpUsed()
    self._speedUpButton:setEnabled(not isUsed)
end

function M:_createOccupiedBuildingView()
    local height = Screen.size.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight
    self._occupiedBuildingView = OccupiedBuildingView.new(cc.size(Screen.width, height), Enum.ProduceType.Resource)
    self._occupiedBuildingView:setPosition(cc.p(0, Screen.height - height - BackgroundLayer.TitleHeight))
    self:addChild(self._occupiedBuildingView)
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "生产")
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createSpeedUpButton()
    self._speedUpButton = CommonUI:createTextButton(self, "全体加速", "ui/login/login-up.png")
    Layout:layout(self._speedUpButton, Screen.size, Layout.center_bottom, cc.p(100, 0))
    self._speedUpButton.onClicked = function()
        local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
        local onePayTbl = PayRatioConfigReader:getTotalProduceResourceSpeedUpPay()
        local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
        local name = BackpackConfigRead:getName(onePayTbl.id)
        local str = string.format(__Localized("您是否花费%d%s开启全体资源生产队列加速50%%服务?"), onePayTbl.count, name)
        AlertView.new(str, __Localized("取 消"), __Localized("确 定"))
        .onClicked = function(index)
            if 1==index then
                CommonUI:showLoadingLayer(true)
                local serviceType = Enum.SpeedUpType.TotalProduceResource
                SocketManager:send(kServiceUse, {service_type = serviceType})
            end
        end
    end
end

function M:_createOneKeyButton()
    self._oneKeyButton = CommonUI:createTextButton(self, "一键完成", "ui/login/login-up.png")
    Layout:layout(self._oneKeyButton, Screen.size, Layout.center_bottom, cc.p(-100, 0))
    self._oneKeyButton.onClicked = function()
        self._oneKeyButton:setEnabled(false)
        local isDone = ProduceBuildingDataManager:sendAllProduceResourcesReceived()
        if not isDone then
            CommonUI:lightTips(__Localized("您的资源已达上限，请提升等级"))
        end
    end
    self._oneKeyButton:setEnabled(false)
end

function M:_produceDoneRequest(resourceData)
    local BackpackDataManager = require("player-data.BackpackDataManager")
    local itemType = resourceData:getItemType()
    local backpackData = BackpackDataManager:getBackpackDataByType(itemType)
    local itemNumber = 0
    if backpackData then
        itemNumber = backpackData:getItemNumber()
    end
    local CastleConfigReader = require("ui.city.king.CastleConfigReader")
    local limit = CastleConfigReader:getStorageConfine(PlayerData:getCastleLevel())
    if itemNumber >= limit then
        return false
    end
    local resourceId = resourceData:getId()
    SocketManager:send(kCastleProductItemReceive, {id = resourceId})
    return true
end

function M:_getFinishProduceList()
    return ProduceBuildingDataManager:getFinishProduceResourcesList()
end

function M:_checkFinishList()
    TimerInterval:addTimer(self, 2)
end

function M:onUpdate()
    local list = self:_getFinishProduceList()
    self._oneKeyButton:setEnabled(table.getn(list) > 0)
end

return M