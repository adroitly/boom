local ArmyData = require("ui.map.data-manager.ArmyData")
local ArmyLeadNode = require("ui.map.ArmyLeadNode")
local ClickOperation = require("ui.map.ClickOperation")
local M = class("ui.map.ArmyLeadLayer", function()
    return cc.Layer:create()
end)

local function _getArmyData(armyId)
    local playerId = PlayerData:getPlayerId()
    local armyDataManager = MapManager:getArmyDataManager()
    return armyDataManager:findArmyData(playerId, armyId)
end

function M:ctor()
    self._armyLeadNodeTable = {}
end

function M:createArmy(armyData)
    assert(armyData)

    local armyId = armyData:getArmyId()
    if self._armyLeadNodeTable[armyId] then 
        return
    end

    local armyLeadNode = ArmyLeadNode.new(armyData)
    self:addChild(armyLeadNode)
    armyLeadNode:setClickCallfun(function(node)
        self:onClickAction(node)
    end)

    self._armyLeadNodeTable[armyId] = armyLeadNode
end
  
function M:deleteArmy(armyData)
    assert(armyData)
    local armyId = armyData:getArmyId()
    local armyLeadNode = self._armyLeadNodeTable[armyId]
    if armyLeadNode then 
        armyLeadNode:removeFromParent()
        self._armyLeadNodeTable[armyId] = nil
    end
end

function M:resetPosition()
    local index = 1
    for _,armyLeadNode in pairs(self._armyLeadNodeTable) do
        local armyLeadNodeSize = armyLeadNode:getContentSize()
        local x = Screen.width - armyLeadNodeSize.width / 2
        local topHight = Screen.height / 2 + armyLeadNodeSize.height * 2.5
        local y = topHight - (index* armyLeadNodeSize.height)
        armyLeadNode:setPosition(cc.p(x, y))
        index = index + 1
    end
end

function M:onClickAction(armyLeadNode)
    local armyId = self:_getArmyId(armyLeadNode)
    local armyData = _getArmyData(armyId)

    self:_changeViewToArmy(armyData)
    self:_selectAction(armyData)
end

function M:setArmyLeadSelect(armyData)
    assert(armyData)
    local armyId = armyData:getArmyId()
    local isSelected = armyData:isSelected()
    local armyLeadNode = self._armyLeadNodeTable[armyId]
    if armyLeadNode then 
        armyLeadNode:setSelected(isSelected)
    end
end

function M:_changeViewToArmy(armyData)
    local position = armyData:getPosition()
    local mapLayer = MapManager:getMapLayerManager()
    mapLayer:changeViewCenterToPosition(position)
end

function M:_selectAction(armyData)
    if armyData:isSelected() then 
        ClickOperation:setMyArmySelect(armyData, false)
        return 
    end

    for iterArmyId,_ in pairs(self._armyLeadNodeTable) do
        local tmpArmyData = _getArmyData(iterArmyId)
        ClickOperation:setMyArmySelect(tmpArmyData, false)
    end
    ClickOperation:setMyArmySelect(armyData, true)
end

function M:_getArmyId(armyLeadNode)
    for armyId,node in pairs(self._armyLeadNodeTable) do
        if node==armyLeadNode then
            return armyId
        end
    end
end

return M

