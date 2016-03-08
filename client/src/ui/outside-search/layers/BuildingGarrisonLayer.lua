local BuildingConfigReader = require("ui/produce/data-manager/BuildingConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local CityDefConfigReader = require("config-reader/CityDefConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local BuildingDefenceCell = require("ui.outside-search.layers.BuildingDefenceCell")
local CastleConfigReader = require("ui/city/king/CastleConfigReader")
local ArmyData = require("ui.map.data-manager.ArmyData")
local TimeTools = require("ui/common/TimeTools")
local M = class("ui.outside-search.layers.BuildingDefenceLayer", function()
    return cc.Layer:create()
end)

local kBuildingGarrisonList = "building_garrison_list"
local kBuildingGuard = "building_guard"
local kCastleRepair = "castle_repair"

local kEmpty = 0
function M:ctor(buildingData)
    self._buildingData = buildingData
    self._armyDataList = {}

    self:_createBackground()
    self:_createCastleCityDefNode()
    self:_createTableView()

    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            TimerInterval:removeTimer(self)
        end
    end)
    self:_getGarrisionList()
    TimerInterval:addTimer(self, 1)
end

function M:_getGarrisionList()
    local coor = self._buildingData:getHomeCoor()
    SocketManager:send(kBuildingGarrisonList, {x = coor.i, y = coor.j})
    CommonUI:showLoadingLayer(true)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kBuildingGarrisonList then
        CommonUI:showLoadingLayer(false)
        self:_initArmyData(msgTable)
        self._tableView:reloadData()
    end
    if cmd == kBuildingGuard then
        if not CommonUI:errorAlertView(msgTable.code) then
            self:_getGarrisionList()
        end
    end
    if cmd == kCastleRepair then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips("修城成功")
            self:_updatePercentage()
        end
    end
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return BuildingDefenceCell.BuildingDefenceCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = BuildingDefenceCell.new()
    end
    cell:reload(self._armyDataList[idx + 1])
    cell:setAddButtonCallback(function()
        self:_addGarrisonTeam()
    end)
    return cell
end

function M:_addGarrisonTeam()
    local coor = self._buildingData:getHomeCoor()
    local goOutOperation = Enum.GoOutOperation.Aid
    local MapConfig = require("ui.map.data-manager.MapConfig")
    local twoDCoor = MapConfig:localTo2D(coor)
    local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
    local goInfo = GoOutInfo:newGoOutInfo(goOutOperation, twoDCoor)
    local layer = require("ui.team.layer-manager.OutTeamLayer").new(goInfo)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(layer)
end

function M:_initArmyData(msgTable)
    self._armyDataList = {}
    for _, armyInfo in ipairs(msgTable.armyInfos) do
        local armyData = ArmyData:newArmyDataWithInfo(armyInfo)
        table.insert(self._armyDataList, armyData)
    end
    -- 添加一个空的
    table.insert(self._armyDataList, kEmpty)
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._armyDataList)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("驻守部队"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTableView()
    local castleCityNodeHeight = self._castleCityDefNode and self._castleCityDefNode:getContentSize().height or 0
    local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight - castleCityNodeHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self._tableView:setPosition(cc.p((Screen.width - BuildingDefenceCell.BuildingDefenceCellSize.width) * 0.5, 0))
    self:addChild(self._tableView)
end

function M:_createCastleCityDefNode()
    local buildingId = self._buildingData:getBuildingId()
    local buildingType = BuildingConfigReader:getBuildingType(buildingId)
    if buildingType ~= Enum.BuildingType.Castle then
        return
    end

    self._castleCityDefNode = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(self._castleCityDefNode)
    local size = self._castleCityDefNode:getContentSize()
    Layout:layout(self._castleCityDefNode, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))

    self:_createCityDefTitle()
    self:_createCityDefProgressTimer()
    self:_createFixButton()
    self:_createFixTime()

    self:_updatePercentage()
end

function M:_createCityDefTitle()
    local titleLabel = CommonUI:createLabel("城防")
    self._castleCityDefNode:addChild(titleLabel)
    Layout:layout(titleLabel, self._castleCityDefNode:getContentSize(), Layout.center_top)
end

