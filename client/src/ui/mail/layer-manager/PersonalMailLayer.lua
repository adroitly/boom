local BackgroundLayer = require("ui.common.BackgroundLayer")
local PersonalMailData = require("ui.mail.data-manager.PersonalMailData")
local PersonalMailDataManager = require("player-data.PersonalMailDataManager")
local PersonalMailFrame = require("ui.mail.layer-manager.PersonalMailFrame")
local M = class("ui.mail.layer-manager.PersonalMailLayer", function()
    return cc.Layer:create()
end)

local kMessagePersonalSend = "message_personal_send"

function M:ctor(playerId, nickname)
    self._playerId = playerId
    self._nickname = nickname
    self:_createBackground()
    self._scrollView = self:_createScrollView()
    self:_reloadMail()
    self:_createInputBox()

    Listener:addListener(self)
    self:registerScriptHandler(function(event)
        if event == "exit"then
            Listener:removeListener(self)
        end
    end)
end

function M:onListenMailPersonalChanged()
    self:_reloadMail()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, self._nickname)
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createScrollView()
    local scrollView = cc.ScrollView:create()
    local viewSize = cc.size(Screen.size.width, Screen.size.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    scrollView:setViewSize(viewSize)
    scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
    self:addChild(scrollView)
    return scrollView
end

function M:_reloadMail()
    self._scrollView:getContainer():removeAllChildren()
    local list = PlayerData:getPersonalMailList()
    local playerMailList = PersonalMailData:getPersonalMailDataList(list[self._playerId])
    if not playerMailList then
        return
    end
    local viewSize = self._scrollView:getViewSize()
    local viewHeight = 0
    for i = 1, table.getn(playerMailList) do
        local mailData = playerMailList[i]
        local frame = PersonalMailFrame.new(mailData)
        self._scrollView:getContainer():addChild(frame)
        local fromPlayerId = PersonalMailData:getFromPlayerId(mailData)
        local isOwner = PlayerData:isOwner(fromPlayerId)
        if isOwner then
            frame:setAnchorPoint(cc.p(1, 0))
            frame:setPosition(cc.p(viewSize.width, viewHeight))
        else
            frame:setAnchorPoint(cc.p(0, 0))
            frame:setPosition(cc.p(0, viewHeight))
        end
        local frameHeight = frame:getContentSize().height
        viewHeight = viewHeight + frameHeight
    end
    viewHeight = viewHeight > viewSize.height and viewHeight or viewSize.height
    local contentSize = cc.size(Screen.size.width, viewHeight)
    self._scrollView:setContentSize(contentSize)
    self._scrollView:setPosition(cc.p(0, BackgroundLayer.BottomHeight))
end

function M:_createInputBox()
    local editBox = ccui.EditBox:create(cc.size(Screen.size.width - 60, 27), "ui/mail/mail-input.png")
    self:addChild(editBox)

    local sendBtn = CommonUI:createTextButton(self, "发送", "ui/login/login-bt.png")
    sendBtn.onClicked = function()
        local messageStr = editBox:getText()
        editBox:setText("")
        local messageData = {to_player_name = self._nickname, message = messageStr}
        SocketManager:send(kMessagePersonalSend, messageData)
    end
    editBox:setContentSize(cc.size(Screen.size.width - sendBtn:getContentSize().width, 50))
    Layout:layout(sendBtn, Screen.size, Layout.right_bottom)
    Layout:layout(editBox, Screen.size, Layout.right_bottom, cc.p(sendBtn:getContentSize().width, 0))
end

return M