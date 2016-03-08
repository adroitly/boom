local CastleConfigReader = require("ui.city.king.CastleConfigReader")
local GameMailDataManager = require("player-data.GameMailDataManager")
local SystemMailDataManager = require("player-data.SystemMailDataManager")
local PersonalMailDataManager = require("player-data.PersonalMailDataManager")
local BackpackDataManager = require("player-data.BackpackDataManager")
local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local TimeTools = require("ui.common.TimeTools")
local M = {}

local kTipsPointTag = 255

local kUserLevelUpTime = "user_level_up_time"
local kBuildingUpgrade = "building_upgrade"
local kMessageGameSend = "message_game_send"
local kMessageSystemSend = "message_system_send"
local kMessagePersonalInfo = "message_personal_info"

local function _newTipsData()
    return {
        playerLevel = 0, 
        cityLevel = 0, 
        emailIdList = {}, 
        resourcesIdList = {}, 
        soldierIdList = {}
    }
end

local function _getTipsData(node, tipsType)
    return {node = node, tipsType = tipsType}
end

local function _getTipsNode(tipsData)
    return tipsData.node
end

local function _getTipsType(tipsData)
    return tipsData.tipsType
end

function M:removeTipsListener(node)
    local indexs = self:_getTipsListIndexs(node)
    for index = #indexs,1, -1 do
        table.remove(self._tipsNodeList, indexs[index])
    end
end

function M:addTipsListener(tipsType, parent, pos)
    local sprite = cc.Sprite:create("ui/main-page/red-point.png")
    sprite:setTag(kTipsPointTag)
    parent:addChild(sprite)

    if not pos then
        Layout:layout(sprite, parent:getContentSize(), Layout.right_top)
    else
        sprite:setPosition(pos)
    end
    sprite:setVisible(false)

    Event:registerNodeEvent(parent)
    parent.onExit = function()
        self:removeTipsListener(parent)
    end
    if not self._tipsNodeList then
        self._tipsNodeList = {}
    end
    table.insert(self._tipsNodeList, _getTipsData(parent, tipsType))
end

function M:startTipsListener()
    self._tipsData = _newTipsData()
    self._isAlertViewShow = false
    SocketManager:addObserver(self)
    TimerInterval:addTimer(self, 1)
end

function M:stopTipsListener()
    SocketManager:removeObserver(self)
    TimerInterval:removeTimer(self)
    self._tipsNodeList = {}
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kUserLevelUpTime or cmd == kBuildingUpgrade then
        CommonUI:showLoadingLayer(false)
    end
end

function M:_getTipsListIndexs(node)
    local indexList = {}
    for index,tipsData in ipairs(self._tipsNodeList) do
        if node == _getTipsNode(tipsData) then
            table.insert(indexList, index)
        end
    end
    return indexList
end

function M:_isCityCanLevelUp()
    local currentLevel = PlayerData:getCastleLevel()
    if currentLevel == CastleConfigReader:getMaxLevel() then
        return false
    end
    local nextLevel = currentLevel + 1
    local playerLevel = PlayerData:getUserInfoData():getLevel()
    local levelCondition = CastleConfigReader:getLevelCondition(currentLevel)

    if playerLevel < levelCondition then
        return false
    end

    local tbl = CastleConfigReader:getUpgradeConditions(currentLevel)
    for i, data in ipairs(tbl) do
        local backpackData = BackpackDataManager:getBackpackDataByType(data.id)
        if not backpackData then
            return false
        end
        local needNumber = backpackData:getItemNumber()
        if needNumber < data.count then
            return false
        end
    end
    return true
end

function M:_isPlayerCanLevelUp()
    local needTime = PlayerData:getUserInfoData():getLevelUpEndTime() - PlayerData:getServerTime()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    if needTime <= 0 then
        if currentLevel < 90 then
            return true
        end
    end
    return false
end

function M:_isProduceSoldiersDone()
    local list = ProduceBuildingDataManager:getFinishProduceSoldierList()
    return table.getn(list) > 0
end

function M:_isProduceResourcesDone()
    local list = ProduceBuildingDataManager:getFinishProduceResourcesList()
    return table.getn(list) > 0
end

function M:_isHasNewEmail()
    local unreadCount = GameMailDataManager:getUnreadMailCount()
    unreadCount = unreadCount + SystemMailDataManager:getUnreadMailCount()
    unreadCount = unreadCount + PersonalMailDataManager:getUnreadMailCount()
    return unreadCount > 0
end

function M:_isPickMoney()
    local userInfoData = PlayerData:getUserInfoData()
    local serverTime = PlayerData:getServerTime()
    local salaryTime = userInfoData:getSalaryReceiveTime()
    return false == TimeTools:isSameDay(serverTime, salaryTime)
end

function M:onUpdate(dt)
    if not PlayerData:getUserInfoData() then
        return
    end
    for _,tipsData in ipairs(self._tipsNodeList) do
        local tipsType = _getTipsType(tipsData)
        local node = _getTipsNode(tipsData)
        local sprite = node:getChildByTag(kTipsPointTag)
        sprite:setVisible(self:_checkTipsShow(tipsType))
    end
    local innerCityLayer = MapManager:getMapMainLayer():getChildByTag(Enum.Tag.InnertCityLayer)
    if not innerCityLayer then
        return
    end
    self:_checkPlayerLevelUpViewShow()
    self:_checkCastleLevelUpViewShow()
    self:_checkProduceSoldierDoneViewShow()
    self:_checkProduceResourcesDoneViewShow()
end

