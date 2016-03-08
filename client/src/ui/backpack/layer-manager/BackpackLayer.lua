local BackgroundLayer = require("ui.common.BackgroundLayer")
local BackpackButton = require("ui.backpack.layer-manager.BackpackButton")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local M = class("ui.backpack.layer-manager.BackpackLayer", function()
	return cc.Layer:create()
end)

function M:ctor()
	self:_getBackpackData()
	self:_createBackView()
	self:_registerScriptHandler()
end

function M:onListenBackpackDataChange()
	self._backData = {}
	self:_getBackpackData()
	self._pageView:reloadData()
end


function M:_registerScriptHandler()
	Listener:addListener(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			Listener:removeListener(self)
		end
    end)
end

function M:_getBackpackData()
	local backpackDataItemList = PlayerData:getBackpackItemList()
	self._backData = {}
	for _,backpackData in pairs(backpackDataItemList) do
		local count = backpackData:getItemNumber()
		local itemId = backpackData:getItemType()
		local itemType = BackpackConfigRead:getItemType(itemId)
		if count > 0 and 2 ~=  itemType then
			table.insert(self._backData, backpackData)
		end
	end
	
end

function M:_createBackView()
	local pageViewSize = cc.size(
		Screen.width,
		Screen.height - BackgroundLayer.TitleHeight * 2
		)
	self._pageView = require("share.PageView").new(pageViewSize, self, 4)
	self._pageView:setPosition(0, BackgroundLayer.TitleHeight)
	self:addChild(self._pageView)
end

function M:onPageViewCellTouched(pageView, cell)
end

function M:onPageViewCellSize(pageView, idx)
	return 50, 0
end

function M:onPageViewCellAtIndex(pageView, idx)
	local button = pageView:dequeueCell()
	if nil == button then
		button = BackpackButton:newIconButton()
		button:setPosition(cc.p(0, button:getContentSize().height))
	end
	button:reloadData(self._backData[idx + 1])
    return button
end

function M:onPageViewCellCount(pageView)
	return table.getn(self._backData)
end

return M
