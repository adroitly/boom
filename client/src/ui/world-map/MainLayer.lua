local BackgroundLayer = require("ui.common.BackgroundLayer")
local mapLayerManager = MapManager:getMapLayerManager()
local M = class("ui.world-map.MainLayer", function()
    return cc.Layer:create()
end)

local m_sketchIcon =
{
    [1] = { fileName = "ui/world-map/worldMap-icon-01.png", name = __Localized("我的主城") },
    [2] = { fileName = "ui/world-map/worldMap-icon-02.png", name = __Localized("收藏位置") },
    [3] = { fileName = "ui/world-map/worldMap-icon-16000.png", name = __Localized("小型城池") },
    [4] = { fileName = "ui/world-map/worldMap-icon-16100.png", name = __Localized("中型城池") },
    [5] = { fileName = "ui/world-map/worldMap-icon-16200.png", name = __Localized("大型城池") },
}

function M:ctor(nowCoordinate)
    local showCoordinate = nil
    if nowCoordinate then
        showCoordinate = cc.p(nowCoordinate.i, nowCoordinate.j)
    end
    self:_createBackground()
    self:_createShowMap(showCoordinate)
    self:_createSketch()
end

function M:_createShowMap(nowCoordinate)
    local layer = require("ui.world-map.layers.ShowWorldLayer").new()
    layer.onClicked = function(coordinate)
        mapLayerManager:changeViewCenterByTwoDCoor(coordinate.x, coordinate.y)
        self:removeFromParent()
    end
    local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight)
    local scrollView = cc.ScrollView:create(viewSize)
    self:addChild(scrollView)
    local layerSize = layer:getContentSize()
    layer:setPosition(cc.p(layerSize.width / 2, layerSize.height / 2))

    scrollView:getContainer():addChild(layer)
    scrollView:getContainer():setContentSize(layerSize)
    scrollView:setMinScale(layer:getMinScale())
    scrollView:setMaxScale(2.0)
    scrollView:setBounceable(false)
    local ratio = layer:getCoordinateRatio(nowCoordinate)
    local minOffset = scrollView:minContainerOffset()
    local maxOffset = scrollView:maxContainerOffset()
    local offset = cc.p((minOffset.x + maxOffset.x) * ratio.x, (minOffset.y + maxOffset.y) * ratio.y)
    scrollView:setContentOffset(offset)
end

function M:_createSketch()
    for index,data in pairs(m_sketchIcon) do
        self:_createSketchShow(index, data)
    end
end

function M:_createSketchShow(index, data)
    local sp = cc.Sprite:create(data.fileName)
    self:addChild(sp)
    local label = CommonUI:createLabel(data.name, 24)
    self:addChild(label)
    sp:setPosition(cc.p(22, Screen.height - BackgroundLayer.TitleHeight - 35 * index))
    local labelSize = label:getContentSize()
    label:setPosition(cc.p(44 + labelSize.width / 2, Screen.height - BackgroundLayer.TitleHeight - 35 * index))
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("世界地图"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end
return M
