local ButtonLongPress = require("libs.widget.ButtonLongPress")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local M = class("ui.team.layer-manager.SoldierSelectCell", function()
    return cc.TableViewCell:new()
end)

M.SoldierSelectCellSize = cc.size(752, 193)

local function _getMaxSoliderNumber(soldierData, heroData)
    local count = soldierData:getSoldierNumber()
    local soldierType = soldierData:getSoldierType()
    local heroType = heroData:getHeroType()
    local heroLevel = heroData:getHeroLevel()
    local limit = HeroAttribute:getTroops(heroType, heroLevel, soldierType)
    return count > limit and limit or count
end

function M:setSelected(selected)
    self._slider:setVisible(selected)
    self._addButton:setVisible(selected)
    self._subButton:setVisible(selected)
    local fileNames = {"ui/team/ui-un-0012a.png", "ui/team/ui-un-0012b.png"}
    -- 刷新显示文字
    if selected then
        self._background:setTexture(fileNames[2])
        local count = self._soldierData:getSoldierNumber()
        local defaultValue = _getMaxSoliderNumber(self._soldierData, self._heroData)

        local value = self._slider:getValue()<=1 and defaultValue or self._slider:getValue()
        self._slider:setValue(value)
    else
        self._background:setTexture(fileNames[1])
        self._slider:setValue(0)
    end
end

function M:getSelectedCount()
    return self._selectedSoldierCount
end

function M:resetSoldierData(soldierData, heroData)
    self._soldierData = soldierData
    self._heroData = heroData
    if not self._slider then
        self._slider = self:_createSlider()
    end
    if not self._totalSoldierCountLabel or not self._selectedSoldierCountLabel then
        self._totalSoldierCountLabel, self._selectedSoldierCountLabel = self:_createSoldierCountLabel()
    end
    if not self._infoLabels then
        self._infoLabels = self:_createInfoLabels()
    end
    self:_resetTotalSoldierCount()
    self:_setSelectedSoldierCount(0)
    self:_resetInfoLabels()

    self._slider:setVisible(false)
    self._addButton:setVisible(false)
    self._subButton:setVisible(false)
    self._background:setTexture("ui/team/ui-un-0012a.png")
    self:_resetHeadIcon()
end

function M:ctor()
    self._background = self:_createBackground()
    self._addButton, self._subButton = self:_createModifyButton()
    self._headIcon = self:_createHeadIcon()
end

function M:_createBackground()
    local background = cc.Sprite:create()
    self:addChild(background)
    self:setContentSize(M.SoldierSelectCellSize)
    background:setAnchorPoint(cc.p(0, 0))
    return background
end

function M:_createHeadIcon()
    local headIcon = Button.new()
    self:addChild(headIcon)
    headIcon.onClicked = function()
        local soldierType = self._soldierData:getSoldierType()
        local soldierInfoLayer = require("ui.team.layer-manager.SoldierInfoLayer").new(soldierType)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(soldierInfoLayer)
    end
    return headIcon
end

function M:_resetHeadIcon()
    local soldierType = self._soldierData:getSoldierType()
    local resType = SoldierConfigReader:getType(soldierType)
    local path = string.format("%d.png", resType)
    local frame = CommonUI:createSpriteFrameTinyName("soldier",path)
    self._headIcon:changeNormalSpriteWithFrame(frame)
    local iconSize = self._headIcon:getContentSize()
    self._headIcon:setPosition(cc.p(iconSize.width * 0.5 + 30, M.SoldierSelectCellSize.height * 0.5))
end

function M:_resetInfoLabels()
    local infoTitles = self:_getAttrTitles()
    local infoValues = self:_getAttrValues()
    local posX = 180
    local posY = 150
    local paddingY = 10
    for i = 1, table.getn(self._infoLabels) do
        local info = string.format("%s:%s", infoTitles[i], infoValues[i] or __Localized("无"))
        local label = self._infoLabels[i]
        label:setPosition(cc.p(posX, posY))
        label:setString(info)
        posY = posY - label:getContentSize().height - paddingY
    end
