local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.mail.layer-manager.AddNameLayer", function()
    return cc.Layer:create()
end)


function M:createWithParent(parent)
    local button = CommonUI:createTextButton(parent, "", "ui/team/button-add.png", "ui/team/button-add.png")
    Layout:layout(button, Screen.size, Layout.right_top, cc.p(30, BackgroundLayer.TitleHeight + 32))
    local layer = M.new()
    parent:addChild(layer)
    layer:setVisible(false)
    button.onClicked = function()
        layer:setVisible(true)
    end
end

function M:ctor()
    self:_createUnionButton()
    self:_createFriendButton()
    self:_createSearchButton()

    Touch:registerTouchOneByOne(self, false)
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch,event)
    if not self:_hitTest(touch, self._unionButton) and
        not self:_hitTest(touch, self._friendButton) and
        not self:_hitTest(touch, self._searchButton) then
        self:setVisible(false)
    end
end

function M:onTouchCancelled(touch,event)
end

function M:_hitTest(touch, node)
    return Touch:isTouchHitted(node, touch)
end

function M:_createBackground()
end

function M:_createUnionButton()
    local button = CommonUI:createTextButton(self, "势力", "ui/login/login-bt.png")
    Layout:layout(button, Screen.size, Layout.right_top, cc.p(10, BackgroundLayer.TitleHeight + 32 + button:getContentSize().height * 0.5))
    self._unionButton = button
end

function M:_createFriendButton()
    local button = CommonUI:createTextButton(self, "好友", "ui/login/login-bt.png")
    Layout:layout(button, Screen.size, Layout.right_top, cc.p(10, BackgroundLayer.TitleHeight + 32 + button:getContentSize().height * 1.5))
    self._friendButton = button
end

function M:_createSearchButton()
    local button = CommonUI:createTextButton(self, "搜索", "ui/login/login-bt.png")
    Layout:layout(button, Screen.size, Layout.right_top, cc.p(10, BackgroundLayer.TitleHeight + 32 + button:getContentSize().height * 2.5))
    self._searchButton = button
end

return M