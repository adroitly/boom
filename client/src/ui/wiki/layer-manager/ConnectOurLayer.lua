local M = class("ui.wiki.layer-manager.ConnectOurLayer", function()
    return cc.LayerColor:create(cc.c4b(0, 0, 0 , 160))
end)

local url = "http://192.168.5.86:8080/three-backend/app/feedback_message.json?play_id=%d&server_id=%d&feedback_message=%s"

function M:ctor()
    self:_createBackground()
    self:_createTitleLabel()
    self:_createInput()
    self:_createSendButton()
    self:_createCancelButton()
    Event:registerNodeEvent(self)
end
function M:onEnterTransitionFinish()
    Touch:registerTouchOneByOne(self, true)
    Touch:addKeyboardTouch(self)
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        self:removeFromParent()
    end
end

function M:_createInput()
    self._input = require("ui.common.InputUI").new(24)
    self:addChild(self._input)
    self._input:setTouchSize(cc.size(Screen.width * 0.8, Screen.width * 0.6))
    self._input:setAnchorPoint(cc.p(0.5, 1))
    self._input:setMaxLength(140)
    self._input:setPosition(cc.p(Screen.cx, Screen.height * 0.7))
    self._input:setTextWidth(Screen.width * 0.8)
end


function M:_createTitleLabel()
    local label = CommonUI:createLabel(__Localized("联系客服"))
    label:setAnchorPoint(cc.p(0.5, 1))
    self:addChild(label)
    label:setPosition(cc.p(Screen.cx, Screen.height * 0.75))
end

function M:_createSendButton()
    local button = CommonUI:createTextButton(self, __Localized("发 送"), "ui/login/login-up.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(Screen.cx + buttonSize.width, Screen.height * 0.3))

    button.onClicked = function()
        local sendMsg = self._input:getString()
        if 0 == string.len(sendMsg) then
            CommonUI:lightTips(__Localized("发送内容不能为空"))
            return
        end
        self:_sendMsgToServer(sendMsg)
    end

end

function M:_createCancelButton()
    local button = CommonUI:createTextButton(self, __Localized("取 消"), "ui/login/login-up.png")
    local buttonSize = button:getContentSize()
    button:setPosition(cc.p(Screen.cx - buttonSize.width, Screen.height * 0.3))
    button.onClicked = function()
        self:removeFromParent()
    end
end

function M:_alertNoticeCallback(info, result)
    CommonUI:showLoadingLayer(false)
    if result ~= "finish" then
        self:_loadFailed()
        return
    end
    self:_loadSuccess(info)
end

function M:_loadDataFromServer(htmlUrl)
    CommonUI:showLoadingLayer(true)
    network.http.get({
        url = htmlUrl,
    }, function(info, result)
        if self._alertNoticeCallback then
            self:_alertNoticeCallback(info, result)
        end
    end)
end

function M:_loadSuccess(info)
    CommonUI:lightTips("发送成功")
    self:removeFromParent()
end

function M:_loadFailed()
    CommonUI:lightTips(__Localized("发送失败请重试"))
end

function M:_sendMsgToServer(msg)
    local serverId = require("ui.login.ServerListUtils"):getLastLoginServerId()
    local sendUrl = string.format(url, PlayerData:getPlayerId(), serverId, msg)
    self:_loadDataFromServer(sendUrl)
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/common/alert-view-bg.png")
    background:setScaleY(2)
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center)
end

return M
