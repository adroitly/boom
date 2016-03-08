local MapConfig = require("ui.map.data-manager.MapConfig")
local TeamDataManager = require("player-data.TeamDataManager")
local DialogUtils = require("ui.map-subview.DialogUtils")

local M = class("ui.map-subview.ClickGrasslandDialog", function()
    return cc.Node:create()
end)

function M:newClickGrasslandDialog(parent, inPoint)
    assert(parent and inPoint)
    local node = M.new()
    node:initWithPoint(inPoint)
    parent:addChild(node, Enum.ZOrder.Dialog)
    return node
end

function M:initWithPoint(inPoint)
    local space = DialogUtils:getDialogRadius()
    local garrisonBt = CommonUI:createTextButton(self, __Localized("出征"), "ui/common/ok.png")
    garrisonBt:setPosition(cc.p(0, space))
    garrisonBt.onClicked = function()
        DialogUtils:showOutTeamLayer(Enum.GoOutOperation.Move, self._toCoor)

        MapManager:removeDialogLayer()
    end

    local teleportBt = CommonUI:createTextButton(self, __Localized("瞬移"), "ui/common/ok.png")
    teleportBt:setPosition(cc.p(0, -space))
    teleportBt.onClicked = function()
        self:_testTeleportAction()
    end

    local localCoor = MapConfig:getCoordinateFromPosition(inPoint)
    local centerPos = MapConfig:getPositionFromCoordinate(localCoor)
    self:setPosition(centerPos) 
    local twoDCoor = MapConfig:localTo2D(localCoor)

    DialogUtils:showCoordinate(self, twoDCoor)
    self._toCoor = localCoor
end

-- 作弊测试用
local function _getDataWithIndex(table, index)
    local tmp = 0
    for _, value in pairs(table) do
        if tmp==index then 
            return value
        end
        tmp = tmp + 1
    end
end

local m_testTag = 0
function M:_testTeleportAction()
    local goOutList = TeamDataManager:getGoOutTeamList()
    local goOutCount = table.getn(goOutList) 
    if goOutList==nil or goOutCount==0 then
        return
    end

    local tag = m_testTag % goOutCount
    local teamData = _getDataWithIndex(goOutList, tag)
    assert(teamData)

    local requestData = { 
        player_id   = PlayerData:getPlayerId(), 
        army_id     = teamData:getArmyId(), 
        to_x        = self._toCoor.i, 
        to_y        = self._toCoor.j }
    
    SocketManager:send(Command.TestTeleport, requestData)
    m_testTag = m_testTag + 1
    MapManager:removeDialogLayer()
end

return M


