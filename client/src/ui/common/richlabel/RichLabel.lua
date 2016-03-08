local M = class("ui.common.richlabel.RichLabel", function()
	return cc.Node:create()
end)

M.LayoutType = 
{
	FromTopToBottom = 1,
	FromBottomToTop = 2,
}

M.Alignment = 
{
	Center = 1,
	Left = 2,
	Right = 3,
}

-- 偏移量，2-5最为合适
local m_skew = 3

--[[
elementList 为ElementSprite,ElementText,ElementButton,ElementTextButton的列表
如:[ElementSprite, ElementText]
viewWWidth为显示的宽度
lineHeight为行间距

需要实现onClick回调则把重写onClicked方法
]]
function M:ctor(elementList, viewWidth, lineHeight)
	self._viewWidth = viewWidth or Screen.width
	self._elementList = elementList or {}
	self._lineHeight = lineHeight or 0
	self._alignment = M.Alignment.Left
	self._layoutType = M.LayoutType.FromTopToBottom
	self:reloadData()
end

-- 设置显示靠左，靠右，居中
function M:setAlignment(alignment)
	self._alignment = alignment
end

-- 设置排版方向，从上往下，从下往上
function M:setLayout(layoutType)
	self._layoutType = layoutType
end

-- 设置行间距
function M:setLineHeight(lineHeight)
	self._lineHeight = lineHeight
end

-- 设置显示的宽度
function M:setViewWidth(viewWidth)
	self._viewWidth = viewWidth
end

-- 重新刷新
function M:reloadData()
	self:removeAllChildren()
	self._showElementList = {}
	self:_split()
	self:_createListShow()
end

-- 在增加一个element
function M:pushElement(element)
	table.insert(self._elementList, element)
end

function M:clearAllElement()
	self._elementList = {}
end

function M:setElementList(elementList)
	self:clearAllElement()
	self._elementList = elementList
end

function M:getElementList()
	return self._elementList
end

-----------------以下为私有方法---------------

function M:_createListShow()
	local nowHeight = 0
	for _,lineRichList in ipairs(self._showElementList) do
		local width = 0
		local height = 0
		local nodeParent = cc.Node:create()
		for _,element in ipairs(lineRichList) do
			local node = self:_getNodeFromBase(element)
			nodeParent:addChild(node)
			node.onClicked = function()
				local func = self:_getRichClicked(element)
				if func then
					func(node, element)
				end
			end

			local size = node:getContentSize()
			self:_updateNodePosition(node, width, nowHeight)
			self:_checkBottomLine(nodeParent, node, element, nowHeight)
			width = width + size.width
			if size.height > height then
				height = size.height
			end
		end
		self:_updateNodeParentPosition(nodeParent, width)
		self:addChild(nodeParent)
		nowHeight = nowHeight + height + self._lineHeight
	end
	nowHeight = nowHeight - self._lineHeight
	self:setContentSize(cc.size(self._viewWidth, nowHeight))
end

function M:_split()
	self._nowWith = 0
	local lineList = {}
	for _,element in ipairs(self._elementList) do
		local isSplit, _last, _next = self:_checkReLine(element)
		if false == isSplit then
			table.insert(lineList, element)
			self._nowWith = self._nowWith + self:_getNodeContentSize(element).width
		else
			table.insert(lineList, _last)
			table.insert(self._showElementList, lineList)
			lineList = {}
			if Enum.RichType.Label == _next:getRichType() then
				self._nowWith = 0
				_last = self:_splitNextElement(_next)
				table.insert(lineList, _last)
				self._nowWith = self:_getNodeContentSize(_last).width
			else
				table.insert(lineList, _next)
				self._nowWith = self:_getNodeContentSize(_next).width
			end
		end
	end
	table.insert(self._showElementList, lineList)
end

function M:_splitNextElement(element)
	local lineList = {}
	while (1 == 1)
	do
		local isSplit, _last, _next = self:_checkReLine(element)
		if isSplit == false then
			return element
		else
			table.insert(lineList, _last)
			table.insert(self._showElementList, lineList)
			lineList = {}
			self._nowWith = 0
			element = _next
		end
	end
end

function M:_updateNodePosition(node, width, nowHeight)
	local position = cc.p(width, nowHeight)
	local anchorPoint = cc.p(0, 0)
	if self._layoutType == M.LayoutType.FromTopToBottom then
		position = cc.p(width, -nowHeight)
		anchorPoint = cc.p(0, 1)
	end
	node:setPosition(position)
	node:setAnchorPoint(anchorPoint)
end

function M:_updateNodeParentPosition(nodeParent, width)
	if M.Alignment.Center == self._alignment then
		nodeParent:setPosition(cc.p((self._viewWidth - width) / 2, 0))
	elseif M.Alignment.Left == self._alignment then
		nodeParent:setPosition(cc.p(0, 0))
	elseif M.Alignment.Right == self._alignment then
		nodeParent:setPosition(cc.p(self._viewWidth - width, 0))
	end
end

