local M = class("ui.notice.notice-manager.AlertNoticeLayer", function()
    return cc.Layer:create()
end)


local m_titleKey = "title"
local m_contentKey = "content"

local serverUrl = "http://192.168.1.52:8080/three-backend/app/notice_get.json?"

function M:createLoginEndAlertLayer()
    local serverId = require("ui.login.ServerListUtils"):getLastLoginServerId()
    local url = string.format("%sserver_id=%s&type=2", serverUrl, serverId)
    return M.new(url)
end

function M:createStartGameAlertLayer()
    local platformId = Platform:getPlatformId()
    local channelId = Platform:getChannelId()
    local url = string.format("%stype=1&channel_id=%d&platform_id=%d", serverUrl, channelId, platformId)
    return M.new(url)
end

function M:ctor(url)
    Event:registerNodeEvent(self)
    self._url = url
end

function M:onEnterTransitionFinish()
    self:setLocalZOrder(Enum.ZOrder.Dialog)
    self:_loadDataFromServer(self._url)
end

function M:onTouchBegan(touch, event)
    return true
end

function M:_initLayer()
    Touch:registerTouchOneByOne(self, true)
    self:_createBackground()
    self:_createConfirmButton()
    self:_createTitleLabel()
end

function M:_createTitleLabel()
    local label = CommonUI:createLabel(__Localized("公告"), 40)
    self:addChild(label)
    label:setPosition(cc.p(Screen.width / 2, Screen.height * 0.8 + 50))
end

function M:_createConfirmButton()
    local button = CommonUI:createTextButton(self,  __Localized("确定"), "ui/login/login-button.png")
    button:setPosition(cc.p(Screen.width / 2, Screen.height * 0.2 - 50))
    button.onClicked = function()
        self:removeFromParent()
    end
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/common/alert-view-bg.png")
    background:setScaleY(3.5)
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center)
end

function M:_alertNoticeCallback(info, result)
    if result ~= "finish" then
        self:_loadFailed()
        return
    end
    CommonUI:showLoadingLayer(false)
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

function M:_loadFailed()
    CommonUI:showLoadingLayer(false)
    self:removeFromParent()
end

function M:_loadSuccess(info)
    local list = json.decode(info.data)
    if 0 == table.getn(list) then
        self:removeFromParent()
        return
    end
    self:_initLayer()
    local titleStr = ""
    local contentStr = ""
    for _,dataTable in pairs(list) do
        for key,data in pairs(dataTable) do
            if m_titleKey == key then
                titleStr = data
            elseif m_contentKey == key then
                contentStr = data
            end
        end
    end
    self:_createInfoScallView(titleStr, contentStr)
end

function M:_createInfoScallView(titleStr, contentStr)
    local scrollView = cc.ScrollView:create(cc.size(Screen.width * 0.8, Screen.height * 0.6))
    scrollView:setPosition(cc.p(Screen.width * 0.1, Screen.height * 0.2))
    scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
    self:addChild(scrollView)

    local titleLabel = CommonUI:createLabel(titleStr, 46)
    local contentLabel = CommonUI:createLabel(contentStr, 24)
    scrollView:getContainer():addChild(titleLabel)
    scrollView:getContainer():addChild(contentLabel)

    titleLabel:setTextColor(Enum.Color.Green)
    titleLabel:setAnchorPoint(cc.p(0.5, 0))

    contentLabel:setTextColor(Enum.Color.Red)
    contentLabel:setWidth(Screen.width * 0.8)
    contentLabel:setAlignment(0)
    contentLabel:setAnchorPoint(cc.p(0.5, 1))

    local contentLabelSize = contentLabel:getContentSize()
    local titleLabelSize = titleLabel:getContentSize()


    local height = Screen.height * 0.6
    if height < contentLabelSize.height + titleLabelSize.height * 2 then
        height = contentLabelSize.height + titleLabelSize.height * 2
    end

    titleLabel:setPosition(cc.p(Screen.width * 0.8 / 2, height - titleLabelSize.height))
    contentLabel:setPosition(cc.p(Screen.width * 0.8 / 2, height - titleLabelSize.height * 2))
    scrollView:getContainer():setContentSize(cc.size(Screen.width * 0.8, height))

    local minOffset = scrollView:minContainerOffset()
    scrollView:setContentOffset(minOffset)
end

return M