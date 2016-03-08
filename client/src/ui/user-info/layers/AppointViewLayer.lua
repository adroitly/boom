local AppointViewLayerCell = require("ui.user-info.layers.AppointViewLayerCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local UserInfoLayerGoldLabel = require("ui.user-info.layers.UserInfoLayerGoldLabel")

local M = class("ui.user-info.layers.AppointViewLayer", function()
	return cc.Layer:create()
end)

local m_userAppointKey = "user_appoint"

local m_enumViewChangeKey =
{
	up = -1,
	down = 1
}

function M:ctor(maxLevel, parent)
	self._maxLevel = maxLevel
	self._parent = parent
	self:_createTimer()
	self:_createBackground()
	self._tableViewData = {}
	self:_createTableView()
	self:_createButtomNodes()
	self:_createPriceLabel()
	self:_createGoldNumberLabel()
end

function M:setMinLevel(minLevel)
	assert(minLevel)
	self._tableViewData = {}
	for level=self._maxLevel,minLevel, -1 do
		table.insert(self._tableViewData, level)
	end
	self._tableView:reloadData()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local commons =
    {
        [m_userAppointKey] = function(msgTable)
			CommonUI:showLoadingLayer(false)
	        assert(msgTable and msgTable.code)
	        self:_checkServerMessage(msgTable)
        end,
    }

    local fun = commons[cmd]
    if fun then
        fun(msgTable)
    end
end

function M:setUserData(searchUserData)
	self._searchUserData = searchUserData
end

function M:_getMinLevel()
	return self._tableViewData[table.getn(self._tableViewData)]
end

function M:_checkServerMessage(msgTable)
	self:_updateGoldNumberLabel()
    if 0 == msgTable.code then
		CommonUI:lightTips(__Localized("升职成功"))
		self:setMinLevel(self._targetLevel)
		self:_updatePriceLabel(self._targetLevel)
		self._searchUserData:updateLevel(self._targetLevel)
		self._parent:onAppointViewLayerReloadDidBack()
	else
		CommonUI:lightTips(__Localized("code = ")..code)
	end
end

function M:_createTimer()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:_updateTableViewOffSet(key, buttonSize)
	local contentOffSet = self._tableView:getContentOffset()
	local tableViewContentSize = self._tableView:getContentSize()
	local tableViewViewSize = self._tableView:getViewSize()
	local offSet = cc.p(contentOffSet.x, contentOffSet.y + (key * buttonSize.height * 2))

	if offSet.y >= 0 then
		offSet = cc.p(0, 0)
	elseif offSet.y - tableViewViewSize.height <= -tableViewContentSize.height then
		offSet = cc.p(0, -tableViewContentSize.height + tableViewViewSize.height)
	end

	self._tableView:setContentOffset(offSet, false)
end

function M:onTouchBegan(touch,event)
	local isTouchIn = Touch:isTouchHitted(self, touch)
	return isTouchIn
end

function M:onTableViewCellTouched(tableView, cell)
	self:_onCellTouch(cell)
end

function M:onTableViewCellSize(tableView, idx)
	return AppointViewLayerCell.AppointViewLayerCellSize.height,0
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = AppointViewLayerCell.new()
	end
	cell:reload(self._tableViewData[idx + 1])
	self:_checkNowLevel(cell, idx)
	self:_checkCellSelect(cell, idx)
	return cell
end

function M:onTableViewCellCount(tableView)
	return table.getn(self._tableViewData)
end


function M:_checkCellSelect(cell, idx)
	if self._touchCellIndex then
		if self._touchCellIndex == idx then
			cell:setSelect(true)
		end
	end
end

function M:_onCellTouch(cell)
	local nowCellIndex = cell:getIdx()
	if self._touchCellIndex then
		if self._touchCellIndex == nowCellIndex then
			return
		end
	end
	self:_lastCellNotSelect()
	local level = cell:getOfficeLevel()
	self._targetLevel = level
	self:_updatePriceLabel(level)
	cell:setSelect(true)
	self._touchCellIndex = nowCellIndex
end

function M:_getCost(level)
	local minLevel = self:_getMinLevel()
	local cost = 0
	for value=minLevel + 1,level do
		local costStr = OfficerConfigRead:getProRes(value)
		local costTable = Utils:formatStringToNumberTable(costStr)
		cost = cost + costTable[1][2]
	end
	return cost
end

function M:_updatePriceLabel(level)
	local cost = self:_getCost(level)
	self._priceLabel:setString(string.format(__Localized("花费元宝:%d"), cost))
end

function M:_lastCellNotSelect()
	if self._touchCellIndex then
		local cell = self._tableView:cellAtIndex(self._touchCellIndex)
		if cell then
			cell:setSelect(false)
		end
	end
end

function M:_checkNowLevel(cell, idx)
	if table.getn(self._tableViewData) - 1 == idx then
		cell:setNowLevel()
	end
end

function M:_sendDataToServer(level, cost)
	local name = OfficerConfigRead:getOfficerName(level)
	local text = string.format(__Localized("确定花费%d元宝升级到%s?"), cost, name)
	AlertView.new(text, __Localized("取 消"), __Localized("确 定"))
	.onClicked = function(index)
		if 1==index then
			local targetId = self._searchUserData:getId()
			local sendData = {target_id = targetId, level = level}
			SocketManager:send(m_userAppointKey, sendData)
			CommonUI:showLoadingLayer(true)
		end
	end
end

function M:_confirmButtonAction()
	if nil == self._touchCellIndex then
		CommonUI:lightTips(__Localized("没有选择"))
		return
	end
	local level = self._targetLevel
	local cost = self:_getCost(level)
	if 0 == cost then
		CommonUI:lightTips(__Localized("没有选择升级"))
		return
	end
	if false == BackpackDataManager:checkBackpackEnough(Enum.ResourceType.Gold, cost) then
		CommonUI:alertRechargeLayer()
	else
		self:_sendDataToServer(level, cost)
	end
end

function M:_createButtomNodes()
	local button = CommonUI:createTextButton(self, __Localized("确定"), "ui/login/login-button.png")
	Layout:layout(button, self:getContentSize(), Layout.center_bottom)
	button.onClicked = function()
		self:_confirmButtonAction()
	end
end

function M:_createGoldNumberLabel()
    self._goldLabel = UserInfoLayerGoldLabel:createGoldNumerLabel()
    self:addChild(self._goldLabel)
    self._goldLabel:setPosition(cc.p(Screen.width, Screen.height - BackgroundLayer.TitleHeight * 1.2))
end

function M:_createPriceLabel()
    self._priceLabel = CommonUI:createLabel(__Localized("花费元宝:0"), 24)
	self:addChild(self._priceLabel)
	self._priceLabel:setPosition(cc.p(Screen.width, Screen.height - BackgroundLayer.TitleHeight * 1.7))
	self._priceLabel:setAnchorPoint(cc.p(1, 0.5))
end

function M:_updateGoldNumberLabel()
    UserInfoLayerGoldLabel:updateGoldNumberLabel(self._goldLabel)
end

function M:_createTableView()
	local viewSize = cc.size(Screen.width,Screen.height - BackgroundLayer.TitleHeight * 2 - BackgroundLayer.BottomHeight)
	self._tableView = require("share.TableView").new(viewSize, self)
	Touch:registerTouchOneByOne(self, true)
	self._tableView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
	self:addChild(self._tableView)
end

function M:_createBackground()
	local background = BackgroundLayer.new(self, __Localized("任命"))
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M