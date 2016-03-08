local GuildInviteCell = require("ui.guild.layer-manager.GuildInviteCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local SearchUserData = require("ui.user-info.datas.SearchUserData")
local M = class("ui.guild.layer-manager.GuildInviteLayer", function()
    return cc.Layer:create()
end)

local kOnlinePlayerRandList = "online_player_rand_list"
local kGuildInvitation = "guild_invitation"
local kUserSearch = "user_search"
function M:ctor()
    self._searchUserDataList = {}

    self:_createBackground()
    self:_createTextField()
    self:_createTableView()

    GuildLayerManager:addLayer(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)
    self:_getPlayerList()
end
function M:_getPlayerList()
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kOnlinePlayerRandList, {})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kOnlinePlayerRandList then
        CommonUI:showLoadingLayer(false)
        self:_initPlayerBaseDataList(msgTable)
        self._tableView:reloadData()
    end
    if cmd == kGuildInvitation then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            AlertView.new(__Localized("邀请成功"))
        end
    end
    if cmd == kUserSearch then
        CommonUI:showLoadingLayer(false)
        self:_initPlayerBaseDataList(msgTable)
        self._tableView:reloadData()
    end
end

function M:_initPlayerBaseDataList(msgTable)
    self._searchUserDataList = {}
    for _, v in pairs(msgTable.player_infos) do
        local data = SearchUserData.new(v)
        table.insert(self._searchUserDataList, data)
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("邀请"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTextField()
    local tfBackground = cc.Sprite:create("ui/mail/mail-input.png")
    self:addChild(tfBackground)
    Layout:layout(tfBackground, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))


    local TextInput = require("ui.common.InputUI")
    local searchTextInput = TextInput.new(26)
    searchTextInput:setPlaceHolder(__Localized("请输入名称"))
    searchTextInput:setMaxLength(14)
    searchTextInput:setAnchorPoint(cc.p(0, 0.5))
    tfBackground:addChild(searchTextInput)
    Layout:layout(searchTextInput, tfBackground:getContentSize(), Layout.left_center, cc.p(10, 0))

    local searchButton = CommonUI:createTextButton(self, __Localized("搜索"), "ui/login/login-bt.png")
    Layout:layout(searchButton, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
    searchButton.onClicked = function()
        local name = searchTextInput:getString()
        if string.len(name) == 0 then
            CommonUI:lightTips("昵称不能为空")
            return
        end
        CommonUI:showLoadingLayer(true)
        SocketManager:send(kUserSearch, {nickname = name})
    end

    -- self._searchTextField = require("share.TextField").new(26)
    -- self._searchTextField:setPlaceHolder(__Localized("请输入名称"))
    -- self._searchTextField:setTextColor(cc.c4b(255, 255, 255, 255))
    -- self._searchTextField:setMaxLength(5)
    -- self._searchTextField:setAnchorPoint(cc.p(0, 0.5))
    -- tfBackground:addChild(self._searchTextField)
    -- Layout:layout(self._searchTextField, tfBackground:getContentSize(), Layout.left_center, cc.p(10, 0))

    self._tfBackground = tfBackground
end

function M:_createTableView()
    local cellSize = GuildInviteCell.GuildInviteCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - self._tfBackground:getContentSize().height - BackgroundLayer.BottomHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    local posY = Screen.height - BackgroundLayer.TitleHeight - viewSize.height - self._tfBackground:getContentSize().height
    self._tableView:setPosition(cc.p((Screen.width - viewSize.width) * 0.5, posY))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return GuildInviteCell.GuildInviteCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = GuildInviteCell.new()
    end
    cell:reset(self._searchUserDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._searchUserDataList)
end

return M