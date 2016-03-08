local BackgroundLayer = require("ui.common.BackgroundLayer")
local FlagData = require("ui.guild.data-manager.FlagData")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildManagerLayer", function()
    return cc.Layer:create()
end)

local kGuildQuit = "guild_quit"
local kGuildSetting = "guild_setting"
local FlagChangedLevelNeed = 5
function M:ctor()
    self:_createBackground()
    self:_createFlagIcon()
    self:_createBillboardFrame()
    self:_createOperateButtons()

    GuildLayerManager:addLayer(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildQuit then
        if CommonUI:errorAlertView(msgTable.code) then
            return
        end
        local GuildDataManager = require("player-data.GuildDataManager")
        GuildDataManager:resetOwnGuildData()
    end
    if cmd == kGuildSetting then
        if CommonUI:errorAlertView(msgTable.code) then
            return
        end
        AlertView.new(__Localized("设置成功"))
        self:_updateSetting()
    end
end

function M:_updateSetting()
    local guildData = PlayerData:getGuildData()
    local billboardStr = guildData:getNote()
    self._billboardLabel:setString(billboardStr)

    local flag = guildData:getFlag()
    local flagData = FlagData.new(flag)
    self._flagIcon:changeNormalSprite(flagData:getFileName())
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("管理"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createFlagIcon()
    local guildData = PlayerData:getGuildData()
    local flag = guildData:getFlag()
    local flagData = FlagData.new(flag)
    self._flagIcon = Button.new(flagData:getFileName())
    self:addChild(self._flagIcon)
    Layout:layout(self._flagIcon, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 10))
    self._flagIcon.onClicked = function()
        if guildData:getLevel() < FlagChangedLevelNeed then
            local str = string.format("势力等级达到%d级才能设置旗帜", FlagChangedLevelNeed)
            AlertView.new(str)
            return
        end
        local layer = require("ui.guild.layer-manager.FlagChangeLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createBillboardFrame()
    self._billboardBg = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(self._billboardBg)
    Layout:layout(self._billboardBg, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + self._flagIcon:getContentSize().height + 20))

    local billboardStr = PlayerData:getGuildData():getNote()
    self._billboardLabel = CommonUI:createLabel(billboardStr, 24)
    self._billboardBg:addChild(self._billboardLabel)
    self._billboardLabel:setWidth(self._billboardBg:getContentSize().width - 20)
    Layout:layout(self._billboardLabel, self._billboardBg:getContentSize(), Layout.center)

    local TextInput = require("ui.common.InputUI")
    local billboardInput = TextInput.new(24)
    billboardInput:setMaxLength(100)
    billboardInput:setTextColor(cc.c4b(255, 255, 255, 255))
    billboardInput:setAnchorPoint(cc.p(0, 0.5))
    local size = cc.size(self._billboardBg:getContentSize().width - 20, self._billboardBg:getContentSize().height - 10)
    billboardInput:setTextWidth(size.width)
    billboardInput:setAnchorPoint(cc.p(0, 1))
    self._billboardBg:addChild(billboardInput)
    -- billboardInput:setTouchEnabled(true)
    billboardInput:setVisible(false)
    billboardInput:setTouchSize(size)
    Layout:layout(billboardInput, self._billboardBg:getContentSize(), Layout.left_top, cc.p(30, 30))
    billboardInput:setTouchEnabled(false)
    local memberData = PlayerData:getGuildMemberData()
    if memberData:getTitle() == Enum.GuildTitle.Normal then
        return
    end
    local isEdit = false
    local button = CommonUI:createTextButton(self._billboardBg, __Localized("编辑"), "ui/login/login-bt.png")
    Layout:layout(button, self._billboardBg:getContentSize(), Layout.right_bottom)
    button.onClicked = function()
        isEdit = not isEdit
        billboardInput:setTouchEnabled(isEdit)
        billboardInput:setVisible(isEdit)
        self._billboardLabel:setVisible(not isEdit)
        button:setText(isEdit and __Localized("完成") or __Localized("编辑"))
        if not isEdit then
            local str = billboardInput:getString()
            if str == "" then
                return
            end
            billboardInput:setString("")
            SocketManager:send(kGuildSetting, {billboard = str})
        else
            local str = self._billboardLabel:getString()
            billboardInput:setString(str)
        end
    end
end

function M:_getButtonPositionByIndex(index, btnUp, btnDown)
    local maxLineCount = 4
    local tempButton = Button.new(btnUp)
    local buttonSize = tempButton:getContentSize()
    local paddingX = (Screen.width - buttonSize.width * maxLineCount) / (maxLineCount + 1)
    local paddingY = 10
    local initPosY = self._billboardBg:getPositionY() - (self._billboardBg:getContentSize().height + buttonSize.height) * 0.5 - paddingY
    local xIndex = math.floor((index - 1) % maxLineCount)
    local yIndex = math.floor((index - 1) / maxLineCount)
    initPosY = initPosY - (buttonSize.height - paddingY) * yIndex
    return cc.p(paddingX * (xIndex + 1) + tempButton:getContentSize().width * (xIndex + 0.5), initPosY)
end

function M:_getCallbacksTable()
    local tbl = {
        {title = __Localized("批准加入"), isNeedTitle = true, callback = function()
            local layer = require("ui.guild.layer-manager.GuildJoinLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
        {title = __Localized("邀请成员"), isNeedTitle = true, callback = function()
            local layer = require("ui.guild.layer-manager.GuildInviteLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
        {title = __Localized("册封封号"), isNeedTitle = true, callback = function()
            local layer = require("ui.guild.layer-manager.GuildOfferLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
        {title = __Localized("捐献排行"), isNeedTitle = false, callback = function()
            local layer = require("ui.guild.layer-manager.DonateRankLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
        {title = __Localized("全体邮件"), isNeedTitle = true, callback = function()
            local layer = require("ui.mail.layer-manager.SendMailLayer").new(Enum.SendMailType.Guild)
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
        {title = __Localized("其他势力"), isNeedTitle = false, callback = function()
            local layer = require("ui.guild.layer-manager.OtherGuildLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
        {title = __Localized("退出势力"), isNeedTitle = false, callback = function()
            local layer = require("ui.guild.layer-manager.GuildQuitLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end},
    }
    return tbl
end

function M:_createOperateButtons()
    local maxLineCount = 4
    local callbacksTable = self:_getCallbacksTable()
    local btnUpFile = "ui/login/login-up.png"
    local btnDownFile = "ui/login/login-down.png"
    for i = 1, table.getn(callbacksTable) do
        local title = callbacksTable[i].title
        local needTitle = callbacksTable[i].isNeedTitle
        local callback = callbacksTable[i].callback
        local button = CommonUI:createTextButton(self, title, btnUpFile, btnDownFile)
        local pos = self:_getButtonPositionByIndex(i, btnUpFile, btnDownFile)
        button:setPosition(pos)
        button.onClicked = function()
            if needTitle then
                local memberData = PlayerData:getGuildMemberData()
                if memberData:getTitle() == Enum.GuildTitle.Normal then
                    AlertView.new(__Localized("您没有权限"))
                    return
                end
            end
            callback()
        end
    end
end



return M