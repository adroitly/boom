local M = class("test-layer.TestAnchorPointInputLayer", function()
    return cc.Layer:create()
end)
function M:ctor()
    self:_createView()
end

function M:_createView()
    local layer = require("test-layer.TestBackgroundLayer").new()
    layer.onClicked = function(coordinate)
        mapLayerManager:changeViewCenterByTwoDCoor(coordinate.x, coordinate.y)
        self:removeFromParent()
    end
    local scrollView = cc.ScrollView:create(Screen.size)
    self:addChild(scrollView)
    local layerSize = layer:getContentSize()
    layer:setPosition(cc.p(layerSize.width / 2, Screen.cy))

    scrollView:getContainer():addChild(layer)
    scrollView:getContainer():setContentSize(layerSize)
    scrollView:setBounceable(false)
    scrollView:setContentOffset(scrollView:minContainerOffset())
end

return M
