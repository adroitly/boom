local BackgroundLayer = require("ui.common.BackgroundLayer")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local HeroDataManager = require("player-data.HeroDataManager")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local M = class("ui.map.layer-manager.ArmySupplyLayer", function(armyData)
	return cc.Layer:create()
end)

local m_infos = {
            { backpackType = Enum.ResourceType.SupplyFood, commandKey = Command.ArmyAddFoodOutside },
            { backpackType = Enum.ResourceType.SupplyPromote, commandKey = Command.ArmyPromoteOutside },
            { backpackType = Enum.ResourceType.SupplySoldier, commandKey = Command.ArmyAddSoldierOutside },
        }

local function _findBackpackType(commandKey)
    for _,info in pairs(m_infos) do
        if info.commandKey == commandKey then
            return info.backpackType
        end
    end
end

local function _getBackpackNumber(backpackType)
    local backpackData = BackpackDataManager:getBackpackDataByType(backpackType)
    local backpackNumber = nil == backpackData and 0 or backpackData:getItemNumber()
    return backpackNumber
end

function M:reload(armyData)
    self._armyData = armyData
end

function M:ctor()
    self:_createBackground()
    self:_createNodes()
    self:_registerSocketCallBack()
end


function M:onSocketClientDidCallback(cmd, msgTable, key)
    local commons = 
    {
        [Command.ArmyPromoteOutside] = function(msgTable)
            assert(msgTable.code)
            self:_showArmySupplyTips(msgTable.code)
        end,
        [Command.ArmyAddFoodOutside] = function(msgTable)
            assert(msgTable.code)
            self:_showArmySupplyTips(msgTable.code)
        end,
        [Command.ArmyAddSoldierOutside] = function(msgTable)
            assert(msgTable.code)
            self:_updateSoldierNumber()
            self:_showArmySupplyTips(msgTable.code)
        end,
    }
    local fun = commons[cmd]
    if fun then 
        fun(msgTable)
    end
end
function M:_updateSoldierNumber()
    local armySpriteManager = MapManager:getArmySpriteManager()
    local armySpriteNode = armySpriteManager:findArmySpriteNode(self._armyData)
    armySpriteNode:setArmyCount(self:_getSoldierNumber())
end

function M:_showArmySupplyTips(code)
    local tipsText = string.format(__Localized("%s"), 0 == code and "补给成功" or "补给失败")
    CommonUI:lightTips(tipsText)
    CommonUI:showLoadingLayer(false)
    self:removeFromParent()
end

function M:_createNodes()
    for key,data in pairs(m_infos) do
        local backpackType = data.backpackType
        local commandKey = data.commandKey
        local itemName = BackpackConfigRead:getName(backpackType)
        local backpackNumber = _getBackpackNumber(backpackType)
        local buttonName = backpackNumber > 0 and __Localized("使用") or __Localized("购买")

        local label = CommonUI:createLabel(string.format(__Localized("%s:%d个"), itemName, backpackNumber), 24)
        local button = CommonUI:createTextButton(self,buttonName,"ui/login/login-bt.png" )
        local buttonSize = button:getContentSize()
        self:addChild(label)

        local posy = Screen.height - BackgroundLayer.TitleHeight - (key - 0.5) * buttonSize.height
        label:setPosition(cc.p(Screen.width / 2, posy))
        button:setPosition(cc.p(Screen.width - buttonSize.width / 2 , posy))

        button.onClicked = function()
            self:_onSupplyAction(commandKey)
        end
    end
end

function M:_getTeamData()
    return self._armyData:getTeamData()
end

function M:_getHeroId()
    local teamData = self:_getTeamData()
    return teamData:getHeroId()
end

function M:_getHeroType()
    local heroId = self:_getHeroId()
    local heroType = HeroDataManager:getHeroTypeById(heroId)
    return heroType
end

function M:_getHeroData()
    local heroId = self:_getHeroId()
    return HeroDataManager:getHeroDataById(heroId)
end

function M:_getSoldierNumber()
    local teamData = self:_getTeamData()
    local soldierNumber = teamData:getSoldierNumber()
    return soldierNumber
end

function M:_checkPromote()
    local heroData = self:_getHeroData()
    local heroType = self:_getHeroType()
    local heroEnergyMax = HeroConfigRead:getEnergyMax(heroType)
    local heroEnergy = heroData:getHeroEnergy()
    if heroEnergy < heroEnergyMax then
        return true
    end
    CommonUI:lightTips(__Localized("部队士气已满，无需补给"))
    return false
end

function M:_checkFood()
    local teamData = self:_getTeamData()
    local soldierFood = teamData:getSoldierFood()
    local heroData = self:_getHeroData()
    local soldierNumber = self:_getSoldierNumber()
    local soldierType = teamData:getSoldierType()
    local heroLevel = heroData:getHeroLevel()
    local targetFood = SoldierConfigReader:getFood(soldierType) * soldierNumber
    if targetFood > soldierFood then
        return true
    end
    CommonUI:lightTips(__Localized("士兵粮食已满，无需补给"))
    return false
end

function M:_checkSoldier()
    local teamData = self:_getTeamData()
    local soldierNumber = self:_getSoldierNumber()
    local heroData = self:_getHeroData()
    local heroType = self:_getHeroType()
    local heroLevel = heroData:getHeroLevel()
    local troops = HeroAttribute:getTroops(heroType, heroLevel, teamData:getSoldierType())
    if soldierNumber < troops then
        return true
    end 
    CommonUI:lightTips(__Localized("士兵已满，无需补给"))
    return false
end


function M:_isCanSendData(commandKey)
    local backpackType = _findBackpackType(commandKey)
    local backpackNumber = _getBackpackNumber(backpackType)

    if backpackNumber <=0 then
        local goldNumber = _getBackpackNumber(Enum.ResourceType.Gold)
        if goldNumber <= 0 then
            CommonUI:alertRechargeLayer()
            return false
        else
            CommonUI:lightTips(__Localized("商城购买"))
            return false
        end
    end

    if Command.ArmyAddFoodOutside == commandKey then
        return self:_checkFood()
    elseif Command.ArmyPromoteOutside == commandKey then
        return self:_checkPromote()
    elseif Command.ArmyAddSoldierOutside == commandKey then
        return self:_checkSoldier()
    end
    
    return false
end

function M:_onSupplyAction(commandKey)
    local canSend = self:_isCanSendData(commandKey)
    if false == canSend then
        return
    end    local armyId = self._armyData:getArmyId()
    local sendData = {army_id = armyId}
    SocketManager:send(commandKey, sendData)
    CommonUI:showLoadingLayer(true)
end

-- 添加背景
function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, __Localized("战补"))
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end


function M:_registerSocketCallBack()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if "exit" == event then
            SocketManager:removeObserver(self)
        end
    end)
end

return M