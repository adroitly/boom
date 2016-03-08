local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildJionCell = require("ui.guild.layer-manager.GuildJionCell")
local PlayerBaseData = require("player-data.PlayerBaseData")
local RadioButtonManager = require("share.radio-button.RadioButtonManager")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildJoinLayer", function()
    return cc.Layer:create()
end)
local kGuildApplyList           = "guild_apply_list";
local kGuildNewMemeberOperate   = "guild_new_member_operate"
local KGuildSetting             = "guild_setting"

local function _getTagButtonSize()
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    return tempSprite:getContentSize()
end

function M:ctor()
    self._playerBaseDataList = {}

    self:_createBackground()
    self:_createNewMemberLayer()
    self:_createJoinSettingLayer()
    self:_createTagButtons()
    self:_createMemberInfoLabels()
    self:_createMemberTableView()
    self:_createMemberButtons()

    GuildLayerManager:addLayer(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)

    self:_sendGetNewMemeberRequest()

end

function M:_sendGetNewMemeberRequest()
    SocketManager:send(kGuildApplyList, {})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildApplyList then
        local code = msgTable.code
        if CommonUI:errorAlertView(code) then
            return
        end
        self._playerBaseDataList = {}
        for _, v in pairs(msgTable.player_base_infos) do
            local playerBaseData = PlayerBaseData.new(v)
            table.insert(self._playerBaseDataList, playerBaseData)
        end
        self._tableView:reloadData()
    end
    if cmd == kGuildNewMemeberOperate then
        local code = msgTable.code
        if CommonUI:errorAlertView(code) then
            return
        end
        self:_sendGetNewMemeberRequest()
    end

    if cmd == "guild_message_send" then
        local code = msgTable.code
        if CommonUI:errorAlertView(code) then
            return
        end
        AlertView.new(__Localized("发送成功"))
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("批准加入"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTagButtons()
    local size = _getTagButtonSize()
    local setInfo = {
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", __Localized("批准新成员"), 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", __Localized("自动加入设置"), 30},
    }
    local buttonRadioLayer = ButtonRadioLayer.new(setInfo)
    self:addChild(buttonRadioLayer)
    buttonRadioLayer:setLayout(cc.size(Screen.width, size.height))
    buttonRadioLayer:setPosition(cc.p(0, Screen.height - BackgroundLayer.TitleHeight - size.height))
    buttonRadioLayer.onClicked = function(sender, index)
        self._newMemberLayer:setVisible(index == 0)
        self._joinSettingLayer:setVisible(index == 1)
    end
end

function M:_createNewMemberLayer()
    self._newMemberLayer = cc.Layer:create()
    self:addChild(self._newMemberLayer)
end

function M:_createMemberInfoLabels()
    local btnSize = _getTagButtonSize()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + btnSize.height))
    self._newMemberLayer:addChild(background)
    self._memberInfoBg = background
    local bgSize = background:getContentSize()

    local nicknameLabel = CommonUI:createLabel(__Localized("玩家名称"), 24)
    Layout:layout(nicknameLabel, bgSize, Layout.center, cc.p(300, 0))
    background:addChild(nicknameLabel)

    local officeLabel = CommonUI:createLabel(__Localized("官职"), 24)
    Layout:layout(officeLabel, bgSize, Layout.center, cc.p(150, 0))
    background:addChild(officeLabel)

    local onlineLabel = CommonUI:createLabel(__Localized("在线"), 24)
    Layout:layout(onlineLabel, bgSize, Layout.center, cc.p(0, 0))
    background:addChild(onlineLabel)

    local operateLabel = CommonUI:createLabel(__Localized("操作"), 24)
    Layout:layout(operateLabel, bgSize, Layout.center, cc.p(-220, 0))
    background:addChild(operateLabel)
end

function M:_createMemberButtons()
    local bottomHeight = BackgroundLayer.BottomHeight
    local agreeButton = CommonUI:createTextButton(self._newMemberLayer, __Localized("全部同意"), "ui/login/login-up.png", "ui/login/login-down.png")
    local offsetPosY = 0.5 * (bottomHeight - agreeButton:getContentSize().height)
    Layout:layout(agreeButton, Screen.size, Layout.center_bottom, cc.p(-220, offsetPosY))
    agreeButton.onClicked = function()
        SocketManager:send(kGuildNewMemeberOperate, {player_id = playerId, operate_type = Enum.GuildNewMemberOperate.AgreeTotal})
    end

    local refuseButton = CommonUI:createTextButton(self._newMemberLayer, "全部拒绝", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(refuseButton, Screen.size, Layout.center_bottom, cc.p(220, offsetPosY))
    refuseButton.onClicked = function()
        SocketManager:send(kGuildNewMemeberOperate, {player_id = playerId, operate_type = Enum.GuildNewMemberOperate.RefuseTotal})
    end
end

function M:_createMemberTableView()
    local btnSize = _getTagButtonSize()
    local cellSize = GuildJionCell.GuildJoinCellSize
    local infoBgSize = self._memberInfoBg:getContentSize()
    local offsetHeight = BackgroundLayer.TitleHeight + self._memberInfoBg:getContentSize().height + btnSize.height
    local leftHeight = Screen.size.height - offsetHeight
    local viewSize = cc.size(cellSize.width, leftHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self._newMemberLayer:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), Screen.height - offsetHeight - viewSize.height))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return GuildJionCell.GuildJoinCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = GuildJionCell.new()
    end
    local otherPlayerData = self._playerBaseDataList[idx + 1]
    cell:reset(otherPlayerData)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._playerBaseDataList)
end

function M:_createJoinSettingLayer()
    local Layer = require("ui.guild.layer-manager.GuildJoinSettingLayer")
    self._joinSettingLayer = Layer.new()
    self:addChild(self._joinSettingLayer)
end

return M