end

function M:_createInfoLabels()
    local infoTitles = self:_getAttrTitles()
    local labels = {}
    for i = 1, table.getn(infoTitles) do
        local label = CommonUI:createLabel("", 24)
        self:addChild(label)
        label:setAnchorPoint(cc.p(0, 1))
        table.insert(labels, label)
    end
    return labels
end

function M:_createModifyButton()
    local addButton = ButtonLongPress.new("ui/team/button-add.png")
    self:addChild(addButton)
    Layout:layout(addButton, M.SoldierSelectCellSize, Layout.right_bottom, cc.p(100, 50))
    addButton.onClicked = function()
        local value = self._slider:getValue()
        self._slider:setValue(value + 1)
    end
    addButton:setSwallowTouches(false)

    local subButton = ButtonLongPress.new("ui/team/button-sub.png")
    self:addChild(subButton)
    Layout:layout(subButton, M.SoldierSelectCellSize, Layout.right_bottom, cc.p(420, 50))
    subButton.onClicked = function()
        local value = self._slider:getValue()
        if value <= 1 then
            return
        end
        self._slider:setValue(value - 1)
    end
    subButton:setSwallowTouches(false)
    return addButton, subButton
end

function M:_createSlider()
    local slider = ControlSlider.new("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
    slider:setMinimumValue(1)
    self:addChild(slider)
    Layout:layout(slider, M.SoldierSelectCellSize, Layout.right_bottom, cc.p(150, 38))
    slider.onValueChanged = function(sender, value)
        self:_sliderValueChanged(sender)
    end
    return slider
end

function M:_createSoldierCountLabel()
    local totalCountLabel = CommonUI:createLabel("", 24)
    totalCountLabel:setAnchorPoint(cc.p(0, 0))
    totalCountLabel:setPosition(cc.p(380, 140))
    self:addChild(totalCountLabel)

    local selectedCountLabel = CommonUI:createLabel("", 24)
    selectedCountLabel:setAnchorPoint(cc.p(0, 0))
    selectedCountLabel:setPosition(cc.p(380, 100))
    self:addChild(selectedCountLabel)

    return totalCountLabel, selectedCountLabel
end

function M:_sliderValueChanged(sender)
    if not sender then
        return
    end
    -- 四舍五入取整
    local senderValue = sender:getValue()
    local value = math.floor(senderValue + 0.5)
    if senderValue ~= value then
        sender:setValue(value)
    else
        self:_setSelectedSoldierCount(value)
    end
end

function M:_setSelectedSoldierCount(count)
    self._selectedSoldierCount = count
    local maxCount = _getMaxSoliderNumber(self._soldierData, self._heroData)
    local str = string.format("可携带兵数:%d/%d", count, maxCount)
    self._selectedSoldierCountLabel:setString(str)
end

function M:_resetTotalSoldierCount()
    local count = _getMaxSoliderNumber(self._soldierData, self._heroData)
    self._slider:setMaximumValue(count)
    local totalNumber = self._soldierData:getSoldierNumber()
    self._totalSoldierCountLabel:setString("总兵数:" .. totalNumber)
end

function M:_getAttrTitles()
    return {"名称", "克制"}
end

function M:_getAttrValues()
    local soldierType = self._soldierData:getSoldierType()
    local level = SoldierConfigReader:getLevel(soldierType)
    local name = SoldierConfigReader:getName(soldierType)
    name = "Lv." .. level .. name
    -- local restrainType = SoldierConfigReader:getRestrain(soldierType)
    -- local restrainSoldierName = SoldierConfigReader:getNameByType(restrainType)
    local restraindesc = SoldierConfigReader:getRestraindesc(soldierType)
    return {
            name,
            restraindesc
        }
end

return M

