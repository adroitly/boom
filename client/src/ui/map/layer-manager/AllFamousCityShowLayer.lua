local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local AllFamousCityShowLayerCell = require("ui.map.layer-manager.AllFamousCityShowLayerCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.map.layer-manager.AllFamousCityShowLayer", function()
	return cc.Layer:create()
end)

function M:ctor()
	self:_createBackground()
	self:_registerClickHandler()
	self:_initData()
	self:_createGridView()
end

function M:onAllFamousCityShowLayerCellDidBack(buildingId)
	if false == self._isMoving then
		local mapLayerManager = MapManager:getMapLayerManager()
		local twoDCoorTable = FamousCityConfigReader:getCoordinate(buildingId)
        mapLayerManager:changeViewCenterByTwoDCoor(twoDCoorTable[1], twoDCoorTable[2])
	end
end

function M:onTouchBegan(touch,event)
	self._beganLocation = touch:getLocation()
	return true
end

function M:onTouchMoved(touch,event)
	local location = touch:getLocation()
	if location.y - self._beganLocation.y > 5 then
		self._isMoving = true
	else
		self._isMoving = false
	end
end

function M:onTouchEnded(touch,event)
	local isTouchOutSide = Touch:isTouchHitted(self, touch)
	if false == isTouchOutSide and false == self._isMoving then
		self:_onClickOutSide()
	end
	self._isMoving = false
end

function M:_initData()
	self._famousCityIdList = self:_getFamousCityConfigIdList()
end

function M:onGridViewCellCount(gridView)
	return table.getn(self._famousCityIdList)
end

function M:onGridViewLineHeight(gridView)
	return AllFamousCityShowLayerCell.AllFamousCityShowLayerCellSize.height
end
function M:onGridViewCellAtIndex(gridView, idx)
	local cell = gridView:dequeueCell()
	if not cell then
		cell = AllFamousCityShowLayerCell.new(self)
	end
	cell:reload(self._famousCityIdList[idx + 1])
	return cell
end

function M:_createGridView()
	local viewSize = cc.size(Screen.width / 4, Screen.height)
	self:setContentSize(viewSize)
	local guildView = GridView.new(viewSize, self, 1)
	self:addChild(guildView)
end

function M:_getFamousCityConfigIdList()
    local famousCityIdList = {}
    for _,famousCityConfigData in pairs(require("config.FamousCityConfig")) do
        table.insert(famousCityIdList, famousCityConfigData.id)
    end
    table.sort(famousCityIdList, function(famousCityId1, famousCityId2)
		return famousCityId1 < famousCityId2
    end)
    return famousCityIdList
end
function M:_onClickOutSide()
	Touch:removeTouchOneByOne(self)
	self:removeFromParent()
end

function M:_createBackground()
	local background = cc.LayerColor:create(cc.c4b(0, 0, 0, 40))
	self:addChild(background)
end

function M:_registerClickHandler()
	Touch:registerTouchOneByOne(self, true)
end

return M