local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.user-info.layers.SalaryShowLayerCell", function()
	return GridViewCell.new()
end)

local function _getFrame(backpackType)
	return CommonUI:createSpriteFrameTinyName("stage-icon", string.format("%d.png", backpackType))
end

M.SalaryShowLayerCellSize = cc.size(300, Screen.width)

function M:ctor()
	self:_createBackground()
	self:_createLevelLabel()
	-- self:_createProvinceLabel()
	self:_createButtons()
end

function M:reload(level)
	self:_updateLevelLabel(level)
	self:_updateButtons(level)
end

function M:_updateButtons(level)
	local laborageStr = OfficerConfigRead:getLaborage(level)
	local laborage = Utils:formatStringToNumberTable(laborageStr)
	for index,data in ipairs(laborage) do
		self:_updateButton(index, data)
	end
end

function M:_updateButton(index, data)
	local backpackType = data[1]
	local name = BackpackConfigRead:getName(backpackType)
	local number = data[2]
	local showText = string.format("%s:%d",name, number)

	local button = self._buttons[index]
	button:setLabel(showText)
	button.backpackType = backpackType
	local frame = _getFrame(backpackType)
	button:changeNormalSpriteWithFrame(frame, frame)

	button.onClicked = function()
		local scene = Director:getRunningScene()
		local layer = require("ui.backpack.layer-manager.SearchGoodsLayer").new()
		layer:reloadByBackpackId(backpackType)
		scene:addChild(layer)
	end

end

function M:_updateLevelLabel(level)
	local name = OfficerConfigRead:getOfficerName(level)
	self._levelLabel:setString(string.format(__Localized("%s(%s级)"), name, level))
	local provinceTypeStr = OfficerConfigRead:getProvinceType(level)
	-- self._provinceLabel:setVisible(false)
	-- if 0 ~= provinceTypeStr then
	-- 	self:_updateProvinceLabel(provinceTypeStr)
	-- end
end

function M:_updateProvinceLabel(provinceTypeStr)
	local provinceName = ""
	local provinceTypeTable = Utils:formatStringToTable(provinceTypeStr)
	for _,value in pairs(provinceTypeTable) do
		provinceName = string.format("%s%s\n", provinceName, value[1])
	end
	self._provinceLabel:setVisible(true)
	self._provinceLabel:setString(provinceName)

end

function M:_createLevelLabel()
	self._levelLabel = CommonUI:createLabel("TEST", 24)
	local labelSize = self._levelLabel:getContentSize()
	self:addChild(self._levelLabel)
	local x = - M.SalaryShowLayerCellSize.width
	local y = M.SalaryShowLayerCellSize.width / 2 - labelSize.height
	self._levelLabel:setPosition(cc.p(x , y))
end

function M:_createProvinceLabel()
	self._provinceLabel = CommonUI:createLabel("TEST", 24)
	self._provinceLabel:setHorizontalAlignment(0)
	self._provinceLabel:setAnchorPoint(cc.p(0,1))
	self:addChild(self._provinceLabel)

	local labelSize = self._provinceLabel:getContentSize()
	local x = - M.SalaryShowLayerCellSize.width - labelSize.width
	local y = M.SalaryShowLayerCellSize.width / 2 - labelSize.height * 2
	self._provinceLabel:setPosition(cc.p(x , y))
end

function M:_createButtons()
	self._buttons = {}
	local buttonWidth = M.SalaryShowLayerCellSize.height / 6
	for index=1,6 do
		local button = require("ui.backpack.layer-manager.IconButton"):newIconButton()
		self:addChild(button)
		table.insert(self._buttons, button)
		local buttonSize = button:getContentSize()
		button:setPosition(cc.p(buttonWidth * (index - 3.5) - 25, - M.SalaryShowLayerCellSize.width / 2 + buttonSize.height / 2))

		button.onClicked = function()
		end
	end
end

function M:_createBackground()
	local sprite = cc.Sprite:create("ui/user-info/salary-bg.png")
	self:addChild(sprite)
end

return M