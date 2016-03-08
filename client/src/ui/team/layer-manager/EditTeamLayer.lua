local BackgroundLayer = require("ui.common.BackgroundLayer")
local EditTeamLayerCell = require("ui.team.layer-manager.EditTeamLayerCell")
local TeamDataManager = require("player-data.TeamDataManager")
local HeroDataManager = require("player-data.HeroDataManager")
local SharedScheduler = cc.Director:getInstance():getScheduler()  

local M = class("ui.team.layer-manager.EditTeamLayer", function ()
	return cc.Layer:create()
end)

function M:onCellSoldierNumberChange(soldierType, soldierCount)
	if self._selectIndex then
		self._isSliderTouch = true
	end
	if self._tableView then
		self:_updateCellSurplus(soldierType, soldierCount)
	end
end

function M:onCellCloseSelect(cell)
	cell:setSelect(false)
	self._selectIndex = nil
end

function M:onListenTeamDataChange()
	CommonUI:showLoadingLayer(false)
	self:onListenHeroDataChange()
	if self._selectIndex then
		local cell = self._tableView:cellAtIndex(self._selectIndex)
		if cell then
			cell:setSelect(false)
			CommonUI:lightTips(__Localized("成功"))
		end
		self._selectIndex = nil
	end
end
function M:onListenHeroDataChange()
	self:reloadTeamData()
end

function M:reloadTeamData()
	self:_initArmyData()
	-- 记录上次滚动
	local contentOffSet = self._tableView:getContentOffset()
	local viewSize = self._tableView:getViewSize()
	local contentSize = self._tableView:getContentSize()
	self._tableView:reloadData()
	-- 滚动到指定地方
	if viewSize.height < contentSize.height then
		self._tableView:setContentOffset(contentOffSet, false)
	end
	if self._selectIndex then
		local cell = self._tableView:cellAtIndex(self._selectIndex)
		if cell then
			cell:setSelect(true)
		end
	end
end

function M:onListenSoldierDataUpdate()
	self._sendCount = self._sendCount - 1
	if self._sendCount < 1 then
		self._sendCount = 0
		self:reloadTeamData()
	end
end


function M:ctor()
	self._contentOffset = cc.p(0,0)
	self._sendCount = 0
	self._isSliderTouch = false
	self:_initArmyData()
	self:_createBackground()
	self:_createAddTeamLayer()
	self:_createTeamView()
	self:_registerScriptHandler()
end



function M:_updateCellSurplus(soldierType, count)
	for key,teamData in pairs(self._armyData) do
		local dataSoldierType = teamData:getSoldierType()
		local cell = self._tableView:cellAtIndex(key - 1)
		if dataSoldierType == soldierType and cell then
			cell:setSurplusSoldierCount(count)
		end
	end
end


function M:_registerScriptHandler()
    self:registerScriptHandler(function(event)
	if event == "exit"then
			Listener:removeListener(self)
        end
    end)
    Listener:addListener(self)
end

function M:_initArmyData()
	self._armyData = {}
	local teamList = PlayerData:getTeamList()
	for _,teamData in pairs(teamList) do
		if Enum.TeamDataState.Inside == teamData:getState() then
			table.insert(self._armyData, teamData)
		end
	end
end

-- 增加tableView
function M:_createTeamView()
	local tableViewSize = cc.size(
		Screen.width, 
		Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight - self._buttonSize.height
		)
	self._tableView = require("share.TableView").new(tableViewSize, self)
	self._tableView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
	self:addChild(self._tableView)
end

function M:onTableViewCellTouched(tableView, cell)
	local selectIndex = cell:getIdx()
	if nil == self._selectIndex then
		cell:setSelect(true)
		self._selectIndex = selectIndex
	elseif selectIndex ~= self._selectIndex then
		local tempCell = self._tableView:cellAtIndex(self._selectIndex)
		tempCell:setSelect(false)
		self._selectIndex = selectIndex
		cell:setSelect(true)
	end
	self._isSliderTouch = false
end

function M:onTableViewCellSize(tableView, idx)
	return EditTeamLayerCell.TableViewCellSize.width, EditTeamLayerCell.TableViewCellSize.height
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = require("ui.team.layer-manager.EditTeamLayerCell").new(self)
	end
	local teamData = self._armyData[idx + 1]
	cell:reload(teamData)
    return cell
end

function M:onTableViewCellCount(tableView)
	return table.getn(self._armyData)
end


-- 增加添加按钮那一栏
function M:_createAddTeamLayer()
	local layer = cc.Layer:create();
	local button = Button.new("ui/team/button-add.png", "ui/team/button-add.png")
	
	button.onClicked = function ()
		local heroSelectLayer = require("ui.team.layer-manager.HeroSelectLayer").new()
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(heroSelectLayer)
	end
	self._buttonSize = button:getContentSize()
	local buttonPosX = Screen.width / 4
	local buttonPosY = Screen.height - BackgroundLayer.TitleHeight - self._buttonSize.height / 2
	button:setPosition(buttonPosX, buttonPosY)
	layer:addChild(button)

	local showlabel = CommonUI:createLabel("点击按钮进行创建编队")
	local showlabelSize = showlabel:getContentSize()
	showlabel:setPosition(buttonPosX + self._buttonSize.width / 2 + showlabelSize.width / 2 , buttonPosY)
	layer:addChild(showlabel)
	self:addChild(layer);
end


-- 添加背景
function M:_createBackground()
	local backgroundLayer = BackgroundLayer.new(self, "编辑")
	backgroundLayer:setBackButtonCallback(function(returnType)
        if returnType ~= BackgroundLayer.ReturnType.TouchMove then
			self:removeFromParent()
		elseif false == self._isSliderTouch then
			self:removeFromParent()
        end
    end)
end

return M