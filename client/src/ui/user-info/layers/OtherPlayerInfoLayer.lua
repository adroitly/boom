local BackgroundLayer = require("ui.common.BackgroundLayer")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.user-info.layers.OtherPlayerInfoLayer", function()
	return cc.Layer:create()
end)

function M:ctor(otherPlayerData)
    self._otherPlayerData = otherPlayerData
	self:_createBackground()
	self:_createInfos()
	self:_createSendEmailButton()
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "个人信息")
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createInfos()
    local icon = self._otherPlayerData:getIcon()
    local iconName = icon .. ".png"
    local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
    local playerIcon = cc.Sprite:createWithSpriteFrame(frame)
    local playerSize = playerIcon:getContentSize()
    self:addChild(playerIcon)
    Layout:layout(playerIcon, self:getContentSize(), Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))
    self:_createHeroInfosLabel(playerSize)
    self:_createHeroGuildInfosLabel(playerSize)
end

function M:_createHeroInfosLabel(playerSize)
    local heroInfosName = self:_getHeroInfosName()
    local labelText = ""
    for _,value in pairs(heroInfosName) do
        labelText = string.format("%s%s\n", labelText, value)
    end
    local label = CommonUI:createLabel(labelText, 24)
    label:setAlignment(0)
    self:addChild(label)

    Layout:layout(label, self:getContentSize(), Layout.left_top, cc.p(playerSize.width + 50, BackgroundLayer.TitleHeight))
end

function M:_createHeroGuildInfosLabel(playerSize)
    local heroGuildInfosName = self:_getHeroGuildInfosName()
    local labelText = ""
    for _,value in pairs(heroGuildInfosName) do
        labelText = string.format("%s%s\n", labelText, value)
    end
    local label = CommonUI:createLabel(labelText, 24)
    label:setAlignment(0)
    self:addChild(label)

    Layout:layout(label, self:getContentSize(), Layout.left_top, cc.p(0, playerSize.height + BackgroundLayer.TitleHeight + 100))
end

function M:_createSendEmailButton()
	local button = CommonUI:createTextButton(self, "发送邮件", "ui/login/login-up.png", "ui/login/login-down.png")
    local buttonSize = button:getContentSize()
    button:setPosition(Screen.width * 0.5, buttonSize.height / 2)
    button.onClicked = function()
        local layer = require("ui.mail.layer-manager.SendMailLayer").new(Enum.SendMailType.Personal, self:_getNickName())
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_getHeroGuildInfosName()
    local space = "       "
    return {
                string.format(__Localized("国%s家:%s"), space, self:_getCountry()),
                string.format(__Localized("君%s王:%s"), space, self:_getGuildLeaderName()),
                string.format(__Localized("势%s力:%s"), space, self:_getGuildName()),
                string.format(__Localized("爵%s位:%s"), space, self:_getNobilityName()),
            }
end

function M:_getHeroInfosName()
    return {
                string.format(__Localized("玩家名称 :%s"), self:_getNickName()),
                string.format(__Localized("玩家ID    :%s"), self:_getUserId()),
                string.format(__Localized("城池等级:%s"), self:_getBuildingLevel()),
                string.format(__Localized("官       职:%s"), self:_getOfficeName()),
            }
end

function M:_getNickName()
    return self._otherPlayerData:getNickname()
end

function M:_getUserId()
    return self._otherPlayerData:getPlayerId()
end


function M:_getBuildingLevel()
    return PlayerData:getCastleLevel()
end

function M:_getCountry()
    local countryId = self._otherPlayerData:getCountry()
    local countryName = CountryConfigReader:getCountryName(countryId)
    return countryName
end
-- 君王
function M:_getGuildLeaderName()
    return self._otherPlayerData:getGuildLeaderName() or __Localized("暂无")
end

function M:_getGuildName()
    return self._otherPlayerData:getGuildName() or __Localized("暂无")
end

function M:_getOfficeName()
    local currentLevel = self._otherPlayerData:getLevel()
    local officeName = OfficerConfigRead:getOfficerName(currentLevel)
    return officeName
end

-- 爵位
function M:_getNobilityName()
    return self._otherPlayerData:getGuildTitle() or __Localized("暂无")
end



return M