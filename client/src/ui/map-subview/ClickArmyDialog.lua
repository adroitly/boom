
local MapConfig = require("ui.map.data-manager.MapConfig")
local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
local DialogUtils = require("ui.map-subview.DialogUtils")
local ClickOperation = require("ui.map.ClickOperation")
local BattleUtils = require("ui.map.logic.BattleUtils")

local M = class("ui.map-subview.ClickArmyDialog", function()
    return cc.Node:create()
end)

function M:newClickArmyDialog(parent, armyData)
    assert(parent and armyData)
    local node = M.new()
    node:initWithData(armyData)
    parent:addChild(node)

    local size = parent:getContentSize()
    node:setPosition(cc.p(size.width/2, size.height/2))
    return node
end

function M:initWithData(armyData)
    self._armyData = armyData

    local space = DialogUtils:getDialogRadius()

    -- 自己军队
    local playerId = self._armyData:getPlayerId()
    local isMy = PlayerData:isOwner(playerId)
    if isMy then 
        local stopBt = CommonUI:createTextButton(self, __Localized("驻扎"), "ui/common/ok.png")
        stopBt:setPosition(cc.p(-space, 0))
        stopBt.onClicked = function()
            self:onStopAction()
        end

        local goBackBt = CommonUI:createTextButton(self, __Localized("回城"), "ui/common/ok.png")
        goBackBt:setPosition(cc.p(space, 0))
        goBackBt.onClicked = function()
            self:onGoBackAction()
        end

        local supplyBt = CommonUI:createTextButton(self, __Localized("战补"), "ui/common/ok.png")
        supplyBt:setPosition(cc.p(0, space))
        supplyBt.onClicked = function()
            self:onSupplyAction()
        end
        return
    end

    -- 同势力
    local guildId = self._armyData:getGuildId()
    local isSameGuild = PlayerData:isSameGuild(guildId)
    if isSameGuild then 
        local searchBt = CommonUI:createTextButton(self, __Localized("侦查"), "ui/common/ok.png")
        searchBt:setPosition(cc.p(-space, 0))
        searchBt.onClicked = function()
            self:onSearchAction()
        end
        return
    end

    -- 敌人
    local searchBt = CommonUI:createTextButton(self, __Localized("侦查"), "ui/common/ok.png")
    searchBt:setPosition(cc.p(-space, 0))
    searchBt.onClicked = function()
        self:onSearchAction()
    end

    local attackBt = CommonUI:createTextButton(self, __Localized("攻击"), "ui/common/ok.png")
    attackBt:setPosition(cc.p(space, 0))
    attackBt.onClicked = function()
        self:onAttackAction()
    end
end


function M:onSupplyAction()
    local armySupplyLayer = require("ui.map.layer-manager.ArmySupplyLayer").new()
    armySupplyLayer:reload(self._armyData)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(armySupplyLayer)

    ClickOperation:setMyArmySelect(self._armyData, false)
    -- MapManager:removeDialogLayer()
end

function M:onStopAction()
    BattleUtils:setWaitStatus(self._armyData)

    ClickOperation:setMyArmySelect(self._armyData, false)
    -- MapManager:removeDialogLayer()
end

function M:onAttackAction()
    local toPlayerId = self._armyData:getPlayerId()
    local toArmyId = self._armyData:getArmyId()
    local localCoor = self._armyData:getFromCoordinate()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.AttackArmy, localCoor, toPlayerId, toArmyId)

    ClickOperation:setMyArmySelect(self._armyData, false)
    -- MapManager:removeDialogLayer()
end

function M:onGoBackAction()
    -- local homeCoor = PlayerData:getHomeCoor()
    
    -- local playerId = self._armyData:getPlayerId()
    -- local armyId = self._armyData:getArmyId()
    -- local armyDataManager = MapManager:getArmyDataManager()
    -- armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.GoHome, homeCoor)
    local armyGoBackLayer = require("ui.map.layer-manager.ArmyGoBackLayer").new()
    armyGoBackLayer:reload(self._armyData)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(armyGoBackLayer)

    ClickOperation:setMyArmySelect(self._armyData, false)
    -- MapManager:removeDialogLayer()
end

function M:onSearchAction()
    -- Print:Table(self._armyData, "army data =")
    
    require("ui.outside-search.layers.SearchArmyLayer"):createArmySearch(self._armyData)
    ClickOperation:setMyArmySelect(self._armyData, false)
    -- MapManager:removeDialogLayer()
end

return M