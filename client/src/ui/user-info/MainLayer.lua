local TimeTools = require("ui.common.TimeTools")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local FlagData = require("ui.guild.data-manager.FlagData")
local BackpackDataManager = require("player-data.BackpackDataManager")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local TipsManager = require("ui.tips.TipsManager")

local M = class("ui.user-info.MainLayer", function ()
    return cc.Layer:create()
end)

local kUserLevelUpUseItem = "user_level_up_use_item"
local kUserLevelUpTime = "user_level_up_time"
local kUserSalaryReceive = "user_salary_receive"
local kUserLevelUpReduceFifty = "user_level_up_reduce_50"

local function _getShowTextFromTable(table)
    local showText = ""
    for _,value in pairs(table) do
        showText = string.format("%s%s\n", showText, value)
    end
    return showText
end

local function _showTips(name, code)
    assert(name and code)
    local tipsText = string.format("%s%s", name , 0 == code and __Localized("成功") or __Localized("失败"))
    CommonUI:lightTips(tipsText)
end

local function _getPositionX(index)
    local maxCount = 4
    local buttonWith = Screen.width / maxCount
    return buttonWith * (index - 0.5)
end

function M:ctor()
    self:setTag(Enum.LayerTag.PlayerLevelUpgrade)
    self._canUpgrade = false
    self:_createBackground()
    self:_createShowSalaryLayer()
    self:_createUpgradeNodes()
    self:_createProgressTimer()
    self:_createProgressTimerLabel()
    self:_createLevelLabel()
    self:_createDonateButton()
    self:_createPickMoneyButton()
    self:_createAppointButton()
    self:_createSettingButton()
    self:_createHandler()
    self:_initUserInfos()
    self:_updateInfo()
end


function M:onSocketClientDidCallback(cmd, msgTable, key)
    local commons = 
    {
        [kUserLevelUpTime] = function(msgTable)
            CommonUI:showLoadingLayer(false)
            assert(msgTable and msgTable.code)
            _showTips(__Localized("升级"), msgTable.code)
        end,
        [kUserSalaryReceive] = function(msgTable)
            CommonUI:showLoadingLayer(false)
            assert(msgTable and msgTable.code)
            _showTips(__Localized("领取俸禄"), msgTable.code)
        end,
        [kUserLevelUpReduceFifty] = function(msgTable)
            CommonUI:showLoadingLayer(false)
            assert(msgTable and msgTable.code)
            _showTips(__Localized("加速"), msgTable.code)
        end
    }

    local fun = commons[cmd]
    if fun then 
        fun(msgTable)
    end
end


function M:_initUserInfos()
    self:_createPlayerHead()
    self:_createCountrysLabel()
    self:_creatGuildNodes()
end

function M:_createHandler()
    SocketManager:addObserver(self)
    
    TimerInterval:addTimer(self, 1)
    Event:registerNodeEvent(self)   
end

function M:onUpdate()
    self:_updateInfo()
end

function M:onExit()
    SocketManager:removeObserver(self)
    TimerInterval:removeTimer(self)
    TipsManager:removeTipsListener(Enum.TipsType.PickMoney, self._pickMoneyButton)
end

function M:_updateInfo()
    self:_updateSelfInfosLabel()
    self:_updateProgressTimerNodes()
    self:_updateVip()
    self:_updatePickMoney()
end

function M:_updateUpgradeButton()
    local isInFiftyAccelerate = PlayerData:getUserInfoData():isInFiftyAccelerate()
    if isInFiftyAccelerate then
        self._upgradeButton:setEnabled(false)
    else
        self._upgradeButton:setEnabled(true)
    end
end

function M:_updatePickMoney()
    local isCanPickMoney = self:_checkCanPickMoney()
    self._pickMoneyButton:setEnabled(isCanPickMoney)
    if isCanPickMoney then
        self._pickMoneyButton:setText(__Localized("领取俸禄"))
    else
        self._pickMoneyButton:setText(__Localized("已领取"))
    end
end

function M:_updateVip()
   local vip = PlayerData:getUserInfoData():getVip()
   self._vipButton:setText(string.format("VIP%d", vip))
end

function M:_updateProgressTimerNodes()
    local needTime = PlayerData:getUserInfoData():getLevelUpEndTime() - PlayerData:getServerTime()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    if 90 == currentLevel or needTime <= 0 then
        self:_onUpgradeNoTime(currentLevel)
        return
    end
    self:_onUpgradeHasTime(currentLevel, needTime)
end