function M:_checkReLine(element)
	local contentSize = self:_getNodeContentSize(element)
	if self._nowWith + contentSize.width > (self._viewWidth + m_skew) then
		local richType = element:getRichType()
		if richType == Enum.RichType.Label then
			return true, self:_splitLabel(element)
		else
			return true, nil, element
		end
	end
	return false
end

function M:_getRichClicked(element)
	local func = nil
	if element.onClicked then
		func = element.onClicked
	elseif element:getParent() and element:getParent().onClicked then
		func = element:getParent().onClicked
	end
	return func
end

function M:_splitLabel(element)
	local nowWidth = self._nowWith
	local richText = element:getText()
	local fontSize = element:getFontSize()
	local fontName = element:getFontName()
	local color = element:getColor()
	local strokeColor = element:getStrokeColor()
	local strokeSize = element:getStrokeSize()
	local textTable = self:_getCharToTable(richText)
	local showText = ""
	local fromIndex = 0
	for index,text in ipairs(textTable) do
		showText = string.format("%s%s", showText, text)
		if text == "\n" then
			fromIndex = index + 1
			break
		end
		local label = self:_createLabel(showText, fontSize, fontName, color, strokeColor, strokeSize)
		if label:getContentSize().width + nowWidth > (self._viewWidth + m_skew) then
			fromIndex = index
			break
		end
	end
	local nextText = self:_mergeTableToChar(textTable, fromIndex)
	local showTextTable = self:_getCharToTable(showText)
	table.remove(showTextTable, #showTextTable)
	local _last = self:_getNewParentRich(element)
	_last:updateText(self:_mergeTableToChar(showTextTable, 1))
	local _next = self:_getNewParentRich(element)
	_next:updateText(nextText)

	return _last, _next
end

function M:_getNodeContentSize(element)
	if nil == element then
		return cc.size(0, 0)
	end
	local node = self:_getNodeFromBase(element)
	assert(node)
	return node:getContentSize()
end

function M:_getNodeFromBase(element)
	local node = nil
	if Enum.RichType.Image == element:getRichType() then
		node = cc.Sprite:create(element:getSpriteFile())
	elseif Enum.RichType.Label == element:getRichType() then
		node = self:_crteateLabelFromBase(element)
	elseif Enum.RichType.Button == element:getRichType() then
		node = self:_getButton(element)
	elseif Enum.RichType.TextButton == element:getRichType() then
		node = self:_getTextButton(element)
	end
	return node
end

function M:_getNewParentRich(element)
	if Enum.RichType.Label == element:getRichType() then
		return require("ui.common.richlabel.ElementText").new(element, element)
	elseif Enum.RichType.Button == element:getRichType() then
		return require("ui.common.richlabel.ElementButton").new(element, element)
	elseif Enum.RichType.TextButton == element:getRichType() then
		return require("ui.common.richlabel.RichTextButton").new(element, element)
	elseif Enum.RichType.Sprite == element:getRichType() then
		return require("ui.common.richlabel.ElementSprite").new(element, element)
	end
end

function M:_crteateLabelFromBase(element)
	return self:_createLabel(element:getText(), element:getFontSize(),
	 element:getFontName(),element:getColor(), element:getStrokeColor(), element:getStrokeSize())
end

function M:_createLabel(text, fontSize,fontName, color, strokeColor, strokeSize)
	if "" == text then
		text = " "
	end
	local label = require("ui.common.ClickLabel").new(text, fontSize)
	label:setFontName(fontName)
	label:setTextColor(color)
    label:enableOutline(strokeColor, strokeSize)
	return label
end

function M:_mergeTableToChar(strTable, fromIndex, endIndex)
	return Utils:mergeTableToChar(strTable, fromIndex, endIndex)
end

function M:_getCharToTable(str)
	return Utils:getCharToTable(str)
end

function M:_getButton(element)
	return Button.new(element:getNomal(), element:getHigh())
end

function M:_checkBottomLine(parent, node, element, nowHeight)
	if Enum.RichType.Label ~= element:getRichType() then
		return
	end
	if not element:getUnderLine() or nil == element:getText() or string.len(element:getText()) == 0 then
		return
	end
	local lineNode = cc.DrawNode:create()
	local color = element:getColor()
	local nodeContentSize = node:getContentSize()
	local nodeX, nodeY = node:getPosition()
	lineNode:drawLine(cc.p(0, 0), cc.p(nodeContentSize.width , 0), cc.c4f(color.r/255, color.g/255, color.b/255, color.a/255))
	if self._layoutType == M.LayoutType.FromBottomToTop then
		lineNode:setPosition(cc.p(nodeX, nowHeight))
	else
		lineNode:setPosition(cc.p(nodeX, - nodeContentSize.height - nowHeight))
	end
	parent:addChild(lineNode)
end

function M:_getTextButton(element)
	local button = ButtonText.new(element:getNomal(), element:getHigh())
	button:setLabel(element:getText(), element:getFontSize())
	button:setDefalutConfig(element:getFontName(), element:getColor(), element:getStrokeColor(), element:getStrokeSize())
	return button
end

return M