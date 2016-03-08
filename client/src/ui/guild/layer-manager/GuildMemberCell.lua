
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local M = class("ui.guild.layer-manager.GuildMemberCell", function()
    return cc.TableViewCell:new()
end)

M.GuildMemberCellSize = cc.size(750, 123)

function M:reset(memberData)
    local nicknameStr = memberData:getNickname()
    self._nicknameLabel:setString(nicknameStr)
    local title = memberData:getTitle()
    local titleName = PlayerData:getGuildData():getTitleNameByTitle(title)
    self._titleLabel:setString(titleName)
    local level = memberData:getLevel()
    local officerName = OfficerConfigRead:getOfficerName(level)
    self._officeLabel:setString(officerName)
    local totalDonate = memberData:getTotalDonate()
    self._donateLabel:setString("" .. totalDonate)
end

function M:ctor()
    self:_createBackground()
    self:_createInfoLabels()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.GuildMemberCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createInfoLabels()
    self._titleLabel = CommonUI:createLabel("君王", 30)
    self:addChild(self._titleLabel)
    Layout:layout(self._titleLabel, M.GuildMemberCellSize, Layout.center, cc.p(320, 0))

    self._nicknameLabel = CommonUI:createLabel("我是XXXX", 30)
    self:addChild(self._nicknameLabel)
    Layout:layout(self._nicknameLabel, M.GuildMemberCellSize, Layout.center, cc.p(180, 0))

    self._officeLabel = CommonUI:createLabel("大将军", 30)
    self:addChild(self._officeLabel)
    Layout:layout(self._officeLabel, M.GuildMemberCellSize, Layout.center)

    self._donateLabel = CommonUI:createLabel("999999", 30)
    self:addChild(self._donateLabel)
    Layout:layout(self._donateLabel, M.GuildMemberCellSize, Layout.center, cc.p(-150, 0))

    self._onlineLabel = CommonUI:createLabel("1小时前", 30)
    self:addChild(self._onlineLabel)
    Layout:layout(self._onlineLabel, M.GuildMemberCellSize, Layout.center, cc.p(-280, 0))
end



return M