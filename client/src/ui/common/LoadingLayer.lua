
local M = class("ui.common.LoadingLayer", function()
	return cc.Node:create()
end)

local m_loadingLayer = nil
function M:show()
	if m_loadingLayer then 
		return
	end

	self:_load()
end

function M:isHide()
	return m_loadingLayer == nil
end

function M:hide()
	if m_loadingLayer then 
		self:_unload()
	end
end


function M:_load()
	m_loadingLayer = M.new()
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(m_loadingLayer)
end

function M:_unload()
	if m_loadingLayer then
		m_loadingLayer:removeFromParent()
		m_loadingLayer = nil 
	end
end

function M:onTouchBegan(touch, event)
    return true
end

function M:ctor()
	local label = CommonUI:createLabel("Loading ...", 50)
	self:addChild(label)
	Layout:layout(label, Screen.size, Layout.center)
	self._testLabel = label
	self._elapseTime = 0

	Touch:registerTouchOneByOne(self, true)

	Event:registerNodeEvent(self)
	TimerInterval:addTimer(self, 1)
end

function M:onUpdate()
	self._elapseTime = self._elapseTime + 1
	local text = string.format("Loading ... %d", self._elapseTime)
	self._testLabel:setString(text)
end

function M:onExit()
	TimerInterval:removeTimer(self)
	m_loadingLayer = nil
end

return M

