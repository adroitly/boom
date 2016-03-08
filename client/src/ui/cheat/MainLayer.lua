local M = class("ui.cheat.MainLayer", function()
    return cc.Layer:create()
end)

local CheatCommand = {
    kTestSetHero         = "test_set_hero",
    kTestSetSoldier      = "test_set_soldier",
    kTestCreateHero      = "test_create_hero",
    kTestCreateSoldier   = "test_create_soldier",
    kTestCreateItem      = "test_create_item",
    kTestSetItem         = "test_set_item",
    kTestSetUser         = "test_set_user",
    kUserInfo            = "user_info",
    kHeroInfo            = "hero_info"
}

function M:createButton(parent)
    if false == app.openTestFunction then
        return
    end
    local cheatButton = CommonUI:createTextButton(parent, "作弊", "ui/login/login-bt.png")
    Layout:layout(cheatButton, Screen.size, Layout.left_center)
    cheatButton.onClicked = function()
        local layer = M.new()
        parent:addChild(layer)
    end
    return cheatButton
end

function M:ctor()
    self._sendCount = 0

    self:_createBackground()
    self:_createButtons()

    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    for _, command in pairs(CheatCommand) do
        if command == cmd then
            self:_sendCountSub()
            return
        end
    end
end

function M:_createBackground()
    local backgroundLayer = require("ui.common.BackgroundLayer").new(self, "作弊接口")
    backgroundLayer:setBackButtonCallback(function ()
        self:removeFromParent()
    end)
end

function M:_getButtonsConfig()
    return {
        {title = "武将士兵", callback = function()
            self:_createAllHeros()
            self:_createAllSoldiers()
        end},
        {title = "士兵数量+10W", callback = function()
            self:_setAllSoldierCount(100000)
        end},
        {title = "武将等级10", callback = function()
            self:_setAllHerosLevel(10)
        end},
        {title = "所有物品", callback = function()
            self:_createAllGoods()
        end},
        {title = "物品数量+100W", callback = function()
            self:_setAllGoodsCount(1000000)
        end},
        {title = "玩家等级90", callback = function()
            self:_setUserLevel(90)
        end},
    }
end

function M:_createButtons()
    local config = self:_getButtonsConfig()
    for k, btnConfig in ipairs(config) do
        local button = CommonUI:createTextButton(self, btnConfig.title, "ui/login/login-up.png", "ui/login/login-down.png")
        button.onClicked = function()
            if not self:_isSendDone() then
                CommonUI:lightTips("请等待上次设置完成")
                return
            end
            btnConfig.callback()
        end
        local btnSize = button:getContentSize()
        Layout:layout(button, Screen.size, Layout.right_bottom, cc.p(0, btnSize.height * (k - 1)))
    end

    self:_createSetLevelButton()
end

function M:_createSetLevelButton()
    local TextInput = require("ui.common.InputUI")
    local textInput = TextInput.new(30)
    self:addChild(textInput)
    textInput:setAnchorPoint(cc.p(0, 0))
    textInput:setInputMode(cc.EDITBOX_INPUT_MODE_NUMERIC)
    textInput:setPosition(cc.p(0, 30))
    textInput:setPlaceHolder("等级")
    textInput:setTextColor(cc.c4b(255, 255, 255, 255))
    textInput:setMaxLength(4)
    local button = CommonUI:createTextButton(self, "玩家等级", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(button, Screen.size, Layout.left_bottom, cc.p(100, 0))
    button.onClicked = function()
        local lv = tonumber(textInput:getString())
        self:_setUserLevel(lv)
    end
end

function M:_createAllHeros()
    local heroConfig = require("config.HeroConfig")
    for id, values in pairs(heroConfig) do
        self:_sendCountAdd()
        SocketManager:send(CheatCommand.kTestCreateHero, {hero_type = id})
    end
end

function M:_createAllSoldiers()
    local soldierConfig = require("config.SoldierConfig")
    for id, values in pairs(soldierConfig) do
        if id <= 20000 then
            self:_sendCountAdd()
            SocketManager:send(CheatCommand.kTestCreateSoldier, {soldier_type = values.id})
        end

    end
end

function M:_setAllSoldierCount(count)
    local soldiers = PlayerData:getSoldiers()
    for k, soldierData in pairs(soldiers) do
        self:_sendCountAdd()
        local soldierType = soldierData:getSoldierType()
        local soldierNumber = soldierData:getSoldierNumber() + count
        local sendData = {soldier_type = soldierType, soldier_number = soldierNumber}
        SocketManager:send(CheatCommand.kTestSetSoldier, sendData)
    end
end

function M:_setAllHerosLevel(level)
    local heros = PlayerData:getHeros()
    for k, heroData in pairs(heros) do
        self:_sendCountAdd()
        local heroId = heroData:getHeroId()
        local setHeroLevelData = {hero_id = heroId, hero_level = level}
        SocketManager:send(CheatCommand.kTestSetHero, setHeroLevelData)
    end
end

function M:_createAllGoods()
    local backpackConfig = require("config.BackpackConfig")
    for id, values in pairs(backpackConfig) do
        self:_sendCountAdd()
        SocketManager:send(CheatCommand.kTestCreateItem, {item_type = id})
    end
end

function M:_setAllGoodsCount(count)
    local items = PlayerData:getBackpackItemList()
    for _, backpackData in pairs(items) do
        self:_sendCountAdd()
        local itemType = backpackData:getItemType()
        local itemNumber = backpackData:getItemNumber() + count
        local itemData = {item_type = itemType, item_number = itemNumber}
        SocketManager:send(CheatCommand.kTestSetItem, itemData)
    end
end

function M:_setUserLevel(userLevel)
    self:_sendCountAdd()
    SocketManager:send(CheatCommand.kTestSetUser, {level = userLevel})
end

function M:_isSendDone()
    return self._sendCount <= 0
end

function M:_sendCountAdd()
    self._sendCount = self._sendCount + 1
end

function M:_sendCountSub()
    self._sendCount = self._sendCount - 1
    if self._sendCount <= 0 then
        CommonUI:lightTips("设置完成")
        self._sendCount = 0
    end
end

return M