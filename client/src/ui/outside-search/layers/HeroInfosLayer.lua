local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.outside-search.layers.HeroInfosLayer", function()
	return cc.Layer:create()
end)

function M:ctor(buildingSearchData)
    self._otherPlayerData = buildingSearchData:getOtherPlayerData()
    self:setContentSize(cc.size(Screen.width, Screen.height / 4 - 100))
    self:_createUserHead()
    self:_createUserInfoLabel()
end

function M:_createUserInfoLabel()
    local showText = ""
    local heroInfoTable = self:_getHeroInfosName()
    for _,value in pairs(heroInfoTable) do
        showText = string.format("%s%s\n", showText, value)
    end
    local label = CommonUI:createLabel(showText, 24)
    label:setAlignment(0)
    self:addChild(label)
    Layout:layout(label, self:getContentSize(), Layout.left_center)
end

function M:_createUserHead()
    local sprite = cc.Sprite:create("ui/main-page/main-player-icon.png")
    self:addChild(sprite)
    Layout:layout(sprite, self:getContentSize(), Layout.center)
end

function M:_getHeroInfosName()
    local space = "       "
    return {    
                string.format(__Localized("国%s家:%s"), space, self:_getCountry()),
                string.format(__Localized("君%s王:%s"), space, self:_getGuildLeaderName()),
                string.format(__Localized("势%s力:%s"), space, self:_getGuildName()),
                string.format(__Localized("爵%s位:%s"), space, self:_getNobilityName()),
            }
end

function M:_getCountry()
    local countryId =  self._otherPlayerData:getCountry()
    if nil == countryId then
        return __Localized("无")
    end
    local name = CountryConfigReader:getCountryName(countryId)
    return name
end
-- 君王
function M:_getGuildLeaderName()
    return self._otherPlayerData:getGuildLeaderName() or __Localized("无")
end

function M:_getGuildName()
    return self._otherPlayerData:getGuildName() or __Localized("无")
end

-- 爵位
function M:_getNobilityName()
    return self._otherPlayerData:getGuildTitle() or __Localized("无")
end

return M