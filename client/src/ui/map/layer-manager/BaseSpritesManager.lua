
local M = class("ui.map.layer-manager.BaseSpritesManager")

local function _newSpriteData(sprite, data)
    return { 
        sprite = sprite,
        data = data,
}
end

function M:ctor()
    self._datas = {}
    self._cacheData = {}

    self._spriteSize = cc.size(200, 200)
end

function M:init(mapLayer)
    assert(mapLayer and mapLayer.isNodeVisible)
    self._mapLayer = mapLayer
end

function M:updateData(data)
    local pos = self:cellPositionForData(data)
    assert(pos)

    local uniqueId = self:cellUniqueIdForData(data)
    assert(uniqueId)

    local spriteData = self:_findSpriteDataByUniqueId(uniqueId)
    if not spriteData then 
        local cacheData = table.remove(self._cacheData)
        if cacheData then 
            cacheData.uniqueId = uniqueId
            cacheData.data = data
            self._datas[uniqueId] = cacheData
            spriteData = cacheData
        else 
            local sprite = self:cellSpriteForData(data)
            assert(sprite)
            self._mapLayer:addChild(sprite)
         
            spriteData = _newSpriteData(sprite, data)
            self._datas[uniqueId] = spriteData
        end        
    end
    
    local sprite = spriteData.sprite
    sprite:setPosition(pos)
    self:cellReloadForData(data, sprite)
    sprite:setVisible(true)
end

function M:findSpriteByUniqueId(uniqueId)
    local spriteData = self:_findSpriteDataByUniqueId(uniqueId)
    if spriteData then 
        return spriteData.sprite
    end
end

function M:findDataByUniqueId(uniqueId)
    local spriteData = self:_findSpriteDataByUniqueId(uniqueId)
    if spriteData then 
        return spriteData.data
    end
end

function M:findDataByConditionFun(conditionFun)
    for _,value in pairs(self._datas) do
        local data = value.data
        if conditionFun(data) then
            return data
        end
    end
end

function M:findSpriteDataWithPoint(point)
    for _,value in pairs(self._datas) do
        local sprite = value.sprite
        local rect =  sprite:getBoundingBox()
        if cc.rectContainsPoint(rect, point) then 
            return sprite, value.data
        end
    end
end

function M:removeSpriteDataByUniqueId(uniqueId)
    local spriteData = self:_findSpriteDataByUniqueId(uniqueId)
    if spriteData then 
        self:_recoverData(spriteData, uniqueId)
    end
end

function M:_findSpriteDataByUniqueId(uniqueId)
    return self._datas[uniqueId]
end

-- 迭代遍历
function M:iterativeDatas(iterFun)
    for _,value in pairs(self._datas) do
        iterFun(value.data, value.sprite)
    end
end

function M:_recoverData(spriteData, key)
    local sprite = spriteData.sprite
    sprite:stopAllActions()
    sprite:setVisible(false)
    table.insert(self._cacheData, spriteData)
    self._datas[key] = nil
end

------------------------------------------
---- 以下必须继承使用
function M:cellPositionForData(data)
    assert(false)
end

function M:cellUniqueIdForData(data)
    assert(false)
end

function M:cellSpriteForData(data)
    assert(false)
end

function M:cellReloadForData(data, sprite)
    assert(false)
end

return M