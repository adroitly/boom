local M = class("ui.map.CoordinateLayer", function()
    return cc.Layer:create()
end)

-- 屏幕坐标点显示Layer
function M:ctor()
    self._coorLabel = CommonUI:createLabel("", 25)
    self:addChild(self._coorLabel)

	local searchCoordinateButton = Button.new("ui/map/map-search-button.png")
	self:addChild(searchCoordinateButton)
    searchCoordinateButton:setSwallowTouches(false)
	searchCoordinateButton.onClicked = function()
		local scene = cc.Director:getInstance():getRunningScene()
		local searchLayer = require("ui.map.SearchCoordinateLayer").new(self._coor)
		scene:addChild(searchLayer)
	end

	local buttonSize = searchCoordinateButton:getContentSize()
	searchCoordinateButton:setPosition(cc.p(Screen.size.width/2 - buttonSize.width * 1.5, 180))
	self._coorLabel:setAnchorPoint(cc.p(0,0.5))
    self._coorLabel:setPosition(cc.p(Screen.size.width/2 - buttonSize.width, 180))
end

function M:showCoordinate(coor)
	self._coor = coor
    local text = string.format("坐标:%d, %d", coor.i, coor.j)
    self._coorLabel:setString(text)
end

function M:getCooridnate()
    return self._coor
end

return M

