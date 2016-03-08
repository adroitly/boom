local MapConfig = require("ui.map.data-manager.MapConfig")
local DialogUtils = require("ui.map-subview.DialogUtils")
local BattleUtils = require("ui.map.logic.BattleUtils")
local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
local M = class("ui.map-subview.ClickBuildingDialog", function()
    return cc.Node:create()
end)

function M:newClickCampDialog(parent, inPoint, buildingData)
    assert(parent and inPoint)
    local node = M.new()
    node:initWithPoint(inPoint, buildingData)
    parent:addChild(node, Enum.ZOrder.Dialog)
    return node
end

function M:initWithPoint(inPoint, buildingData)
    self._buildingData = buildingData

    local coor = self._buildingData:getHomeCoor()
    local center = MapConfig:getResourcePointPosition(coor)
    self:setPosition(center)

    local resOwnerId = self._buildingData:getOwnerId()
    local rewGuildId = self._buildingData:getGuildId()
    DialogUtils:showResourcePointButton(self, resOwnerId, rewGuildId, buildingData)

    local localCoor = buildingData:getHomeCoor()
    local twoDCoor = MapConfig:localTo2D(localCoor)
    DialogUtils:showCoordinate(self, twoDCoor)
end

-- 由DialogUtils:showResourcePointButton内实现
function M:onSearchAction()
    -- Print:Table(self._buildingData, "data =")
    require("ui.outside-search.MainLayer"):createOtherBuildingLayer(self._buildingData)

    MapManager:removeDialogLayer()
end

function M:onAttackAction()
    if not BattleUtils:canAttackFamousCity(self._buildingData) then 
        return
    end

    local coor = self._buildingData:getHomeCoor()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.AttackBuilding, coor)
    MapManager:removeDialogLayer()
end

function M:onOccupyAction()
    if not BattleUtils:canAttackFamousCity(self._buildingData) then 
        return
    end
    
    local coor = self._buildingData:getHomeCoor()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.OccupyBuilding, coor)
    MapManager:removeDialogLayer()
end

function M:onEnterAction()
    local mapLayer = MapManager:getMapMainLayer()
    mapLayer:onEnterInnerCityAction(self._buildingData)

    MapManager:removeDialogLayer()
end

function M:onAidAction()
    local localCoor = self._buildingData:getHomeCoor()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.Aid, localCoor)

    MapManager:removeDialogLayer()
end

function M:onCollectAction()
    local collectLayer = require("ui.collection.layer-manager.CollectLayer").new(self._buildingData)
    cc.Director:getInstance():getRunningScene():addChild(collectLayer)
    MapManager:removeDialogLayer()
end

return M