local BattleUtils = require("ui.map.logic.BattleUtils")
local TeamDataManager = require("player-data.TeamDataManager")
local BackpackDataManager = require("player-data.BackpackDataManager")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.map.layer-manager.ArmyGoBackLayer",function(armyData)
	return cc.Layer:create()
end)

local function _goBackSoonAction(msgTable)
    CommonUI:showLoadingLayer(false)
    assert(msgTable.code)
    if 0 ~= msgTable.code then
        CommonUI:lightTips(__Localized("回城失败,请检查回城令是否充足"))
        return 
    end

    assert(msgTable.army)
    local outside_army_info = msgTable.army
    assert(outside_army_info.player_id)
    local playerId = outside_army_info.player_id
    assert(outside_army_info.army)
    local armyInfo = outside_army_info.army
    assert(armyInfo.army_id)
    local armyId = armyInfo.army_id

    BattleUtils:removeArmy(playerId, armyId) 
    TeamDataManager:setState(armyId, Enum.TeamDataState.Inside)
    CommonUI:lightTips(__Localized("军队回城成功"))
end


local function _getGoldNumber()
    local backpackData = BackpackDataManager:getBackpackDataByType(Enum.ResourceType.Gold)
    if backpackData then
        return backpackData:getItemNumber()
    end
end

local function _getGoldType()
    local goldNumber = _getGoldNumber()
    if nil ~= goldNumber and 0 ~= goldNumber then
        return Enum.ResourceType.Gold
    end
end

local function _getResourceType()
    local backTokenBackpackData = BackpackDataManager:getBackpackDataByType(Enum.ResourceType.BackToken)
    if nil == backTokenBackpackData then
        return _getGoldType()
    else
        local number = backTokenBackpackData:getItemNumber()
        if 0 ~= number then
            return Enum.ResourceType.BackToken
        else
            return _getGoldType()
        end
    end
    return nil
end

local function _getResourceName()
    local resourceType = _getResourceType()
    if resourceType then
        return BackpackConfigRead:getName(resourceType)
    end
    return nil
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local commons = 
    {
        [Command.ArmyGoBackUseItem] = function(msgTable)
            assert(msgTable)
            _goBackSoonAction(msgTable)
            self:removeFromParent()
        end,
    }
    local fun = commons[cmd]
    if fun then 
        fun(msgTable)
    end
end
function M:ctor()
    self:_registerSocketCallBack()
	self:_createBackground()
    self:_createGouBackButton()
    self:_createGouBackSoonButton()
end

function M:reload(armyData)
	self._armyData = armyData
end

function M:_registerSocketCallBack()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if "exit" == event then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:_createGouBackButton()
    local button = CommonUI:createTextButton(self, __Localized("回城"), "ui/common/ok.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(Screen.width / 2 - buttonSize.width, Screen.height / 2))
    button.onClicked = function()
        self:_onGoBackAction()
    end
end

function M:_createGouBackSoonButton()
    local labelName = _getResourceName()

    local buttonText = nil == labelName and __Localized("去充值") or __Localized("立刻回城")
    local button = CommonUI:createTextButton(self, buttonText, "ui/common/ok.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(Screen.width / 2 + buttonSize.width, Screen.height / 2))
    button.onClicked = function()
        if labelName then
            self:_onGoBackSoonAction()
        else
            local layer = require("ui.recharge.layer-manager.RechargeLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end
    end

    local label = CommonUI:createLabel(labelName, 24)
    self:addChild(label)
    local labelSize = label:getContentSize()
    label:setPosition(cc.p(Screen.width / 2 + buttonSize.width, Screen.height / 2 + buttonSize.height + labelSize.height / 2))
end

-- 添加背景
function M:_createBackground()
    local backgroundLayer = require("ui.common.BackgroundLayer").new(self, __Localized("回城"))
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_onGoBackSoonAction()
    local armyId = self._armyData:getArmyId()
    local sendData = {army_id = armyId}
    SocketManager:send(Command.ArmyGoBackUseItem, sendData)
    CommonUI:showLoadingLayer(true)
end

function M:_onGoBackAction()
    local homeCoor = PlayerData:getHomeCoor()
    local playerId = self._armyData:getPlayerId()
    local armyId = self._armyData:getArmyId()
    local armyDataManager = MapManager:getArmyDataManager()
    armyDataManager:changeStatus(playerId, armyId, Enum.GoOutOperation.GoHome, homeCoor)
    self:removeFromParent()
end

return M