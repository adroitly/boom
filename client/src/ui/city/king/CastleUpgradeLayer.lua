local BackgroundLayer = require("ui.common.BackgroundLayer")
local CastleConfigReader = require("ui.city.king.CastleConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local M = class("ui.city.king.CastleUpgradeLayer", function()
    return cc.Layer:create()
end)

local function _getResoucesName(id)
    return string.format("%s.png", id)
end

local kBuildingUpgrade = "building_upgrade"

function M:ctor()
    self:_createBackground()
    self:_createBuildingInfo()
    self:_createUpgradeButton()
    self:_createArrow()
    self:_updateBuildingInfo()
    self:setTag(Enum.LayerTag.CastleUpgrade)

    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kBuildingUpgrade then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            AlertView.new(__Localized("升级成功"))
            self:_updateBuildingInfo()
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("主城升级"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createArrow()
    self._arrowList = {}
    local bgPosX, bgPosY = self._currentLevelBackground:getPosition()
    local bgSize = self._currentLevelBackground:getContentSize()
    for i = 1, 3 do
        local sprite = cc.Sprite:create("ui/city/arrow.png")
        sprite:setRotation(90)
        self:addChild(sprite)
        local size = sprite:getContentSize()
        sprite:setPosition(cc.p(Screen.size.width * 0.5, bgPosY - bgSize.height * 0.5 - i * size.height * 0.5 + 100))
        table.insert(self._arrowList, sprite)
    end
end

function M:_removeArrow()
    if not self._arrowList then
        return
    end
    for k, v in pairs(self._arrowList) do
        v:removeFromParent()
        self._arrowList[k] = nil
    end
end

function M:_createBuildingInfo()
    self._currentLevelBackground = self:_createInfoBackground()
    Layout:layout(self._currentLevelBackground, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))

    self._nextLevelBackground = self:_createInfoBackground()
    local currentlevelSize = self._currentLevelBackground:getContentSize()
    Layout:layout(self._nextLevelBackground, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + currentlevelSize.height))
end

function M:_updateBuildingInfo()
    self._currentLevelBackground:removeAllChildren()
    self._nextLevelBackground:removeAllChildren()

    -- 当前等级
    local currentLevel = PlayerData:getCastleLevel()
    self:_createBuildingIcon(self._currentLevelBackground, currentLevel)
    self:_createBuildingInfoLabels(self._currentLevelBackground, currentLevel)

    -- 是否最高等级
    if currentLevel == CastleConfigReader:getMaxLevel() then
        self:_removeArrow()
        self._nextLevelBackground:removeFromParent()
        Layout:layout(self._currentLevelBackground, Screen.size, Layout.center)
        return
    end
    -- 下一等级
    local nextLevel = currentLevel + 1
    self:_createBuildingIcon(self._nextLevelBackground, nextLevel)
    self:_createBuildingInfoLabels(self._nextLevelBackground, nextLevel)
    self:_createUpgradeConditionLabels(self._nextLevelBackground, currentLevel)
end

function M:_createUpgradeButton()
    local button = CommonUI:createTextButton(self, __Localized("升级"), "ui/login/login-bt.png")
    button.onClicked = function()
        CommonUI:showLoadingLayer(true)
        SocketManager:send(kBuildingUpgrade, {})
    end
    Layout:layout(button, Screen.size, Layout.center_bottom, cc.p(0, 10))
end

function M:_createUpgradeConditionLabels(parent, level)
    local resLabel = CommonUI:createLabel(__Localized("升级所需资源："), 24)
    parent:addChild(resLabel)
    Layout:layout(resLabel, parent:getContentSize(), Layout.left_bottom, cc.p(10, 110))
    local resLabelSize = resLabel:getContentSize()
    local tbl = CastleConfigReader:getUpgradeConditions(level)
    for i, data in ipairs(tbl) do
        local icon = self:_createResourceConditionIcon(data)
        parent:addChild(icon)
        Layout:layout(icon, parent:getContentSize(), Layout.left_bottom, cc.p(10 + resLabelSize.width + 50 * (i - 1), 110))
    end

    local levelLabel = CommonUI:createLabel(__Localized("限制条件："), 24)
    parent:addChild(levelLabel)
    Layout:layout(levelLabel, parent:getContentSize(), Layout.left_bottom, cc.p(10, 30))

    local currentLevel = PlayerData:getUserInfoData():getLevel()
    local levelCondition = CastleConfigReader:getLevelCondition(level)
    local officerName = OfficerConfigRead:getOfficerName(levelCondition)
    local levelStr = "Lv." .. levelCondition .. " " .. officerName
    local levelConditionLabel = CommonUI:createLabel(levelStr, 24)
    parent:addChild(levelConditionLabel)
    Layout:layout(levelConditionLabel, parent:getContentSize(), Layout.left_bottom, cc.p(10 + levelLabel:getContentSize().width, 30))
    if currentLevel >= levelCondition then
        levelConditionLabel:setTextColor(cc.c4b(0, 255, 0, 255))
    else
        levelConditionLabel:setTextColor(cc.c4b(255, 0, 0, 255))
    end
