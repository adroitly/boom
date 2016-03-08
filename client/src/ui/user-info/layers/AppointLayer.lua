local BackgroundLayer = require("ui.common.BackgroundLayer")
local AppointLayerCell = require("ui.user-info.layers.AppointLayerCell")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local SearchUserData = require("ui.user-info.datas.SearchUserData")
local M = class("ui.user-info.AppointLayer", function()
	return cc.Layer:create()
end)

local m_infosTitleName = {
	__Localized("名称"),
	__Localized("联盟"),
	__Localized("官职"),
}

local m_userSearchCommand = "user_search"

local function _isHitted(node, touch)
	return Touch:isTouchHitted(node, touch)
end


function M:onAppointViewLayerReloadDidBack()
	self._tableView:reloadData()
end

function M:ctor()
	self:_createBackground()
	self:_registerScriptHandler()
	self._searchUserDataList = {}
	self:_createInputFiled()
	self:_createSearchButton()
	self:_createInfosTitileLabel()
	self:_createTableView()
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    local commons =
    {
        [m_userSearchCommand] = function(msgTable)
			CommonUI:showLoadingLayer(false)
	        assert(msgTable)
	        self:_reload(msgTable)
        end,
    }

    local fun = commons[cmd]
    if fun then
        fun(msgTable)
        CommonUI:showLoadingLayer(false)
    end
end

function M:onTableViewCellTouched(tableView, cell)
	self:_onCellTouch(cell)
end

function M:onTableViewCellSize(tableView, idx)
	return AppointLayerCell.AppointLayerCellSize.width, AppointLayerCell.AppointLayerCellSize.height
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = AppointLayerCell.new()
	end
	local data = self._searchUserDataList[idx + 1]
	cell:reload(data)
	self:_checkCellSelect(cell, idx)
    return cell
end

function M:onTableViewCellCount(tableView)
	return table.getn(self._searchUserDataList)
end

function M:_registerScriptHandler()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:_reload(msgTable)
	self._searchUserDataList = {}
	self._searchUserDataList = SearchUserData:getSearchUserDataList(msgTable)
	self._tableView:reloadData()
end


function M:_initAppointView()
	local currentLevel = PlayerData:getUserInfoData():getLevel()
	local maxLevel = OfficerConfigRead:getAppointMax(currentLevel)
	self._appointViewLayer = require("ui.user-info.layers.AppointViewLayer").new(maxLevel)
	self:addChild(self._appointViewLayer)
	self._appointViewLayer:setVisible(false)
end

function M:_createTableView()
	local viewSize = cc.size(
								Screen.width,
								Screen.height - BackgroundLayer.TitleHeight * 2.5
		)
	self._tableView = require("share.TableView").new(viewSize, self)
	self:addChild(self._tableView)
end

function M:_checkCellSelect(cell, idx)
	if self._touchCellIndex then
		if self._touchCellIndex == idx then
			cell:setSelect(true)
		end
	end
end

function M:_onCellTouch(cell)
	self._cellIsTouch = true
	cell:setSelect(true)
	local nowCellIndex = cell:getIdx()
	local currentLevel = PlayerData:getUserInfoData():getLevel()
	local appointMaxLevel = OfficerConfigRead:getAppointMax(currentLevel)
	local searchUserData = self._searchUserDataList[nowCellIndex + 1]
	if appointMaxLevel > searchUserData:getLevel() then
		self:_createAppointLayerView(searchUserData)
	else
		CommonUI:lightTips(__Localized("玩家等级已经超过了可任命等级"))
	end
	if self._touchCellIndex then
		if self._touchCellIndex == nowCellIndex then
			return
		end
	end
	self:_lastCellNotSelect()
	self._touchCellIndex = nowCellIndex
end

function M:_createAppointLayerView(searchUserData)
	local scene = cc.Director:getInstance():getRunningScene()
	local layer = require("ui.user-info.layers.AppointViewLayer").new(30, self)
	layer:setMinLevel(searchUserData:getLevel())
	layer:setUserData(searchUserData)
	scene:addChild(layer)
end

function M:_lastCellNotSelect()
	if self._touchCellIndex then
		local cell = self._tableView:cellAtIndex(self._touchCellIndex)
		if cell then
			cell:setSelect(false)
		end
	end
end

function M:_createInputFiled()
	self._textFiled = require("ui.common.EditBox").new(cc.size(Screen.width - 200, 70), "ui/login/login-bt.png")
	self._textFiled:setPlaceHolder(__Localized("请输入玩家名称"))
	self._textFiled:setTextColor(cc.c4b(255, 255, 255, 255))
	self:addChild(self._textFiled)
	Layout:layout(self._textFiled, Screen.size, Layout.center_top, cc.p(100, BackgroundLayer.TitleHeight))
end

function M:_createSearchButton()
	local button = CommonUI:createTextButton(self, __Localized("搜索"), "ui/login/login-up.png")
	Layout:layout(button, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
	button.onClicked = function()
		-- print("=========>", self._textFiled:getString())
		local userName = self._textFiled:getString()
		if nil == userName then
			return
		end
		local sendData = {nickname = userName}
		SocketManager:send(m_userSearchCommand, sendData)
		CommonUI:showLoadingLayer(true)
	end
end

function M:_createInfosTitileLabel()
	local labelWidth = Screen.width / table.getn(m_infosTitleName)
	for index,value in ipairs(m_infosTitleName) do
		local label = require("ui.common.ClickLabel").new(value)
		self:addChild(label)
		label.onClicked = function()
			self:_reloadRank(index)
		end
		label:registerTouchOneByOne(false)
		label:setPosition(labelWidth * (index - 0.5), Screen.height - BackgroundLayer.TitleHeight * 2)
	end
end

function M:_reloadRank(index)
	table.sort( self._searchUserDataList, function(data1, data2)
		return data1[index] > data2[index]
	end )
	self._tableView:reloadData()
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, __Localized("官职任命"))
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

return M