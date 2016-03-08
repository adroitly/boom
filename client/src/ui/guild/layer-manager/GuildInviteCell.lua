local M = class("ui.guild.layer-manager.GuildInviteCell", function()
    return cc.TableViewCell:new()
end)

local kGuildInvitation = "guild_invitation"

M.GuildInviteCellSize = cc.size(756, 193)

function M:reset(searchUserData)
    self._searchUserData = searchUserData
    self._nicknameLabel:setString(searchUserData:getName())
    local levelStr = string.format("Lv.%d", searchUserData:getLevel())
    self._officeLabel:setString(levelStr)
    local guildName = string.format("势力：%s", searchUserData:getGuildName() or "无")
    self._guildLabel:setString(guildName)

    local icon = searchUserData:getIcon()
    local iconName = icon .. ".png"
    local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
    self._headIcon:setSpriteFrame(frame)

end

function M:ctor()
    self:_createBackground()
    self:_createHeadIcon()
    self:_createInfoLabels()
    self:_createInviteButton()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.GuildInviteCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createHeadIcon()
    self._headIcon = cc.Sprite:create("ui/test.png")
    self:addChild(self._headIcon)
    Layout:layout(self._headIcon, M.GuildInviteCellSize, Layout.left_center, cc.p(10, 0))
end

function M:_createInfoLabels()
    local posX = self._headIcon:getPositionX()
    local flagWidth = self._headIcon:getContentSize().width
    local initPosX = posX + flagWidth * 0.5 + 20

    local posY = M.GuildInviteCellSize.height * 0.5
    self._countryLabel = CommonUI:createLabel("国家：魏", 28)
    self:addChild(self._countryLabel)
    self._countryLabel:setAnchorPoint(cc.p(0, 0.5))
    self._countryLabel:setPosition(cc.p(initPosX, posY))

    posY = self._countryLabel:getPositionY() + self._countryLabel:getContentSize().height * 0.5 + 20
    self._nicknameLabel = CommonUI:createLabel("我是大魔王", 28)
    self:addChild(self._nicknameLabel)
    self._nicknameLabel:setAnchorPoint(cc.p(0, 0))
    self._nicknameLabel:setPosition(cc.p(initPosX, posY))

    self._officeLabel = CommonUI:createLabel("官职：上将军", 28)
    self:addChild(self._officeLabel)
    self._officeLabel:setAnchorPoint(cc.p(0, 0))
    self._officeLabel:setPosition(cc.p(initPosX + self._nicknameLabel:getContentSize().width + 100, self._nicknameLabel:getPositionY()))

    posY = self._countryLabel:getPositionY() - self._countryLabel:getContentSize().height * 0.5 - 20
    self._guildLabel = CommonUI:createLabel("势力：超级无极限", 28)
    self:addChild(self._guildLabel)
    self._guildLabel:setAnchorPoint(cc.p(0, 1))
    self._guildLabel:setPosition(cc.p(initPosX, posY))

end

function M:_createInviteButton()
    local button = CommonUI:createTextButton(self, "邀请", "ui/login/login-bt.png")
    Layout:layout(button, M.GuildInviteCellSize, Layout.right_center, cc.p(10, 0))
    button.onClicked = function()
        local targetId = self._searchUserData:getId()
        SocketManager:send(kGuildInvitation, {target_id = targetId})
    end
end

return M