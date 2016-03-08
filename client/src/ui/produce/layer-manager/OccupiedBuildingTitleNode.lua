local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local ExpandableNode = require("share.expandable-view.ExpandableNode")
local ProduceSoldierNode = require("ui.produce.layer-manager.ProduceSoldierNode")
local ProduceResourceNode = require("ui.produce.layer-manager.ProduceResourceNode")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.produce.layer-manager.OccupiedBuildingTitleNode", ExpandableNode)

function M:reset(buildingData, produceType)
    self._buildingData = buildingData
    self:_initNodes(produceType)
end

function M:ctor(buildingData, produceType)
    ExpandableNode.init(self)
    self._buildingData = buildingData
    self:_createBackground()
    self:_createInfoLabels()
    self:_createExpandableArrow()
    self:_initNodes(produceType)
    
end

function M:setClickCallback(callback)
    self._callback = callback
end

function M:setTag(tag)
    cc.Node.setTag(self, tag)
    self._background:setTag(tag)
    -- self._expandableButton:setTag(tag)
end

function M:setExpanded(isExpanded)
    ExpandableNode.setExpanded(self, isExpanded)
    self._expandableButton:setRotation(isExpanded and 90 or 270)
end

function M:_createBackground()
    self._background = CommonUI:createTextButton(self, "", "ui/mail/mail-title-bg.png")
    self._background:setZoomOnTouchDown(false)
    local size = self._background:getContentSize()
    self:setContentSize(size)
    self._background:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
    self._background.onClicked = function(sender)
        if self._callback then
            self._callback(sender)
        end
    end
end

function M:_createInfoLabels()
    local buildingId = self._buildingData:getBuildingId()
    local buildingName = BuildingConfigReader:getName(buildingId)

    local size = self:getContentSize()
    local nameStr = buildingName
    local nameLabel = CommonUI:createLabel(nameStr, 30)
    self:addChild(nameLabel)
    Layout:layout(nameLabel, size, Layout.left_center, cc.p(50, 0))

    local localX, localY = self._buildingData:getLocalCoor()
    local coor = MapConfig:localTo2D({i = localX, j = localY})
    local posNameStr = string.format("坐标点：%d,%d", coor.i, coor.j)
    local posNameLabel = CommonUI:createLabel(posNameStr, 30)
    self:addChild(posNameLabel)
    Layout:layout(posNameLabel, size, Layout.center)
end

function M:_initNodes(produceType)
    self:removeAllNodes()
    if produceType == Enum.ProduceType.Resource then
        self:_initResourceDataNodes()
    elseif produceType == Enum.ProduceType.Soldier then
        self:_initSoldierDataNodes()
    end
end

function M:_initSoldierDataNodes()
    local soldierDataList = self._buildingData:getProduceSoliderDataList()
    for _, soldierData in pairs(soldierDataList) do
        local node = ProduceSoldierNode.new(soldierData)
        self:insertNode(node)
    end
end

function M:_initResourceDataNodes()
    local resourceDataList = self._buildingData:getProduceResourceDataList()
    for _, resourceData in pairs(resourceDataList) do
        local node = ProduceResourceNode.new(resourceData)
        self:insertNode(node)
    end
end

function M:_createExpandableArrow()
    self._expandableButton = cc.Sprite:create("ui/city/arrow.png")
    self:addChild(self._expandableButton)
    self._expandableButton:setRotation(270)
    Layout:layout(self._expandableButton, self:getContentSize(), Layout.right_center, cc.p(40, 0))
end

return M