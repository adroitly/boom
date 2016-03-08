local M = class("ui.market.layers.MarketBottomLayer", function()
	return cc.Layer:create()
end)

local m_labelTextList = 
{
	__Localized("已到底部了"),
	__Localized("向上滑动加载下一页")
}

function M:ctor()
	self:_createBackground()
	self:setContentSize(cc.size(Screen.width, 100))
	self:_createLabel()
end
function M:updateListEnd()
	self._showLabel:setString(m_labelTextList[1])
	self._isInEnd = true
end

function M:updateListNotEnd()
	self._showLabel:setString(m_labelTextList[2])
	self._isInEnd = false
end

function M:isInEnd()
	return self._isInEnd == true
end

function M:_createBackground()
	local background = cc.LayerColor:create(cc.c4b(0, 100, 100, 150))
    background:setContentSize(cc.size(Screen.width, 100))
    self:addChild(background)
end

function M:_createLabel()
	self._showLabel = CommonUI:createLabel(m_labelTextList[1], 30)
	self._showLabel:setPosition(cc.p(Screen.width / 2, 50))
	self:addChild(self._showLabel)
end

return M