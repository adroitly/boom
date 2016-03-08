local BackpackConfigRead= require("ui.backpack.data-manager.BackpackConfigRead")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local SoldierConfigReader= require("config-reader.SoldierConfigReader")
local ItemDataFrame = require("ui.backpack.data-manager.ItemDataFrame")
local M = class("ui.backpack.layer-manager.ItemIconButton", function()
    return Button.new("ui/backpack/backpack-item-bg.png")
end)

function M:ctor()
    self:_init()
end
--[[
resourceType请查看Enum的resourceTypeId
itemId就是资源ID，如18600
]]
function M:reloadByResoure(resourceType, itemId, number, level)
    assert(resourceType and itemId)
    self._itemId = itemId
    self._resourceId = resourceType
    self._number = number or 1
    self._level = level or 1
    self:_reloadLayer()
end

function M:setNumberLabelVisible(visible)
    self._numberLabel:setVisible(visible)
end

function M:setLevelLabelVisible(visible)
    self._levelLabel:setVisible(visible)
end

function M:_reloadLayer()
    self:_updateLabels()
    self:_updateIcon()
end

function M:_updateLabels()
    self._numberLabel:setString(self:_getNumber())
    self._nameLabel:setString(self:_getName())
    local resourceId = self:_getResourceId()
    if resourceId ~= Enum.ResourceTypeId.Hero then
        self._levelLabel:setVisible(false)
    else
        self._levelLabel:setVisible(true)
        self._levelLabel:setString(self:_getLevel())
    end
end

function M:_updateIcon()
    local spriteFrame = ItemDataFrame:getSpriteFrame(self:_getResourceId(), self:_getItemId())
    self:changeNormalSpriteWithFrame(spriteFrame)
end

function M:_init()
    self:_createIconNameLabel()
    self:_createLevelLabel()
    self:_createNumberLabel()
    self:setSwallowTouches(false)
end

function M:_getItemId()
    return self._itemId
end

function M:_getResourceId()
    return self._resourceId
end

function M:_getName()
    local resourceId = self:_getResourceId()
    if resourceId == Enum.ResourceTypeId.Item then
        return BackpackConfigRead:getName(self:_getItemId())
    elseif resourceId == Enum.ResourceTypeId.Soldier then
        return SoldierConfigReader:getName(self:_getItemId())
    elseif resourceId == Enum.ResourceTypeId.Hero then
        return HeroConfigRead:getName(self:_getItemId())
    end
end

function M:_getNumber()
    return self._number
end

function M:_getLevel()
    return self._level
end

function M:_createNumberLabel()
    self._numberLabel = CommonUI:createLabel("1", 24)
    self._numberLabel:setLocalZOrder(1)
    self:addChild(self._numberLabel)
    Layout:layout(self._numberLabel, self:getContentSize(), Layout.right_bottom)
end

function M:_createIconNameLabel()
    self._nameLabel = CommonUI:createLabel("test", 24)
    self._nameLabel:setLocalZOrder(1)
    self:addChild(self._nameLabel)
    Layout:layout(self._nameLabel, self:getContentSize(), Layout.center_top)
end

function M:_createLevelLabel()
    self._levelLabel = CommonUI:createLabel("test", 24)
    self._levelLabel:setLocalZOrder(1)
    self:addChild(self._levelLabel)
    Layout:layout(self._levelLabel, self:getContentSize(), Layout.center_bottom)
end

return M