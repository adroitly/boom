local M = class("share.expandable-view.ExpandableView", function(viewSize)
    return cc.ScrollView:create(viewSize)
end)

local function _assert(delegate)
    assert(delegate and delegate.onExpandableViewCount and delegate.onExpandableViewAtIndex)
end

function M:ctor(viewSize, delegate)
    _assert(delegate)
    self._expandableNodeList = {}
    self:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
    self:setViewSize(viewSize)
    Event:registerNodeEvent(self)
    self:_initData(delegate)
end

function M:onExit()
    self:removeAllExpandableNodes()
end

function M:expand(idx)
    self._expandableNodeList[idx]:setExpanded(true)
end

function M:collapse(idx)
    self._expandableNodeList[idx]:setExpanded(false)
end

function M:getExpandableNodeAtIdx(idx)
    return self._expandableNodeList[idx]
end

function M:insertExpandableNode(expandableNode)
    expandableNode:retain()
    table.insert(self._expandableNodeList, expandableNode)
    return table.getn(self._expandableNodeList)
end

function M:removeExpandableNode(idx)
    local node = self._expandableNodeList[idx]
    node:removeAllNodes()
    node:release()
    table.remove(self._expandableNodeList, idx)
end

function M:removeAllExpandableNodes()
    for idx, node in ipairs(self._expandableNodeList) do
        node:removeAllNodes()
        node:release()
    end
    self._expandableNodeList = {}
end

function M:getAllExpandableNodes()
    return self._expandableNodeList
end

function M:reloadData()
    self:_updateNodesPosition()
    local newHeight = self:getContentSize().height
    local offsetPos = cc.p(0, self:getContentOffset().y - newHeight)
    self:setContentOffset(offsetPos)
    self:_relocateContainer()
end

function M:_relocateContainer()
    local min = self:minContainerOffset()
    local max = self:maxContainerOffset()
    local oldPointY = self:getContainer():getPositionY()
    local newY = oldPointY
    newY = math.min(newY, max.y)
    newY = math.max(newY, min.y)
    if newY ~= oldPointY then
        self:setContentOffset(cc.p(0, newY));
    end
end

function M:_updateNodesPosition()
    self:getContainer():removeAllChildren()
    local expandableNodeCount = table.getn(self._expandableNodeList)
    if expandableNodeCount == 0 then
        return
    end
    local allNodeHeight = 0
    for _, expandableNode in ipairs(self._expandableNodeList) do
        allNodeHeight = allNodeHeight + expandableNode:getContentSize().height
        if expandableNode:isExpanded() then
            local nodeList = expandableNode:getNodeList()
            for __, node in ipairs(nodeList) do
                allNodeHeight = allNodeHeight + node:getContentSize().height
            end
        end
    end
    local viewSize = self:getViewSize()
    allNodeHeight = math.max(viewSize.height, allNodeHeight)
    self:setContentSize(cc.size(viewSize.width, allNodeHeight))
    for _, expandableNode in ipairs(self._expandableNodeList) do
        allNodeHeight = allNodeHeight - expandableNode:getContentSize().height
        expandableNode:setAnchorPoint(cc.p(0, 0))
        expandableNode:setPosition(cc.p(0, allNodeHeight))
        self:getContainer():addChild(expandableNode)
        if expandableNode:isExpanded() then
            local nodeList = expandableNode:getNodeList()
            for __, node in ipairs(nodeList) do
                allNodeHeight = allNodeHeight - node:getContentSize().height
                node:setAnchorPoint(cc.p(0, 0))
                node:setPosition(cc.p(0, allNodeHeight))
                self:getContainer():addChild(node)
            end
        end
    end
end

function M:_initData(delegate)
    local count = delegate:onExpandableViewCount(self)
    for index=1,count do
        local node = delegate:onExpandableViewAtIndex(self, index)
        self:insertExpandableNode(node)
    end
end

return M