end

function M:_createResourceConditionIcon(data)
    local iconName = _getResoucesName(data.id)
    local icon = CommonUI:createSpriteWithFrame("stage-icon", iconName)
    local countStr = "" .. data.count
    local countLabel = CommonUI:createLabel(countStr, 24)
    icon:addChild(countLabel)
    countLabel:setAnchorPoint(cc.p(0.5, 1))
    local labelSize = countLabel:getContentSize()
    countLabel:setPosition(cc.p(labelSize.width * 0.5, 0))
    local backpackData = BackpackDataManager:getBackpackDataByType(data.id)
    if backpackData then
        local needNumber = backpackData:getItemNumber()
        if needNumber >= data.count then
            countLabel:setTextColor(cc.c4b(0, 255, 0, 255))
            return icon
        end
    end
    countLabel:setTextColor(cc.c4b(255, 0, 0, 255))
    return icon
end

function M:_createBuildingIcon(parent, level)
    local resId = CastleConfigReader:getResId(level)
    local resStr = string.format("%d.png", resId)
    local sprite = CommonUI:createSpriteWithFrame("building", resStr)
    parent:addChild(sprite)
    Layout:layout(sprite, parent:getContentSize(), Layout.left_center, cc.p(200, -30))
    return sprite
end

function M:_createInfoBackground()
    local tempSprite = cc.Sprite:create("ui/login/login-bt.png")
    local tempSize = tempSprite:getContentSize()
    local background = ccui.Scale9Sprite:create("ui/login/login-bt.png", cc.rect(0, 0, tempSize.width, tempSize.height), cc.rect(20, 20, tempSize.width - 40, tempSize.height - 40))
    self:addChild(background)
    background:setContentSize(cc.size(Screen.width, 420))
    return background
end

function M:_createBuildingInfoLabels(parent, level)
    local background = parent
    local bgSize = background:getContentSize()
    local titleStr = __Localized("主城等级")
    local titleLabel = CommonUI:createLabel(titleStr, 30)
    Layout:layout(titleLabel, bgSize, Layout.center_top, cc.p(0, 10))
    background:addChild(titleLabel)

    local levelStr = "Lv." .. level
    local levelLabel = CommonUI:createLabel(levelStr, 30)
    Layout:layout(levelLabel, bgSize, Layout.center_top, cc.p(0, titleLabel:getContentSize().height + 10))
    background:addChild(levelLabel)

    local rightSidePosX = bgSize.width - 250
    local rightSidePosY = 80
    local soldierLevelStr = __Localized("兵种等级：") .. levelStr
    local soldierLevelLabel = CommonUI:createLabel(soldierLevelStr, 24)
    Layout:layout(soldierLevelLabel, bgSize, Layout.left_top, cc.p(rightSidePosX, rightSidePosY))
    background:addChild(soldierLevelLabel)
    local soldierLevelLabelSize = soldierLevelLabel:getContentSize()

    rightSidePosY = rightSidePosY + soldierLevelLabelSize.height
    local protectLimitStr = __Localized("保护上限：") .. CastleConfigReader:getSafeConfine(level)
    local protectLimitLabel = CommonUI:createLabel(protectLimitStr, 24)
    Layout:layout(protectLimitLabel, bgSize, Layout.left_top, cc.p(rightSidePosX, rightSidePosY))
    background:addChild(protectLimitLabel)
    local protectLimitSize = protectLimitLabel:getContentSize()

    rightSidePosY = rightSidePosY + protectLimitSize.height
    local saveLimitStr = __Localized("存储上限：") .. CastleConfigReader:getStorageConfine(level)
    local saveLimitLabel = CommonUI:createLabel(saveLimitStr, 24)
    Layout:layout(saveLimitLabel, bgSize, Layout.left_top, cc.p(rightSidePosX, rightSidePosY))
    background:addChild(saveLimitLabel)
    local saveLimitSize = saveLimitLabel:getContentSize()

    rightSidePosY = rightSidePosY + saveLimitSize.height
    local tbl = CastleConfigReader:getProduceResSpeed(level)
    for i, data in ipairs(tbl) do
        local label = self:_createResourceInfoLabel(data)
        local labelSize = label:getContentSize()
        background:addChild(label)
        Layout:layout(label, bgSize, Layout.left_top, cc.p(rightSidePosX, rightSidePosY + labelSize.height * (i - 1)))
    end
    return background
end

function M:_createResourceInfoLabel(data)
    local resNameStr = BackpackConfigRead:getName(data.id)
    -- 每分钟数量
    local count = math.floor(60 / data.time + 0.5)
    local str = resNameStr .. "：" .. count .. "/分钟"
    str = __Localized(str)
    local label = CommonUI:createLabel(str, 24)
    return label
end



return M