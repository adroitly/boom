local CountryWarCell = require("ui.country-war.layer-manager.CountryWarCell")
local CountryWarData = require("ui.country-war.data-manager.CountryWarData")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.country-war.MainLayer", function()
    return cc.Layer:create()
end)

local kCountryWarInfoGet = "country_war_info_get"

function M:ctor()
    self._countryWarDataList = {}

    self:_createBackground()
    self:_createTableView()
    self:_createButton()

    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    SocketManager:addObserver(self)
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kCountryWarInfoGet, {})
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kCountryWarInfoGet then
        self._countryWarDataList = {}
        CommonUI:showLoadingLayer(false)
        for k, info in pairs(msgTable.info_list) do
            local data = CountryWarData.new(info)
            table.insert(self._countryWarDataList, data)
        end
        self._tableView:reloadData()
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "国战")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTableView()
    local cellSize = CountryWarCell.CountryWarCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:onTableViewCellTouched(tableView, cell)
    local curSelectedIndex = cell:getIdx()
    if curSelectedIndex == self._selectedIndex then
        return
    end
    if self._selectedIndex then
        local cell = tableView:cellAtIndex(self._selectedIndex)
        if cell then
            cell:setSelected(false)
        end
    end
    cell:setSelected(true)
    self._selectedIndex = cell:getIdx()
end

function M:onTableViewCellSize(tableView, idx)
    return CountryWarCell.CountryWarCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = CountryWarCell.new()
    end
    cell:setSelected(idx == self._selectedIndex)
    cell:reset(self._countryWarDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._countryWarDataList)
end

function M:_createButton()
    local button = CommonUI:createTextButton(self, "宣战", "ui/login/login-up.png", "ui/login/login-down.png")
    button:setPosition(cc.p(Screen.width * 0.5, BackgroundLayer.BottomHeight * 0.5))
    button.onClicked = function()
        if not self._selectedIndex then
            CommonUI:lightTips("请先选择一个需要宣战的国家")
            return
        end
        local countryWarData = self._countryWarDataList[self._selectedIndex + 1]
        local selectedCountryId = countryWarData:getCountryId()
        local selfCountryId = PlayerData:getCountryId()
        if selectedCountryId == selfCountryId then
            CommonUI:lightTips("不能对自己国家宣战")
            return
        end
        local layer = require("ui.country-war.layer-manager.CountryWarFightLayer").new(selectedCountryId)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

return M