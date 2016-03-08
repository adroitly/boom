local ButtonLongPress = require("libs.widget.ButtonLongPress")
local BackpackDataManager = require("player-data.BackpackDataManager")
local GuildDonateRatioConfigRead = require("ui.guild.data-manager.GuildDonateRatioConfigRead")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.guild.layer-manager.ResourceOperateCell", function()
    return cc.TableViewCell:new()
end)

M.ResourceOperateCellSize = cc.size(752, 193)

function M:reset(resourceType, value, valueChangedCallback)
    local resourceName = self:_getResourceName(resourceType)
    self._resourceType = resourceType
    self._resourceTitle:setString(resourceName)
    Layout:layout(self._resourceTitle, M.ResourceOperateCellSize, Layout.left_center, cc.p(30, 0))
    self._valueChangedCallback = valueChangedCallback
    self._slider:setValue(value)
    local backpackData = BackpackDataManager:getBackpackDataByType(resourceType)
    local itemNumber = 0
    if backpackData then
        itemNumber = backpackData:getItemNumber()
    end
    local str = string.format("拥有%s：%d", resourceName, itemNumber)
    str = __Localized(str)
    self._ownLabel:setString(str)
    self._slider:setMaximumValue(itemNumber)
    
end

function M:getSelectedCount()
    return self._selectedCount
end

function M:ctor(operateType)
    self._operateType = operateType
    self:_createBackground()
    self:_createResourceTitle()
    self:_createSlider()
    self:_createModifyButton()
    self:_createSelectedCountLabel()
    self:_createInfoLabels()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.ResourceOperateCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createResourceTitle()
    self._resourceTitle = CommonUI:createLabel("", 40)
    self:addChild(self._resourceTitle)
end

function M:_createSlider()
    self._slider = ControlSlider.new("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
    self._slider:setMinimumValue(0)
    self._slider:setMaximumValue(100)
    -- self._slider:setSwallowTouches(false)
    self:addChild(self._slider)
    Layout:layout(self._slider, M.ResourceOperateCellSize, Layout.center)
    self._slider.onValueChanged = function(sender, value)
        self:_sliderValueChanged(sender)
    end
end

function M:_createModifyButton()
    local paddingX = 30
    local posX, posY = self._slider:getPosition()
    local sliderSize = self._slider:getContentSize()
    self._addButton = ButtonLongPress.new("ui/team/button-add.png")
    self:addChild(self._addButton)
    self._addButton:setPosition(cc.p(posX + 0.5 * (sliderSize.width + self._addButton:getContentSize().width) + paddingX, posY))
    self._addButton.onClicked = function()
        local value = self._slider:getValue()
        self._slider:setValue(value + 1)
    end
    self._addButton:setSwallowTouches(false)

    self._subButton = ButtonLongPress.new("ui/team/button-sub.png")
    self:addChild(self._subButton)
    self._subButton.onClicked = function()
        local value = self._slider:getValue()
        if value <= 0 then
            return
        end
        self._slider:setValue(value - 1)
    end
    self._subButton:setPosition(cc.p(posX - 0.5 * (sliderSize.width + self._subButton:getContentSize().width) - paddingX, posY))
    self._subButton:setSwallowTouches(false)
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
        self:_setSelectedCount(value)
    end
    
    if self._valueChangedCallback then
        self._valueChangedCallback(value)
    end
end

function M:_createSelectedCountLabel()
    self._selectedCountLabel = CommonUI:createLabel("0", 40)
    self:addChild(self._selectedCountLabel)
    self._selectedCountLabel:setAnchorPoint(cc.p(0, 0.5))
    self._selectedCountLabel:setPosition(cc.p(self._addButton:getPositionX() + self._addButton:getContentSize().width * 0.5 + 20, self._addButton:getPositionY()))
end

function M:_setSelectedCount(count)
    self._selectedCount = count
    self._selectedCountLabel:setString("" .. count)
    if self._operateType == Enum.ResourceOperateType.Donate then
        local ratio = GuildDonateRatioConfigRead:getPersonalDonateRatio(self._resourceType)
        local donateValue = count * ratio
        local str = string.format("贡献：%d", donateValue)
        str = __Localized(str)
        self._donateLabel:setString(str)
    end
end

function M:_createInfoLabels()
    self._ownLabel = CommonUI:createLabel("拥有粮食:9999999", 24)
    Layout:layout(self._ownLabel, M.ResourceOperateCellSize, Layout.left_top, cc.p(30, 30))
    self:addChild(self._ownLabel)

    if self._operateType == Enum.ResourceOperateType.Donate then
        self:_createDonateInfoLabels()
    elseif self._operateType == Enum.ResourceOperateType.Save then
        self:_createSaveInfoLabels()
    elseif self._operateType == Enum.ResourceOperateType.Take then
        self:_createTakeInfoLabels()
    end
    
end

function M:_createDonateInfoLabels()
    self._donateLabel = CommonUI:createLabel("贡献:0", 24)
    Layout:layout(self._donateLabel, M.ResourceOperateCellSize, Layout.right_top, cc.p(30, 30))
    self:addChild(self._donateLabel)
end

function M:_createSaveInfoLabels()
    self._canSaveLabel = CommonUI:createLabel("还可存入:0", 24)
    Layout:layout(self._canSaveLabel, M.ResourceOperateCellSize, Layout.center_top, cc.p(30, 30))
    self:addChild(self._canSaveLabel)

    self._hasSaveLabel = CommonUI:createLabel("已存入:0", 24)
    Layout:layout(self._hasSaveLabel, M.ResourceOperateCellSize, Layout.right_top, cc.p(30, 30))
    self:addChild(self._hasSaveLabel)
end

function M:_createTakeInfoLabels()
    self._canTakeLabel = CommonUI:createLabel("可取出:999999", 24)
    Layout:layout(self._canTakeLabel, M.ResourceOperateCellSize, Layout.center_top, cc.p(30, 30))
    self:addChild(self._canTakeLabel)
end

function M:_getResourceName(id)
    return BackpackConfigRead:getName(id)
end

return M