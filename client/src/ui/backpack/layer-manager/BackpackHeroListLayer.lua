local HeroDataManager = require("player-data.HeroDataManager")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.backpack.layer-manager.BackpackHeroListLayer", function()
	return cc.Layer:create()
end)

function M:ctor()
	Event:registerNodeEvent(self)
	self:_getHeroListData()
	self:_createGridView()
end

function M:onEnterTransitionFinish()
    Listener:addListener(self)
end

function M:onExit()
    Listener:removeListener(self)
end

function M:onListenHeroDataChange()
	-- 记录上次滚动
	local contentOffset = self._gridView:getContentOffset()
	self._gridView:reloadData()
	local minOffset = self._gridView:minContainerOffset()
	local maxOffset = self._gridView:maxContainerOffset()
	if contentOffset.x >= minOffset.x and contentOffset.x <= maxOffset.x then
		self._gridView:setContentOffset(contentOffset)
	end
end

function M:_getHeroListData()
	self._heroList  = HeroDataManager:getBackpackHeroList()
end

function M:_createGridView()
	local gridViewSize = cc.size(
		Screen.width,
		Screen.height - BackgroundLayer.TitleHeight * 2
		)
	self._gridView = GridView.new(gridViewSize, self, 4)
	self._gridView:setPosition(0, BackgroundLayer.TitleHeight)
	self:addChild(self._gridView)
end


function M:onGridViewLineHeight(pageView, idx)
	return 200
end

function M:onGridViewCellAtIndex(pageView, idx)
	local button = pageView:dequeueCell()
	if nil == button then
		button = require("ui.backpack.layer-manager.BackpackHeroListCell").new()
		button:setPosition(cc.p(0, button:getContentSize().height))
	end
	button:reloadData(self._heroList[idx + 1])
    return button
end

function M:onGridViewCellCount(pageView)
	return table.getn(self._heroList)
end

return M