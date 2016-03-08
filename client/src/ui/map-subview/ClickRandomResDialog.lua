local MapConfig = require("ui.map.data-manager.MapConfig")
local DialogUtils = require("ui.map-subview.DialogUtils")

local M = class("ui.map-subview.ClickRandomResDialog", function()
    return cc.Node:create()
end)

function M:newClickRandomResDialog(parent, inPoint, randomResourceData)
    assert(parent and inPoint and randomResourceData)
    local node = M.new()
    node:initWithPoint(inPoint, randomResourceData)
    parent:addChild(node, Enum.ZOrder.Dialog)
    return node
end

function M:initWithPoint(inPoint, randomResourceData)
    self._randomResourceData = randomResourceData
    local space = DialogUtils:getDialogRadius()
    local lookBt = CommonUI:createTextButton(self, __Localized("查看"), "ui/common/ok.png")
    lookBt:setPosition(cc.p(0, space))
    lookBt.onClicked = function()
        self:onLookAction()
        MapManager:removeDialogLayer()
    end

    local getBt = CommonUI:createTextButton(self, __Localized("拾取"), "ui/common/ok.png")
    getBt:setPosition(cc.p(0, -space))
    getBt.onClicked = function()
        self:onGetAction()
    end

    local localCoor = MapConfig:getCoordinateFromPosition(inPoint)
    local centerPos = MapConfig:getPositionFromCoordinate(localCoor)
    self:setPosition(centerPos) 

    local twoDCoor = MapConfig:localTo2D(localCoor)
    DialogUtils:showCoordinate(self, twoDCoor)
end

function M:onLookAction()
    -- Print:Table(self._randomResourceData, "random data =")
    -- local items = self._randomResourceData:getItems()
    -- local item = items[1]
    -- local packageItemData = require("ui.backpack.data-manager.PackageItemData").new(item)
    -- Print:Table(packageItemData)
    local layer = require("ui.outside-search.layers.SearchRandomLayer").new(self._randomResourceData)
    local scene = Director:getRunningScene()
    scene:addChild(layer)

end

function M:onGetAction()
    local coor = self._randomResourceData:getHomeCoor()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.Pickup, coor)
    MapManager:removeDialogLayer()
end

return M


