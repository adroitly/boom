local CountryConfigReader = require("config-reader.CountryConfigReader")
local CountryWarRecordCell = require("ui.country-war.layer-manager.CountryWarRecordCell")
local CountryWarRecordData = require("ui.country-war.data-manager.CountryWarRecordData")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.country-war.layer-manager.CountryWarFightLayer", function()
    return cc.Layer:create()
end)

local kCountryWarRecordGet = "country_war_record_get"
local kCountryWarFight = "country_war_fight"
local kCountryWarInfoGet = "country_war_info_get"

local kLevelNeed = 31

function M:ctor(countryId)
    self._countryWarRecordDataList = {}

    self._countryId = countryId
    self:_createBackground()
    self:_createCountryIcon()
    self:_createInfoLabel()
    self:_createButtons()
    self:_createTableView()
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    SocketManager:addObserver(self)
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kCountryWarRecordGet, {country_id = self._countryId})
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kCountryWarRecordGet then
        CommonUI:showLoadingLayer(false)
        for k, record in pairs(msgTable.record_list) do
            local data = CountryWarRecordData.new(record)
            table.insert(self._countryWarRecordDataList, data)
        end
        self._tableView:reloadData()
    end
    
    if cmd == kCountryWarFight then
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips("宣战成功")
            SocketManager:send(kCountryWarInfoGet, {})
            self:removeFromParent()
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "宣战")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createCountryIcon()
    local countryIconRes = string.format("ui/country-icon/country-icon-%d.png", self._countryId)
    self._countryIcon = cc.Sprite:create(countryIconRes)
    self:addChild(self._countryIcon)
    Layout:layout(self._countryIcon, Screen.size, Layout.center, cc.p(0, -self._countryIcon:getContentSize().height - 150))
end

function M:_createInfoLabel()
    local countryName = CountryConfigReader:getCountryName(self._countryId)
    local infoStr = string.format("您是否确认向%s国宣战？宣战后不可撤销", countryName)
    self._infoLabel = CommonUI:createLabel(infoStr, 30)
    self:addChild(self._infoLabel)
    Layout:layout(self._infoLabel, Screen.size, Layout.center, cc.p(0, -150))
end

function M:_createTableView()
    local cellSize = CountryWarRecordCell.WarRecordCellSize
    local viewSize = cc.size(cellSize.width, cellSize.height * 5)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), self._infoLabel:getPositionY() - self._infoLabel:getContentSize().height - viewSize.height))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return CountryWarRecordCell.WarRecordCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = CountryWarRecordCell.new(self._countryId)
    end
    cell:reset(self._countryWarRecordDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._countryWarRecordDataList)
end

function M:_createButtons()
    local setInfo = {
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "取消", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "确定", 30},
    }
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    local btnSize = tempSprite:getContentSize()
    local buttonSetLayer = require("libs.widget.ButtonSetLayer").new(setInfo)
    buttonSetLayer:setLayout(cc.size(Screen.width, btnSize.height))
    self:addChild(buttonSetLayer)
    buttonSetLayer.onClicked = function(sender, index)
        self:_onButtonClicked(sender, index)
    end
    buttonSetLayer:setPosition(cc.p(0, Screen.height * 0.5 - btnSize.height - 200))
end

function M:_onButtonClicked(sender, index)
    if index == 0 then
        self:removeFromParent()
    elseif index == 1 then
        if PlayerData:getUserInfoData():getLevel() <= kLevelNeed then
            CommonUI:lightTips("等级不足，不能宣战")
            return
        end
        SocketManager:send(kCountryWarFight, {country_id = self._countryId})
    end
end


return M