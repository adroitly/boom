local M = {}

-------- 1
local kMapMainLayerTag = 100001
function M:loadMapMainLayer(msgTable)
    local mapLayer = require("ui.map.MainLayer").new(msgTable)
    mapLayer:setTag(kMapMainLayerTag)
    Director:replaceSceneWithLayer(mapLayer)
end

function M:getMapMainLayer()
    local scene = cc.Director:getInstance():getRunningScene()
    local mapLayer = scene:getChildByTag(kMapMainLayerTag)
    assert(mapLayer)
    return mapLayer
end

-------- 2
function M:getMapDataManager()
    local mapLayer = self:getMapMainLayer()
    return mapLayer:getMapDataManager()
end

function M:getMapLayerManager()
    local mapLayer = self:getMapMainLayer()
    return mapLayer:getMapLayerManager()
end

function M:getArmyLeadLayer()
    local mapLayer = self:getMapMainLayer()
    return mapLayer:getArmyLeadLayer()
end

function M:getCoordinateLayer()
    local mapLayer = self:getMapMainLayer()
    return mapLayer:getCoordinateLayer()
end

function M:getCastlePointArrowLayer()
    local mapLayer = self:getMapMainLayer()
    return mapLayer:getCastlePointArrowLayer()
end

-------- 3 - data
function M:getArmyDataManager()
    return self:getMapDataManager():getArmyDataManager()
end

function M:getRandomResourceManager()
    return self:getMapDataManager():getRandomResourceManager()
end

function M:getBuildingDataManager()
    return self:getMapDataManager():getBuildingDataManager()
end

-------- 3 - layer
function M:getArmySpriteManager() 
    return self:getMapLayerManager():getArmySpriteManager()
end

function M:getRandomResourceSpriteManager()
    return self:getMapLayerManager():getRandomResourceSpriteManager()
end

function M:getBuildingSpriteManager()
    return self:getMapLayerManager():getBuildingSpriteManager()
end

-------- 3 - other
function M:removeDialogLayer()
    local mapLayerManager = self:getMapLayerManager()
    return mapLayerManager:removeDialogLayer()
end

return M