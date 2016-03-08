local ResourcePointUtils    = require("ui.map.data-manager.ResourcePointUtils")
local DialogUtils           = require("ui.map-subview.DialogUtils")
local MapConfig             = require("ui.map.data-manager.MapConfig")
local CollectDataManager    = require("ui.collection.data-manager.CollectDataManager")
local CountryWarOpenCallback        = require("ui.map.logic.CountryWarOpenCallback")

local M = class("ui.map-subview.ClickCastleDialog", function()
    return cc.Node:create()
end)

function M:newClickCastleDialog(castleData)
    local node = M.new()
    node:initWithPoint(castleData)
    local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:addChild(node, Enum.ZOrder.Dialog)
    return node
end

function M:initWithPoint(castleData)
    self._castleData = castleData
    assert(castleData)

    local coor = self._castleData:getHomeCoor()
    local center = MapConfig:getResourcePointPosition(coor)
    self:setPosition(center)

    local localCoor = castleData:getHomeCoor()
    local twoDCoor = MapConfig:localTo2D(localCoor)
    DialogUtils:showCoordinate(self, twoDCoor)

    -- 点击自己主城
    local space = DialogUtils:getDialogRadius()
    local playerId = self._castleData:getOwnerId()
    local isMy = ResourcePointUtils:isMyHomeCastle(castleData)
    if isMy then
        local enterBt = CommonUI:createTextButton(self, __Localized("进入"), "ui/common/ok.png")
        enterBt:setPosition(cc.p(-space, 0))
        enterBt.onClicked = function()
            self:onEnterAction()
        end
        return
    end

    local twoDCoor = MapConfig:localTo2D(localCoor)
    if not CollectDataManager:isDataCollected(twoDCoor) then
        local collectBt = CommonUI:createTextButton(self, __Localized("收藏"), "ui/common/ok.png")
        collectBt:setPosition(cc.p(0, -space))
        collectBt.onClicked = function()
            self:onCollectAction()
        end
    end

    -- 点击同势力
    local resGuildId = self._castleData:getGuildId()
    local isSameGuild = PlayerData:isSameGuild(resGuildId)
    if isSameGuild then
        local searchBt = CommonUI:createTextButton(self, __Localized("侦查"), "ui/common/ok.png")
        searchBt:setPosition(cc.p(-space, 0))
        searchBt.onClicked = function()
            self:onSearchAction()
        end

        local aidBt = CommonUI:createTextButton(self, __Localized("援助"), "ui/common/ok.png")
        aidBt:setPosition(cc.p(space, 0))
        aidBt.onClicked = function()
            self:onAidAction()
        end
        return
    end

    -- 点击同国
    local resCountryId = self._castleData:getCountryId()
    local isSameCountry = PlayerData:isSameCountry(resCountryId)
    if isSameCountry then
        local searchBt = CommonUI:createTextButton(self, __Localized("侦查"), "ui/common/ok.png")
        searchBt:setPosition(cc.p(-space, 0))
        searchBt.onClicked = function()
            self:onSearchAction()
        end
        return
    end

    -- 点击敌国(国战开启攻击按钮)
    local searchBt = CommonUI:createTextButton(self, __Localized("侦查"), "ui/common/ok.png")
    searchBt:setPosition(cc.p(-space, 0))
    searchBt.onClicked = function()
        self:onSearchAction()
    end

    if CountryWarOpenCallback:isCountryWarOpen() then
        local attackBt = CommonUI:createTextButton(self, __Localized("攻击"), "ui/common/ok.png")
        attackBt:setPosition(cc.p(space, 0))
        attackBt.onClicked = function()
            self:onAttackAction()
        end
    end
end

function M:onEnterAction()
    local mapLayer = MapManager:getMapMainLayer()
    mapLayer:onEnterInnerCityAction(self._castleData)
    MapManager:removeDialogLayer()
end

function M:onSearchAction()
    Print:Table(self._castleData, "data =")
    require("ui.outside-search.MainLayer"):createOtherCastleLayer(self._castleData)

    MapManager:removeDialogLayer()
end

function M:onAidAction()
    local localCoor = self._castleData:getHomeCoor()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.Aid, localCoor)

    MapManager:removeDialogLayer()
end

function M:onCollectAction()
    local collectLayer = require("ui.collection.layer-manager.CollectLayer").new(self._castleData)
    cc.Director:getInstance():getRunningScene():addChild(collectLayer)
    MapManager:removeDialogLayer()
end

function M:onAttackAction()
    local coor = self._castleData:getHomeCoor()
    DialogUtils:showOutTeamLayer(Enum.GoOutOperation.AttackBuilding, coor)

    MapManager:removeDialogLayer()
end

return M