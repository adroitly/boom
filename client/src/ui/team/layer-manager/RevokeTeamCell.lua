
local MapConfig = require("ui.map.data-manager.MapConfig")
local HeroDataManager = require("player-data.HeroDataManager")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local StatuIdConfigRead = require("ui.team.data-manager.StatuIdConfigRead")
local M = class("ui.team.layer-manager.RovokeTeamCell", function()
    return cc.TableViewCell:new()
end)

M.CellSize = cc.size(752, 193)

function M:setSelected(isSelected)
    local fileNames = {"ui/team/ui-un-0012a.png", "ui/team/ui-un-0012b.png"}
    self._background:setTexture(isSelected and fileNames[2] or fileNames[1])
end

function M:resetTeamData(teamData)
    self._teamData = teamData

    if not self._infoLabels then
        self._infoLabels = self:_createInfoLabel()
    end
    self:_resetInfoLabels()
    local heroId = self._teamData:getHeroId()
    local heroData = HeroDataManager:getHeroDataById(heroId)
    self._headIcon:reload(heroData)
    self._headIcon:setupClick(function()
        local HeroInfoLayer = require("ui.team.layer-manager.HeroInfoLayer")
        local infoLayer = HeroInfoLayer.new()
        -- local heroData = HeroDataManager:getHeroDataById(heroId)
        infoLayer:reloadLayerByHeroData(heroData)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(infoLayer)
    end)
    self:setSelected(false)
end

function M:ctor()
    self._background = self:_createBackground()
    self._headIcon = self:_createHeadIcon()
end

function M:_createBackground()
    local background = cc.Sprite:create()
    self:addChild(background)
    self:setContentSize(M.CellSize)
    background:setAnchorPoint(cc.p(0, 0))
    return background
end

function M:_createHeadIcon()
    local headIcon = require("ui.common.HeroIcon").new()
    self:addChild(headIcon)
    local iconSize = headIcon:getContentSize()
    headIcon:setPosition(cc.p(iconSize.width * 0.5 + 30, iconSize.height * 0.5 + 40))
    return headIcon
end

function M:_createInfoLabel()
    local labels = {}
    local infoTitles = self:_getInfoTitles()
    for i = 1, #infoTitles do
        local label = CommonUI:createLabel("", 24)
        self:addChild(label)
        label:setAnchorPoint(cc.p(0, 1))
        table.insert(labels, label)
    end
    return labels
end

function M:_resetInfoLabels()
    local infoTitles = self:_getInfoTitles()
    local infoValues = self:_getInfoValues()
    local posX = 200
    local initPosY = 150
    local posY = initPosY
    local paddingY = 10
    for i = 1, table.getn(infoTitles) do
        local info = infoTitles[i] .. ":" .. infoValues[i]
        self._infoLabels[i]:setString(info)
        if i == 4 then
            posX = 400
            posY = initPosY
        end
        if i == 6 then
            local state = self._teamData:getState()
            local showPos = state ~= Enum.TeamDataState.Inside
            self._infoLabels[i]:setVisible(showPos)
        end
        self._infoLabels[i]:setPosition(cc.p(posX, posY))
        posY = posY - self._infoLabels[i]:getContentSize().height - paddingY
    end
end

function M:_getInfoTitles()
    local soldierNameStr = ""
    if self._teamData then
        local soldierType = self._teamData:getSoldierType()
        soldierNameStr = SoldierConfigReader:getName(soldierType)
    end
    return {soldierNameStr, "粮食", "士气", "状态", "所在区域", "坐标"}
end

function M:_getInfoValues()
    local soldierNumber = self._teamData:getSoldierNumber()
    local soldierType = self._teamData:getSoldierType()
    local heroId = self._teamData:getHeroId()
    local heroData = HeroDataManager:getHeroDataById(heroId)
    local heroLevel = heroData:getHeroLevel()
    local coor = self._teamData:getCooridnate()
    local twoDCoor = MapConfig:localTo2D(coor)
    local coorStr = (twoDCoor.i or 0) .. "," .. (twoDCoor.j or 0)
    local energy = heroData:getHeroEnergy() or 0
    local fodder = SoldierConfigReader:getFood(soldierType) * soldierNumber or 0
    local statuId = self._teamData:getStatuId()
    local statuName = StatuIdConfigRead:getNameById(statuId)
    return {soldierNumber, fodder, energy, self:_getStateStr(), statuName, coorStr}
end

function M:_getStateStr()
    local state = self._teamData:getState()
    local stateStr = {
        [Enum.TeamDataState.Inside] = "空闲",
        [Enum.TeamDataState.Outside] = "移动",
        [Enum.TeamDataState.Guard] = "驻守"
    }
    return stateStr[state]
end
return M