local ExpandableView = require("share.expandable-view.ExpandableView")
local OccupiedBuildingTitleNode = require("ui.produce.layer-manager.OccupiedBuildingTitleNode")
local MapConfig = require("ui.map.data-manager.MapConfig")
local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local M = class("ui.produce.layer-manager.OccupiedBuildingView", function()
    return cc.Node:create()
end)

local function _addDataToListByBuildingId(buildingId, list, data)
    if ResourcePointUtils:isCastleType(buildingId) then
        table.insert(list, 1, data)
    else
        table.insert(list, data)
    end
end

function M:ctor(viewSize, produceType)
    self:setContentSize(viewSize)
    self._produceType = produceType
    self:_initProduceData()
    self:_createExpandableView()
end

function M:updateView()
    self:_initProduceData()
    local nodeList = self._expandableView:getAllExpandableNodes()
    local nodeCount = table.getn(nodeList)
    local dataCount = table.getn(self._produceBuildingDataList)
    for k, buildingData in ipairs(self._produceBuildingDataList) do
        local titleNode = self._expandableView:getExpandableNodeAtIdx(k)
        titleNode:reset(buildingData, self._produceType)
    end
    local contentOffset = self._expandableView:getContentOffset()
    self._expandableView:reloadData()
    self._expandableView:setContentOffset(contentOffset)
end

function M:_createTopTitle()
    self._topTitle = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(self._topTitle)
    Layout:layout(self._topTitle, self:getContentSize(), Layout.center_top)
    local title = CommonUI:createLabel("已占领兵营", 40)
    self._topTitle:addChild(title)
    Layout:layout(title, self._topTitle:getContentSize(), Layout.center)
end

function M:_createNodeTitle(tag, name, pos)
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    local nameLabel = CommonUI:createLabel(name, 30)
    background:addChild(nameLabel)
    Layout:layout(nameLabel, background:getContentSize(), Layout.left_center, cc.p(40, 0))

    local posStr = string.format("坐标点：%d,%d", pos.x, pos.y)
    local posLabel = CommonUI:createLabel(posStr, 30)
    background:addChild(posLabel)
    Layout:layout(posLabel, background:getContentSize(), Layout.center)

    local expandedButton = CommonUI:createTextButton(background, "", "ui/city/arrow.png")
    Layout:layout(expandedButton, background:getContentSize(), Layout.right_center, cc.p(40, 0))
    expandedButton:setTag(tag)
    expandedButton:setRotation(270)
    expandedButton:setZoomOnTouchDown(false)
    expandedButton.onClicked = function(sender)
        self:_onButtonClick(sender)
    end
    return background
end

function M:_initProduceData()
    self._produceBuildingDataList = {}
    local buildingDataList = ProduceBuildingDataManager:getProduceBuildingDataList()
    for _, data in pairs(buildingDataList) do
        local buildingId = data:getBuildingId()
        local buildingType = BuildingConfigReader:getBuildingType(buildingId)
        if self._produceType == Enum.ProduceType.Soldier and
            self:_isProduceSoldier(buildingType) then
            _addDataToListByBuildingId(buildingId, self._produceBuildingDataList, data)
        end
        if self._produceType == Enum.ProduceType.Resource and
            self:_isProduceResource(buildingType) then
            _addDataToListByBuildingId(buildingId, self._produceBuildingDataList, data)
        end
    end
end

function M:_isProduceSoldier(buildingType)
    if buildingType == Enum.BuildingType.Camp or 
        buildingType == Enum.BuildingType.FamousCity or 
        buildingType == Enum.BuildingType.Castle then
        return true
    end
    return false
end

function M:_isProduceResource(buildingType)
    if buildingType == Enum.BuildingType.FamousCity or 
        buildingType == Enum.BuildingType.Castle or 
        buildingType == Enum.BuildingType.ResourcePoint then
        return true
    end
    return false
end

function M:_createExpandableNode(idx, buildingData)
    local node = OccupiedBuildingTitleNode.new(buildingData, self._produceType)
    node:setTag(idx)
    node:setClickCallback(function(sender)
        self:_onButtonClick(sender)
    end)
    return node
end

function M:onExpandableViewCount(expandableView)
    return table.getn(self._produceBuildingDataList)
end

function M:onExpandableViewAtIndex( expandableView, index )
    local buildingData =  self._produceBuildingDataList[index]
    local expandableNode = self:_createExpandableNode(index, buildingData)
    if ResourcePointUtils:isCastleType(buildingData:getBuildingId()) then
        expandableNode:setExpanded(true)
    end
    return expandableNode
end

function M:_createExpandableView()
    local tempSprite = cc.Sprite:create("ui/mail/mail-title-bg.png")
    local titleSize = tempSprite:getContentSize()
    local viewSize = cc.size(titleSize.width, self:getContentSize().height)
    self._expandableView = ExpandableView.new(viewSize, self)
    self._expandableView:reloadData()
    self:addChild(self._expandableView)
    local posX = 0.5 * (self:getContentSize().width - titleSize.width)
    local posY = 0.5 * (self:getContentSize().height - viewSize.height)
    self._expandableView:setPosition(cc.p(posX, posY))
end

function M:_onButtonClick(sender)
    local tag = sender:getTag()
    local expandableNode = self._expandableView:getExpandableNodeAtIdx(tag)
    local isExpanded = expandableNode:isExpanded()
    if isExpanded then
        self._expandableView:collapse(tag)
    else
        self._expandableView:expand(tag)
    end
    self._expandableView:reloadData()
    
end

return M