
local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local M = class("ui.map.layer-manager.AllFamousCityShowLayerCell",function()
	return GridViewCell.new()
end)
M.AllFamousCityShowLayerCellSize = cc.size(0, 120)
function M:ctor(delegate)
	self:_createButton(delegate)
end

function M:reload(buildingId)
	self._buildingId = buildingId
	local placeName = FamousCityConfigReader:getName(buildingId)
	local coordinate = FamousCityConfigReader:getCoordinate(buildingId)
	local nodeText = string.format("%s\n%d,%d", placeName, coordinate[1], coordinate[2])
	self._button:setText(nodeText)
end

function M:_createButton(delegate)
	self._button = CommonUI:createTextButton(self, "", "ui/login/login-button.png")
	self._button:setSwallowTouches(false)
	self._button.onClicked = function()
		delegate:onAllFamousCityShowLayerCellDidBack(self._buildingId)
	end
end

return M