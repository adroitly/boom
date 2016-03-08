
local M = class("ui.backpack.layer-managet.SearchGoodsCell", function()
	return cc.TableViewCell:create()
end)

M.SearchGoodsCellSize = cc.size(100, 0)

function M:ctor()
	self:_createBackground()
	self:_createShowPlaceLabel()
	self:_createButton()
end

function M:reload(data)
end

function M:_createButton()
	local searchButton = CommonUI:createTextButton(
		self, __Localized("前往"),  "ui/team/ui-but-0004a.png", "ui/team/ui-but-0004a.png")
	local searchButtonSize = searchButton:getContentSize()
	searchButton.onClicked = function()
		self:_searchButtonClick()
	end
	searchButton:setPosition(Screen.width - searchButtonSize.width, M.SearchGoodsCellSize.width / 2)
end

function M:_searchButtonClick()
	
end

function M:_createShowPlaceLabel()
	local placeName = "火焰山"
	self._placeLabel = CommonUI:createLabel(__Localized("前往")..placeName..__Localized("采集"), 36)
	self._placeLabel:setAnchorPoint(0, 0.5)
	self._placeLabel:setPosition(50, M.SearchGoodsCellSize.width / 2)
	self:addChild(self._placeLabel)
end

function M:_createBackground()
	local backgroundSprite = cc.Sprite:create("ui/team/ui-un-0015.png")
	local backSpriteSize = backgroundSprite:getContentSize()
	backgroundSprite:setScaleX(3)
	backgroundSprite:setPosition(Screen.width / 2 , M.SearchGoodsCellSize.width / 2)
	self:addChild(backgroundSprite)
end

return M