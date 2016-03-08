local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local M = class("test-layer.TestBackgroundLayer", function()
    return cc.Layer:create()
end)

local m_keyList =
{
    building = "building",
}
function M:ctor()
    self:_createBg()
    self:_createInput()
    self:_createSprite()
end

function M:_createInput()
    local input = require("ui.common.InputUI").new()
    self:addChild(input)
    input:setTextColor(cc.c4b(255, 255, 255, 255))
    input:setListener(self)
    input:setPosition(cc.p(Screen.width + 200, 0))
    input:setPlaceHolder("请输入ID")
    input:setPlaceHolderColor(Enum.Color.Yellow)
    input:setTextColor(Enum.Color.Black)
    -- input:setString("请输入ID")
end

function M:_getFrameValue(buildingId)
    if self:_isFamousCity(buildingId) then
        return FamousCityConfigReader:getResId(buildingId)
    else
        return buildingId
    end
end

function M:_isFamousCity(buildingId)
    if buildingId <= 14010 then
        buildingId = 14000
    end
    return ResourcePointUtils:isFamousCity(buildingId)
end

function M:_isCastle(buildingId)
    return buildingId >= 14000 and buildingId <= 14009
end


function M:onInsertEnd(inputUI)
    local text = tonumber(inputUI:getString())
    local frameText = self:_getFrameValue(text) .. ".png"
    local frame = nil
    for _,value in pairs(m_keyList) do
        frame = CommonUI:createSpriteFrameTinyName(value, frameText)
        if frame then
            local anchorPoint = cc.p(0.5, 0.5)
            if false == self:_isFamousCity(text) then
                local buildingId = math.floor(text / 10) * 10
                local level = text % 10 or 0
                level  = level + 1
                if self:_isCastle(text) then
                    anchorPoint = ResourcePointUtils:getBuildingAnchorPoint(buildingId, level)
                else
                    anchorPoint = ResourcePointUtils:getBuildingAnchorPoint(text, 1)
                end
            else
                anchorPoint = ResourcePointUtils:getBuildingAnchorPoint(text, 1)
            end
            self._sprite:setSpriteFrame(frame)
            self._sprite:setAnchorPoint(anchorPoint)
        end
    end
end

function M:_createSprite()
    self._sprite = cc.Sprite:create()
    self._sprite:setPosition(cc.p(Screen.width / 2 + 130, 0))
    self:addChild(self._sprite)
end

function M:_createBg()
    local bg = cc.Sprite:create("ui/map/map-tile.jpg")
    self:addChild(bg)
    self:setContentSize(bg:getContentSize())
end
return M
