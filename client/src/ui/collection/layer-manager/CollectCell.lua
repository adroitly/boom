local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local RichLabel = require("ui.common.richlabel.RichLabel")
local ElementText = require("ui.common.richlabel.ElementText")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.collection.layer-manager.CollectCell", GridViewCell)

local kCollectInfoDelete = "collect_info_delete"
M.CollectCellSize = cc.size(752, 193)

function M:reset(collectData)
    self._collectData = collectData
    local buildingId = collectData:getBuildingId()
    local buildingLevel = collectData:getBuildingLevel()
    local resId = ResourcePointUtils:getBuildingResourceId(buildingId, buildingLevel)
    local resIdStr = string.format("%d.png", resId)
    local frame = CommonUI:createSpriteFrameTinyName("building", resIdStr)
    if not frame then
        frame = CommonUI:createSpriteFrameTinyName("building", "14000.png")
    end
    self._iconSprite:setSpriteFrame(frame)
    Layout:layout(self._iconSprite, M.CollectCellSize, Layout.left_bottom, cc.p(30, -30))

    local buildingName = collectData:getBuildingName()
    local playerName = collectData:getPlayerName()
    local nameStr
    if playerName == " " then
        nameStr = buildingName
    else
        nameStr = string.format("%s/%s", buildingName, playerName)
    end
    self._nameLabel:setString(nameStr)
    self._nameLabel:setPosition(cc.p(self._iconSprite:getPositionX(), M.CollectCellSize.height - 20))

    local coor = collectData:getCoor()
    local coorStr = string.format("X%d,Y%d", coor.i, coor.j)
    self._elementLabel:updateText(coorStr)

    -- self._elementLabel.onClicked = function()
    --     local mapLayerManager = MapManager:getMapLayerManager()
    --     mapLayerManager:changeViewCenterByTwoDCoor(coor.i, coor.j)
    -- end
    self._richLabel:reloadData()
    Layout:layout(self._richLabel, M.CollectCellSize, Layout.left_center, cc.p(400, 0))
end

function M:ctor()
    self:setAnchorPoint(cc.p(0.5, 0.5))
    self:setContentSize(M.CollectCellSize)
    self:_createBackground()
    self:_createIcon()
    self:_createNameLabel()
    self:_createCoorLabel()
    self:_createCloseButton()
end

function M:_createCloseButton()
    local button = CommonUI:createTextButton(self, "", "ui/collection/btn-close.png")
    Layout:layout(button, M.CollectCellSize, Layout.right_top, cc.p(30, 30))
    button.onClicked = function()
        AlertView.new(__Localized("确定删除？"), __Localized("取 消"), __Localized("删 除")).onClicked = function(index)
            if 1==index then 
                CommonUI:showLoadingLayer(true)
                SocketManager:send(kCollectInfoDelete, {id = self._collectData:getId()})
            end
        end
    end
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.CollectCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createIcon()
    self._iconSprite = cc.Sprite:create()
    self:addChild(self._iconSprite)
end

function M:_createNameLabel()
    self._nameLabel = CommonUI:createLabel("", 30)
    self:addChild(self._nameLabel)
end

function M:_createCoorLabel()
    self._richLabel = RichLabel.new()
    self._elementLabel = ElementText:createLabel("", 30, cc.c4b(0, 0, 255, 255))
    self._elementLabel:setUnderLine(true)
    self._richLabel:pushElement(self._elementLabel)
    self:addChild(self._richLabel)
end

function M:_getBuildingResourceId(buildingId, buildingLevel)
    if ResourcePointUtils:isCastleType(buildingId) then
        return buildingLevel + ResourcePointUtils:getCastleTag() - 1
    end
    if ResourcePointUtils:isFamousCity(buildingId) then
        return FamousCityConfigReader:getResId(buildingId)
    end
    return buildingId
end

return M