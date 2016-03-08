local MapConfig = require("ui.map.data-manager.MapConfig")
local TeamDataManager = require("player-data.TeamDataManager")
local CollectDataManager = require("ui.collection.data-manager.CollectDataManager")
local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local TipsManager = require("ui.tips.TipsManager")

local M = class("ui.map.MainLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    Event:registerNodeEvent(self)
    Listener:addListener(self)
end

function M:onExit()
    self._mapDataManager:clean()
    Listener:removeListener(self)
    Touch:removeKeyboardTouch(self)
    TipsManager:stopTipsListener()
end

function M:onEnterTransitionFinish()
    self:initWithUserInfo()
    Touch:addKeyboardTouch(self)
    TipsManager:startTipsListener()
    CollectDataManager:collectInfoGetRequest()
    ProduceBuildingDataManager:produceInfoRequest()
    self:_getCountryWarOpenRequest()
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        self:_onExitConfirm()
    end
end


function M:onEnterMoreAlertLayer()
    self._alertLayer:onEnterMoreAlertLayer()
end

function M:onEnterInnerCityAction(buildingData)
    self._bottomBarLayer:onEnterInnerCityAction(buildingData)
end

function M:_onExitConfirm()
    local view = AlertView.new(__Localized("确定退出登录?"), __Localized("取 消"), __Localized("确 定"))
    view.onClicked = function(index)
        if 1 == index then
            self:_onExitAction()
        end
    end
end

function M:_onExitAction()
    SocketManager:disconnect()
    PlayerData:logout()
    Director:replaceSceneWithClass(app.firstUILayer)
end

function M:initWithUserInfo()
    self._mapDataManager = require("ui.map.data-manager.MapDataManager").new()
    self._mapDataManager:initUserInfo()
    self._mapDataManager:openSchedule()

    self._mapLayerManager = require("ui.map.layer-manager.MapLayerManager").new()
    self:addChild(self._mapLayerManager)

    self._coordinateLayer = require("ui.map.CoordinateLayer").new()
    self:addChild(self._coordinateLayer)

    self._castlePointArrowLayer = require("ui.map.CastlePointArrowLayer").new()
    self:addChild(self._castlePointArrowLayer)
    self._castlePointArrowLayer:setLocalZOrder(Enum.ZOrder.Dialog)

    local topBackgroundLayer = require("ui.map.MapTopLayer").new()
    topBackgroundLayer:setLocalZOrder(1)
    self:addChild(topBackgroundLayer)
    Layout:layout(topBackgroundLayer, Screen.size, Layout.left_top)

    -- 创建地下条
    self._bottomBarLayer = require("ui.tabbar.MainLayer").new()
    self:addChild(self._bottomBarLayer)

    self:_initArmy()
    self:_initArmyLead()
    self:_initAlertTipsLayer()
    self:_createAllFamousCityButton()
    self:_createCollectionIcon()
    self:_createPropertyNode(topBackgroundLayer)
    self:_createScrollNoticeLayer()
    self:_createAlertNoticeLayer()
    self:_createCountryWarLayer()
    self:_createWorldMapButton()
end

function M:homeButtonChange(imageFile)
    self._homeButton:changeNormalSprite(imageFile)
end

function M:getMapDataManager()
    return self._mapDataManager
end

function M:getMapLayerManager()
  return self._mapLayerManager
end

function M:getArmyLeadLayer()
    return self._armyLeadLayer
end

function M:getCoordinateLayer()
    return self._coordinateLayer
end

function M:getCastlePointArrowLayer()
    return self._castlePointArrowLayer
end

function M:getScrollNoticeLayer()
    return self._scrollNoticeLayer
end

-- 获取国战开启状态
function M:_getCountryWarOpenRequest()
    SocketManager:send(Command.CountryWarOpen, {})
end

function M:_initAlertTipsLayer()
    self._alertLayer = require("ui.alert.MainAlertLayer").new()
    self._alertLayer:setLocalZOrder(1)
    self:addChild(self._alertLayer)
end

function M:_initArmyLead()
    self._armyLeadLayer = require("ui.map.ArmyLeadLayer").new()
    self:addChild(self._armyLeadLayer)

    local myArmys = self._mapDataManager:getSelfArmysData()
    for _, armyData in pairs(myArmys) do
        self._armyLeadLayer:createArmy(armyData)
    end
    self._armyLeadLayer:resetPosition()
end

function M:_initArmy()
    -- 初始化自己军队
    local armyDataManager = MapManager:getArmyDataManager()
    local armySpriteManager = MapManager:getArmySpriteManager()
    local goOutTeamsData = TeamDataManager:getGoOutTeamList()
    for _,teamData in pairs(goOutTeamsData) do
        local armyData = armyDataManager:addArmyWithTeamData(teamData)
        armySpriteManager:armyDidCreate(armyData)
    end
end

function M:_createAllFamousCityButton()
    local famousCityButton = CommonUI:createTextButton(self, __Localized("名城"), "ui/city/famous-button.png")
    Layout:layout(famousCityButton, Screen.size, Layout.left_top , cc.p(10, 200))
    famousCityButton.onClicked = function()
        local scene = cc.Director:getInstance():getRunningScene()
        local layer = require("ui.map.layer-manager.AllFamousCityShowLayer").new()
        scene:addChild(layer)
    end
end


function M:_createCollectionIcon()
    local button = Button.new("ui/collection/btn-collect.png")
    self:addChild(button)
    Layout:layout(button, Screen.size, Layout.left_bottom , cc.p(10, 300))
    button.onClicked = function()
        local layer = require("ui.collection.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createPropertyNode(topBackgroundLayer)
    local function _openLayer()
        local scene = Director:getRunningScene()
        local layer = require("ui.backpack.layer-manager.PropertyUseShowLayer").new()
        scene:addChild(layer)
    end
    local TabbarLayer = require("ui.tabbar.MainLayer")
    local textButton = CommonUI:createTextButton(self, __Localized("道具"), "ui/main-page/button-useitem.png")
    Layout:layout(textButton, Screen.size, Layout.right_bottom , cc.p(10, TabbarLayer.TabbarLayerSize.height))
    textButton.onClicked = function()
        _openLayer()
    end
end

function M:_createWorldMapButton()
    local button = Button.new("ui/world-map/button-worldMap.png")
    self:addChild(button)
    Layout:layout(button, Screen.size, Layout.left_bottom , cc.p(10, 400))
    button.onClicked = function()
        local layer = require("ui.world-map.MainLayer").new(self._coordinateLayer:getCooridnate())
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createScrollNoticeLayer()
    self._scrollNoticeLayer = require("ui.notice.MainLayer").new()
    local scene = Director:getRunningScene()
    scene:addChild(self._scrollNoticeLayer)
    self._scrollNoticeLayer:setLocalZOrder(Enum.ZOrder.Dialog)
    -- self._scrollNoticeLayer:addScrollNotice("[Green 颜色]测试", 5)
end

function M:_createAlertNoticeLayer()
    local layer = require("ui.notice.notice-manager.AlertNoticeLayer"):createLoginEndAlertLayer()
    self:addChild(layer)
end

function M:_createCountryWarLayer()
    local CountryWarInfoLayer = require("ui.country-war.layer-manager.CountryWarInfoLayer")
    self._countryWarInfoButton = CountryWarInfoLayer:createWarInfoButton(self)
    self._countryWarInfoButton:setVisible(false)
end

function M:onListenCountryWarOpened(open)
    local isOpen = open == 1
    self._countryWarInfoButton:setVisible(isOpen)
    Listener:postEvent(Listener.EventName.onListenCountryWarInfoShow, false)
    if isOpen then
        local noticeStr = "[Yellow 国战已开启]"
        self:getScrollNoticeLayer():addScrollNotice(noticeStr, 3)
    end
end

return M


