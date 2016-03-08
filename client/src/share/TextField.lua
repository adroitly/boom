local SuperClass = ccui.TextField 

local M = class("share.TextField", function()
	return SuperClass:create() 
end)

-- event 
-- onAttachWithIME(self)
-- onDetachWithIME(self)
-- onInsertText(self)
-- onDeleteBackward(self) 

function M:ctor(fontSize) 
	self:_createShowLabel()
	
	self._placeHolder = "" 

	self._cursorColor = cc.c4f(1, 1, 1, 1) -- c4f for draw node 
	self:setTextColor(cc.c4b(0, 0, 0, 255))
	self:setFontSize(fontSize or 20) 

	self:_setupListener() 

	self._isAttach = false 
end

function M:setPlaceHolder(text)
	self._placeHolder = text 
	if not self._isAttach then 
		self:onDetachWithIME() 
	end 
end

function M:setCursorColor(color)
	self._cursorColor = color 
	self:_setupCursor() 
end

function M:_updateCursorPosition()
	Layout:layout(self._cursor, self:getContentSize(), Layout.right_center, cc.p(-6, 0)) 
end

function M:_setupCursor()
	if self._cursor ~= nil then 
		self._cursor:removeFromParent() 
	end 

	local height = self:getContentSize().height - 8 
	local drawNode = cc.DrawNode:create() 
	drawNode:drawLine(cc.p(0, 0), cc.p(0, height), self._cursorColor)
	drawNode:setContentSize(cc.size(2, height)) 
	self:addChild(drawNode) 

	self._cursor = drawNode 
	self:_updateCursorPosition() 

	-- 闪烁
	local seq = Action:Sequence()
		.delayTime(0.6)
        .callFunc(function()
        	self._cursor:setVisible(self._isAttach)
    	end)
        .delayTime(1) 
        .callFunc(function()
        	self._cursor:setVisible(false)
    	end)

    local rep = cc.RepeatForever:create(seq.raw)
    self._cursor:runAction(rep)
end

function M:setFontSize(size)
	SuperClass.setFontSize(self, size) 
	self:_setupCursor() 
end

function M:setMaxLength(maxLength) -- BUG:不计算汉字，只按ASCII
	self._maxLength = maxLength 
end

-- opt 
function M:attachWithIME()
	SuperClass.attachWithIME(self) 
	self:onAttachWithIME()  
end

function M:detachWithIME()
	cc.Director:getInstance():getOpenGLView():setIMEKeyboardState(false) 
	
	if self._listener ~= nil and self._listener["onDetachWithIME"] ~= nil then 
		self._listener["onDetachWithIME"](self._listener) 
	end 

	self:onDetachWithIME() 
end

-- listener 
function M:setListener(listener)
	self._listener = listener 
end

function M:_createShowLabel()
	local scene = cc.Director:getInstance():getRunningScene()
	self._showLabel = scene:getChildByTag(Enum.ZOrder.Dialog)

	if nil == self._showLabel then
		self._showLabel = CommonUI:createLabel("")
		scene:addChild(self._showLabel, Enum.ZOrder.Dialog)
		self._showLabel:setTag(Enum.ZOrder.Dialog)
		self._showLabel:setPosition(cc.p(Screen.width / 2, Screen.height - 115))
	end

	self:registerScriptHandler(function(event)
		if "exit" == event then
			self:onDetachWithIME()
			self:detachWithIME()
		end
	end)

end

function M:onAttachWithIME()
	self._isAttach = true 
	SuperClass.setPlaceHolder(self, "")
	self._cursor:setVisible(self._isAttach)
	self:_updateCursorPosition() 
	self._showLabel:setString(self:getString())
	self._showLabel:setVisible(self._isAttach)
end

function M:onDetachWithIME()
	self._isAttach = false 
	SuperClass.setPlaceHolder(self, self._placeHolder)
	self._cursor:setVisible(self._isAttach)
	self._showLabel:setVisible(self._isAttach)
end

function M:onInsertText()
	if self._maxLength ~= nil and self._maxLength > 0 then 
		if self:getStringLength() > self._maxLength then 
			local str = self:getString() 
			str = string.sub(str, 0, self._maxLength) 
			self:setString(str) 
		end 
	end 
	self._showLabel:setString(self:getString())
	self:_updateCursorPosition() 
end

function M:onDeleteBackward() 
	self._showLabel:setString(self:getString())
	self:_updateCursorPosition() 
end


local s_event_types = {
	[ccui.TextFiledEventType.attach_with_ime] = "onAttachWithIME",
	[ccui.TextFiledEventType.detach_with_ime] = "onDetachWithIME",
	[ccui.TextFiledEventType.insert_text] = "onInsertText",
	[ccui.TextFiledEventType.delete_backward] = "onDeleteBackward",
}

function M:_setupListener()
	local function eventHandler(textField, eventType)
		local funcName = s_event_types[eventType] 
		self[funcName](self) 

		if self._listener ~= nil and self._listener[funcName] ~= nil then 
			self._listener[funcName](self._listener) 
		end 
	end

	SuperClass.addEventListener(self, eventHandler)
	self:onDetachWithIME() 
end

return M 

