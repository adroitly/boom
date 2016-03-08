local BackgroundLayer = require("ui.common.BackgroundLayer")
local BuildingDefenceCell = require("ui.outside-search.layers.BuildingDefenceCell")
local M = class("ui.outside-search.layers.BuildingDefenceLayer", function()
	return cc.Layer:create()
end)

function M:ctor(buildingSearchData)
	self._armyDataList = buildingSearchData:getArmyDataList()
	self:_createTableView()
	self:_init()
end

function M:_init()
	local viewSize = cc.size(Screen.width, Screen.height / 2 - BackgroundLayer.BottomHeight)
	self:setContentSize(viewSize)
end


function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
	return BuildingDefenceCell.BuildingDefenceCellSize.height,0
end

function M:onTableViewCellAtIndex(tableView, idx)
	local cell = tableView:dequeueCell()
	if nil == cell then
		cell = BuildingDefenceCell.new()
	end
	cell:reload(self._armyDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
	return table.getn(self._armyDataList)
end

function M:_createTableView()
	local viewSize = cc.size(Screen.width, Screen.height / 2 - BackgroundLayer.BottomHeight)
	self._tableView = require("share.TableView").new(viewSize, self)
	self:addChild(self._tableView)
end

return M