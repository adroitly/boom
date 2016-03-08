local BackgroundLayer = require("ui.common.BackgroundLayer")
local MoreAlertCell = require("ui.alert.MoreAlertCell")
local AlertData = require("ui.alert.AlertData")
local M = class("ui.alert.MoreAlertLayer", function()
	return cc.Layer:create()
end)

function M:ctor()
	self._alertDataList = {}
	self:_registerScriptHandler()
	self:_createBackground()
	self:_createTableView()
end

function M:reloadData(alertList)
	self._alertDataList = alertList
	self._tableView:reloadData()
end

function M:onListenOpenAlertCoordinate()
	self:removeFromParent()
end

function M:onTableViewCellTouched(tableView, cell)

end

function M:onTableViewCellSize(tableView, idx)
	return MoreAlertCell.MoreAlertCellSize.width, MoreAlertCell.MoreAlertCellSize.height
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = MoreAlertCell.new()
	end
	local alertData = self._alertDataList[idx + 1]
	cell:reloadData(alertData)
    return cell
end


function M:onTableViewCellCount(tableView)
	return table.getn(self._alertDataList)
end

function M:_registerScriptHandler()
    self:registerScriptHandler(function(event)
	if event == "exit"then
			Listener:removeListener(self)
        end
    end)
    Listener:addListener(self)
end

function M:_createTableView()
	local tableViewSize = cc.size(
		Screen.width, 
		Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight
		)
	self._tableView = require("share.TableView").new(tableViewSize, self)
	self._tableView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
	self:addChild(self._tableView)
end

function M:_createBackground()
	local backgroundLayer = BackgroundLayer.new(self, "预警信息")
	backgroundLayer:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M