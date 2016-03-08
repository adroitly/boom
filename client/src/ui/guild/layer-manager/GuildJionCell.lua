
local M = class("ui.guild.layer-manager.GuildJionCell", function()
    return cc.TableViewCell:new()
end)

local kGuildNewMemeberOperate = "guild_new_member_operate"

M.GuildJoinCellSize = cc.size(752, 123)

function M:reset(playerBaseData)
    self._playerBaseData = playerBaseData
    self._nicknameLabel:setString(playerBaseData:getNickname())
    local levelStr = string.format("Lv.%d", playerBaseData:getLevel())
    self._officeLabel:setString(playerBaseData:getLevel())
    local onlineTime = playerBaseData:getPreOnlineTime()
    local onlineStr = string.format("%d", playerBaseData:getPreOnlineTime())
    if onlineTime == 0 then
        onlineStr = __Localized("在线")
    end
    self._onlineLabel:setString(onlineStr)
end

function M:ctor()
    self:_createBackground()
    self:_createInfoLabels()
    self:_createButtons()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.GuildJoinCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createInfoLabels()
    self._nicknameLabel = CommonUI:createLabel("玩家名称", 24)
    Layout:layout(self._nicknameLabel, M.GuildJoinCellSize, Layout.center, cc.p(300, 0))
    self:addChild(self._nicknameLabel)

    self._officeLabel = CommonUI:createLabel("官职", 24)
    Layout:layout(self._officeLabel, M.GuildJoinCellSize, Layout.center, cc.p(150, 0))
    self:addChild(self._officeLabel)

    self._onlineLabel = CommonUI:createLabel("在线", 24)
    Layout:layout(self._onlineLabel, M.GuildJoinCellSize, Layout.center, cc.p(0, 0))
    self:addChild(self._onlineLabel)
end

function M:_createButtons()
    local agreeButton = CommonUI:createTextButton(self, "同意", "ui/login/login-bt.png")
    Layout:layout(agreeButton, M.GuildJoinCellSize, Layout.center, cc.p(-220 + agreeButton:getContentSize().width * 0.5, 0))
    agreeButton.onClicked = function()
        local playerId = self._playerBaseData:getPlayerId()
        SocketManager:send(kGuildNewMemeberOperate, {player_id = playerId, operate_type = Enum.GuildNewMemberOperate.Agree})
    end

    local refuseButton = CommonUI:createTextButton(self, "拒绝", "ui/login/login-bt.png")
    Layout:layout(refuseButton, M.GuildJoinCellSize, Layout.center, cc.p(-220 - refuseButton:getContentSize().width * 0.5, 0))
    refuseButton.onClicked = function()
        local playerId = self._playerBaseData:getPlayerId()
        SocketManager:send(kGuildNewMemeberOperate, {player_id = playerId, operate_type = Enum.GuildNewMemberOperate.Refuse})
    end
end



return M