function M:_createCityDefProgressTimer()
    self._cityDefProgressBackground = cc.Sprite:create("ui/hero-museum/progressbg.png")
    self._castleCityDefNode:addChild(self._cityDefProgressBackground)
    Layout:layout(self._cityDefProgressBackground, self._castleCityDefNode:getContentSize(), Layout.left_center, cc.p(100, 50))

    self._cityDefProgressTimer = cc.ProgressTimer:create(cc.Sprite:create("ui/hero-museum/progressup.png"))
    self._cityDefProgressBackground:addChild(self._cityDefProgressTimer)
    Layout:layout(self._cityDefProgressTimer, self._cityDefProgressBackground:getContentSize(), Layout.center)
    self._cityDefProgressTimer:setBarChangeRate(cc.p(1, 0))
    self._cityDefProgressTimer:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self._cityDefProgressTimer:setMidpoint(cc.p(0,1))

    self._cityDefProgressLabel = CommonUI:createLabel("", 30)
    self._castleCityDefNode:addChild(self._cityDefProgressLabel)
    local bgX, bgY = self._cityDefProgressBackground:getPosition()
    local bgSize = self._cityDefProgressBackground:getContentSize()
    self._cityDefProgressLabel:setPosition(cc.p(bgX, bgY + bgSize.height * 0.5))
    self._cityDefProgressLabel:setAnchorPoint(cc.p(0.5, 0))
end

function M:_createFixButton()
    local percentage = self._cityDefProgressTimer:getPercentage()
    self._fixButton = CommonUI:createTextButton(self._castleCityDefNode, "修城", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(self._fixButton, self._castleCityDefNode:getContentSize(), Layout.left_center, cc.p(100 + self._cityDefProgressBackground:getContentSize().width + 20, 50))
    
    self._fixButton.onClicked = function()
        self:_createFixAlertView()
    end
end

function M:_createFixTime()
    self._fixTimeLabel = CommonUI:createLabel("", 30)
    self._castleCityDefNode:addChild(self._fixTimeLabel)
    local bgX, bgY = self._fixButton:getPosition()
    local bgSize = self._fixButton:getContentSize()
    self._fixTimeLabel:setPosition(cc.p(bgX, bgY + bgSize.height * 0.5))
    self._fixTimeLabel:setAnchorPoint(cc.p(0.5, 0))
end

function M:onUpdate()
    self:_updateFixTime()
end

function M:_updateFixTime()
    local nextTime = self._buildingData:getNextRepairTime()
    local nowTime = PlayerData:getServerTime()
    local percentage = self._cityDefProgressTimer:getPercentage()
    local canFix = false
    if nextTime - nowTime > 0 then
        local timeStr = TimeTools:getTimeCountDownString(nextTime - nowTime)
        self._fixTimeLabel:setString(timeStr)
    else
        self._fixTimeLabel:setString("")
        if percentage < 100 then
            canFix = true
        end
    end
    self._fixButton:setEnabled(canFix)
end

function M:_updatePercentage()
    local buildingId = self._buildingData:getBuildingId()
    local totalCityDef = CityDefConfigReader:getCityAmount(buildingId)
    local curCityDef = self._buildingData:getCityDef()
    local percentage = curCityDef / totalCityDef * 100
    self._cityDefProgressTimer:setPercentage(percentage)

    local progressStr = string.format("%d/%d", curCityDef, totalCityDef)
    self._cityDefProgressLabel:setString(progressStr)
    self:_updateFixTime()
end

function M:_createFixAlertView()
    local level = PlayerData:getCastleLevel()
    local speed = CastleConfigReader:getCityDefSpeed(level)
    local conditionList = CastleConfigReader:getCityDefCondition(level)
    local str = ""
    for _, item in ipairs(conditionList) do
        local name = BackpackConfigRead:getName(item.id)
        str = str .. name .. "×" .. item.count .. " "
    end
    str = string.format("修城可立即恢复城防%d点，花费以下材料\n修城所需材料：\n%s", speed, str)
    local alertView = AlertView.new(str, __Localized("取 消"), __Localized("确 定"))
    alertView.onClicked = function(index)
        if 1 == index then
            CommonUI:showLoadingLayer(true)
            SocketManager:send(kCastleRepair, {})
        end
    end
end

return M