local RichLabel = require("ui.common.richlabel.RichLabel")
local RichLabelBase = require("ui.common.richlabel.RichLabelBase")
local SkillConfigReader = require("config-reader.SkillConfigReader")
local M = class("ui.team.layer-manager.UserSkillLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createOneSkillNodes()
    self:_createTwoSkillNodes()
end

function M:reload(skillIds, level)
    self:_updateSkillsDesc(skillIds, level or 1)
    self:_updateSkillsName(skillIds)
end

function M:_updateSkillsDesc(heroSkills, level)
    local skillOneDesc = SkillConfigReader:getDescription(heroSkills[1], level)
    local skillTwoDesc = SkillConfigReader:getDescription(heroSkills[2], level)
    local skillOneElementList = RichLabelBase:getElementListByStr(skillOneDesc)
    local skillTwoElementList = RichLabelBase:getElementListByStr(skillTwoDesc)
    self._oneSkillDescLabel:setElementList(skillOneElementList)
    self._twoSkiillDescLabel:setElementList(skillTwoElementList)
    self._oneSkillDescLabel:reloadData()
    self._twoSkiillDescLabel:reloadData()
end

function M:_updateSkillsName(heroSkills)
    local skillOneName = SkillConfigReader:getName(heroSkills[1])
    local skillTwoName = SkillConfigReader:getName(heroSkills[2])
    self._oneSkillNameLabel:setString(string.format(__Localized("武将技能1:%s"), skillOneName))
    self._twoSkillNameLabel:setString(string.format(__Localized("武将技能2:%s"), skillTwoName))
end

function M:_createOneSkillNodes()
    self._oneSkillNameLabel = CommonUI:createLabel("武将技能1:", 24)
    local labelSize = self._oneSkillNameLabel:getContentSize()
    self._oneSkillDescLabel = RichLabel.new()
    self._oneSkillNameLabel:setAnchorPoint(0, 0)
    self._oneSkillNameLabel:setPosition(cc.p(0, 0))
    self._oneSkillDescLabel:setPosition(cc.p(0, 0))
    self:addChild(self._oneSkillNameLabel)
    self:addChild(self._oneSkillDescLabel)
end

function M:_createTwoSkillNodes()
    self._twoSkillNameLabel = CommonUI:createLabel("武将技能2:", 24)
    local labelSize = self._twoSkillNameLabel:getContentSize()
    self._twoSkiillDescLabel = RichLabel.new()
    self._twoSkillNameLabel:setAnchorPoint(0, 1)
    self._twoSkillNameLabel:setPosition(cc.p(0, - labelSize.height * 3))
    self._twoSkiillDescLabel:setPosition(cc.p(0, - labelSize.height * 4))
    self:addChild(self._twoSkillNameLabel)
    self:addChild(self._twoSkiillDescLabel)
end

return M