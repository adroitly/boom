--[[
	* 描述：背景大地图，可以无限循环
	* 参数mapFile：地图模板文件名
	* 参数rowTable：{row=几列, line=几行}
]]
local M = class("share.BigMapLayer", function()
    return cc.ScrollView:create()
end)

function M:bigMapLayer(mapFile, rowTable)
	local layer = M.new()
	layer:init(mapFile, rowTable)
	return layer
end

function M:init(mapFile, rowTable)
	self._recodeRefreshArray = {}
	self._cacheTileSprite = {}	
	self._useTileSprite = {}
	self._mapFile = mapFile
	
	self:_preLoadTileSprite()
	assert(#self._cacheTileSprite > 0)
	self._tileSize = self._cacheTileSprite[1]:getContentSize()
	self._tileRectangle = rowTable	

	local size = cc.Director:getInstance():getWinSize()
	self:setViewSize(size)
	self:setBounceable(false)
	self:setDelegate()
	self:_setMapContentSize()

	self:registerScriptHandler(function()
		self:_onScrollViewDidScroll()
	end, cc.SCROLLVIEW_SCRIPT_SCROLL)

	self:registerScriptHandler(function()
		self:_onScrollViewDidZoom()
	end, cc.SCROLLVIEW_SCRIPT_ZOOM)

	self._zoomScaleCache = 1.0
	self._offsetCache = cc.p(0, 0)
	self._viewSizeCache = self:getViewSize()
	self:_refreshWithIndex(0)
end

function M:setBigMapLayerDelegate(onBigMapLayerDidScroll)
	self._bigMapLayerDidScroll = onBigMapLayerDidScroll
end

function M:isRectVisible(rect)
	local offset = self._offsetCache
    local size   = self._viewSizeCache
    local scale  = self._zoomScaleCache
   
    local viewRect = cc.rect(-offset.x/scale,
    					 -offset.y/scale, 
    					 size.width/scale,
    					  size.height/scale)
  
 	return cc.rectIntersectsRect(viewRect, rect)   
end

-- 为了提高效率使用
function M:getCacheContentOffset()
	return cc.p(self._offsetCache.x, self._offsetCache.y)
end

function M:getCacheViewSize()
	return cc.size(self._viewSizeCache.width, self._viewSizeCache.height)
end

function M:getCacheZoomScale()
	return self._zoomScaleCache
end

function M:_tileIndexWithPosition(position)
	local rowNumber = math.floor(position.x / self._tileSize.width) 
	local lineNumber = math.floor(position.y / self._tileSize.height) * self._tileRectangle.row
	return rowNumber + lineNumber
end

-- index位置的坐标
function M:_posWithIndex(index)
	local x = (index % self._tileRectangle.row) * self._tileSize.width
	local y = math.floor((index / self._tileRectangle.row)) * self._tileSize.height
	return cc.p(x, y)
end

function M:_rectWithTileIndex(index)
	local pos = self:_posWithIndex(index)
	return cc.rect(pos.x, pos.y, self._tileSize.width, self._tileSize.height)
end

function M:_createCacheMapTile()
	local tile = cc.Sprite:create(self._mapFile)
	self:addChild(tile, -100)
	table.insert(self._cacheTileSprite, tile)
end

function M:_preLoadTileSprite()
	-- 预先加载4个
	for i=1,4 do
		self:_createCacheMapTile()
	end
end

function M:_setMapContentSize()
	local sprite = self._cacheTileSprite[1]
	local size = cc.size(self._tileSize.width * self._tileRectangle.row, 
						 self._tileSize.height * self._tileRectangle.line)
	self:setContentSize(size)
end

function M:_getTileSprite()
	if table.getn(self._cacheTileSprite)==0 then 
		self:_createCacheMapTile()
	end 

	local sprite = table.remove(self._cacheTileSprite)
	if sprite then 
		table.insert(self._useTileSprite, sprite)
		return sprite
	end 
	assert(sprite)
end

-- 递归index4个方向
function M:_refreshRoundWithIndex(index)
	local indexs = {index+1, index-1, 
					index+self._tileRectangle.row, 
					index-self._tileRectangle.row}
	for _, v in pairs(indexs) do
		self:_refreshWithIndex(v)
	end
end

function M:_isSpriteWithIndex(index)
	for _, v in pairs(self._useTileSprite) do 
		if v:getTag()==index then 
			return true
		end 
	end 
end

-- 查询index位置是否已存在，否则创建精灵并把精灵移到该位置
function M:_showSpriteWithIndex(index)
	local res = self:_isSpriteWithIndex(index)
	if res then 
		return 
	end

	local sprite = self:_getTileSprite()
	local pos = self:_posWithIndex(index)
	pos.x = pos.x + self._tileSize.width/2
	pos.y = pos.y + self._tileSize.height/2
	sprite:setPosition(pos)
	sprite:setTag(index)
end

function M:_isIndexExist(index)
	for _, v in pairs(self._recodeRefreshArray) do
		if v == index then 
			return true
		end 
	end
end

-- 从index开始递归索引需要显示的sprite
function M:_refreshWithIndex(index)
	-- 防止重复索引 
	if self:_isIndexExist(index) then 
		return
	end 
	table.insert(self._recodeRefreshArray, index)

	local rect = self:_rectWithTileIndex(index)
	local isVisiable = self:isRectVisible(rect)
	if isVisiable then 
		self:_showSpriteWithIndex(index)
		self:_refreshRoundWithIndex(index)
	end 
end

function M:_getVaildIndex()
	local offsetx, offsety = self._offsetCache.x, self._offsetCache.y
	local scale  = self._zoomScaleCache;
	offsetx = math.abs(offsetx / scale)
	offsety = math.abs(offsety / scale)
	local x = math.floor(offsetx / self._tileSize.width)
	local y = math.floor(offsety / self._tileSize.height) * self._tileRectangle.row
	return x + y
end

function M:_recoverySprite()
	for k, sprite in pairs(self._useTileSprite) do 
		if not self:isNodeVisible(sprite) then
			sprite:setTag(-100)
			table.insert(self._cacheTileSprite, sprite)  
			self._useTileSprite[k] = nil
		end 
	end 

	local index = self:_getVaildIndex()
	self._recodeRefreshArray = {}
	self:_refreshWithIndex(index)
end

function M:_onScrollViewDidScroll(scrollView)
	self._offsetCache = self:getContentOffset()
	
	self:_recoverySprite()

	if self._bigMapLayerDidScroll then 
		self:_bigMapLayerDidScroll()
	end 
end

function M:_onScrollViewDidZoom(scrollView)
	self._zoomScaleCache = self:getZoomScale()
end

return M


