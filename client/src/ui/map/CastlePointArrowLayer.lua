local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.CastlePointArrowLayer", function()
    return cc.Layer:create()
end)

-- 主城指示箭头layer
function M:ctor()
    self:_createArrow()
    self:_createDistanceLabel()
end

function M:_createArrow()
    self._arrow = Button.new("ui/map/map-direction.png")
    self:addChild(self._arrow)
    self._arrow:setPosition(cc.p(Screen.width * 0.5, Screen.height * 0.5))
    self._arrow.onClicked = function()
        local homeCoor = PlayerData:getHomeCoor()
        local homePosition = MapConfig:getPositionFromCoordinate(homeCoor)
        MapManager:getMapLayerManager():changeViewCenterToPosition(homePosition)
    end
end

function M:_createDistanceLabel()
    self._distanceLabel = CommonUI:createLabel("", 24)
    self:addChild(self._distanceLabel)
end

function M:showCastlePointArrow(centerPosition)
    local homeCoor = PlayerData:getHomeCoor()
    local homePosition = MapConfig:getPositionFromCoordinate(homeCoor)
    if self:_isInScreen(homePosition) then
        self._arrow:setVisible(false)
        self._distanceLabel:setVisible(false)
        return
    end
    self._arrow:setVisible(true)
    self._distanceLabel:setVisible(true)

    -- local centerPosition = MapConfig:getPositionFromCoordinate(viewCoor)
    local disX = homePosition.x - centerPosition.x
    local disY = homePosition.y - centerPosition.y
    local vec = cc.p(disX, disY)
    local radians = cc.pGetAngle(vec, cc.p(1, 0))
    local angle = radians * (180 / math.pi)
    self._arrow:setRotation(angle)

    local arrowSize = self._arrow:getContentSize()
    local posX = Screen.width * 0.5 + disX
    if posX < 0 then
        posX = arrowSize.width * 0.5
    elseif posX > Screen.width then
        posX = Screen.width - arrowSize.width * 0.5
    end

    local TabbarLayer = require("ui.tabbar.MainLayer")
    local MapTopLayer = require("ui.map.MapTopLayer")

    local topLayerHeight = MapTopLayer.MapTopLayerSize.height
    local bottomLayerHeight = TabbarLayer.TabbarLayerSize.height

    local posY = Screen.height * 0.5 + disY
    if posY < bottomLayerHeight then
        posY = bottomLayerHeight + arrowSize.width * 0.5
    elseif posY > Screen.height - topLayerHeight then
        posY = Screen.height - topLayerHeight - arrowSize.width * 0.5
    end
    self._arrow:setPosition(cc.p(posX, posY))
    
    local viewCoor = MapConfig:getCoordinateFromPosition(centerPosition)
    self:_updateDistanceLabel(angle, viewCoor, homeCoor)
end

function M:_updateDistanceLabel(angle, viewCoor, homeCoor)
    local posX, posY = self._arrow:getPosition()
    local coorDisX = math.abs(viewCoor.i - homeCoor.i)
    local coorDisY = math.abs(viewCoor.j - homeCoor.j)
    local coorDis = math.sqrt(coorDisX * coorDisX + coorDisY * coorDisY)
    coorDis = math.floor(coorDis)
    local coorDisStr = string.format("相距%d里路", coorDis)
    self._distanceLabel:setString(coorDisStr)
    if angle < -90 then
        self._distanceLabel:setRotation(angle + 180)
    elseif angle > 90 then
        self._distanceLabel:setRotation(angle - 180)
    else
        self._distanceLabel:setRotation(angle)
    end
    self._distanceLabel:setPosition(cc.p(posX , posY))
end

function M:_isInScreen(homePosition)
    local rect = MapConfig:getRectWithPosition(homePosition)
    return MapManager:getMapLayerManager():isRectVisible(rect)
end

return M