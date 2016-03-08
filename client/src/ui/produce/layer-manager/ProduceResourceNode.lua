local TimeTools = require("ui.common.TimeTools")
local M = class("ui.produce.layer-manager.ProduceResourceNode", function ()
    return cc.Node:create()
end)
local ProduceState = {
    Before = 1,
    Ing = 2,
    End = 3,
}

local kCastleProductItem = "castle_product_item"
local kCastleProductItemReceive = "castle_product_item_receive"
local kServiceUse = "service_use"

local function _getResoucesName(id)
    return string.format("%s.png", id)
end

function M:ctor(produceResourceData)
    self._produceResourceData = produceResourceData
    self:_createBackground()
    self:_createInfoLabels()
    self:_createProduceButton()
    self:_createProgressBar()

    self:registerScriptHandler(function(event)
        if "exit" == event then
            self:_removeTimer()
        end
        if "enterTransitionFinish" == event then
            self:_startTimer()
        end
    end)
end

function M:_startTimer()
    local endTime = self._produceResourceData:getProduceEndTime()
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

function M:_removeTimer()
    TimerInterval:removeTimer(self)
end

function M:_updateProgress()
    local endTime = self._produceResourceData:getProduceEndTime()
    local nowTime = PlayerData:getServerTime()
    local diffTime = endTime - nowTime
    local count = self._produceResourceData:getItemNumber()
    local rate = self._produceResourceData:getProduceTime()
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

function M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    local size = background:getContentSize()
    self:setContentSize(size)
    background:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
end

function M:_createInfoLabels()
    local resourceId = self._produceResourceData:getItemType()
    local iconName = _getResoucesName(resourceId)
    local size = self:getContentSize()
    local icon = CommonUI:createSpriteWithFrame("stage-icon", iconName)
    self:addChild(icon)
    Layout:layout(icon, size, Layout.left_center, cc.p(50, 0))

    self._limitLabel = CommonUI:createLabel("", 24)
    self:addChild(self._limitLabel)

    self._needTimeLabel = CommonUI:createLabel("", 24)
    self:addChild(self._needTimeLabel)

    self:_updateInfo()
end

function M:_updateInfo()
    local produceLimit = self:_getProduceLimit()
    local str = string.format("%s%d", __Localized("生产上限："), produceLimit)
    self._limitLabel:setString(str)

    local size = self:getContentSize()
    Layout:layout(self._limitLabel, size, Layout.left_center, cc.p(130, 0))

    local oneNeedTime = self._produceResourceData:getProduceTime()
    local needTime = produceLimit * oneNeedTime
    local timeStr = TimeTools:getTimeStringBySec(needTime)
    str = string.format("%s%s", __Localized("所需时间："), timeStr)
    self._needTimeLabel:setString(str)
    Layout:layout(self._needTimeLabel, size, Layout.left_center, cc.p(350, 0))
end

function M:_showNeedTimeLabel(isShow)
    self._needTimeLabel:setVisible(isShow)
end

function M:_createProgressBar()
    self._progressBar = ProgressBar.new("ui/main-page/main-exp02.png", "ui/main-page/main-exp01.png")
    self:addChild(self._progressBar)
    self._progressBar:setPosition(cc.p(450, 30))
    self._progressLabel = CommonUI:createLabel("1000", 24)
    self:addChild(self._progressLabel)
    self._progressLabel:setPosition(self._progressBar:getPosition())

    self:_updateProgress()
end

function M:_showProgrssBar(isShow)
    self._progressBar:setVisible(isShow)
    self._progressLabel:setVisible(isShow)
end

function M:_updateState(state)
    self:_updateProduceButton(state)
    if state == ProduceState.Before then
        self:_showProgrssBar(false)
    elseif state == ProduceState.Ing then
        self:_showProgrssBar(true)
    elseif state == ProduceState.End then
        self._progressLabel:setString("00:00:00")
        self._progressBar:setPercentage(100)
        self:_showProgrssBar(true)
    end
end

function M:_createProduceButton()
    self._produceButton = CommonUI:createTextButton(self, "生产", "ui/login/login-bt.png")
    Layout:layout(self._produceButton, self:getContentSize(), Layout.right_center)
    self._produceButton:setSwallowTouches(false)
end

