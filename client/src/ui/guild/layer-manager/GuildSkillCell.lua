local GuildSkillConfigRead = require("ui.guild.data-manager.GuildSkillConfigRead")
local TimeTools = require("ui.common.TimeTools")
local M = class("ui.guild.layer-manager.GuildSkillCell", function()
    return cc.TableViewCell:new()
end)

local kGuildSkillUpgrade = "guild_skill_upgrade"
local kDonateValue = 1000

M.GuildSkillCellSize = cc.size(752, 193)

function M:reset(guildSkillData)
    self._guildSkillData = guildSkillData
    local skillId = guildSkillData:getSkillId()
    local skillLevel = guildSkillData:getSkillLevel()
    local skillName = GuildSkillConfigRead:getSkillName(skillId)
    self._nameLabel:setString(skillName)
    Layout:layout(self._nameLabel, M.GuildSkillCellSize, Layout.left_top, cc.p(self._skillIcon:getContentSize().width + 10, 30))
    self._levelLabel:setString("Lv." .. skillLevel)
    local namePosX, namePosY = self._nameLabel:getPosition()
    local nameSize = self._nameLabel:getContentSize()
    self._levelLabel:setAnchorPoint(cc.p(0, 0.5))
    self._levelLabel:setPosition(cc.p(namePosX + nameSize.width * 0.5, namePosY))

    self:_resetSkillDesc(guildSkillData)
    self:_updateExpProgress(guildSkillData)

    local lvmax = GuildSkillConfigRead:getSkillLevelMax(skillId)
    self._upgradeButton:setText("升级")
    if skillLevel == lvmax then
        self._upgradeButton:setEnabled(false)
    else
        self._upgradeButton:setEnabled(true)
    end

end

function M:ctor()
    self:_createBackground()
    self:_createSkillIcon()
    self:_createInfoLabels()
    self:_createUpgradeButton()
    self:_createExpProgress()
end

function M:_resetSkillDesc(guildSkillData)
    local skillType = guildSkillData:getSkillType()
    local skillId = guildSkillData:getSkillId()
    local skillLevel = guildSkillData:getSkillLevel()
    local skillExp = guildSkillData:getSkillExp()

    local currentDescStr = GuildSkillConfigRead:getSkillDesc(skillId, skillLevel)
    self._currentLevelDescLabel:setString(__Localized("当前等级：") .. currentDescStr)
    Layout:layout(self._currentLevelDescLabel, M.GuildSkillCellSize, Layout.left_top, cc.p(self._skillIcon:getContentSize().width + 10, 60))
    local levelMax = GuildSkillConfigRead:getSkillLevelMax(skillId)
    if skillLevel == levelMax then
        self._priceLabel:setVisible(false)
        self._nextLevelDescLabel:setString(__Localized("下一等级：无"))
    else
        self._priceLabel:setVisible(true)
        local nextSkillId = skillType + skillLevel + 1
        local nextDescStr = GuildSkillConfigRead:getSkillDesc(nextSkillId)
        self._nextLevelDescLabel:setString(__Localized("下一等级：") .. nextDescStr)
        self._priceLabel:setString(__Localized("升级费用：") .. kDonateValue)
    end
    Layout:layout(self._nextLevelDescLabel, M.GuildSkillCellSize, Layout.left_top, cc.p(self._skillIcon:getContentSize().width + 10, 90))
    Layout:layout(self._priceLabel, M.GuildSkillCellSize, Layout.left_top, cc.p(self._skillIcon:getContentSize().width + 10, 120))
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.GuildSkillCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createSkillIcon()
    self._skillIcon = cc.Sprite:create("ui/test.png")
    self:addChild(self._skillIcon)
    Layout:layout(self._skillIcon, M.GuildSkillCellSize, Layout.left_center, cc.p(10, 0))
end

function M:_createInfoLabels()
    self._nameLabel = CommonUI:createLabel("技能名称", 24)
    self:addChild(self._nameLabel)
    
    self._levelLabel = CommonUI:createLabel("Lv", 24)
    self:addChild(self._levelLabel)

    self._currentLevelDescLabel = CommonUI:createLabel("Lv", 24)
    self:addChild(self._currentLevelDescLabel)

    self._nextLevelDescLabel = CommonUI:createLabel("Lv", 24)
    self:addChild(self._nextLevelDescLabel)

    self._priceLabel = CommonUI:createLabel("价格", 24)
    self:addChild(self._priceLabel)
end

function M:_createUpgradeButton()
    self._upgradeButton = CommonUI:createTextButton(self, "升级", "ui/login/login-bt.png")
    Layout:layout(self._upgradeButton, M.GuildSkillCellSize, Layout.right_center, cc.p(10, 0))
    self._upgradeButton.onClicked = function()
        self:_sendUpgradeRequest()
    end
end

function M:_createExpProgress()
    local progressBackground = cc.Sprite:create("ui/hero-museum/progressbg.png")
    self:addChild(progressBackground)
    local progressSize = progressBackground:getContentSize()
    Layout:layout(progressBackground, M.GuildSkillCellSize, Layout.center_bottom, cc.p(0, 10))

    self._progressTimer = cc.ProgressTimer:create(cc.Sprite:create("ui/hero-museum/progressup.png"))
    Layout:layout(self._progressTimer, progressSize, Layout.center)
    self._progressTimer:setBarChangeRate(cc.p(1, 0))
    self._progressTimer:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self._progressTimer:setMidpoint(cc.p(0,1))
    self._progressTimer:setPercentage(0)
    progressBackground:addChild(self._progressTimer)

    self._progressLabel = CommonUI:createLabel("0/100", 36)
    Layout:layout(self._progressLabel, progressSize, Layout.center)
    progressBackground:addChild(self._progressLabel)
end

function M:_updateExpProgress(guildSkillData)
    local skillType = guildSkillData:getSkillType()
    local skillId = guildSkillData:getSkillId()
    local skillLevel = guildSkillData:getSkillLevel()
    local skillExp = guildSkillData:getSkillExp()

    local levelMax = GuildSkillConfigRead:getSkillLevelMax(skillId)
    local nextSkillId = skillType + skillLevel + 1
    if skillLevel == levelMax then
        nextSkillId = skillId
        skillId = skillId - 1
    end
    local preNeedExp = GuildSkillConfigRead:getSkillUpgradeExp(skillId)
    local nextNeedExp = GuildSkillConfigRead:getSkillUpgradeExp(nextSkillId) - preNeedExp
    local curExp = skillExp - preNeedExp
    local percentage = curExp / nextNeedExp * 100
    self._progressTimer:setPercentage(percentage)
    local str = string.format("%d/%d", curExp, nextNeedExp)
    self._progressLabel:setString(str)
end

function M:_sendUpgradeRequest()
    local title = PlayerData:getGuildMemberData():getTitle()
    if title == Enum.GuildTitle.Normal then
        CommonUI:lightTips("您没有操作权限")
        return
    end
    local skillType = self._guildSkillData:getSkillType()
    local memberDonate = PlayerData:getGuildMemberData():getTotalDonate()
    if memberDonate < kDonateValue then
        local str = string.format("捐献值不足，需要%d", kDonateValue)
        CommonUI:lightTips(str)
        return
    end
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kGuildSkillUpgrade, {skill_type = skillType, donate = kDonateValue})
end


return M