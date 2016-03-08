local BackgroundLayer = require("ui.common.BackgroundLayer")
local FamousCityConfig = require("config.FamousCityConfig")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local MapConfig = require("ui.map.data-manager.MapConfig")
local CollectConfig = require("ui.collection.data-manager.CollectConfig")
local CollectDataManager = require("ui.collection.data-manager.CollectDataManager")
local M = class("ui.world-map.layers.ShowWorldLayer", function()
    return cc.Layer:create()
end)

local function _getHomeCoordinate()
    local homeCoor = PlayerData:getHomeCoor()
    local pos = MapConfig:localTo2D(homeCoor)
    local coordinate = cc.p(pos.i, pos.j)
    return coordinate
end

function M:getMinScale()
    local viewHeight = Screen.height - BackgroundLayer.TitleHeight
    local viewWidth = Screen.width
    local scaleY = viewHeight / self._contentSize.height
    local scaleX = viewWidth / self._contentSize.width
    local scale = scaleX > scaleY and scaleX or scaleY
    if scale > 1 then
        scale = 1
    elseif scale < 0.7 then
        scale = 0.7
    end
    return scale
end

function M:getCoordinateRatio(coordinate)
    local localCoor = coordinate or _getHomeCoordinate()
    local coor = self:_twoToLocal(localCoor)
    return cc.p(coor.x / self._contentSize.width, coor.y / self._contentSize.height)
end

function M:ctor()
    self:_createBackground()
    Event:registerNodeEvent(self)
end


function M:onEnterTransitionFinish()
    Touch:registerTouchOneByOne(self, false)
    self:_createFamousIcon()
    self:_createSaveIcon()
    self:_createOwnCity()
end


function M:onTouchBegan(touch, event)
    self._isMoveing = false
    return true
end

function M:onTouchMoved(touch, event)
    self._isMoveing = true
end

function M:onTouchEnded(touch, event)
    if self._isMoveing then
        return
    end
    local pt = touch:getLocation()
    if pt.y >= Screen.height - BackgroundLayer.TitleHeight then
        return
    end
    pt = self:getParent():convertToNodeSpace(pt)
    local coordinate = self:_localTo2D(pt)
    self.onClicked(coordinate)
end

function M:_createBackground()
    local bg = cc.Sprite:create("ui/world-map/worldMap.jpg")
    self._contentSize = bg:getContentSize()
    self:setContentSize(self._contentSize)
    self:addChild(bg)
end

function M:_createFamousIcon()
    for key,famousCityData in pairs(FamousCityConfig) do
        local coordinate = FamousCityConfigReader:getCoordinate(key)
        local resId = FamousCityConfigReader:getResId(key)
        local name = FamousCityConfigReader:getName(key)
        self:_createIcon(string.format("ui/world-map/worldMap-icon-%d.png", resId), cc.p(coordinate[1], coordinate[2]), name)
    end
end

function M:_createIcon(fileName, coordinate, name)
    local position = self:_twoToLocalPotion(coordinate)
    local button = ButtonText.new(fileName)
    button:setSwallowTouches(false)
    self:addChild(button)
    if name then
        button:setLabel(name, 12)
    end
    button:setPosition(cc.p(position.x, position.y))
    button.onClicked = function()
        self.onClicked(coordinate)
    end
end

function M:_twoToLocalPotion(coordinate)
    if nil == self._position then
        local x, y = self:getPosition()
        self._position = cc.p(x, y)
    end
    return cc.p(coordinate.x * 1.4 - self._position.x, coordinate.y * 1.4 - self._position.y)
end

function M:_localTo2D(localCoor)
    return cc.p(localCoor.x / 1.4 , localCoor.y / 1.4)
end
function M:_twoToLocal(coordinate)
    return cc.p(coordinate.x * 1.4 , coordinate.y * 1.4)
end

function M:_createOwnCity()
    local coordinate = _getHomeCoordinate()
    self:_createIcon("ui/world-map/worldMap-icon-01.png", coordinate)
end

--[[
    Friend      = 1,
    Enemy       = 2,
    Resource    = 3,
    Mark        = 4,
]]

function M:_createSaveIcon()
    local friendList = CollectDataManager:getDataListByType(CollectConfig.CollectType.Friend)
    local enemyList = CollectDataManager:getDataListByType(CollectConfig.CollectType.Enemy)
    local resourceList = CollectDataManager:getDataListByType(CollectConfig.CollectType.Resource)
    local markList = CollectDataManager:getDataListByType(CollectConfig.CollectType.Mark)
    self:_createCollectIcon(friendList)
    self:_createCollectIcon(enemyList)
    self:_createCollectIcon(resourceList)
    self:_createCollectIcon(markList)
end

function M:_createCollectIcon(collectDataList)
    for _,collectData in pairs(collectDataList) do
        local coor = collectData:getCoor()
        self:_createIcon("ui/world-map/worldMap-icon-02.png", cc.p(coor.i, coor.j))
    end
end

return M
