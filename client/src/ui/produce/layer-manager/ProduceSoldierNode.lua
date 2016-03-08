local TimeTools = require("ui.common.TimeTools")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.produce.layer-manager.ProduceSoldierNode", function()
    return cc.Node:create()
end)

local ProduceState = {
    Before = 1,
    Ing = 2,
    End = 3,
}

local kCastleProductSoldier = "castle_product_soldier"
local kCastleProductSoldierReceive = "castle_product_soldier_receive"
local kServiceUse = "service_use"

function M:ctor(produceSoldierData)
    self._produceSoldierData = produceSoldierData
    self:_createBackground()
    self:_createIcon()
    self:_createInfoLabels()
    self:_createSlider()
    self:_createSliderButtons()
    self:_createProduceButton()
    self:_createProgressInfo()
    
    self:registerScriptHandler(function(event)
        if "exit" == event then
            self:_removeTimer()
        end
        if "enterTransitionFinish" == event then
            self:_reset(self._produceSoldierData)
        end
    end)
end

function M:_updateProgress()
    local endTime = self._produceSoldierData:getProduceEndTime()
    local nowTime = PlayerData:getServerTime()
    local diffTime = endTime - nowTime
    local soldierType = self:_getSoldierType()
    local count = self._produceSoldierData:getSoldierNumber()
    local level = self:_getLevel()
    local rate = SoldierConfigReader:getProductionRate(soldierType)
    local time = rate * count
    local percentage = (time - diffTime) / time * 100
    self._progressBar:setPercentage(percentage)
    local str = TimeTools:getTimeCountDownString(diffTime)
    self._progressLabel:setString(str)
    if diffTime <= 0 then
        self:_removeTimer()
        self:_updateState(ProduceState.End)
    end
end

function M:_removeTimer()
    TimerInterval:removeTimer(self)
end

function M:_reset(produceSoldierData)
    self._produceSoldierData = produceSoldierData
    self:_resetInfoLabels()

    local endTime = self._produceSoldierData:getProduceEndTime()
    local nowTime = PlayerData:getServerTime()
    local diffTime = endTime - nowTime
    local state = ProduceState.Before
    if endTime == 0 then
        state = ProduceState.Before
    elseif diffTime < 0 then
        state = ProduceState.End
    else
        state = ProduceState.Ing
        TimerInterval:addTimer(self, 1)
    end
    self:_updateState(state)
end

function M:onUpdate()
    self:_updateProgress()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    local size = background:getContentSize()
    self:setContentSize(size)
    background:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
end

function M:_createIcon()
    self._headIcon = Button.new()
    self:addChild(self._headIcon)
    self._headIcon.onClicked = function()
        local soldierType = self:_getSoldierType()
        local soldierInfoLayer = require("ui.team.layer-manager.SoldierInfoLayer").new(soldierType)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(soldierInfoLayer)
    end
end

function M:_createInfoLabels()
    self._nameLabel = CommonUI:createLabel("", 24)
    self:addChild(self._nameLabel)
    self._limitLabel = CommonUI:createLabel("", 24)
    self:addChild(self._limitLabel)
    self._needTimeLabel = CommonUI:createLabel("", 24)
    self:addChild(self._needTimeLabel)
    self._levelLabel = CommonUI:createLabel("", 24)
    self:addChild(self._levelLabel)
    self._resourcesLabel = CommonUI:createLabel("", 24)
    self._resourcesLabel:setWidth(300)
    self._resourcesLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)
    self:addChild(self._resourcesLabel)
    self._countLabel = CommonUI:createLabel("", 24)
    self:addChild(self._countLabel)

    local needResourceLabel = CommonUI:createLabel("所需资源：", 24)
    self:addChild(needResourceLabel)
    Layout:layout(needResourceLabel, self:getContentSize(), Layout.left_top, cc.p(150, 90))
end

