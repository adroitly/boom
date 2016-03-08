local SkillConfigReader = require("config-reader.SkillConfigReader")
local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local M = class("ui.team.layer-manager.HeroSelectCell", function()
    return cc.TableViewCell:new()
end)

M.HeroSelectCellSize = cc.size(756, 193)

function M:setSelected(isSelected)
    local fileNames = {"ui/team/ui-un-0012a.png", "ui/team/ui-un-0012b.png"}
    self._background:setTexture(isSelected and fileNames[2] or fileNames[1])
end

function M:resetHeroData(heroData)
    self._heroData = heroData
    self._headIcon:reload(heroData)
    self._headIcon:setupClick(function()
        local HeroInfoLayer = require("ui.team.layer-manager.HeroInfoLayer")
        local infoLayer = HeroInfoLayer.new()
        infoLayer:reloadLayerByHeroData(self._heroData)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(infoLayer)
    end)
    if not self._infoLabels then
        self._infoLabels = self:_createInfoLabels()
    end
    self:_resetInfoLabels()
    self:setSelected(false)
end

function M:ctor()
    self._background = self:_createBackground()
    self._headIcon = self:_createHeadIcon()
end

function M:_createBackground()
    local background = cc.Sprite:create()
    self:addChild(background)
    self:setContentSize(M.HeroSelectCellSize)
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

function M:_createInfoLabels()
    local labels = {}
    -- 属性
    local attrCount = table.getn(self:_getAttrTitles())
    for i = 1, attrCount do
        local label = CommonUI:createLabel("", 24)
        self:addChild(label)
        label:setAnchorPoint(cc.p(0, 1))
        table.insert(labels, label)
    end
    -- 技能
    local skillCount = table.getn(self:_getSkills())
    for i = 1, skillCount do
        local label = CommonUI:createLabel("", 24)
        self:addChild(label)
        label:setAnchorPoint(cc.p(0, 0))
        table.insert(labels, label)
    end
    -- 推荐兵种
    local label = CommonUI:createLabel("", 24)
    label:setAnchorPoint(cc.p(0, 0))
    self:addChild(label)
    table.insert(labels, label)
    return labels
end

function M:_resetInfoLabels()
    local size = self:getContentSize()
    local initPosX = 120
    local paddingX = 10
    local paddingY = 30
    local posX = initPosX
    -- 属性
    local attrTitles = self:_getAttrTitles()
    local attrValues = self:_getAttrValues()
    local labelIndex = 0
    for i = 1, table.getn(attrTitles) do
        local infoStr = attrTitles[i] .. ":" .. attrValues[i]
        labelIndex = labelIndex + 1
        local label = self._infoLabels[labelIndex]
        label:setString(infoStr)
        label:setPosition(cc.p(posX, size.height - paddingY))
        posX = posX + label:getContentSize().width + paddingX
    end
    -- 技能
    posX = initPosX
    local skills = self:_getSkills()
    for i = 1, table.getn(skills) do
        local skillStr = string.format(__Localized("技能：%s"), SkillConfigReader:getName(skills[i]))
        labelIndex = labelIndex + 1
        local label = self._infoLabels[labelIndex]
        label:setString(skillStr)
        label:setPosition(cc.p(posX, paddingY))
        posX = posX + label:getContentSize().width + paddingX
    end
    -- 推荐兵种
    local soldierType = self:_getRecommendSoldier()
    local soldierStr = "推荐：" .. SoldierConfigReader:getNameByType(soldierType)
    labelIndex = labelIndex + 1
    self._infoLabels[labelIndex]:setString(soldierStr)
    self._infoLabels[labelIndex]:setPosition(cc.p(posX, paddingY))
end

function M:_getAttrTitles()
    return {"统率", "武力", "智力", "体质"}
end

function M:_getAttrValues()
    local heroType = self._heroData:getHeroType()
    local heroLevel = self._heroData:getHeroLevel()
    return {
            HeroAttribute:getCommander(heroType, heroLevel),
            HeroAttribute:getForce(heroType, heroLevel),
            HeroAttribute:getBrains(heroType, heroLevel),
            HeroAttribute:getConstitution(heroType, heroLevel)
        }
end

function M:_getSkills()
    local heroType = self._heroData:getHeroType()
    return HeroConfigRead:getSkill(heroType)
end

function M:_getRecommendSoldier()
    local heroType = self._heroData:getHeroType()
    return HeroConfigRead:getRecommendSoldier(heroType)
end

return M