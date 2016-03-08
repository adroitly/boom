local M = class("ui.message-board.layer-manager.OperateMenuLayer", function()
    return cc.Layer:create()
end)

function M:ctor(sendNickname)
    self:_createMailButton(sendNickname)
    self:_createCancelButton()

    Touch:registerTouchOneByOne(self, true)
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchMoved(touch,event)
end

function M:onTouchEnded(touch,event)
    if not Touch:isTouchHitted(self._mailButton, touch) and 
        not Touch:isTouchHitted(self._cancelButton, touch) then
        self:removeFromParent()
    end
end

function M:onTouchCancelled(touch,event)
end

function M:_createMailButton(sendNickname)
    self._mailButton = CommonUI:createTextButton(self, "邮件", "ui/mail/mail-title-bg.png")
    Layout:layout(self._mailButton, Screen.size, Layout.center_bottom, cc.p(0, self._mailButton:getContentSize().height))
    self._mailButton.onClicked = function()
        local layer = require("ui.mail.layer-manager.SendMailLayer").new(Enum.SendMailType.Personal, sendNickname)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:_createCancelButton()
    self._cancelButton = CommonUI:createTextButton(self, "取消", "ui/mail/mail-title-bg.png")
    Layout:layout(self._cancelButton, Screen.size, Layout.center_bottom)
    self._cancelButton.onClicked = function()
        self:removeFromParent()
    end
end

return M