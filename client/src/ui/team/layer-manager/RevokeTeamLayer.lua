local RevokeTeamCell = require("ui.team.layer-manager.RevokeTeamCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroDataManager = require("player-data.HeroDataManager")
-- 撤销编队
local M = class("ui.team.layer-manager.RevokeTeamLayer", function()
    return cc.Layer:create()
end)

local kArmyRevoke = "army_cancel"

function M:ctor()
    self:_initData()
    self:_createBackground()
    self:_createConfirmButton()
    self:_createTableView()

    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            Listener:removeListener(self)
        end
    end)
    Listener:addListener(self)
end

function M:onListenHeroDataChange()
    self._selectedTeamIndex = nil
    self:_initData()
    self._tableView:reloadData()
end

function M:_initData()
    self._teamDataList = {}
    local teamList = PlayerData:getTeamList()
    for k, teamData in pairs(teamList) do
        local heroId = teamData:getHeroId()
        local heroData = HeroDataManager:getHeroDataById(heroId)
        local endEnergyTime = heroData:getEndEnergyTime()
        if teamData:getState() == Enum.TeamDataState.Inside and endEnergyTime <= PlayerData:getServerTime() then
            table.insert(self._teamDataList, teamData)
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "撤销")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createConfirmButton()
    local confirmButton = CommonUI:createTextButton(self, "确定", "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom)
    confirmButton.onClicked = function()
        if not self._selectedTeamIndex then
            CommonUI:lightTips(__Localized("您还没有选择军队"))
            return
        end
        self:_sendTeamRevokeRequest()
    end
end

function M:_sendTeamRevokeRequest()
    local playerId = PlayerData:getPlayerId()
    local teamData = self._teamDataList[self._selectedTeamIndex + 1]
    local state = teamData:getState()
    if state == Enum.TeamDataState.Outside then
        CommonUI:lightTips(__Localized("在城外的军队不能被撤销"))
        return
    elseif state == Enum.TeamDataState.Guard then
        CommonUI:lightTips(__Localized("驻守状态的军队不能被撤销"))
        return
    end
    local armyId = teamData:getArmyId()
    local armyRevokeData = {player_id = playerId, army_id = armyId}
    SocketManager:send(kArmyRevoke, armyRevokeData)
end

function M:_createTableView()
    local cellCount = table.getn(self._teamDataList)
    if cellCount == 0 then
        return
    end
    local cellSize = RevokeTeamCell.CellSize
    local TableView = require("share.TableView")
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    self._tableView = TableView.new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:onTableViewCellTouched(tableView, cell)
    if self._selectedTeamIndex then
        local preCell = tableView:cellAtIndex(self._selectedTeamIndex)
        if preCell then
            preCell:setSelected(false)
        end
    end
    self._selectedTeamIndex = cell:getIdx()
    cell:setSelected(true)
end

function M:onTableViewCellSize(tableView, idx)
    return RevokeTeamCell.CellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = RevokeTeamCell.new()
    end
    local teamData = self._teamDataList[idx + 1]
    cell:resetTeamData(teamData)
    local isSelected = self._selectedTeamIndex and self._selectedTeamIndex == idx or false
    cell:setSelected(isSelected)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._teamDataList)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kArmyRevoke then
        if msgTable.code ~= 0 then
            local text = string.format("撤销失败：错误码=%d", msgTable.code)
            CommonUI:lightTips(text)
            return
        end
        local TeamDataManager = require("player-data.TeamDataManager")
        TeamDataManager:removeTeamData(msgTable.army_id)
        AlertView.new(__Localized("解散军队成功")).onClicked = function(index)
            self:_initData()
            self._tableView:reloadData()
        end
    end
end

return M