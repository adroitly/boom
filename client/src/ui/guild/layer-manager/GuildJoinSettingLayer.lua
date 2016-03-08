local ToggleTextButton = require("share.toggle-button.ToggleTextButton")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildJoinSettingLayer", function()
    return cc.Layer:create()
end)

local KGuildSetting             = "guild_setting"

local function _checkLevel(level)
    if level > OfficerConfigRead:getMaxLevel() then
        return OfficerConfigRead:getMaxLevel()
    end
    if level < 1 then
        return 1
    end
    return level
end

local function _getTitle(isAutoOpen)
    return isAutoOpen and __Localized("开启") or __Localized("关闭")
end

local kGuildInfo = "guild_info"
function M:ctor()
    SocketManager:addObserver(self)
    GuildLayerManager:addLayer(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)
    self:_getGuildInfo()
    self._isInit = false
end

function M:_getGuildInfo()
    local guildId = PlayerData:getGuildId()
    SocketManager:send(kGuildInfo, {guild_id = guildId})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildInfo then
        if not self._isInit then
            self._isInit = true
            self:_initLayer()
        end
    end
end

function M:_initLayer()
    self:_createLevelSettingLayer()
    self:_createAutoButton()
    self:_createConfirmButton()
end

function M:_createAutoButton()
    self._isAutoJoin = PlayerData:getGuildData():isAutoJoin()
    self._settingLevelLayer:setVisible(self._isAutoJoin)
    local label = CommonUI:createLabel(__Localized("开启自动加入："), 30)
    self:addChild(label)
    Layout:layout(label, Screen.size, Layout.center, cc.p(150, 0))
    local button = ToggleTextButton.new(_getTitle(self._isAutoJoin), "ui/login/login-up.png", "ui/login/login-down.png")
    button:setSelected(self._isAutoJoin)
    button.onSelected = function(isSelected)
        local str = _getTitle(isSelected)
        button:setText(str)
        self._isAutoJoin = isSelected
        self._settingLevelLayer:setVisible(isSelected)
    end
    self:addChild(button)
    Layout:layout(button, Screen.size, Layout.center, cc.p(-150, 0))
end

function M:_createLevelSettingLayer()
    self._settingLevelLayer = cc.Layer:create()
    self:addChild(self._settingLevelLayer)

    self._settingLevel = PlayerData:getGuildData():getJoinLevel()
    if not self._settingLevel or self._settingLevel == 0 then
        self._settingLevel = 1
    end

    local officerName = OfficerConfigRead:getOfficerName(self._settingLevel)
    local posY = 100
    local label = CommonUI:createLabel(__Localized("玩家等级要求："), 30)
    self._settingLevelLayer:addChild(label)
    Layout:layout(label, Screen.size, Layout.center, cc.p(150, posY))

    local levelLabel = CommonUI:createLabel(officerName, 30)
    self._settingLevelLayer:addChild(levelLabel)
    Layout:layout(levelLabel, Screen.size, Layout.center, cc.p(-150, posY))

    local addButton = CommonUI:createTextButton(self._settingLevelLayer, "", "ui/team/button-add.png")
    Layout:layout(addButton, Screen.size, Layout.center, cc.p(-270, posY))
    addButton.onClicked = function()
        self._settingLevel = _checkLevel(self._settingLevel + 1)
        local officerName = OfficerConfigRead:getOfficerName(self._settingLevel)
        levelLabel:setString(officerName)
    end

    local subButton = CommonUI:createTextButton(self._settingLevelLayer, "", "ui/team/button-sub.png")
    Layout:layout(subButton, Screen.size, Layout.center, cc.p(-40, posY))
    subButton.onClicked = function()
        self._settingLevel = _checkLevel(self._settingLevel - 1)
        local officerName = OfficerConfigRead:getOfficerName(self._settingLevel)
        levelLabel:setString(officerName)
    end
end

function M:_createConfirmButton()
    local button = CommonUI:createTextButton(self, "确定修改", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(button, Screen.size, Layout.center_bottom, cc.p(0, 10))
    button.onClicked = function()
        local autoOpen = self._isAutoJoin and Enum.GuildSetting.AutoOpen or Enum.GuildSetting.AutoClose
        SocketManager:send(KGuildSetting, {auto = autoOpen, level = self._settingLevel})
    end
end

return M