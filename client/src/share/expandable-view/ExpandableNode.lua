local M = class("share.expandable-view.ExpandableNode", function()
    return cc.Node:create()
end)

function M:ctor()
    self:init()
end

function M:init()
    self._nodeList = {}
    self._isExpanded = false
end

function M:insertNode(node)
    node:retain()
    table.insert(self._nodeList, node)
    return table.getn(self._nodeList)
end

function M:removeAllNodes()
    for _, node in ipairs(self._nodeList) do
        node:release()
    end
    self._nodeList = {}
end

function M:getNodeList()
    return self._nodeList
end

function M:setExpanded(isExpanded)
    self._isExpanded = isExpanded
end

function M:isExpanded()
    return self._isExpanded
end

return M
