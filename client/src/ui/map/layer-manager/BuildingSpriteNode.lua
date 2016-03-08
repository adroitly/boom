local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local CityDefConfigReader = require("config-reader.CityDefConfigReader")
local BattleUtils = require("ui.map.logic.BattleUtils")

local M = class("ui.map.layer-manager.CastleSpriteNode", function()
    return cc.Node:create()
end)

local function _getBuildingSpriteFrame(buildingData)
    local resId = ResourcePointUtils:getBuildingResourceIdByBuildingData(buildingData)
    local resIdStr = string.format("%d.png", resId)
    local frame = CommonUI:createSpriteFrameTinyName("building", resIdStr)
    if frame then
        return frame
    end

    local text = string.format("找不到建筑物类型id=%d", buildingData:getBuildingId())
    CommonUI:lightTips(text)
    Print:Table(buildingData, "错误提示，building data =")

    return CommonUI:createSpriteFrameTinyName("building", "14000.png")
end

local function _getBuildingAnchorPoint(buildingData)
    return ResourcePointUtils:getBuildingAnchorPointByBuildingData(buildingData)
end

function M:ctor()
    self._sprite = cc.Sprite:create()
    self:addChild(self._sprite)

    local size = self._sprite:getContentSize()
    self:setContentSize(size)
    self:setAnchorPoint(cc.p(0.5, 0.5))
    self._sprite:setPosition( cc.p(size.width/2, size.height/2) )

    self._userNameLabel = CommonUI:createLabel(" ", 26)
    self:addChild(self._userNameLabel)
    self._userNameLabel:setPosition(cc.p(0, -60))
end

function M:reloadData(buildingData)
    local frame = _getBuildingSpriteFrame(buildingData)
    self._sprite:setSpriteFrame(frame)
    local anchorPoint = _getBuildingAnchorPoint(buildingData)
    self._sprite:setAnchorPoint(anchorPoint)

    local x,y = self:getPosition()
    self:setLocalZOrder(Enum.ZOrder.BuildingMax - y)

    local text = buildingData:getOwnerName()
    self._userNameLabel:setString(text)

    self:checkCityDef(buildingData)
end

function M:checkCityDef(buildingData)
    local remainCityDef = buildingData:getCityDef()
    local buildingId = buildingData:getBuildingId()
    local totalCityAmount = CityDefConfigReader:getCityAmount(buildingId)
    if remainCityDef == totalCityAmount then
        self:_removeCityDefLostEeffect()
        return
    end
    self:_playCityDefLostEffect(buildingData)
end

function M:_playCityDefLostEffect(buildingData)
    self:_removeCityDefLostEeffect()
    self._defLostEffectSprite = BattleUtils:getCityDefLostEffectAnimateSprite(buildingData)
    self:addChild(self._defLostEffectSprite)
end

function M:_removeCityDefLostEeffect()
    if self._defLostEffectSprite then
        self._defLostEffectSprite:removeFromParent()
        self._defLostEffectSprite = nil
    end
end

return M