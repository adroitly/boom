local BackgroundLayer = require("ui.common.BackgroundLayer")
local PlayerMailCell = require("ui.mail.layer-manager.PlayerMailCell")
local PersonalMailData = require("ui.mail.data-manager.PersonalMailData")
local PersonalMailDataManager = require("player-data.PersonalMailDataManager")
local SettingMailLayer = require("ui.mail.layer-manager.SettingMailLayer")
local OtherPlayerData = require("ui.user-info.datas.OtherPlayerData")
local M = class("ui.mail.layer-manager.PlayerMailLayer", function()
    return cc.Layer:create()
end)

local kPlayerBaseInfo2 = "player_base_info2"

function M:ctor()
    self._selectedIndexList = {}

    self:_createBackground()
    self:_reloadTableView()
    self._settingLayer = SettingMailLayer:createWithSettingButton(self)
    
    Event:registerNodeEvent(self)
end

function M:onExit()
    Listener:removeListener(self)
    SocketManager:removeObserver(self)
end

function M:onEnter()
    Listener:addListener(self)
    SocketManager:addObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kPlayerBaseInfo2 then
        CommonUI:showLoadingLayer(false)
        local otherPlayerData = OtherPlayerData.new(msgTable)
        local layer = require("ui.user-info.layers.OtherPlayerInfoLayer").new(otherPlayerData)
        cc.Director:getInstance():getRunningScene():addChild(layer)
        Listener:postEvent(Listener.EventName.onListenGuildMemberOperate)
    end
end

function M:onListenMailPersonalChanged()
    self:_reloadTableView()
end

function M:_initMailData()
    self._mailList = {}
    self._selectedIndexList = {}
    local personalMailList = PlayerData:getPersonalMailList()

    for playerId, mailData in pairs(personalMailList) do
        table.insert(self._mailList, mailData)
        table.insert(self._selectedIndexList, false)
    end
    -- 最新的一条邮件排在最前面
    table.sort(self._mailList, function(a, b)
        -- 第一条为最新的
        local aPlayerId = PersonalMailData:getPlayerId(a)
        local bPlayerId = PersonalMailData:getPlayerId(b)
        local aPersonalMailData = PersonalMailDataManager:getNewestPersonalMailData(aPlayerId)
        local bPersonalMailData = PersonalMailDataManager:getNewestPersonalMailData(bPlayerId)
        return aPersonalMailData.time > bPersonalMailData.time
    end)
end

function M:onOpenCallback()
    self:_showSelect(true)
end

function M:onCloseCallback()
    self:_showSelect(false)
    self:_resetSelect()
end

function M:onTotalSelectCallback()
    self:_setTotalSelect()
end

function M:onDeleteCallback()
    local selectedCount = self:_getSelectedCount()
    if selectedCount > 0 then
        AlertView.new(__Localized("确定要删除邮件吗？"), __Localized("取 消"), __Localized("删 除"))
        .onClicked = function(index)
            if 1==index then 
                self:_deleteSelectedMail()
            end
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "玩家邮件")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_resetSelect()
    for i in pairs(self._selectedIndexList) do
        self._selectedIndexList[i] = false
        local cell = self._tableView:cellAtIndex(i - 1)
        if cell then
            cell:setSelected(false)
        end
    end
end

function M:_setTotalSelect()
    for i in pairs(self._mailList) do
        self._selectedIndexList[i] = true
        local cell = self._tableView:cellAtIndex(i - 1)
        if cell then
            cell:setSelected(true)
        end
    end
end

function M:_deleteSelectedMail()
    local playerIdList = {}
    for i in pairs(self._selectedIndexList) do
        local isSelected = self._selectedIndexList[i]
        if isSelected then
            local mailData = self._mailList[i]
            local playerId = PersonalMailData:getPlayerId(mailData)
            table.insert(playerIdList, playerId)
        end
    end
    PersonalMailDataManager:batchDeletePersonalMail(playerIdList)
end

function M:_showSelect(isShow)
    for i in pairs(self._mailList) do
        local cell = self._tableView:cellAtIndex(i - 1)
        if cell then
            cell:showSelectButton(isShow)
        end
    end
end

function M:_reloadTableView()
    self:_initMailData()
    if not self._tableView then
        self._tableView = self:_createTableView()
    end
    self._tableView:reloadData()
end

function M:_createTableView()
    local cellSize = PlayerMailCell.PlayerMailCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight)
    local tableView = require("share.TableView").new(viewSize, self)
    self:addChild(tableView)
    local winSize = cc.Director:getInstance():getVisibleSize()
    tableView:setPosition(cc.p((Screen.width - viewSize.width) * 0.5, Screen.height - BackgroundLayer.TitleHeight - viewSize.height))
    return tableView
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    if self._settingLayer:isShow() then
        local isSelected = cell:isSelected()
        cell:setSelected(not isSelected)
        self._selectedIndexList[idx + 1] = cell:isSelected()
        return
    end
    local mailData = self._mailList[idx + 1]
    local playerId = PersonalMailData:getPlayerId(mailData)
    local nickname = PersonalMailData:getNickname(mailData)
    local personalMailLayer = require("ui.mail.layer-manager.PersonalMailLayer").new(playerId, nickname)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(personalMailLayer)

    PersonalMailDataManager:resetMailCount(playerId)
    Listener:postEvent(Listener.EventName.onListenMailPersonalChanged)
end

function M:onTableViewCellSize(tableView, idx)
    return PlayerMailCell.PlayerMailCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = PlayerMailCell.new()
    end
    local mailData = self._mailList[idx + 1]
    cell:resetMailData(mailData)
    cell:setSelected(self._selectedIndexList[idx + 1])
    local isShow = false
    if self._settingLayer and self._settingLayer:isShow() then
        isShow = true
    end
    cell:showSelectButton(isShow)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._mailList)
end

function M:_getSelectedCount()
    local count = 0
    for _, v in pairs(self._selectedIndexList) do
        if v == true then
            count = count + 1
        end
    end
    return count
end

return M