function M:_onUpgradeHasTime(currentLevel, needTime)
    local costTime = OfficerConfigRead:getCostTime(currentLevel)
    self._upgradeButton:setText(__Localized("加速"))

    local percentage = (1 - needTime / costTime) * 100
    self._progressTimer:setPercentage(percentage)

    self._needTimeLabel:setString(Function:timeToDateString(needTime))
    self._canUpgrade = false
    self:_updateExpLabel(currentLevel, percentage)
    self:_updateUpgradeButton()
end

function M:_onUpgradeNoTime(currentLevel)
    self._upgradeButton:setText(__Localized("升级"))
    self._needTimeLabel:setString("00:00:00")
    self._progressTimer:setPercentage(100)
    self._canUpgrade = true
    self:_updateExpLabel(currentLevel, 100)
    if self:_hasNextLevel() then
        self._upgradeButton:setEnabled(true)
    else
        self._upgradeButton:setEnabled(false)
    end
end

function M:_updateExpLabel(currentLevel, percentage)
    local levelText = string.format("等级:%d", currentLevel)
    self._levelLabel:setString(levelText)

    local nextExp = OfficerConfigRead:getNextExp(currentLevel)
    local nowExp = math.floor(nextExp * percentage / 100)
    local showText = string.format("%d/%d", nowExp, nextExp)
    self._expLabel:setString(showText)
end

function M:_createBackground()
    local playerId = PlayerData:getPlayerId()
    local backgroundLayer = BackgroundLayer.new(self, "ID:" .. playerId)
    backgroundLayer:setBackButtonCallback(function(returnType)
        self:removeFromParent()
    end)
end

function M:_createLevelLabel()
    self._levelLabel = CommonUI:createLabel(__Localized("等级:99"), 24)
    self:addChild(self._levelLabel)
    local progressSize = self._progressTimer:getContentSize()
    local labelSize = self._levelLabel:getContentSize()
    self._levelLabel:setPosition(cc.p(Screen.width/ 2 - progressSize.width / 2 - labelSize.width / 2, Screen.height / 2))
end

function M:_createUpgradeNodes()
    self._upgradeButton = CommonUI:createTextButton(self, __Localized("升级"), "ui/login/login-up.png")
    Layout:layout(self._upgradeButton, Screen.size, Layout.right_center)
    self._upgradeButton.onClicked = function()
        self:_onUpgradeButtonAction()
    end
end

function M:_createShowSalaryLayer()
    local layer = require("ui.user-info.layers.SalaryShowLayer").new()
    local x = (Screen.width - layer:getContentSize().width) / 2
    layer:setPosition(cc.p(x,100))
    self:addChild(layer)
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    layer:showPageByLevel(currentLevel)
end

function M:_hasNextLevel()
    local growth = self:_getGrowth()
    if growth <= 0 then
        return false
    end
    return true
end

function M:_onUpgradeButtonAction()
    if self._canUpgrade then
        if self:_hasNextLevel() then
            CommonUI:showLoadingLayer(true)
            SocketManager:send(kUserLevelUpTime, {})
        else
            CommonUI:lightTips(__Localized("玩家等级已达上限，无法升级"))
        end
        return
    end
    self:_checkSendAccelerate()
end

function M:_sendAccelerateAction()
    local curLevel = PlayerData:getUserInfoData():getLevel()
    local speedCostStr = OfficerConfigRead:getSpeedCost(curLevel)
    local costTable = Utils:formatStringToNumberTable(speedCostStr)
    local backpackType = tonumber(costTable[1][1])
    local cost = tonumber(costTable[1][2])
    if BackpackDataManager:checkBackpackEnough(backpackType, cost) then
        local alert = AlertView.new(string.format(__Localized("确定花费%s元宝加速?"), cost), __Localized("取 消"), __Localized("确 定"))
        alert.onClicked = function(index)
            if 1 == index then
                local sendData = {}
                SocketManager:send(kUserLevelUpReduceFifty, sendData)
                CommonUI:showLoadingLayer(true)
            end
        end
        
    else
        self:_showRecharge(backpackType)
    end
end

function M:_checkSendAccelerate()
    local isInFiftyAccelerate = PlayerData:getUserInfoData():isInFiftyAccelerate()
    if false == isInFiftyAccelerate then
        self:_sendAccelerateAction()
    else
        CommonUI:lightTips(__Localized("当前等级已使用过加速50%道具"))
    end
end

function M:_createProgressTimer()
    self._progressTimer = ProgressBar.new("ui/hero-museum/progressbg.png","ui/hero-museum/progressup.png")
    self:addChild(self._progressTimer)
    self._progressTimer:setPosition(cc.p(Screen.width / 2, Screen.height / 2))
end

