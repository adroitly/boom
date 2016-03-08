local OutTeamCell = require("ui.team.layer-manager.OutTeamCell")
local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
local MapConfig = require("ui.map.data-manager.MapConfig")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local TeamDataManager = require("player-data.TeamDataManager")
local GoOutCallback = require("ui.map.logic.GoOutCallback")
local HeroDataManager = require("player-data.HeroDataManager")
local BackpackDataManager = require("player-data.BackpackDataManager")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
-- 撤销编队
local M = class("ui.team.layer-manager.OutTeamLayer", function(goOutInfo)
    return cc.Layer:create()
end)


local kMaxOutTeamCount = 5

function M:ctor(goOutInfo)
    self._goOutInfo = goOutInfo
    self._selectedIndexList = {}
    -- 准备出征队伍的数量
    self._readyOutTeamCount = 0
    self:_initData()
    self:_createBackground()
    self:_createConfirmButton()
    self:_createTableView()
    self._tfPosX, self._tfPosY = self:_createTextField()
    
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
    self:_initData()
    self._tableView:reloadData()
    if nil ~= self._tipsLabel then
        self._tipsLabel:removeFromParent()
        self._tipsButton:removeFromParent()
        self._tipsButton = nil
        self._tipsLabel = nil
    end
end

function M:_initData()
    self._teamDataList = {}
    local teamList = PlayerData:getTeamList()
    for k, teamData in pairs(teamList) do
        local heroId = teamData:getHeroId()
        local heroData = HeroDataManager:getHeroDataById(heroId)
        local endEnergyTime = heroData:getEndEnergyTime()
        if endEnergyTime <= PlayerData:getServerTime() then
            table.insert(self._teamDataList, teamData)
        end
    end
end