function M:_checkCastleLevelUpViewShow()
    if self._isAlertViewShow then
        return
    end
    local isCanShow = false
    local currentLevel = PlayerData:getCastleLevel()
    if self:_isCityCanLevelUp() then
        if self._tipsData.cityLevel < currentLevel then
            isCanShow = true
        end
    end
    if not isCanShow then
        return
    end
    local scene = cc.Director:getInstance():getRunningScene()
    local layer = scene:getChildByTag(Enum.LayerTag.CastleUpgrade)
    if layer then
        return
    end
    self._tipsData.cityLevel = currentLevel
    self._isAlertViewShow = true
    AlertView.new(__Localized("您的主城可以升级至下一等级"), __Localized("查 看"), __Localized("完 成")).onClicked = function(index)
        self._isAlertViewShow = false
        if 0 == index then
            local layer = require("ui.city.king.CastleUpgradeLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        elseif 1 == index then
            CommonUI:showLoadingLayer(true)
            SocketManager:send(kBuildingUpgrade, {})
        end
    end
end

function M:_checkProduceSoldierDoneViewShow()
    if self._isAlertViewShow then
        return
    end
    local isCanShow = false
    local produceList = ProduceBuildingDataManager:getFinishProduceSoldierList()
    for _, produceData in pairs(produceList) do
        local list = self._tipsData.soldierIdList
        local id = produceData:getId()
        if not list[id] then
            self._tipsData.soldierIdList[id] = true
            isCanShow = true
        end
    end
    if not isCanShow then
        return
    end
    local scene = cc.Director:getInstance():getRunningScene()
    local layer = scene:getChildByTag(Enum.LayerTag.ProduceSoldier)
    if layer then
        return
    end
    self._isAlertViewShow = true
    AlertView.new(__Localized("您的征兵已经完成"), __Localized("取 消"), __Localized("查 看"), __Localized("完 成")).onClicked = function(index)
        self._isAlertViewShow = false
        if index == 1 then
            local layer = require("ui.produce.layer-manager.ProduceSoldierLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        elseif index == 2 then
            ProduceBuildingDataManager:sendAllProduceSoldierReceived()
        end
    end
end

function M:_checkProduceResourcesDoneViewShow()
    if self._isAlertViewShow then
        return
    end
    local isCanShow = false
    local produceList = ProduceBuildingDataManager:getFinishProduceResourcesList()
    for _, produceData in pairs(produceList) do
        local list = self._tipsData.resourcesIdList
        local id = produceData:getId()
        if not list[id] then
            self._tipsData.resourcesIdList[id] = true
            isCanShow = true
        end
    end
    if not isCanShow then
        return
    end
    local scene = cc.Director:getInstance():getRunningScene()
    local layer = scene:getChildByTag(Enum.LayerTag.ProduceResources)
    if layer then
        return
    end
    self._isAlertViewShow = true
    AlertView.new(__Localized("您的资源已经生产完成"), __Localized("取 消"), __Localized("查 看"), __Localized("完 成")).onClicked = function(index)
        self._isAlertViewShow = false
        if index == 1 then
            local layer = require("ui.produce.layer-manager.ProduceResourcesLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        elseif index == 2 then
            ProduceBuildingDataManager:sendAllProduceResourcesReceived()
        end
    end
end

function M:_checkPlayerLevelUpViewShow()
    if self._isAlertViewShow then
        return
    end
    local isCanShow = false
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    if self:_isPlayerCanLevelUp() then
        if self._tipsData.playerLevel < currentLevel then
            isCanShow = true
        end
    end
    if not isCanShow then
        return
    end
    local scene = cc.Director:getInstance():getRunningScene()
    local layer = scene:getChildByTag(Enum.LayerTag.PlayerLevelUpgrade)
    if layer then
        return
    end
    self._tipsData.playerLevel = currentLevel
    self._isAlertViewShow = true
    AlertView.new(__Localized("您的官职可以升级至下一等级"), __Localized("查 看"), __Localized("完 成")).onClicked = function(index)
        self._isAlertViewShow = false
        if 0 == index then
            local layer = require("ui.user-info.MainLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        elseif 1 == index then
            CommonUI:showLoadingLayer(true)
            SocketManager:send(kUserLevelUpTime, {})
        end
    end
end

function M:_checkTipsShow(tipsType)
    local isShowCmd = {
        [Enum.TipsType.ProduceResources] = function()
            return self:_isProduceResourcesDone()
        end,
        [Enum.TipsType.ProduceSoldier] = function()
            return self:_isProduceSoldiersDone()
        end,
        [Enum.TipsType.LevelUp] = function()
            return self:_isPlayerCanLevelUp()
        end,
        [Enum.TipsType.CityLevelUp] = function()
            return self:_isCityCanLevelUp()
        end,
        [Enum.TipsType.Email] = function()
            return self:_isHasNewEmail()
        end,
        [Enum.TipsType.PickMoney] = function()
            return self:_isPickMoney()
        end
    }
    return Function:safeCall(isShowCmd, tipsType)
end

function M:_checkMailCmd(cmd, msgTable)
    local cmdTbl = {
        [kMessageGameSend] = function()
            local layer = require("ui.mail.layer-manager.GameMailLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end,
        [kMessageSystemSend] = function()
            local layer = require("ui.mail.layer-manager.SystemMailLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end,
        [kMessagePersonalInfo] = function()
            local layer = require("ui.mail.layer-manager.PlayerMailLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end,
    }
    if not cmdTbl[cmd] or self._isAlertViewShow then
        return
    end
    if cmd == kMessagePersonalInfo then
        if PlayerData:isOwner(msgTable.from_player_id) then
            return
        end
    end
    self._isAlertViewShow = true
    AlertView.new(__Localized("您有新的邮件"), __Localized("取 消"), __Localized("查 看")).onClicked = function(index)
        self._isAlertViewShow = false
        if index == 1 then
            Function:safeCall(cmdTbl, cmd)
        end
    end
end

return M