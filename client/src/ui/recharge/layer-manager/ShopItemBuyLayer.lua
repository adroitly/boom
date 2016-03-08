local ShopConfigReader = require("ui.recharge.data-manager.ShopConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.recharge.layer-manager.ShopItemBuyLayer", function()
    return cc.Layer:create()
end)

local kShopExchange = "shop_exchange"

function M:ctor(id)
    self._buyId = id
    self:_createBackground()
    self:_createInfoLabels()
    self:_createSlider()
    self:_createModifyButtons()
    self:_createBuyButton()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if "exit" == event then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kShopExchange then
        if not CommonUI:errorAlertView(msgTable.code) then
            self:removeFromParent()
            return
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("商城"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createBuyButton()
    local button = CommonUI:createTextButton(self, "购买", "ui/login/login-up.png", "ui/login/login-down.png")
    button.onClicked = function()
        AlertView.new(__Localized("你确定要购买吗？"), __Localized("取 消"), __Localized("购 买"))
        .onClicked = function(index)
            if 1==index then 
                SocketManager:send(kShopExchange, {id = self._buyId, count = self._selectedCount})    
            end
        end
    end
    Layout:layout(button, Screen.size, Layout.center, cc.p(0, 100))
end

function M:_createInfoLabels()
    local nameStr = ShopConfigReader:getName(self._buyId)
    self._nameLabel = CommonUI:createLabel(nameStr, 36)
    self:addChild(self._nameLabel)
    Layout:layout(self._nameLabel, Screen.size, Layout.center, cc.p(0, -150))

    local descStr = ShopConfigReader:getDesc(self._buyId)
    self._descLabel = CommonUI:createLabel(descStr, 30)
    self:addChild(self._descLabel)
    Layout:layout(self._descLabel, Screen.size, Layout.center, cc.p(0, -100))

    self._tipsLabel = CommonUI:createLabel("asjdaisjdlkas", 30)
    self:addChild(self._tipsLabel)
    Layout:layout(self._tipsLabel, Screen.size, Layout.center, cc.p(0, -50))

    self._buyCountLabel = CommonUI:createLabel("90", 30)
    self:addChild(self._buyCountLabel)
    Layout:layout(self._buyCountLabel, Screen.size, Layout.center, cc.p(-300, 0))
end

function M:_createSlider()
    self._slider = cc.ControlSlider:create("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
    self._slider:setMinimumValue(1)
    self._slider:setMaximumValue(99)
    self:addChild(self._slider)
    Layout:layout(self._slider, Screen.size, Layout.center)
    self._slider:registerControlEventHandler(function(sender)
        self:_sliderValueChanged(sender)
    end, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
    self._slider:setValue(1)
end

function M:_sliderValueChanged(sender)
    if not sender then
        return
    end
    -- 四舍五入取整
    local senderValue = sender:getValue()
    local value = math.floor(senderValue + 0.5)
    if senderValue ~= value then
        sender:setValue(value)
    else
        self:_updateSelectedInfo(senderValue)
    end
end

function M:_updateSelectedInfo(value)
    self._selectedCount = value
    local priceType, price = ShopConfigReader:getPrice(self._buyId)
    local priceTypeName = BackpackConfigRead:getName(priceType)
    price = price * value
    local str = string.format("主公，您确定花费%d%s购买该物品吗？", price, priceTypeName)
    self._tipsLabel:setString(str)
    self._buyCountLabel:setString(tostring(value))
end

function M:_createModifyButtons()
    local sliderPosX, sliderPosY = self._slider:getPosition()
    local sliderSize = self._slider:getContentSize()
    local addButton = CommonUI:createTextButton(self, "", "ui/team/button-add.png")
    addButton:setPosition(cc.p(sliderPosX + sliderSize.width * 0.5 + 100, sliderPosY))
    addButton.onClicked = function()
        local value = self._slider:getValue()
        self._slider:setValue(value + 1)
    end
    addButton.onLongTouch = function()
        addButton.onClicked()
    end

    local subButton = CommonUI:createTextButton(self, "", "ui/team/button-sub.png")
    subButton:setPosition(cc.p(sliderPosX - sliderSize.width * 0.5 - 100, sliderPosY))
    subButton.onClicked = function()
        local value = self._slider:getValue()
        if value <= 1 then
            return
        end
        self._slider:setValue(value - 1)
    end
    subButton.onLongTouch = function()
        subButton.onClicked()
    end
    return addButton, subButton
end

return M