function M:_createProgressTimerLabel()
    self._expLabel = CommonUI:createLabel("0/300", 20)
    self:addChild(self._expLabel)
    local x, y = self._progressTimer:getPosition()
    self._expLabel:setPosition(cc.p(x, y))
    self._needTimeLabel = CommonUI:createLabel("00:00:00", 24)
    local labelSize = self._needTimeLabel:getContentSize()
    self:addChild(self._needTimeLabel)
    self._needTimeLabel:setPosition(cc.p(x, y + labelSize.height))
end

function M:_createDonateButton()
    local button = CommonUI:createTextButton(self, __Localized("捐官"), "ui/login/login-up.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(_getPositionX(2), buttonSize.height / 2))

    button.onClicked = function()
        self:_onDonateButtonAction()
    end
end

function M:_showRecharge(backpackType)
     CommonUI:alertRechargeLayer()
end

function M:_onDonateButtonAction()
    local scene = cc.Director:getInstance():getRunningScene()
    local layer = require("ui.user-info.layers.ContributeOfficerLayer").new()
    scene:addChild(layer)
end

function M:_checkCanPickMoney()
    local userInfoData = PlayerData:getUserInfoData()
    local serverTime = PlayerData:getServerTime()
    local salaryTime = userInfoData:getSalaryReceiveTime()
    return false == TimeTools:isSameDay(serverTime, salaryTime)
end

function M:_createPickMoneyButton()
    self._pickMoneyButton = CommonUI:createTextButton(self, __Localized("领取俸禄"), "ui/login/login-up.png")
    TipsManager:addTipsListener(Enum.TipsType.PickMoney, self._pickMoneyButton)
    local buttonSize = self._pickMoneyButton:getContentSize()
    self._pickMoneyButton:setPosition(cc.p(_getPositionX(3), buttonSize.height / 2))

    self._pickMoneyButton.onClicked = function()
        
        if self:_checkCanPickMoney() then
            CommonUI:showLoadingLayer(true)
            local sendData = {}
            SocketManager:send(kUserSalaryReceive, sendData)
        else
            CommonUI:lightTips(__Localized("当前已经领过俸禄了"))
            self._pickMoneyButton:setEnabled(false)
        end
    end
end

function M:_createAppointButton()
    local button = CommonUI:createTextButton(self, __Localized("任命"), "ui/login/login-up.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(_getPositionX(1), buttonSize.height / 2))

    button.onClicked = function()
        self:_onAppointButtonAction()
    end
end

function M:_onAppointButtonAction()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    local isCanAppoint = OfficerConfigRead:isCanAppoint(currentLevel)
    if 0 ~= isCanAppoint then
        local layer = require("ui.user-info.layers.AppointLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
        return
    end
    local minAppointLevel = OfficerConfigRead:getMinLevelHasAppointPower()
    CommonUI:lightTips(string.format(__Localized("官职等级需达到%s级开启此功能"), minAppointLevel))
end

function M:_createSettingButton()
    local button = CommonUI:createTextButton(self, __Localized("设置"), "ui/login/login-up.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(_getPositionX(4), buttonSize.height / 2))

    button.onClicked = function()
        self:_onSettingButtonClick()
    end
end

function M:_creatGuildNodes()
    local guildData = PlayerData:getGuildData()
    local flag = guildData:getFlag()
    local flagData = FlagData.new(flag)
    local guildButton = Button.new(flagData:getFileName())
    local buttonSize = guildButton:getContentSize()
    self:addChild(guildButton)
    Layout:layout(guildButton, Screen.size, Layout.right_top , cc.p(0, BackgroundLayer.TitleHeight + buttonSize.height / 4))

    self:_createGuildNameLabel(guildButton, buttonSize)
    self:_createGuildLeaderNameLabel(guildButton, buttonSize)

    guildButton.onClicked = function()
        self:_onGuildButtonAction()
    end
end

function M:_onSettingButtonClick()
    local layer = require("ui.setting.MainLayer").new()
    local scene = Director:getRunningScene()
    scene:addChild(layer)
end

function M:_onGuildButtonAction()
    local scene = cc.Director:getInstance():getRunningScene()
    local layer = require("ui.guild.MainLayer").new()
    scene:addChild(layer)
end

function M:_createGuildNameLabel(parent, parentSize)
    local showText = string.format(__Localized("%s"), self:_getGuildName())
    local label = CommonUI:createLabel(showText, 24)
    local labelSize = label:getContentSize()
    parent:addChild(label)
    Layout:layout(label, parentSize, Layout.center_top, cc.p(0, -labelSize.height / 2))
end

function M:_createGuildLeaderNameLabel(parent, parentSize)
    local showText = string.format(__Localized("%s"), self:_getGuildLeaderName())
    local label = CommonUI:createLabel(showText, 24)
    local labelSize = label:getContentSize()
    parent:addChild(label)
    Layout:layout(label, parentSize, Layout.center_bottom, cc.p(0, labelSize.height / 2))
end

function M:_createPlayerHead()
    local frame = PlayerData:getPlayerIconFrame()
    local playerIcon = cc.Sprite:createWithSpriteFrame(frame)
    local playerSize = playerIcon:getContentSize()
    self:addChild(playerIcon)
    Layout:layout(playerIcon, self:getContentSize(), Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight + playerSize.height / 4))

    self:_createSelfInfosLabel(playerSize)
    self:_createVipButton(playerSize)
end

function M:_updateSelfInfosLabel()
    local heroInfosTable = self:_getHeroInfosTable()
    local showText = _getShowTextFromTable(heroInfosTable)
    self._selfInfoLabel:setString(showText)
end

function M:_createSelfInfosLabel(playerSize)
    local heroInfosTable = self:_getHeroInfosTable()
    local showText = _getShowTextFromTable(heroInfosTable)
    self._selfInfoLabel = CommonUI:createLabel(showText, 24)
    self._selfInfoLabel:setAlignment(0)
    self:addChild(self._selfInfoLabel)

    Layout:layout(self._selfInfoLabel, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 50))

end

function M:_createCountrysLabel()
    local space = "     "
    local countryText = string.format(__Localized("国%s家:%s"), space, self:_getCountry())
    local kingText = string.format(__Localized("皇%s帝:%s"), space, self:_getKing())
    local showText = string.format("%s%s%s",countryText, space, kingText)
    local label = CommonUI:createLabel(showText, 24)
    self:addChild(label)
    Layout:layout(label, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))
end

function M:_createVipButton(playerSize)
    self._vipButton = CommonUI:createTextButton(self, "VIP1", "ui/main-page/button-vip.png")
    local buttonSize = self._vipButton:getContentSize()
    Layout:layout(self._vipButton, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight + playerSize.height + buttonSize.height / 2))

    self._vipButton.onClicked = function()
        local layer = require("ui.recharge.layer-manager.VipRightsLayer").new()
        local scene = Director:getRunningScene()
        scene:addChild(layer)
    end
