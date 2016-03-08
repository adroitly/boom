
local GuildDataManager = require("player-data.GuildDataManager")
local M = class("ui.guild.layer-manager.GuildCreateLayer", function()
    return cc.Layer:create()
end)

local kGuildCreate = "guild_create"

function M:ctor()
    self:_createBackground()
    self:_createInfoLabel()
    self:_createTextField()
    self:_createButtons()

    SocketManager:addObserver(self)
    Touch:registerTouchOneByOne(self, true)
    Event:registerNodeEvent(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:_createBackground()
    local tempSprite = cc.Sprite:create("ui/team/ui-un-0015.png")
    local tempSize = tempSprite:getContentSize()
    self._background = ccui.Scale9Sprite:create("ui/team/ui-un-0015.png", cc.rect(0, 0, tempSize.width, tempSize.height), cc.rect(20, 20, tempSize.width - 40, tempSize.height - 40))
    self:addChild(self._background)
    self._background:setContentSize(cc.size(Screen.width, 200))
    Layout:layout(self._background, Screen.size, Layout.center)
end

function M:_createInfoLabel()
    local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
    local payTbl = PayRatioConfigReader:getGuildCreate()
    local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
    local name = BackpackConfigRead:getName(payTbl.id)
    local str = string.format("主公，您是否愿意花费%d%s创建属于您的势力，一统天下", payTbl.count, name)
    local label = CommonUI:createLabel(str, 28)
    label:setWidth(Screen.size.width - 100)
    self._background:addChild(label)
    Layout:layout(label, self._background:getContentSize(), Layout.center_top, cc.p(0, 10))
end

function M:_createTextField()
    local label = CommonUI:createLabel(__Localized("势力名称："), 28)
    self._background:addChild(label)
    Layout:layout(label, self._background:getContentSize(), Layout.center_top, cc.p(200, 82))

    local tfBackground = cc.Sprite:create("ui/team/ui-un-0005a.png")
    self._background:addChild(tfBackground)
    Layout:layout(tfBackground, self._background:getContentSize(), Layout.center_top, cc.p(-55, 80))

    local TextInput = require("ui.common.InputUI")
    self._guildNameInput = TextInput.new(26)
    self._guildNameInput:setPlaceHolder(__Localized("请输入名称"))
    self._guildNameInput:setTextColor(cc.c4b(255, 255, 255, 255))
    self._guildNameInput:setMaxLength(14)
    self._guildNameInput:setTouchSize(tfBackground:getContentSize())
    self._background:addChild(self._guildNameInput)
    Layout:layout(self._guildNameInput, self._background:getContentSize(), Layout.center_top, cc.p(-55, 80))
end

function M:_createButtons()
    local confirmButton = CommonUI:createTextButton(self._background, __Localized("确定"), "ui/login/login-bt.png")
    Layout:layout(confirmButton, self._background:getContentSize(), Layout.center_bottom, cc.p(confirmButton:getContentSize().width * 0.5 + 30, 10))
    confirmButton.onClicked = function()
        local guildName = self._guildNameInput:getString()
        if string.len(guildName) == 0 then
            AlertView.new(__Localized("势力名称不能为空"))
            return
        end
        SocketManager:send(kGuildCreate, {name = guildName, flag = 1})
    end

    local cancelButton = CommonUI:createTextButton(self._background, __Localized("取消"), "ui/login/login-bt.png")
    Layout:layout(cancelButton, self._background:getContentSize(), Layout.center_bottom, cc.p(-cancelButton:getContentSize().width * 0.5 - 30, 10))
    cancelButton.onClicked = function()
        self:removeFromParent()
    end
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildCreate then
        if msgTable.code == 15 then
            CommonUI:alertRechargeLayer()
        else
            AlertView.new(__Localized("势力创建成功"))
            self:_gotoGuildLayer()
        end
    end
end

function M:_gotoGuildLayer()
    local GuildLayer = require("ui.guild.layer-manager.GuildLayer")
    local guildLayer = GuildLayer.new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(guildLayer)
    self:getParent():removeFromParent()
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch,event)
end

function M:onTouchCancelled(touch,event)
end
return M