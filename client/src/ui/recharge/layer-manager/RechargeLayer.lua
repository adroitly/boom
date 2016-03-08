local BackgroundLayer = require("ui.common.BackgroundLayer")
local RechargeConfig = require("config.RechargeConfig")
local RechargeConfigReader = require("ui.recharge.data-manager.RechargeConfigReader")
local RechargeItemCell = require("ui.recharge.layer-manager.RechargeItemCell")
local M = class("ui.recharge.layer-manager.RechargeLayer", function()
    return cc.Layer:create()
end)

local kTestRecharge = "test_recharge"

function M:ctor()
    self:_initDataList()

    self:_createBackground()
    self:_createGridView()

    Event:registerNodeEvent(self)

    SocketManager:addObserver(self)
    Listener:addListener(self)
end
function M:onExit()
    Listener:removeListener(self)
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kTestRecharge then
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips("充值成功")
        end
    end
end

function M:_initDataList()
    self._rechargeDataList = {}
    for _, config in ipairs(RechargeConfig) do
        table.insert(self._rechargeDataList, config.id)
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("充值"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createGridView()
    local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight)
    local gridView = GridView.new(viewSize, self, 4)
    self:addChild(gridView)
end

function M:onGridViewCellCount()
    return table.getn(self._rechargeDataList)
end

function M:onGridViewLineHeight()
    return RechargeItemCell.RechargeItemCellSize.height
end

function M:onGridViewCellTouched(gridView, idx)
    AlertView.new(__Localized("你确定要购买吗？"), __Localized("取 消"), __Localized("购 买"))
    .onClicked = function(index)
        if 1==index then 
            local id = self._rechargeDataList[idx + 1]
            self:_sendPayRequest(id)
        end
    end
end

function M:_sendPayRequest(id)
    local price = RechargeConfigReader:getPrice(id)
    local pageInfo = {
        price = price,
        productId = id,
        userId = PlayerData:getPlayerId(),
        userName = PlayerData:getNickname(),
        serverId = 0,
    }
    c_BridgeSDK:pay(pageInfo)

    SocketManager:send(kTestRecharge, {id = id})
end

function M:onGridViewCellAtIndex(pageView, idx)
    local cell = pageView:dequeueCell()
    if nil == cell then
        cell = RechargeItemCell.new()
    end
    cell:reset(self._rechargeDataList[idx + 1])
    return cell
end

function M:onListenSDKDidPaySuccess()
    CommonUI:lightTips("支付成功")
    print("=======pay suc")
end

function M:onListenSDKDidPayFailed()
    CommonUI:lightTips("支付失败")
    print("=======pay fail")
end

function M:onListenSDKDidPayCancel()
    CommonUI:lightTips("支付取消")
    print("=======pay cancel")
end


return M