function M:_resetInfoLabels()
    local level = self:_getLevel()
    local soldierType = self:_getSoldierType()
    local resType = SoldierConfigReader:getType(soldierType)
    local key = string.format("%d.png", resType)
    local frame = CommonUI:createSpriteFrameTinyName("soldier", key)
    self._headIcon:changeNormalSpriteWithFrame(frame)
    local iconSize = self._headIcon:getContentSize()
    Layout:layout(self._headIcon, self:getContentSize(), Layout.left_center, cc.p(30, 0))

    local initPosX = 130
    local nameStr = SoldierConfigReader:getName(soldierType)

    self._nameLabel:setString(nameStr)
    Layout:layout(self._nameLabel, self:getContentSize(), Layout.left_top, cc.p(initPosX + 20, 30))

    local levelStr = string.format("等级：Lv.%d", level)
    self._levelLabel:setString(levelStr)
    Layout:layout(self._levelLabel, self:getContentSize(), Layout.left_top, cc.p(initPosX + 160, 30))
    local limit = SoldierConfigReader:getCapacity(soldierType)
    local limitStr = string.format("招募上限：%d", limit)
    self._limitLabel:setString(limitStr)
    Layout:layout(self._limitLabel, self:getContentSize(), Layout.left_top, cc.p(initPosX + 20, 60))
    self._slider:setMaximumValue(limit)
end

function M:_updateSoldierInfo(count)
    local level = self:_getLevel()
    local soldierType = self:_getSoldierType()
    self._selectedCount = count
    local countStr = string.format("数量：%d", count)
    self._countLabel:setString(countStr)
    Layout:layout(self._countLabel, self:getContentSize(), Layout.right_bottom, cc.p(30, 20))

    local vipLv = PlayerData:getUserInfoData():getVip()
    local recruitUp = VipConfigReader:getRecruitUp(vipLv)
    local rate = SoldierConfigReader:getProductionRate(soldierType)
    local time = rate * count * recruitUp
    time = math.floor(time)
    local timeStr = TimeTools:getTimeStringBySec(time)
    timeStr = string.format("所需时间：%s", timeStr)
    self._needTimeLabel:setString(timeStr)
    Layout:layout(self._needTimeLabel, self:getContentSize(), Layout.left_top, cc.p(400, 60))

    self:_updateNeedResourcesInfo(count)
end

function M:_updateNeedResourcesInfo(count)
    local level = self:_getLevel()
    local soldierType = self:_getSoldierType()
    local initPosX = 260
    local initPosY = 90
    local paddingX = 10

    local resourcesNeedList = SoldierConfigReader:getResources(soldierType)
    local str = ""
    for idx, data in ipairs(resourcesNeedList) do
        local name = BackpackConfigRead:getName(data.id)
        str = string.format("%s%s×%d ", str, name, (data.count * count))
    end
    self._resourcesLabel:setString(str)
    Layout:layout(self._resourcesLabel, self:getContentSize(), Layout.left_top, cc.p(initPosX, initPosY))
end

function M:_createProduceButton()
    self._produceButton = CommonUI:createTextButton(self, "生产", "ui/login/login-bt.png")
    Layout:layout(self._produceButton, self:getContentSize(), Layout.right_center)
    self._produceButton:setSwallowTouches(false)
end

function M:_updateProduceButton(state)
    local tbl = {
        [ProduceState.Before] = {title = "征兵", callback = function()
            CommonUI:showLoadingLayer(true)
            local soldierType = self:_getSoldierType()
            local coorX, coorY = self._produceSoldierData:getLocalCoor()
            SocketManager:send(kCastleProductSoldier, {soldier_type = soldierType, number = self._selectedCount, x = coorX, y = coorY})
        end},
        [ProduceState.Ing] = {title = "加速", callback = function()
            self:_speedUpRequest()
        end},
        [ProduceState.End] = {title = "完成", callback = function()
            CommonUI:showLoadingLayer(true)
            local id = self._produceSoldierData:getId()
            SocketManager:send(kCastleProductSoldierReceive, {id = id})
        end},
    }
    local title = tbl[state].title
    self._produceButton:setText(title)
    local callback = tbl[state].callback
    self._produceButton.onClicked = callback

    if state == ProduceState.Ing then
        local reduceCount = self._produceSoldierData:getReduceCount()
        self._produceButton:setEnabled(reduceCount == 0)
    else
        self._produceButton:setEnabled(true)
    end
