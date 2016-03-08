local BackgroundLayer = require("ui.common.BackgroundLayer")
local ShopConfig = require("config.ShopConfig")
local ShopItemCell = require("ui.recharge.layer-manager.ShopItemCell")
local M = class("ui.recharge.layer-manager.ShopLayer", function()
    return cc.Layer:create()
end)

local kShopExchange = "shop_exchange"

function M:ctor()
    self:_initDataList()

    self:_createBackground()
    self:_createMyGoldLabel()
    self:_createGridView()

    SocketManager:addObserver(self)
    Listener:addListener(self)
    self:registerScriptHandler(function(event)
        if "exit" == event then
            Listener:removeListener(self)
            SocketManager:removeObserver(self)
        end
    end)
end

function M:onListenBackpackDataChange(backpackType)
    if backpackType == Enum.ResourceType.Gold then
        self:_updateMyGoldInfo()
    end
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kShopExchange then
        if msgTable.code == 0 then
            CommonUI:lightTips(__Localized("购买成功"))
        end
    end
end

function M:_initDataList()
    self._shopDataList = {}
    for _, config in ipairs(ShopConfig) do
        table.insert(self._shopDataList, config.id)
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("商城"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_updateMyGoldInfo()
    local BackpackDataManager = require("player-data.BackpackDataManager")
    local backpackData = BackpackDataManager:getBackpackDataByType(Enum.ResourceType.Gold)
    local goldNumber = 0
    if backpackData then
        goldNumber = backpackData:getItemNumber()
    end
    local goldStr = string.format("我的元宝：%d", goldNumber)
    self._myGoldLabel:setString(goldStr)
    Layout:layout(self._myGoldLabel, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
end

function M:_createMyGoldLabel()
    self._myGoldLabel = CommonUI:createLabel("", 36)
    self:addChild(self._myGoldLabel)
    self:_updateMyGoldInfo()
end

function M:_createGridView()
    local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight - self._myGoldLabel:getContentSize().height)
    local gridView = GridView.new(viewSize, self, 4)
    self:addChild(gridView)
end

function M:onGridViewCellCount()
    return table.getn(self._shopDataList)
end

function M:onGridViewLineHeight()
    return ShopItemCell.ShopItemCellSize.height
end

function M:onGridViewCellTouched(gridView, idx)
    local id = self._shopDataList[idx + 1]
    local buyLayer = require("ui.recharge.layer-manager.ShopItemBuyLayer").new(id)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(buyLayer)
end

function M:onGridViewCellAtIndex(pageView, idx)
    local cell = pageView:dequeueCell()
    if nil == cell then
        cell = ShopItemCell.new()
    end
    cell:reset(self._shopDataList[idx + 1])
    return cell
end



return M