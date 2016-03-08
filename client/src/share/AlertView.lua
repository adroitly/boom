
local M = class("libs.widget.AlertView", function(text, ...)
    return cc.LayerColor:create(cc.c4b(0, 0, 0, 160))
end)

function M:ctor(text, ...)
	local scene = Director:getRunningScene()
 	assert(scene)
 	scene:addChild(self, 1000000)
    Touch:registerTouchOneByOne(self, true)

 	-- 背景图
 	local bgSprite = cc.Sprite:create("ui/common/alert-view-bg.png")
 	bgSprite:setPosition(Screen.center)
 	self:addChild(bgSprite)

 	-- 信息框
 	local showWidth = Screen.width * 0.8
 	local label = cc.Label:create()
 	label:setSystemFontSize(30)
    label:setSystemFontName("STHeitiSC-Medium")
    label:setHorizontalAlignment(1)
    label:setVerticalAlignment(1)
    label:setString(text)
    label:enableOutline(cc.c4b(0, 0, 0, 255), 3)
    label:setTextColor(cc.c4b(255, 255, 255, 255))
    label:setWidth(showWidth)
    label:setPosition(cc.p(Screen.cx, Screen.cy + 50))
    self:addChild(label)
    
    -- 按钮集合
    local btTable = #{...}==0 and {__Localized("确 定")} or {...}
    local setInfo = {}
    for _,value in ipairs(btTable) do
    	local info = { [1]="ui/login/login-up.png", [4]=value, [5]=30 }
    	table.insert(setInfo, info)
    end

    self._buttonSetLayer = ButtonSetLayer.new(setInfo)
    self._buttonSetLayer:setLayout(cc.size(showWidth, 100))
    self._buttonSetLayer:setPositionAtCenterAnchor(cc.p(Screen.cx, Screen.cy - 80))
    self:addChild(self._buttonSetLayer)
    self._buttonSetLayer.onClicked = function(button, index)
	if self.onClicked then 
           self.onClicked(index) 
        end
        self:removeFromParent()
    end
    Touch:addKeyboardTouch(self)
    Event:registerNodeEvent(self)
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        self:removeFromParent()
    end
end

function M:onTouchBegan(touch, event)
    return true
end

return M



