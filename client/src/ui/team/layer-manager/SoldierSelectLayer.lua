local BackgroundLayer = require("ui.common.BackgroundLayer")
local SoldierSelectCell = require("ui.team.layer-manager.SoldierSelectCell")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local M = class("ui.team.layer-manager.SoldierSelectLayer", function()
    return cc.Layer:create()
end)

local kArmyCreate = "army_create"

function M:ctor(selectedHeroData)
    self._selectedHeroData = selectedHeroData
    self._selectedSoldierCount = 0

    self:_initSoldiersData()
    self:_createBackground()
    self:_createTableView()
    self:_createConfirmButton()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:_initSoldiersData()
    self._soldiersList = {}
    local soldiers = PlayerData:getSoldiers()
    for _, soldierData in pairs(soldiers) do
        local soldierNumber = soldierData:getSoldierNumber()
        if soldierNumber > 0 then
            table.insert(self._soldiersList, soldierData)
        end
    end

    -- 按照等级,ID排序
    table.sort(self._soldiersList, function(a, b)
        local aSoldierType = a:getSoldierType()
        local bSoldierType = b:getSoldierType()
        local aType = SoldierConfigReader:getType(aSoldierType)
        local bType = SoldierConfigReader:getType(bSoldierType)
        if aType > bType then
            return false
        end
        if aType == bType then
            local aLevel = SoldierConfigReader:getLevel(aSoldierType)
            local bLevel = SoldierConfigReader:getLevel(bSoldierType)
            if aLevel > bLevel then
                return true
            end
            return false
        end
        return true
    end)
end


function M:_createBackground()
    local background = BackgroundLayer.new(self, "士兵")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createConfirmButton()
    local confirmButton = CommonUI:createTextButton(self, "创建", "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom)
    confirmButton.onClicked = function()
        if not self._selectedSoldierCellIndex then
            CommonUI:lightTips(__Localized("请选择哪种士兵"))
            return
        end
        self:_sendCreateTeamRequest()
    end
end

function M:_createTableView()
    local cellCount = table.getn(self._soldiersList)
    if cellCount == 0 then
        return
    end
    local cellSize = SoldierSelectCell.SoldierSelectCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:onTableViewCellTouched(tableView, cell)
    local curSelectedIndex = cell:getIdx()
    if self._selectedSoldierCellIndex == curSelectedIndex then
        return
    end
    if self._selectedSoldierCellIndex then
        local preCell = tableView:cellAtIndex(self._selectedSoldierCellIndex)
        if preCell then
            preCell:setSelected(false)
        end
    end
    cell:setSelected(true)
    self._selectedSoldierCellIndex = cell:getIdx()
end

function M:onTableViewCellSize(tableView, idx)
    return SoldierSelectCell.SoldierSelectCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = SoldierSelectCell.new()
    end
    local soldiersList = self._soldiersList
    local soldierData = soldiersList[idx + 1]
    cell:resetSoldierData(soldierData, self._selectedHeroData)
    cell:setSelected(self._selectedSoldierCellIndex == idx)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._soldiersList)
end

function M:_sendCreateTeamRequest()
    local playerId = PlayerData:getPlayerId()
    local heroId = self._selectedHeroData:getHeroId()
    local soldiersList = self._soldiersList
    local soldierData = soldiersList[self._selectedSoldierCellIndex + 1]
    local soldierType = soldierData:getSoldierType()
    local cell = self._tableView:cellAtIndex(self._selectedSoldierCellIndex)
    local selectedSoldierCount = 0
    if not cell then
        selectedSoldierCount = self._selectedSoldierCount
    else
        selectedSoldierCount = cell:getSelectedCount()
    end
    local armyData = {player_id = playerId, hero_id = heroId, soldier_type = soldierType, number = selectedSoldierCount}
    SocketManager:send(kArmyCreate, armyData)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kArmyCreate then
        if CommonUI:errorAlertView(msgTable.code) then
            return
        end
        CommonUI:lightTipsFormat("创建军队成功")
        self:removeFromParent()
    end
end

return M