local M = class("ui.Common.TextSprite" , function(spriteName)
	return cc.Sprite:create(spriteName)
end)

function M:createTextSprite(parent, spriteName, text, size)
	assert(text, spriteName)
	local sprite = M.new(spriteName)
	sprite:_initText(text, size or 26)
	parent:addChild(sprite)
	return sprite
end


function M:_initText(text, size)
	self._textLabel = CommonUI:createLabel(text, size)
	self._textLabel:enableOutline(cc.c4b(0, 0, 0, 255), 3)
	self:addChild(self._textLabel)
	Layout:layout(self._textLabel, self:getContentSize(), Layout.center)
end

function M:setTextColor(color)
	self._textLabel:setTextColor(color)
end

function M:setText(text)
	self._textLabel:setString(text)
end

function M:setSystemFontSize(size)
	self._textLabel:setSystemFontSize(size)
end
return M
