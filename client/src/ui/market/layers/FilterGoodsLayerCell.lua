local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.market.layers.FilterGoodsLayerCell", function()
	return cc.TableViewCell:new()
end)
M.FilterGoodsLayerCellSize = cc.size(200 , 120)
function M:ctor(delegate)
	self:_createButton(delegate)
end

function M:reload(filterData)
	self:_reloadNodes(filterData)
end

function M:_reloadNodes(filterData)
	local showText = ""
	if Enum.ResourceTypeId.Hero == filterData:getResourceId() then
		if not filterData:getLevel() then
			showText = __Localized("所有英雄")
		else
			showText = string.format(__Localized("%d级英雄"), filterData:getLevel())
		end
	elseif Enum.ResourceTypeId.Item == filterData:getResourceId() then
		if not filterData:getBackpackType() then
			showText = __Localized("所有道具")
		else
			showText = BackpackConfigRead:getName(filterData:getBackpackType())
		end
	else
		showText = __Localized("所有物品")
	end
	self._button:setText(showText)
end

function M:_createButton(delegate)
	self._button = CommonUI:createTextButton(self, "", "ui/login/login-button.png")
	self._button:setSwallowTouches(false)
	self._button.onClicked = function()
		if delegate.onFilterGoodsCellDidBack then
			delegate:onFilterGoodsCellDidBack(self:getIdx(), self._button:getText())
		end
	end

	self._button:setPosition(cc.p(M.FilterGoodsLayerCellSize.width / 2, M.FilterGoodsLayerCellSize.height / 2))
end

return M