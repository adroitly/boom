local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local M = class("ui.user-info.layers.ContributeOfficerCell" , function()
	return cc.TableViewCell:create()
end)

M.ContributeOfficerCellSize = cc.size(70,100)

function M:ctor()
	self._officerLevel = 1
	self:_createBackground()
	self:_createLevelLabel()
	self:_createNowLevelLabel()
	self:_createVipTipsLabel()
end

function M:getOfficeLevel()
	return self._officerLevel
end

function M:reload(level)
	local name = OfficerConfigRead:getOfficerName(level)
	self._officerLevel = level
	self._levelLabel:setString(string.format(__Localized("%s(%d级)"), name, level))
	self._nowLevelLabel:setVisible(false)
	self:_updateVipTipsLabel(level)
end

function M:setNowLevel()
	self._nowLevelLabel:setVisible(true)
end

function M:_updateVipTipsLabel(level)
	self._vipTipsLabel:setVisible(false)
	local vipMax = VipConfigReader:getVipMax()
	for vipLevel=1,vipMax do
		local officersmax = VipConfigReader:getOfficersMax(vipLevel)
		if level == officersmax then
			self._vipTipsLabel:setVisible(true)
			self._vipTipsLabel:setString(string.format(__Localized("需达到VIP%s"), vipLevel))
			return
		end
	end
end

function M:_createNowLevelLabel()
	self._nowLevelLabel = CommonUI:createLabel(__Localized("当前官职"), 24)
	local labelSize = self._nowLevelLabel:getContentSize()
	self:addChild(self._nowLevelLabel)
	self._nowLevelLabel:setPosition(labelSize.width, M.ContributeOfficerCellSize.height / 2)
end

function M:_createLevelLabel()
	self._levelLabel = CommonUI:createLabel("TEST", 24)
	self:addChild(self._levelLabel)
	self._levelLabel:setPosition(Screen.width / 2, M.ContributeOfficerCellSize.height / 2)
end

function M:_createVipTipsLabel()
    self._vipTipsLabel = CommonUI:createLabel(__Localized("需达到VIP10"), 24)
	local labelSize = self._vipTipsLabel:getContentSize()
	self:addChild(self._vipTipsLabel)
	self._vipTipsLabel:setPosition(Screen.width - labelSize.width, M.ContributeOfficerCellSize.height / 2)
end

function M:_createBackground()
	local backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	backgroundSprite:setScaleY(0.5)
	local backgroundSize = backgroundSprite:getContentSize()
	backgroundSprite:setPosition(cc.p(cc.p(backgroundSize.width / 2, M.ContributeOfficerCellSize.height / 2)))
	self:addChild(backgroundSprite)
end

return M