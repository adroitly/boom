local BackpackDataManager = require("player-data.BackpackDataManager")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local ContributeOfficerCell = require("ui.user-info.layers.ContributeOfficerCell")
local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local UserInfoLayerGoldLabel = require("ui.user-info.layers.UserInfoLayerGoldLabel")
local M = class("ui.user-info.layers.ContributeOfficerLayer", function()
	return cc.Layer:create()
end)

local m_maxLevel = 90
local kUserLevelUpUseItem = "user_level_up_use_item"

local function _showTips(name, code)
    assert(name and code)
    local tipsText = string.format("%s%s", name , 0 == code and __Localized("成功") or __Localized("失败"))
    CommonUI:lightTips(tipsText)
end

function M:ctor()
	self:_createBackground()
    self:_initData()
    self:_createTableView()
    self:_scrollToCell()
	self:_registerScriptHandler()
	self:_createUpAllLevelButton()
	self:_createUpOneLevelButton()
    self:_createGoldNumberLabel()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local commons =
    {
        [kUserLevelUpUseItem] = function(msgTable)
            assert(msgTable and msgTable.code)
            _showTips(__Localized("升级"), msgTable.code)
            self._tableView:reloadData()
            self:_scrollToCell()
            self:_updateGoldNumberLabel()
        end,
    }

    local fun = commons[cmd]
    if fun then
        fun(msgTable)
        CommonUI:showLoadingLayer(false)
    end
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return ContributeOfficerCell.ContributeOfficerCellSize.height,0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if nil == cell then
        cell = ContributeOfficerCell.new()
    end
    cell:reload(self._showTableViewData[idx + 1])
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    if idx == (m_maxLevel - currentLevel) then
        cell:setNowLevel()
    end
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._showTableViewData)
end

function M:_getOffset(currentLevel)
    local maxLevel = m_maxLevel
    local tableViewContentSize = self._tableView:getContentSize()
    local viewSize = self._tableView:getViewSize()
    local tableOffset = self._tableView:getContentOffset()
    local perWidth = ContributeOfficerCell.ContributeOfficerCellSize.width
    local midIndex = math.floor(viewSize.height / perWidth) / 2
    local index = (currentLevel + 1 - midIndex) / maxLevel
    local offSet = cc.p(tableOffset.x, - index * tableViewContentSize.height)
    if offSet.y > 0 then
        offSet = cc.p(offSet.x , 0)
    elseif math.abs(offSet.y) > (tableViewContentSize.height - viewSize.height) then
        offSet = cc.p(offSet.x, - (tableViewContentSize.height- viewSize.height))
    end
    return offSet
end

function M:_scrollToCell()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    local offSet = self:_getOffset(currentLevel)
    self._tableView:setContentOffset(offSet)
end

function M:_createTableView()
    local viewSize = cc.size(Screen.width, Screen.height - BackgroundLayer.TitleHeight * 2 - BackgroundLayer.BottomHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self._tableView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
    self:addChild(self._tableView)
end

function M:_initData()
    self._showTableViewData = {}
    for i=m_maxLevel,1,-1 do
        table.insert(self._showTableViewData, i);
    end
end

-- 功勋成长
function M:_getGrowth()
    local currentLevel = PlayerData:getUserInfoData():getLevel()
    local growth = OfficerConfigRead:getGrowthRate(currentLevel) * 60
    return growth
end

function M:_confirm(level)
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kUserLevelUpUseItem, {level = level})
end

function M:_checkMaxLevel(level)
    if level > m_maxLevel then
        CommonUI:lightTips(__Localized("选择等级超过最高级，请重新选择"))
        return true
    end
    return false
end

function M:_setDataToServer(addLevel)
	local curLevel = PlayerData:getUserInfoData():getLevel()
    if self:_checkMaxLevel(curLevel + addLevel) then
        return
    end
	local cost = 0
	local backpackType = nil
	for level=1,addLevel do
		local costStr = OfficerConfigRead:getOffDonation(curLevel + level)
		local costTable = Utils:formatStringToNumberTable(costStr)
		backpackType = costTable[1][1]
		cost = cost + costTable[1][2]
	end
    local curLevelName = OfficerConfigRead:getOfficerName(curLevel + addLevel)
    local showText = string.format(__Localized("是否花费%d元宝升级到%d级(%s)"), cost, curLevel + addLevel, curLevelName)
    if self:_getGrowth() > 0 then
        if BackpackDataManager:checkBackpackEnough(backpackType, cost) then
            AlertView.new(showText, __Localized("取 消"), __Localized("确 定"))
            .onClicked = function(index)
                if 1==index then
                    self:_confirm(curLevel + addLevel)
                end
            end
        else
            self:_showRecharge(backpackType)
        end
    end
end

function M:_showRecharge(backpackType)
    CommonUI:alertRechargeLayer()
end

function M:_createUpAllLevelButton()
	local button = CommonUI:createTextButton(self, "官升满级", "ui/login/login-button.png")
	button.onClicked = function()
        self:_onUpAllLevelButtonClick()
	end
    local buttonSize = button:getContentSize()
	button:setPosition(cc.p(Screen.width / 4, buttonSize.height / 2))
end

function M:_onUpAllLevelButtonClick()
    local curLevel = PlayerData:getUserInfoData():getLevel()
    local addLevel = self:_getCanUpMaxLevel() - curLevel
    if addLevel < 0 then
        self:_checkUpLevel(0)
    else
        self:_checkUpLevel(addLevel)
    end
end

function M:_checkUpLevel(addLevel)
    if addLevel == 0 then
        CommonUI:lightTips(__Localized("当前可捐献等级已达上限,请提升VIP等级"))
        return
    end
    self:_setDataToServer(addLevel)
end
function M:_createUpOneLevelButton()
	local button = CommonUI:createTextButton(self, "官升一级", "ui/login/login-button.png")
	button.onClicked = function()
		self:_onUpOneLevelButtonClick()
	end
    local buttonSize = button:getContentSize()
	button:setPosition(cc.p(Screen.width * 0.75, buttonSize.height / 2))
end
function M:_onUpOneLevelButtonClick()
    local curLevel = PlayerData:getUserInfoData():getLevel()
    local addLevel = self:_getCanUpMaxLevel() - curLevel
    if addLevel > 1 then
        self:_checkUpLevel(1)
    else
        self:_checkUpLevel(0)
    end
end

function M:_createGoldNumberLabel()
    self._goldLabel = UserInfoLayerGoldLabel:createGoldNumerLabel()
    self:addChild(self._goldLabel)
    self._goldLabel:setPosition(cc.p(Screen.width, Screen.height - BackgroundLayer.TitleHeight * 1.5))
end

function M:_updateGoldNumberLabel()
    UserInfoLayerGoldLabel:updateGoldNumberLabel(self._goldLabel)
end

function M:_registerScriptHandler()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("捐官"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

function M:_getCanUpMaxLevel()
    local vip = self:_getVip()
    local maxLevel = VipConfigReader:getOfficersMax(vip)
    return maxLevel or 0
end

function M:_getVip()
    return PlayerData:getUserInfoData():getVip()
end

return M