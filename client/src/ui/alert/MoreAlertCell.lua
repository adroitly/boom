local AlertData = require("ui.alert.AlertData")
local MapConfig = require("ui.map.data-manager.MapConfig")
local ElementText = require("ui.common.richlabel.ElementText")
local RichLabel = require("ui.common.richlabel.RichLabel")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local M = class("ui.alert.MoreAlertCell", function()
	return cc.TableViewCell:new()
end)

M.MoreAlertCellSize = cc.size(100, Screen.width)

function M:ctor()
	self:_createShowLabel()
end

function M:reloadData(alertData)
	local showTime = alertData:getDate()
	local nickName = alertData:getNickName()
	local toPosi = alertData:getToPosition()
	local fromPosi = alertData:getFromPosition()
	local buildingId = alertData:getBuildingId()

	local startStr = string.format("%s%s%s", showTime, __Localized("来自玩家"), nickName)
	self._startElenemt:updateText(startStr)

	local fromStr = string.format("[%s,%s]", fromPosi.i, fromPosi.j)
	self._fromElement:updateText(fromStr)

	self._fromElement.onClicked = function()
		self:_labelClick(fromPosi)
	end

	local endStr = string.format("%s%s",__Localized("的部队正向您的"), BuildingConfigReader:getName(buildingId))
	self._endElement:updateText(endStr)

	local toStr = string.format("[%s,%s]", toPosi.i, toPosi.j)
	self._toElememt:updateText(toStr)
	self._toElememt.onClicked = function()
		self:_labelClick(toPosi)
	end

	self._lastElement:updateText(__Localized("移动"))
	self._richLabel:reloadData()
end

function M:_labelClick(position)
	local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:changeViewCenterByTwoDCoor(position.i, position.j)

    Listener:postEvent(Listener.EventName.onListenOpenAlertCoordinate)
end


function M:_createShowLabel()
	self._richLabel = RichLabel.new()
	self:addChild(self._richLabel)

	self._startElenemt = ElementText:createLabel("", 24)
	self._richLabel:pushElement(self._startElenemt)

	self._fromElement = ElementText:createLabel("", 24, cc.c4b(63, 49, 252, 244))
	self._fromElement:setUnderLine(true)
	self._richLabel:pushElement(self._fromElement)

	self._endElement = ElementText:createLabel("", 24)
	self._richLabel:pushElement(self._endElement)

	self._toElememt = ElementText:createLabel("", 24, cc.c4b(63, 49, 252, 244))
	self._toElememt:setUnderLine(true)
	self._richLabel:pushElement(self._toElememt)

	self._lastElement = ElementText:createLabel("", 24)
	self._richLabel:pushElement(self._lastElement)

	self._richLabel:setPosition(cc.p(0, M.MoreAlertCellSize.width))
end


return M