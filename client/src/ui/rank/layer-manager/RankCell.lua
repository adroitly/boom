local RankConfig = require("ui.rank.data-manager.RankConfig")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local FlagData = require("ui.guild.data-manager.FlagData")
local M = class("ui.rank.layer-manager.RankCell", function()
    return cc.TableViewCell:new()
end)

M.RankCellSize = cc.size(750, 123)

function M:reset(rankType, rankData)
    local ranking = rankData:getRank()
    self._rankingLabel:setString(tostring(ranking))
    Layout:layout(self._rankingLabel, M.RankCellSize, Layout.left_center, cc.p(50, 0))

    local value = rankData:getValue()
    self._valueLabel:setString(tostring(value))
    Layout:layout(self._valueLabel, M.RankCellSize, Layout.center, cc.p(-250, 0))

    local countryId = rankData:getCountry()
    if rankType == RankConfig.RankType.Country then
        local countryIconRes = string.format("ui/country-icon/country-icon-%d.png", countryId)
        self._icon:setTexture(countryIconRes)
        return
    end

    local nameStr = rankData:getName()
    if rankType == RankConfig.RankType.Guild then
        nameStr = __Localized("君王：") .. nameStr
    else
        nameStr = __Localized("姓名：") .. nameStr
    end
    self._nameLabel:setString(nameStr)
    Layout:layout(self._nameLabel, M.RankCellSize, Layout.left_center, cc.p(200, -20))

    local guildName = rankData:getGuildName()
    if not guildName then
        guildName = __Localized("无")
    end
    guildName = __Localized("势力：") .. guildName
    self._guildNameLabel:setString(guildName)
    Layout:layout(self._guildNameLabel, M.RankCellSize, Layout.left_center, cc.p(200, 20))

    local countryName = CountryConfigReader:getCountryName(countryId)
    countryName = __Localized("国家：") .. countryName
    self._countryLabel:setString(countryName)
    Layout:layout(self._countryLabel, M.RankCellSize, Layout.left_center, cc.p(400, -20))
    if rankType ~= RankConfig.RankType.Guild then
        local level = rankData:getLevel()
        local officerName = OfficerConfigRead:getOfficerName(level)
        officerName = __Localized("官职：") .. officerName
        self._officerLabel:setString(officerName)
        Layout:layout(self._officerLabel, M.RankCellSize, Layout.left_center, cc.p(400, 20))
    end

    local iconId = rankData:getIcon()
    if rankType == RankConfig.RankType.Guild then
        local data = FlagData.new(iconId)
        self._icon:setTexture(data:getFileName())
    else
        local iconName = (iconId == 0 and 20100 or iconId) .. ".png"
        local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
        self._icon:setSpriteFrame(frame)
    end
end

function M:ctor(rankType)
    self:_createBackground()
    self:_createInfoLabels()
    self:_createIcon()
    if rankType == RankConfig.RankType.Guild then
        self:_createArrow()
    end
end

function M:setExpanded(isExpanded)
    if self._arrowSprite and isExpanded then
        self._arrowSprite:setRotation(90)
    end
end

function  M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.RankCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createIcon()
    self._icon = cc.Sprite:create("ui/test.png")
    self:addChild(self._icon)
    Layout:layout(self._icon, M.RankCellSize, Layout.center, cc.p(250, 0))
end

function M:_createArrow()
    self._arrowSprite = cc.Sprite:create("ui/city/arrow.png")
    self:addChild(self._arrowSprite)
    Layout:layout(self._arrowSprite, M.RankCellSize, Layout.right_center, cc.p(50, 0))
end

function M:_createInfoLabels()
    self._rankingLabel = CommonUI:createLabel("", 24)
    self:addChild(self._rankingLabel)

    self._nameLabel = CommonUI:createLabel("", 24)
    self:addChild(self._nameLabel)

    self._guildNameLabel = CommonUI:createLabel("", 24)
    self:addChild(self._guildNameLabel)

    self._countryLabel = CommonUI:createLabel("", 24)
    self:addChild(self._countryLabel)

    self._officerLabel = CommonUI:createLabel("", 24)
    self:addChild(self._officerLabel)

    self._valueLabel = CommonUI:createLabel("", 24)
    self:addChild(self._valueLabel)
end

return M