function M:_createBackground()
    local title = self:_getTitle()
    local background = BackgroundLayer.new(self, title)
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createConfirmButton()
    local title = self:_getTitle()
    local confirmButton = CommonUI:createTextButton(self, title, "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom, cc.p(-200, 0))
    confirmButton.onClicked = function()
        self:_sendAmryGoRequest()
    end
end

function M:_createTableView()
    local cellCount = table.getn(self._teamDataList)
    if cellCount == 0 then
        self:_createTips()
        -- return
    end
    local cellSize = OutTeamCell.CellSize
    local TableView = require("share.TableView")
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    self._tableView = TableView.new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:_createTips()
    self._tipsLabel = CommonUI:createLabel("请前往编队界面进行编队")
    self:addChild(self._tipsLabel)
    Layout:layout(self._tipsLabel, Screen.size, Layout.center)
    self._tipsButton = CommonUI:createTextButton(self, __Localized("前往"), "ui/login/login-button.png")
    Layout:layout(self._tipsButton, Screen.size, Layout.center , cc.p(0, 100))
    self._tipsButton.onClicked = function()
        local layer = require("ui.team.MainLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createTextField()
    local offsetPos = {cc.p(250, 20), cc.p(30, 20)}
    local placeHolders = {"请输入坐标X", "请输入坐标Y"}
    local textFields = {}
    for i = 1, 2 do
        -- local textField = require("share.TextField").new(26)
        local textField = ccui.EditBox:create(cc.size(200, 50), "ui/login/login-bt.png")
        -- 数字键盘
        textField:setInputMode(cc.EDITBOX_INPUT_MODE_NUMERIC)
        textField:setPlaceHolder(placeHolders[i])
        textField:setMaxLength(5)
        textField:setFontColor(cc.c4b(255, 255, 255, 255))
        self:addChild(textField)
        Layout:layout(textField, Screen.size, Layout.center_bottom, offsetPos[i])
        table.insert(textFields, textField)
    end
    if self._goOutInfo then
        local coor = GoOutInfo:getTwoDCoor(self._goOutInfo)
        textFields[1]:setText(tostring(coor.i))
        textFields[2]:setText(tostring(coor.j))
        textFields[1]:setTouchEnabled(false)
        textFields[2]:setTouchEnabled(false)
    end
    return textFields[1], textFields[2]
end

function M:_canSelectedCount()
    local outSideCount = 0
    for i, teamData in pairs(self._teamDataList) do
        local state = teamData:getState()
        if state == Enum.TeamDataState.Outside then
            outSideCount = outSideCount + 1
        end
    end
    local selectedCount = 0
    for i, isSelected in pairs(self._selectedIndexList) do
        local teamData = self._teamDataList[i]
        local state = teamData:getState()
        if state ~= Enum.TeamDataState.Outside and isSelected then
            selectedCount = selectedCount + 1
        end
    end
    return kMaxOutTeamCount - selectedCount - outSideCount
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    local teamData = self._teamDataList[idx + 1]
    local isSelected = cell:isSelected()
    if isSelected then
        cell:setSelected(false)
        self._selectedIndexList[idx + 1] = false
        return
    end
    if teamData:getState() ~= Enum.TeamDataState.Outside then
        if self:_canSelectedCount() > 0 then
            cell:setSelected(true)
            self._selectedIndexList[idx + 1] = true
        else
            local tips = string.format(__Localized("在外城您最多只能拥有%d支军队"), kMaxOutTeamCount)
            CommonUI:lightTips(tips)
        end
    else
        cell:setSelected(true)
        self._selectedIndexList[idx + 1] = true
    end
end

function M:onTableViewCellSize(tableView, idx)
    return OutTeamCell.CellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = OutTeamCell.new()
    end
    local teamData = self._teamDataList[idx + 1]
    cell:resetTeamData(teamData)
    cell:setSelected(self._selectedIndexList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._teamDataList)
end

function M:_sendAmryGoRequest()
    local outTeamCount = 0
    local selectedIndexList = {}
    for idx, isSelected in pairs(self._selectedIndexList) do
        if isSelected then
            outTeamCount = outTeamCount + 1
            table.insert(selectedIndexList, idx)
        end
    end
    if outTeamCount == 0 then
        CommonUI:lightTips(__Localized("您还没有选择军队"))
        return
    end
    local posX = tonumber(self._tfPosX:getText())
    local posY = tonumber(self._tfPosY:getText())
    if not self._goOutInfo and (not posX or not posY) then
        CommonUI:lightTips(__Localized("请输入坐标"))
        return
    end
    if not self:_isFoodsEnough(selectedIndexList) then
        return
    end
    local targetTwoDCoor = MapConfig:coordinate(posX, posY)
    local targetLocalCoor = MapConfig:twoDToLocal(targetTwoDCoor)
    self._readyOutTeamCount = outTeamCount
    for _, idx in pairs(selectedIndexList) do
        self:_amryGo(self._teamDataList[idx], targetLocalCoor)
    end
end

function M:_isFoodsEnough(selectedIndexList)
    local level = PlayerData:getCastleLevel()
    local needFoods = 0
    for _, idx in pairs(selectedIndexList) do
        local teamData = self._teamDataList[idx]
        local soldierType = teamData:getSoldierType()
        local soldierNumber = teamData:getSoldierNumber()
        local state = teamData:getState()
        if state == Enum.TeamDataState.Inside then
            local food = SoldierConfigReader:getFood(soldierType)
            needFoods = needFoods + soldierNumber * food
        end
    end
    local foodData = BackpackDataManager:getBackpackDataByType(Enum.ResourceType.Food)
    local itemNumber = 0
    if foodData then
        itemNumber = foodData:getItemNumber()
    end
    if itemNumber < needFoods then
        local str = string.format("当前出征部队%d支，需要携带%d粮食，您当前粮食不足，不可出征！",
                                     table.getn(selectedIndexList), needFoods)
        AlertView.new(str)
        return false
    end
    return true
end

function M:_sendAlertMessage(fromCoor, toCoor)
    if nil == self._goOutInfo then
        return
    end
    local operation = GoOutInfo:getOperation(self._goOutInfo)
    if operation == Enum.GoOutOperation.AttackBuilding or operation == Enum.GoOutOperation.OccupyBuilding then
        local alertData = {from_x = fromCoor.i, from_y = fromCoor.j, to_x = toCoor.i, to_y = toCoor.j}
        SocketManager:send(Command.AttackAlert, alertData)
    end
end

local function _isSameCoor(fromCoor, toCoor)
    if fromCoor.i == toCoor.i and toCoor.j == fromCoor.j then
        return true
    end
    return false
end

function M:_amryGo(teamData, toCoor)
    local state = teamData:getState()
    local fromCoor = {}
    if state == Enum.TeamDataState.Inside then
        fromCoor = PlayerData:getHomeCoor()
        self:_sendAlertMessage(fromCoor, toCoor)
        self:_armyGoInsideState(teamData)
    elseif state == Enum.TeamDataState.Guard then
        fromCoor = teamData:getCooridnate()
        if _isSameCoor(fromCoor, toCoor) then
            CommonUI:lightTips(__Localized("该部队已驻守"))
            return
        end
        self:_sendAlertMessage(fromCoor, toCoor)
        self:_armyGoGuardState(teamData)
    elseif state == Enum.TeamDataState.Outside then
        fromCoor = teamData:getCooridnate()
        self:_sendAlertMessage(fromCoor, toCoor)
        self:_armyGoOutsideState(teamData)
    end
end



-- 在主城时
function M:_armyGoInsideState(teamData)
    local armyId = teamData:getArmyId()
    local playerId = PlayerData:getPlayerId()
    local armyGoData = {player_id = playerId, army_id = armyId}
    SocketManager:send(Command.ArmyGo, armyGoData)
end

-- 驻守时
function M:_armyGoGuardState(teamData)
    local armyId = teamData:getArmyId()
    SocketManager:send(Command.BuildingUnguard, {army_id = armyId})
end

-- 在城外时
function M:_armyGoOutsideState(teamData)
    local armyId = teamData:getArmyId()
    self:_armyGoAction(armyId)
    self._readyOutTeamCount = self._readyOutTeamCount - 1
    if self._readyOutTeamCount == 0 then
        CommonUI:lightTipsFormat(string.format("%s成功", self:_getTitle()))
        self:removeFromParent()
    end
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == Command.ArmyGo then
        if CommonUI:errorAlertView(msgTable.code) then
            return
        end

        local outsideArmy = msgTable.army
        local armyInfo = outsideArmy.army 
        local armyId = armyInfo.army_id
        self:_armyGoAction(armyId, msgTable)
        self._readyOutTeamCount = self._readyOutTeamCount - 1
        if self._readyOutTeamCount == 0 then
            CommonUI:lightTipsFormat(string.format("%s成功", self:_getTitle()))
            self:removeFromParent()
        end
    end

    if cmd == Command.BuildingUnguard then
        if CommonUI:errorAlertView(msgTable.code) then
            return
        end

        local outsideArmy = msgTable.army 
        local armyInfo = outsideArmy.army 
        local teamData = TeamDataManager:updateTeamData(armyInfo)
        self:_armyGoOutsideState(teamData)
    end
end

function M:_armyGoAction(armyId, msgTable)
    local goOutInfo = self._goOutInfo
    if not goOutInfo then
        local posX = tonumber(self._tfPosX:getText())
        local posY = tonumber(self._tfPosY:getText())
        local twoDCoor = MapConfig:coordinate(posX, posY)
        goOutInfo = GoOutInfo:newDefalutInfo(twoDCoor)
    end

    GoOutCallback:goOutCallback(armyId, goOutInfo, msgTable)
end

function M:_getTitle()
    if self._goOutInfo then
        local operation = GoOutInfo:getOperation(self._goOutInfo)
        if operation == Enum.GoOutOperation.Aid then
            return "驻守"
        end
    end
    return "出征"
end

return M