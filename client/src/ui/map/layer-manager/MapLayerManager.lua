
local MapConfig = require("ui.map.data-manager.MapConfig")
local ArmyData = require("ui.map.data-manager.ArmyData")
local ClickOperation = require("ui.map.ClickOperation")

local M = class("ui.map.layer-manager.MapLayerManager", function() 
	local mapModeFile = "ui/map/map-tile.jpg"
	local mapRowData = {row=MapConfig.mapRow, line=MapConfig.mapLine}
	return require("share.BigMapLayer"):bigMapLayer(mapModeFile, mapRowData)
end)

local function _adaptationScale()
	local standardFactor = 1136 / 768
	local screenFactor = Screen.size.height / Screen.size.width
	return screenFactor / standardFactor
end

function M:ctor()
	self._moveTimes = 0

	local adaptationScale = _adaptationScale()
	self:setMinScale(0.8 * adaptationScale)
	self:setMaxScale(1.2 * adaptationScale)
	self:setZoomScale(adaptationScale)
	
	-- 滚动回调
	self:setBigMapLayerDelegate(self._onBigMapLayerDidScroll)
	Touch:registerTouchOneByOne(self, false)

	self._armySpritesManager = require("ui.map.layer-manager.ArmySpritesManager").new()
	self._armySpritesManager:init(self)

	self._buildingSpriteManager = require("ui.map.layer-manager.BuildingSpritesManager").new()
	self._buildingSpriteManager:init(self)

	self._randomResourceSpritesManager = require("ui.map.layer-manager.RandomResSpritesManager").new()
	self._randomResourceSpritesManager:init(self)

	self._scrollViewDidScroll = require("ui.map.logic.ScrollViewDidScroll").new()

	self:scheduleUpdateWithPriorityLua(function(dt) 
		self:_update(dt)
	 end, 0)
end

function M:getArmySpriteManager()
	return self._armySpritesManager
end

function M:getRandomResourceSpriteManager()
	return self._randomResourceSpritesManager
end

function M:getBuildingSpriteManager()
	return self._buildingSpriteManager
end

function M:changeViewCenterToPosition(position)
	local offset = self:_viewPositionChangeToOffset(position)
	self:setContentOffset(offset)

	self._scrollViewDidScroll:changeViewCenter(position)
	Listener:postEvent(Listener.EventName.onViewCenterToPositionChanged)
end

function M:changeViewCenterByTwoDCoor(x, y)
	local twoDCoor = MapConfig:coordinate(x, y)
	local localCoor = MapConfig:twoDToLocal(twoDCoor)
	local position = MapConfig:getPositionFromCoordinate(localCoor)
    self:changeViewCenterToPosition(position)
end

function M:setWaitStatus(armyData)
	self._armySpritesManager:setSpriteWait(armyData)
end

function M:newDialogLayer(dialogLayer)
	assert(dialogLayer)
	self:removeDialogLayer()
	self._dialogLayer = dialogLayer
end

function M:touchGround(point)
	if self._dialogLayer then 
        self:removeDialogLayer()
    else
        self._dialogLayer = require("ui.map-subview.ClickGrasslandDialog"):newClickGrasslandDialog(self, point)     
    end
end

function M:removeDialogLayer()
	if self._dialogLayer then
		self._dialogLayer:removeFromParent()
		self._dialogLayer = nil 
	end
end

------------------ on touch delegate begin ----------------
function M:onTouchBegan(touch, event)
	self._moveLength = 0
    return true
end

function M:onTouchMoved(touch, event)
	local delta = touch:getDelta()
	self._moveLength = self._moveLength + math.abs(delta.x) + math.abs(delta.y)
end

function M:onTouchEnded(touch, event)
	local pt = touch:getLocation()
	local point = self:_mapPointFromLocation(pt)

	if self._moveLength < 10 then 
		ClickOperation:touchMapLayer(point)
	end
end

function M:onTouchCancelled(touch, event)
	self:onTouchEnded(touch, event)
end
------------------ on touch delegate begin ----------------

function M:_onBigMapLayerDidScroll()
	local rect = self:_getViewRect()
	local x = cc.rectGetMidX(rect)
	local y = cc.rectGetMidY(rect)

	self._scrollViewDidScroll:didScroll(cc.p(x, y))
end

function M:_getViewRect()
	local offset = self:getCacheContentOffset();
    local size   = self:getCacheViewSize();
    local scale  = self:getCacheZoomScale();
   
    return cc.rect(-offset.x/scale,
                    -offset.y/scale, 
                    size.width/scale,
                    size.height/scale)
end

function M:_viewPositionChangeToOffset(position)
	local scale  = self:getCacheZoomScale();
    local size   = self:getCacheViewSize();
    local offsetx = size.width/2/scale - position.x 
	local offsety = size.height/2/scale - position.y 
    
	return cc.p(offsetx*scale, offsety*scale)
end

-- 由屏幕坐标转换为地图坐标
function M:_mapPointFromLocation(location)
	local scale  = self:getCacheZoomScale();
	local offset = self:getCacheContentOffset();

    local x = (location.x - offset.x) / scale
    local y = (location.y - offset.y) / scale

	return cc.p(x, y)
end

function M:_update(dt)
	self._armySpritesManager:update(dt)
end

return M


