local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.country-war.layer-manager.CountryWarCell", function()
    return cc.TableViewCell:new()
end)

M.CountryWarCellSize = cc.size(752, 193)

function M:reset(countryWarData)
    local spaceX = 20

    local countryId = countryWarData:getCountryId()
    local countryIconRes = string.format("ui/country-icon/country-icon-%d.png", countryId)
    self._countryIcon:setTexture(countryIconRes)
    Layout:layout(self._countryIcon, M.CountryWarCellSize, Layout.left_center, cc.p(spaceX, 0))
    local countryIconSize = self._countryIcon:getContentSize()

    local playerCount = countryWarData:getPlayerCount()
    local playerCountStr = string.format("玩家人数：%d", playerCount)
    self._playerCountLabel:setString(playerCountStr)
    Layout:layout(self._playerCountLabel, M.CountryWarCellSize, Layout.left_center, cc.p(spaceX * 2 + countryIconSize.width, 0))
    local playerCountSize = self._playerCountLabel:getContentSize()

    local relation = countryWarData:getRelation()
    local relationStr = "无"
    if relation == Enum.CountryWarRelation.FightTo then
        relationStr = "宣战"
    end
    relationStr = string.format("当前关系：%s", relationStr)
    self._relationLabel:setString(relationStr)
    Layout:layout(self._relationLabel, M.CountryWarCellSize, Layout.left_center, cc.p(spaceX * 2 + countryIconSize.width, playerCountSize.height))

    local fighting = countryWarData:getFighting()
    local fightingStr = string.format("国家总战力：%d", fighting)
    self._fightingLabel:setString(fightingStr)
    Layout:layout(self._fightingLabel, M.CountryWarCellSize, Layout.left_center, cc.p(spaceX * 2 + countryIconSize.width, -playerCountSize.height))

    local score = countryWarData:getScore()
    local scoreStr = string.format("国家功勋：%d", score)
    self._scoreLabel:setString(scoreStr)
    Layout:layout(self._scoreLabel, M.CountryWarCellSize, Layout.left_center, cc.p(20, 0))
    Layout:layout(self._scoreLabel, M.CountryWarCellSize, Layout.left_center, cc.p(400, 0))
end

function M:setSelected(selected)
    local fileNames = {"ui/team/ui-un-0012a.png", "ui/team/ui-un-0012b.png"}
    self._background:setTexture(selected and fileNames[2] or fileNames[1])
end

function M:ctor()
    self:_createBackground()
    self:_createIcon()
    self:_createInfo()
end

function M:_createBackground()
    self._background = cc.Sprite:create()
    self:addChild(self._background)
    self:setContentSize(M.CountryWarCellSize)
    self._background:setAnchorPoint(cc.p(0, 0))
end

function M:_createIcon()
    self._countryIcon = cc.Sprite:create()
    self:addChild(self._countryIcon)
end

function M:_createInfo()
    self._relationLabel = CommonUI:createLabel("", 24)
    self:addChild(self._relationLabel)

    self._playerCountLabel = CommonUI:createLabel("", 24)
    self:addChild(self._playerCountLabel)

    self._fightingLabel = CommonUI:createLabel("", 24)
    self:addChild(self._fightingLabel)

    self._scoreLabel = CommonUI:createLabel("", 24)
    self:addChild(self._scoreLabel)
end


return M