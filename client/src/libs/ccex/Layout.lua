
local M = {}

M.left_top      = cc.p(0.0, 1.0)
M.left_center   = cc.p(0.0, 0.5)
M.left_bottom   = cc.p(0.0, 0.0)
M.center_bottom = cc.p(0.5, 0.0)
M.center_top    = cc.p(0.5, 1.0)
M.right_top     = cc.p(1.0, 1.0)
M.right_center  = cc.p(1.0, 0.5)
M.right_bottom  = cc.p(1.0, 0.0)
M.center        = cc.p(0.5, 0.5)

local function compute_point_offset(node, anchor)
    local size = node:getContentSize()
    local nodeAnchor = node:isIgnoreAnchorPointForPosition() and cc.p(0, 0) or node:getAnchorPoint() 
    local tmp = cc.pSub(anchor, nodeAnchor) 
    local x = size.width * node:getScaleX() * tmp.x
    local y = size.height * node:getScaleY() * tmp.y
    return cc.p(x, y)
end

local function alignNodesVerticallyWithPadding(nodes, start, padding)
    for _, node in ipairs(nodes) do
        M:setLocation(node, M.center_top, start)
        local height = node:getContentSize().height * node:getScaleY()
        start.y = start.y - height - padding
    end
end

local function alignNodesHWithPadding(nodes, start, padding)
    for _, node in ipairs(nodes) do
        M:setLocation(node, M.left_center, start)
        local width = node:getContentSize().width * node:getScaleX()
        start.x = start.x + width + padding
    end
end

local function alignNodesVerticallyWithRange(nodes, startV, endV)
    local height = 0
    for _, node in ipairs(nodes) do
        height = height + node:getContentSize().height
    end

    local totalHeight = math.abs(endV.y - startV.y)
    local padding = 0
    if #nodes > 1 then
        padding = (totalHeight - height) / (#nodes - 1)
    end
    alignNodesVerticallyWithPadding(nodes, startV, padding)
end

local function alignNodesHWithRange(nodes, startV, endV)
    local width = 0
    for _, node in ipairs(nodes) do
        width = width + node:getContentSize().width
    end

    local totalWidth = math.abs(endV.x - startV.x)
    local padding = 0
    if #nodes > 1 then
        padding = (totalWidth - width) / (#nodes - 1)
    end
    alignNodesHWithPadding(nodes, startV, padding)
end

local function adjust_offset(x, b)
    if b == 0.5 then
        return 0
    end
    return b < 0.5 and x or -x
end

local function parse_offset(edge, node_anchor)
    if type(edge) == "table" then
        local x = node_anchor.x < 0.5 and edge.x or -edge.x
        local y = node_anchor.y < 0.5 and edge.y or -edge.y
        return cc.p(x, y)
    end
    local x = adjust_offset(edge, node_anchor.x)
    local y = adjust_offset(edge, node_anchor.y)
    return cc.p(x, y)
end



function M:getLocation(node, anchor)
    local offset = compute_point_offset(node, anchor)
    return cc.pAdd(cc.p(node:getPosition()), offset)
end

function M:setLocation(node, anchor, location)
    local offset = compute_point_offset(node, anchor)
    node:setPosition(cc.pSub(location, offset))
end

function M:getFrame(node)
    local pos = M:getLocation(node, cc.p(0, 0))
    local size = node:getContentSize()
    size.width = size.width * node:getScaleX()
    size.height = size.height * node:getScaleY()

    if size.width < 0 then 
        pos.x = pos.x + size.width
        size.width = -size.width 
    end 
    if size.height < 0 then 
        pos.y = pos.y + size.height 
        size.height = -size.height 
    end 
    
    return cc.rect(pos.x, pos.y, size.width, size.height)
end

function M:layout(node, ref, anchor, edge)
    local ref_point = nil
    local node_anchor = nil

    if type(ref) == "table" and ref.width and ref.height then
        ref_point = cc.p(ref.width * anchor.x, ref.height * anchor.y)
        node_anchor = anchor
    else
        ref_point = M:getLocation(ref, anchor)
        node_anchor = cc.p(1.0 - anchor.x, 1.0 - anchor.y)
    end

    if edge then
        local offset = parse_offset(edge, node_anchor)
        ref_point = cc.pAdd(ref_point, offset)
    end

    M:setLocation(node, node_anchor, ref_point)
end

function M:alignNodesWithPadding(nodes, start, padding, mode)
    if mode == "v" then
        alignNodesVerticallyWithPadding(nodes, start, padding)
    elseif mode == "h" then
        alignNodesHWithPadding(nodes, start, padding)
    end
end


return M