end

function M:_createSlider()
    self._slider = cc.ControlSlider:create("ui/team/sliderback.png", "ui/team/sliderback.png", "ui/team/progress.png")
    self._slider:setMinimumValue(1)
    self:addChild(self._slider)
    Layout:layout(self._slider, self:getContentSize(), Layout.center_bottom, cc.p(0, 10))
    self._slider:registerControlEventHandler(function(sender)
        self:_sliderValueChanged(sender)
    end, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
end

function M:_sliderValueChanged(sender)
    if not sender then
        return
    end
    -- 四舍五入取整
    local senderValue = sender:getValue()
    local value = math.floor(senderValue + 0.5)
    if senderValue ~= value then
        sender:setValue(value)
    else
        self:_updateSoldierInfo(value)
    end
end

function M:_createSliderButtons()
    local sliderSize = self._slider:getContentSize()
    self._addButton = CommonUI:createTextButton(self, "", "ui/team/button-add.png")
    Layout:layout(self._addButton, self:getContentSize(), Layout.center_bottom, cc.p(-sliderSize.width * 0.5 - 50, 20))
    self._addButton.onClicked = function()
        local value = self._slider:getValue()
        self._slider:setValue(value + 1)
    end
    self._addButton.onLongTouch = function()
        self._addButton.onClicked()
    end
    self._addButton:setSwallowTouches(false)

    self._subButton = CommonUI:createTextButton(self, "", "ui/team/button-sub.png")
    Layout:layout(self._subButton, self:getContentSize(), Layout.center_bottom, cc.p(sliderSize.width * 0.5 + 50, 20))
    self._subButton.onClicked = function()
        local value = self._slider:getValue()
        if value <= 1 then
            return
        end
        self._slider:setValue(value - 1)
    end
    self._subButton:setSwallowTouches(false)
    self._subButton.onLongTouch = function()
        self._subButton.onClicked()
    end
end

function M:_createProgressInfo()
    self._progressBar = ProgressBar.new("ui/main-page/main-exp02.png", "ui/main-page/main-exp01.png")
    self._progressBar:setPosition(self._slider:getPosition())
    self:addChild(self._progressBar)

    self._progressLabel = CommonUI:createLabel("", 20)
    self:addChild(self._progressLabel)
    self._progressLabel:setPosition(self._slider:getPosition())
end

function M:_showSlider(isShow)
    self._slider:setVisible(isShow)
    self._addButton:setVisible(isShow)
    self._subButton:setVisible(isShow)
end

function M:_showProgress(isShow)
    self._progressBar:setVisible(isShow)
    self._progressLabel:setVisible(isShow)
end

function M:_updateState(state)
    self:_updateProduceButton(state)
    if state == ProduceState.Before then
        self:_showSlider(true)
        self:_showProgress(false)
    elseif state == ProduceState.Ing then
        self:_showSlider(false)
        self:_showProgress(true)
    elseif state == ProduceState.End then
        self._progressLabel:setString("00:00:00")
        self._progressBar:setPercentage(100)
        self:_showSlider(false)
        self:_showProgress(true)
    end
    local count = self._produceSoldierData:getSoldierNumber()
    self._slider:setValue(count)
end

function M:_getLevel()
    local level = PlayerData:getCastleLevel()
    return level
end

function M:_getSoldierType()
    return self._produceSoldierData:getSoldierType()
end

function M:_speedUpRequest()
    local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
    local onePayTbl = PayRatioConfigReader:getOneProduceSoldierSpeedUpPay()
    local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
    local name = BackpackConfigRead:getName(onePayTbl.id)
    local str = string.format(__Localized("您是否花费%d%s开启征兵加速50%%服务?"), onePayTbl.count, name)
    AlertView.new(str, __Localized("取 消"), __Localized("确 定"))
    .onClicked = function(index)
        if 1==index then
            CommonUI:showLoadingLayer(true)
            local produceId = self._produceSoldierData:getId()
            local serviceType = Enum.SpeedUpType.OneProduceSoldier
            SocketManager:send(kServiceUse, {id = produceId, service_type = serviceType})
        end
    end
end


return M