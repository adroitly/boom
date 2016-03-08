local M = class("test-layer.TestLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    -- local backSprite = cc.Sprite:create("ui/common/BackgroundLayer.png")
    -- local backSpriteSize = backSprite:getContentSize()
    -- backSprite:setPosition(Screen.width / 2 , Screen.height / 2)
    -- self:addChild(backSprite)
    -- local node = require("ui.common.InputUI").new()
    -- self:addChild(node)
    -- node:setPlaceHolder("AAAAAAAAA")
    -- node:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
    -- node:setTouchSize(cc.size(Screen.width, Screen.height / 4))
    local viewSize = cc.size(Screen.width, Screen.height - 120)
    local gridView = GridView.new(viewSize, self, 4)
    gridView:setPosition(cc.p(0, 120))
    self:addChild(gridView)
    -- 按钮合集
    local layer = ButtonSetLayer.new({
        { "ui/login/login-up.png", nil, nil, "1", 30},
        { "ui/login/login-up.png", nil, nil, "2", 30},
        { "ui/login/login-up.png", nil, nil, "3", 30},
    })
    self:addChild(layer)
    layer.onClicked = function(button, index)
        print("clickIndex")
        local maxOffset = gridView:maxContainerOffset()
        local minOffset = gridView:minContainerOffset()
        gridView:setContentOffset(cc.p(maxOffset.x, maxOffset.y))
    end
    layer:setLayout(cc.size(Screen.width, 100), ButtonSetLayer.LayoutType.FromTopToBottom)
    layer:setPositionAtCenterAnchor(cc.p(Screen.cx, 100))
    -- Event:registerNodeEvent(self)
    -- TimerInterval:addTimer(self, 0.1)
end

function M:onGridViewCellCount()
    return 100
end

function M:onGridViewLineHeight()
    return 200
end

function M:onGridViewCellAtIndex(gridView, idx)
    local cell = gridView:dequeueCell()
    if not cell then
        cell = require("test-layer.TestCell").new()
    end
    cell:reload(idx)
    return cell
end

function M:onUpdate()

end

function M:onEnter()
end

function M:onExit()
    -- print("onExit()")
end

return M
