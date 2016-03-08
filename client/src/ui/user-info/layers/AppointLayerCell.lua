local M = class("ui.user-info.layers.AppointLayerCell", function()
	return cc.TableViewCell:create()
end)

M.AppointLayerCellSize = cc.size(100,0)

function M:setSelect(isSelect)
	local backSpriteName = {"ui/team/ui-un-0012b.png", "ui/team/ui-un-0012a.png"}
	self._backgroundSprite:setTexture(isSelect and backSpriteName[1] or backSpriteName[2])
end

function M:ctor()
	self:_createBackground()
	self:_createShowLabels()
end

function M:reload(data)
	self._searchUserData = data
	self:_updateLabels()
end

function M:_updateLabels()
	self._labels[1]:setString(self._searchUserData:getName())
	self._labels[2]:setString(self._searchUserData:getGuildName())
	self._labels[3]:setString(self._searchUserData:getLevel())
end

function M:_createShowLabels()
	self._labels = {}
	local labelWidth = Screen.width / 3
	for index=1,3 do
		local label = CommonUI:createLabel("1234567", 30)
		label:setPosition(cc.p(labelWidth * (index - 0.5), M.AppointLayerCellSize.width / 2))
		self:addChild(label)
		table.insert(self._labels, label)
	end
end

function M:_createBackground()
	self._backgroundSprite = cc.Sprite:create("ui/team/ui-un-0012a.png")
	self._backgroundSprite:setScaleY(0.5)
	self._backgroundSprite:setPosition(cc.p(Screen.width / 2, M.AppointLayerCellSize.width / 2))
	self:addChild(self._backgroundSprite)
end

return M