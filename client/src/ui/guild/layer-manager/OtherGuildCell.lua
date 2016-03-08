local GuildLevelConfigRead = require("ui.guild.data-manager.GuildLevelConfigRead")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.guild.layer-manager.OtherGuildCell", function()
    return cc.TableViewCell:new()
end)

local kGuildJoin = "guild_join"

M.OtherGuildCellSize = cc.size(756, 193)

function M:reset(guildData)
    self._guildData = guildData
    local guildNameStr = string.format("势力名称：%s", guildData:getName())
    guildNameStr = __Localized(guildNameStr)
    self._nameLabel:setString(guildNameStr)
    local leaderNameStr = string.format("君王名称：%s", guildData:getLeaderName())
    leaderNameStr = __Localized(leaderNameStr)
    self._leaderNameLabel:setString(leaderNameStr)
    local levelStr = string.format("Lv.%d", guildData:getLevel())
    self._levelLabel:setString(levelStr)
    local memberMax = GuildLevelConfigRead:getMemberMax(guildData:getLevel())
    local memberStr = string.format("成员：%d/%d", guildData:getMemberNum(), memberMax)
    memberStr = __Localized(memberStr)
    self._memberCountLabel:setString(memberStr)

    local countryId = guildData:getCountryId()
    local countryName = CountryConfigReader:getCountryName(countryId)
    countryName = string.format("国家: %s", countryName)
    self._countryLabel:setString(countryName)

    local FlagData = require("ui.guild.data-manager.FlagData")
    local flagData = FlagData.new(guildData:getFlag())
    self._flagIcon:setTexture(flagData:getFileName())
end

function M:ctor()
    self:_createBackground()
    self:_createFlagIcon()
    self:_createInfoLabels()
    self:_createJoinButton()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.OtherGuildCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createFlagIcon()
    self._flagIcon = cc.Sprite:create("ui/guild/guild-flag-0.png")
    self:addChild(self._flagIcon)
    Layout:layout(self._flagIcon, M.OtherGuildCellSize, Layout.left_center, cc.p(20, 0))
end

function M:_createInfoLabels()
    local posX = self._flagIcon:getPositionX()
    local flagWidth = self._flagIcon:getContentSize().width
    local initPosX = posX + flagWidth * 0.5 + 20

    local posY = M.OtherGuildCellSize.height * 0.5
    self._memberCountLabel = CommonUI:createLabel("成员数：33", 28)
    self:addChild(self._memberCountLabel)
    self._memberCountLabel:setAnchorPoint(cc.p(0, 0.5))
    self._memberCountLabel:setPosition(cc.p(initPosX, posY))
    local memberCountLabelPosY = self._memberCountLabel:getPositionY()

    posY = memberCountLabelPosY
    self._countryLabel = CommonUI:createLabel("国家：魏", 28)
    self:addChild(self._countryLabel)
    self._countryLabel:setAnchorPoint(cc.p(0, 0.5))
    self._countryLabel:setPosition(cc.p(initPosX + self._memberCountLabel:getContentSize().width + 50, posY))

    posY = memberCountLabelPosY + self._memberCountLabel:getContentSize().height * 0.5 + 20
    self._nameLabel = CommonUI:createLabel("势力名称：天地无极限", 28)
    self:addChild(self._nameLabel)
    self._nameLabel:setAnchorPoint(cc.p(0, 0))
    self._nameLabel:setPosition(cc.p(initPosX, posY))

    self._levelLabel = CommonUI:createLabel("Lv.3", 28)
    self:addChild(self._levelLabel)
    self._levelLabel:setAnchorPoint(cc.p(0, 0))
    self._levelLabel:setPosition(cc.p(initPosX + self._nameLabel:getContentSize().width + 100, self._nameLabel:getPositionY()))

    posY = memberCountLabelPosY - self._memberCountLabel:getContentSize().height * 0.5 - 20
    self._leaderNameLabel = CommonUI:createLabel("君王：我是大帅锅", 28)
    self:addChild(self._leaderNameLabel)
    self._leaderNameLabel:setAnchorPoint(cc.p(0, 1))
    self._leaderNameLabel:setPosition(cc.p(initPosX, posY))

end

function M:_createJoinButton()
    if PlayerData:isHasGuild() then
        return
    end
    local button = CommonUI:createTextButton(self, "申请加入", "ui/login/login-bt.png")
    Layout:layout(button, M.OtherGuildCellSize, Layout.right_center, cc.p(10, 0))
    button.onClicked = function()
        self:_sendJoinRequest()
    end
end

function M:_sendJoinRequest()
    CommonUI:showLoadingLayer(true)
    local guildId = self._guildData:getGuildId()
    SocketManager:send(kGuildJoin, {guild_id = guildId})
end

return M