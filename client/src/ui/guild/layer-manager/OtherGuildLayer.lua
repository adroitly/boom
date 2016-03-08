local BackgroundLayer = require("ui.common.BackgroundLayer")
local OtherGuildCell = require("ui.guild.layer-manager.OtherGuildCell")
local GuildData = require("player-data.GuildData")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.OtherGuildLayer", function()
    return cc.Layer:create()
end)

local kGuildJoin = "guild_join"
local kGuildOwnInfo = "guild_own_info"
local kGuildInfoList = "guild_info_list"
local kGuildInfo = "guild_info"
function M:ctor()
    self._guildDataList = {}
    self._displayGuildDataList = {}

    self:_createBackground()
    self:_createTextField()
    self:_createButton()
    self:_createTableView()
    
    GuildLayerManager:addLayer(self)
    Event:registerNodeEvent(self)
end
function M:onExit()
    SocketManager:removeObserver(self)
    GuildLayerManager:removeLayer(self)
end
function M:onEnterTransitionFinish()
    SocketManager:addObserver(self)
    self:_getGuildInfoList()
end

function M:_getGuildInfoList()
    local requestType = Enum.GuildCountryType.OwnCountry
    if PlayerData:isHasGuild() then
        requestType = Enum.GuildCountryType.AllCountry
    end
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kGuildInfoList, {type = requestType})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildJoin then
        CommonUI:showLoadingLayer(false)
        if msgTable.code == 100 then
            AlertView.new(__Localized("已加入势力")).onClicked = function(index)
                self:_getGuildInfo()
            end
            return
        end
        if not CommonUI:errorAlertView(msgTable.code) then    
            AlertView.new(__Localized("已成功申请加入"))
        end
    end
    if cmd == kGuildOwnInfo then
        CommonUI:showLoadingLayer(false)
        self:_gotoGuildLayer()
    end
    if cmd == kGuildInfoList then
        CommonUI:showLoadingLayer(false)
        self:_reloadOtherGuilds(msgTable)
    end
    if cmd == kGuildInfo then
        CommonUI:showLoadingLayer(false)
        self:_gotoGuildLayer()
    end
end

function M:_getGuildInfo()
    CommonUI:showLoadingLayer(true)
    local guildId = PlayerData:getGuildId()
    SocketManager:send(kGuildInfo, {guild_id = guildId})
end

function M:_reloadOtherGuilds(msgTable)
    self._guildDataList = {}
    local guildInfoList = msgTable.guild_infos
    for i = 1, table.getn(guildInfoList) do
        local guildInfo = guildInfoList[i]
        local guildData = GuildData.new(guildInfo)
        table.insert(self._guildDataList, guildData)
    end
    Table:copy(self._displayGuildDataList, self._guildDataList)
    table.sort(self._displayGuildDataList, function(a, b)
        return a:getLevel() > b:getLevel()
    end)
    self._tableView:reloadData()
end

function M:_gotoGuildLayer()
    if PlayerData:getGuildId() ~= 0 then
        self:removeFromParent()
        local layer = require("ui.guild.layer-manager.GuildLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("其他势力"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTextField()
    local TextInput = require("ui.common.EditBox")
    local searchTextInput = TextInput.new(cc.size(Screen.width - 200, 70),"ui/mail/mail-input.png")
    searchTextInput:setPlaceHolder(__Localized("请输入名称"))
    searchTextInput:setMaxLength(14)
    searchTextInput:setAnchorPoint(cc.p(0, 0.5))
    searchTextInput:setPosition(cc.p(0, Screen.height - BackgroundLayer.TitleHeight - 35))
    self:addChild(searchTextInput)

    local searchButton = CommonUI:createTextButton(self, __Localized("搜索"), "ui/login/login-bt.png")
    Layout:layout(searchButton, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
    searchButton.onClicked = function()
        local name = searchTextInput:getString()
        self:_searchGuildByName(name)
    end

    self._tfBackground = searchTextInput
end

function M:_searchGuildByName(name)
    if self._tiplabel then
        self._tiplabel:removeFromParent()
        self._tiplabel = nil
    end
    self._displayGuildDataList = {}
    for i, guildData in pairs(self._guildDataList) do
        local guildName = guildData:getName()
        if guildName == name then
            table.insert(self._displayGuildDataList, guildData)
            self._tableView:reloadData()
            return
        end
    end
    self._tableView:reloadData()
    self._tiplabel = CommonUI:createLabel(__Localized("没有搜索到相关的势力，请重新搜索"), 24)
    self:addChild(self._tiplabel)
    Layout:layout(self._tiplabel, Screen.size, Layout.center)
end

function M:_createButton()
    if PlayerData:isHasGuild() then
        return
    end
    local button = CommonUI:createTextButton(self, __Localized("创建势力"), "ui/login/login-bt.png")
    Layout:layout(button, Screen.size, Layout.center_bottom)
    button.onClicked = function()
        local layer = require("ui.guild.layer-manager.GuildCreateLayer").new()
        self:addChild(layer)
    end
end

function M:_createTableView()
    local cellSize = OtherGuildCell.OtherGuildCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - self._tfBackground:getContentSize().height)
    if not PlayerData:isHasGuild() then
        viewSize.height = viewSize.height - BackgroundLayer.BottomHeight
    end
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    local posY = Screen.height - BackgroundLayer.TitleHeight - viewSize.height - self._tfBackground:getContentSize().height
    self._tableView:setPosition(cc.p((Screen.width - viewSize.width) * 0.5, posY))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return OtherGuildCell.OtherGuildCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = OtherGuildCell.new()
    end
    cell:reset(self._displayGuildDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._displayGuildDataList)
end

return M
