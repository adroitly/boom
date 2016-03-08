local MapConfig = require("ui.map.data-manager.MapConfig")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local M = class("ui.alert.AlertData")

local function _isVoidMsgTable(msgTable)
	assert(msgTable.nickname and msgTable.from_x and 
		msgTable.from_y and msgTable.to_x and msgTable.to_y and msgTable.building_id and msgTable.time)
end

function M:ctor(msgTable)
	_isVoidMsgTable(msgTable)
	Table:copy(self, msgTable)
end

function M:newAlertData(msgTable)
	local alertData = M.new(msgTable)
	return alertData
end

function M:getTime()
	return self.time
end

-- 日期转换
function M:getDate()
	return os.date("%Y-%m-%d %H:%M:%S", self.time)
end

function M:getNickName()
	return self.nickname
end

function M:getBuildingId()
	return self.building_id
end

function M:getFromPosition()
	local localCoor = {i = self.from_x, j = self.from_y}
	local twoDCoor = MapConfig:localTo2D(localCoor)
	return twoDCoor
end

function M:getToPosition()
	local localCoor = {i = self.to_x, j = self.to_y}
	local twoDCoor = MapConfig:localTo2D(localCoor)
	return twoDCoor
end
-- 在主页面显示的文字
function M:getAlertMessage()
	local fromPosi = self:getFromPosition()
	local toPosi = self:getToPosition()
	local attackMessage = string.format(__Localized("来自玩家%s[%d,%d]"), self:getNickName(), fromPosi.i, fromPosi.j)
	local aimMessage = string.format(__Localized("的部队正向您的%s[%d,%d]移动"), BuildingConfigReader:getName(self:getBuildingId()), toPosi.i, toPosi.j)
	return string.format("%s%s", attackMessage, aimMessage)
end

return M