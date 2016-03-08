local BackgroundLayer = require("ui.common.BackgroundLayer")
local GameMailCell = require("ui.mail.layer-manager.GameMailCell")
local GameMailData = require("ui.mail.data-manager.GameMailData")
local GameMailDataManager = require("player-data.GameMailDataManager")
local SettingMailLayer = require("ui.mail.layer-manager.SettingMailLayer")
local M = class("ui.mail.layer-manager.GameMailLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self._selectedIndexList = {}

    self:_createBackground()
    self:_reloadTableView()
    self._settingLayer = SettingMailLayer:createWithSettingButton(self)
    
    Listener:addListener(self)
    self:registerScriptHandler(function(event)
        if event == "exit"then
            Listener:removeListener(self)
        end
    end)
end

function M:onListenMailGameChanged()
    self:_reloadTableView()
end

function M:_initMailData()
    self._mailList = {}
    self._selectedIndexList = {}
    for _, mailData in pairs(PlayerData:getGameMailList()) do
        table.insert(self._mailList, mailData)
        table.insert(self._selectedIndexList, false)
    end
    table.sort(self._mailList, function(a, b)
        local aTime = GameMailData:getTime(a)
        local bTime = GameMailData:getTime(b)
        return aTime > bTime
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
            if 1 == index then 
                self:_deleteSelectedMail()
            end
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "战斗报告")
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

function M:_showSelect(isShow)
    for i in pairs(self._mailList) do
        local cell = self._tableView:cellAtIndex(i - 1)
        if cell then
            cell:showSelectButton(isShow)
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
    local deleteMailList = {}
    for i in pairs(self._selectedIndexList) do
        local isSelected = self._selectedIndexList[i]
        if isSelected then
            local mailData = self._mailList[i]
            table.insert(deleteMailList, mailData)
        end
    end
    GameMailDataManager:batchDeleteGameMail(deleteMailList)
end

function M:_reloadTableView()
    self:_initMailData()
    local cellCount = table.getn(self._mailList)
    if not self._tableView then
        self._tableView = self:_createTableView()
    else
        self._tableView:reloadData()
    end
end

function M:_createTableView()
    local cellCount = table.getn(self._mailList)
    if cellCount == 0 then
        return
    end
    local cellSize = GameMailCell.GameMailCellSize
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
    local idx = cell:getIdx()
    local mailData = self._mailList[idx + 1]
    local gameMailDetalsLayer = require("ui.mail.layer-manager.GameMailDetailsLayer").new(mailData)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(gameMailDetalsLayer)
    
    GameMailDataManager:updateMailType(mailData, Enum.MailType.Read)
    Listener:postEvent(Listener.EventName.onListenMailGameChanged)
end

function M:onTableViewCellSize(tableView, idx)
    return GameMailCell.GameMailCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = GameMailCell.new()
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