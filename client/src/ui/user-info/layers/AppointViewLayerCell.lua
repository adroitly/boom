local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local M = class("ui.user-info.layers.AppointViewLayerCell", function()
	return cc.TableViewCell:create()
end)
M.AppointViewLayerCellSize = cc.size(70,100)

function M:setSelect(isSelect)
	local backSpriteName = {"ui/team/ui-un-0012b.png", "ui/team/ui-un-0012a.png"}
	self._backgroundSprite:setTexture(isSelect and backSpriteName[1] or backSpriteName[2])
end

function M:ctor()
	self._officerLevel = 1
	self:_createBackground()
	self:_createLevelLabel()
	self:_createNowLevelLabel()
end

function M:getOfficeLevel()
	return self._officerLevel
end

function M:reload(level)
	local name = OfficerConfigRead:getOfficerName(level)
	self._officerLevel = level
	self._levelLabel:setString(string.format(__Localized("%s(%d级)"), name, level))
	self._nowLevelLabel:setVisible(false)
	self:setSelect(false)
end

function M:setNowLevel()
	self._nowLevelLabel:setVisible(true)
end

function M:_createNowLevelLabel()
	self._nowLevelLabel = CommonUI:createLabel(__Localized("当前官职"), 24)
	local labelSize = self._nowLevelLabel:getContentSize()
	self:addChild(self._nowLevelLabel)
	self._nowLevelLabel:setPosition(labelSize.width, M.AppointViewLayerCellSize.height / 2)
end

function M:_createLevelLabel()
	self._levelLabel = CommonUI:createLabel("TEST", 24)
	self:addChild(self._levelLabel)
	self._levelLabel:setPosition(Screen.width / 2, M.AppointViewLayerCellSize.height / 2)
end

function M:_createBackground()
	self._backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	self._backgroundSprite:setScaleY(0.5)
	local backgroundSize = self._backgroundSprite:getContentSize()
	self._backgroundSprite:setPosition(cc.p(cc.p(backgroundSize.width / 2, M.AppointViewLayerCellSize.height / 2)))
	self:addChild(self._backgroundSprite)
end

return M