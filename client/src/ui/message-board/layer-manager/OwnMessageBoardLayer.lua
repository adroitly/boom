local BackgroundLayer = require("ui.common.BackgroundLayer")
local TextInput = require("ui.common.InputUI")
local M = class("ui.message-board.layer-manager.OwnMessageBoardLayer", function()
    return cc.Layer:create()
end)

local kMessageBoardAdd = "message_board_add"

function M:ctor()
    self:_createBackground()
    self:_createContentFrame()
    self:_createSendButton()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kMessageBoardAdd then
        if not CommonUI:errorAlertView(msgTable.code) then
            AlertView.new(__Localized("发布成功"))
            self:removeFromParent()
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("外交"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createContentFrame()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
    local bgSize = background:getContentSize()

    self._contentTextInput = TextInput.new(26)
    self._contentTextInput:setPlaceHolder("请输入发送的内容, 最多50字")
    self._contentTextInput:setMaxLength(100)
    self._contentTextInput:setTextWidth(bgSize.width - 40)
    self._contentTextInput:setAnchorPoint(cc.p(0, 1))
    self._contentTextInput:setTouchSize(cc.size(bgSize.width - 40, bgSize.height - 30))
    self._contentTextInput:setTextColor(cc.c4b(255, 255, 255, 255))
    background:addChild(self._contentTextInput)
    Layout:layout(self._contentTextInput, bgSize, Layout.left_top, cc.p(20, 30))
end

function M:_createSendButton()
    local button = CommonUI:createTextButton(self, "发布", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(button, Screen.size, Layout.center_bottom)
    button.onClicked = function()
        local str = self._contentTextInput:getString()
        if str == "" then
            CommonUI:lightTips(__Localized("内容不能为空"))
            return
        end
        SocketManager:send(kMessageBoardAdd, {content = str})
    end
end

return M