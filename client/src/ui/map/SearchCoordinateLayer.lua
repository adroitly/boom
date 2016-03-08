local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.SearchCoordinateLayer",function()
	return cc.Layer:create()
end)

function M:ctor(coor)
	self:_createBackground()
	self:_createInputTextField(coor)
	self:_createConfirmButton()
end

function M:_createInputTextField(coor)
	-- self._inputXTextField = require("ui.common.EditBox").new(cc.size(200, 50), "ui/login/login-bt.png")
	self._inputXTextField = require("ui.common.InputUI").new()
	-- 数字键盘
	self._inputXTextField:setInputMode(cc.EDITBOX_INPUT_MODE_NUMERIC)

	self:addChild(self._inputXTextField)

	self._inputYTextField = require("ui.common.InputUI").new()
	-- self._inputYTextField = require("ui.common.EditBox").new(cc.size(200, 50), "ui/login/login-bt.png")
	-- 数字键盘
	self._inputYTextField:setInputMode(cc.EDITBOX_INPUT_MODE_NUMERIC)

	self:addChild(self._inputYTextField)


	self._inputXTextField:setTextColor(cc.c4b(255, 255, 255, 255))
	self._inputXTextField:setString(coor.i)
	self._inputXTextField:setMaxLength(3)

	self._inputYTextField:setTextColor(cc.c4b(255, 255, 255, 255))
	self._inputYTextField:setPlaceHolder(__Localized("请输入"))
	self._inputYTextField:setString(coor.j)
	self._inputYTextField:setMaxLength(3)

	local textFieldSize = self._inputXTextField:getContentSize()

	self._inputXTextField:setPosition(cc.p(Screen.width / 2 - textFieldSize.width, Screen.height / 2))
	self._inputYTextField:setPosition(cc.p(Screen.width / 2 + textFieldSize.width, Screen.height / 2))

end

local function _changeMapView(x, y)
	local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:changeViewCenterByTwoDCoor(x, y)
end

function M:_createConfirmButton()
	local confirmButton = CommonUI:createTextButton(self, "查看", "ui/login/login-button.png")
	local confirmButtonSize = confirmButton:getContentSize()
	confirmButton:setPosition(cc.p(Screen.width / 2, Screen.height / 2 - confirmButtonSize.height * 2))
	confirmButton.onClicked = function()
		local inputXStr = self._inputXTextField:getString()
		local inputYStr = self._inputYTextField:getString()
		local x = tonumber(inputXStr)
		local y = tonumber(inputYStr)
		if x and y then
			_changeMapView(x, y)
			self:removeFromParent()
		else
			CommonUI:lightTips(__Localized("输入有误"))
		end
	end
end

function M:_createBackground()
	local background = require("ui.common.BackgroundLayer").new(self, "输入坐标")
	background:setBackButtonCallback(function()
		self:removeFromParent()
	end)
end

return M