function M:_updateProduceButton(state)
    local tbl = {
        [ProduceState.Before] = {title = "生产", callback = function()
            self:_produceRequest()
        end},
        [ProduceState.Ing] = {title = "加速", callback = function()
            self:_speedUpRequest()
        end},
        [ProduceState.End] = {title = "完成", callback = function()
            self:_produceDoneRequest()
        end},
    }
    local title = tbl[state].title
    self._produceButton:setText(title)
    local callback = tbl[state].callback
    self._produceButton.onClicked = callback

    if state == ProduceState.Ing then
        local reduceCount = self._produceResourceData:getReduceCount()
        self._produceButton:setEnabled(reduceCount == 0)
    else
        self._produceButton:setEnabled(true)
    end
end

function M:_produceDoneRequest()
    local BackpackDataManager = require("player-data.BackpackDataManager")
    local itemType = self._produceResourceData:getItemType()
    local backpackData = BackpackDataManager:getBackpackDataByType(itemType)
    local itemNumber = 0
    if backpackData then
        itemNumber = backpackData:getItemNumber()
    end
    local CastleConfigReader = require("ui.city.king.CastleConfigReader")
    local limit = CastleConfigReader:getStorageConfine(PlayerData:getCastleLevel())
    if itemNumber >= limit then
        CommonUI:lightTips(__Localized("您的资源已达上限，请提升等级"))
        return
    end
    local produceId = self._produceResourceData:getId()
    SocketManager:send(kCastleProductItemReceive, {id = produceId})
    CommonUI:showLoadingLayer(true)
end

function M:_produceRequest()
    local resourceId = self._produceResourceData:getItemType()
    local coorX, coorY = self._produceResourceData:getLocalCoor()
    SocketManager:send(kCastleProductItem, {item_type = resourceId, x = coorX, y = coorY})
    CommonUI:showLoadingLayer(true)
end

function M:_speedUpRequest()
    local PayRatioConfigReader = require("config-reader.PayRatioConfigReader")
    local onePayTbl = PayRatioConfigReader:getOneProduceResourceSpeedUpPay()
    local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
    local name = BackpackConfigRead:getName(onePayTbl.id)
    local str = string.format(__Localized("您是否花费%d%s开启资源生产队列加速50%%服务"), onePayTbl.count, name)
    AlertView.new(str, __Localized("取 消"), __Localized("确 定"))
    .onClicked = function(index)
        if 1==index then
            CommonUI:showLoadingLayer(true)
            local produceId = self._produceResourceData:getId()
            local serviceType = Enum.SpeedUpType.OneProduceResource
            SocketManager:send(kServiceUse, {id = produceId, service_type = serviceType})
        end
    end
end


function M:_getProduceLimit()
    local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
    local guildData = PlayerData:getGuildData()
    local produceLimit = self._produceResourceData:getProduceLimit()
    local vipLv = PlayerData:getUserInfoData():getVip()
    local productionUp = VipConfigReader:getProductionUp(vipLv)
    if not guildData then
        produceLimit = math.floor(produceLimit * productionUp)
        return
    end
    local pro = 0
    local value = 0
    local guildSkillDataList = guildData:getGuildSkillDataList()
    for skillType, skillData in pairs(guildSkillDataList) do
        local skillId = skillData:getSkillId()
        local tempValue, tempPro = self:_getValueAndPro(skillId)
        value = value + tempValue
        pro = pro + tempPro
    end
    produceLimit = produceLimit * (productionUp + pro) + value
    produceLimit = math.floor(produceLimit)
    return produceLimit
end

function M:_getValueAndPro(skillId)
    local GuildSkillConfigRead = require("ui.guild.data-manager.GuildSkillConfigRead")
    local itemType = self._produceResourceData:getItemType()
    local value = 0
    local pro = 0
    if itemType == Enum.ResourceType.Food then
        value = GuildSkillConfigRead:getFoodValue(skillId)
        pro = GuildSkillConfigRead:getFoodPro(skillId)
    elseif itemType == Enum.ResourceType.Wood then
        value = GuildSkillConfigRead:getWoodValue(skillId)
        pro = GuildSkillConfigRead:getWoodPro(skillId)
    elseif itemType == Enum.ResourceType.Stone then
        value = GuildSkillConfigRead:getStoneValue(skillId)
        pro = GuildSkillConfigRead:getStonePro(skillId)
    elseif itemType == Enum.ResourceType.Coin then
        value = GuildSkillConfigRead:getCoinValue(skillId)
        pro = GuildSkillConfigRead:getCoinPro(skillId)
    end
    return value, pro / 1000
end

return M