end

function M:_getHeroInfosTable()
    return {
                string.format(__Localized("玩家名称:%s"), self:_getNickName()),
                string.format(__Localized("官       职:%s"), self:_getOfficeName()),
                string.format(__Localized("功勋成长:%s/h%s"), self:_getGrowth(), self:_getAccelerate()),
            }
end

function M:_createHeroInfosLabel(playerSize)
    local heroInfosName = self:_getHeroInfosName()
    local labelText = ""
    for _,value in pairs(heroInfosName) do
        labelText = string.format("%s%s\n", labelText, value)
    end
    local label = CommonUI:createLabel(labelText, 24)
    label:setAlignment(0)
    self:addChild(label)

    Layout:layout(label, self:getContentSize(), Layout.left_top, cc.p(playerSize.width + 50, BackgroundLayer.TitleHeight))
end

function M:_createHeroGuildInfosLabel(playerSize)
    local heroGuildInfosName = self:_getHeroGuildInfosName()
    local labelText = ""
    for _,value in pairs(heroGuildInfosName) do
        labelText = string.format("%s%s\n", labelText, value)
    end
    local label = CommonUI:createLabel(labelText, 24)
    label:setAlignment(0)
    self:addChild(label)

    Layout:layout(label, self:getContentSize(), Layout.left_top, cc.p(0, playerSize.height + BackgroundLayer.TitleHeight + 100))
end

function M:_getAccelerate()
    local accelerate = 0
    if PlayerData:getUserInfoData():isInFiftyAccelerate() then
        accelerate = accelerate + 50
    end
    if 0 == accelerate then
        return ""
    end
    local showTextStr = "    加速"
    return string.format("%s%d%s", showTextStr, accelerate , "%")
end

-- 功勋成长
function M:_getGrowth()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    local growth = OfficerConfigRead:getGrowthRate(currentLevel) * 60
    return growth
end

function M:_getNickName()
    return PlayerData:getNickName()
end

function M:_getBuildingLevel()
    return PlayerData:getCastleLevel()
end

function M:_getKing()
    return __Localized("暂无")
end

function M:_getCountry()
    return CountryConfigReader:getCountryName(PlayerData:getUserInfoData():getCountryId()) or 0
end
-- 君王
function M:_getGuildLeaderName()
    local guildData = PlayerData:getGuildData()
    return guildData:getLeaderName()
end

function M:_getGuildName()
    local guildData = PlayerData:getGuildData()
    if guildData:getName() == "" then
        return __Localized("加入势力")
    end
    return guildData:getName()
end

function M:_getOfficeName()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    local officeName = OfficerConfigRead:getOfficerName(currentLevel)
    return officeName
end


return M