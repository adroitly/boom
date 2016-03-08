local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local M = class("ui.hero-museum.layers.HeroPlaceLayerCell", function()
	return GridViewCell.new()
end)

function M:ctor(delegate)
	self._delegate = delegate
	self:_createButton()
end

function M:reload(buildingData)
	self._buildingData = buildingData
	self:_reload()
end

function M:_reload()
	local buildingId = self._buildingData:getBuildingId()
	local placeName = FamousCityConfigReader:getName(buildingId)
	local coordinate = FamousCityConfigReader:getCoordinate(buildingId)
	local nodeText = string.format("%s\n%d,%d", placeName, coordinate[1], coordinate[2])
	self._button:setText(nodeText)
end

function M:_createButton()
	self._button = CommonUI:createTextButton(self, __Localized("洛阳"), "ui/login/login-button.png")
	self._button.onClicked = function()
		self._delegate:onHeroPlaceCellDidBack(self._buildingData)
	end
end

return M