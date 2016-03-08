local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.mail.layer-manager.SettingMailLayer", function()
    return cc.Layer:create()
end)

function M:createWithSettingButton(parent)
    local settingBtn = CommonUI:createTextButton(parent, "设置", "ui/login/login-bt.png")
    local posY = (BackgroundLayer.TitleHeight - settingBtn:getContentSize().height) * 0.5
    Layout:layout(settingBtn, Screen.size, Layout.right_top, cc.p(0, posY))
    local settingLayer = M.new(parent)
    parent:addChild(settingLayer)
    settingLayer:setVisible(false)

    settingBtn.onClicked = function()
        local isShow = settingLayer:isVisible()
        settingLayer:setVisible(not isShow)
        if isShow then
            if parent.onCloseCallback then
                parent:onCloseCallback()
            end
        else
            if parent.onOpenCallback then
                parent:onOpenCallback()
            end
        end
    end
    
    return settingLayer
end

function M:isShow()
    return self:isVisible()
end

function M:ctor(delegate)
    self._delegate = delegate
    self._background = self:_createBackground()
    self:_createButton()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_bottom)
    return background
end

function M:_createButton()
    local titles = {"写邮件", "全选", "删除邮件"}
    local callbacks = {
        [1] = function()
            self:_toSendMailLayer()
        end,
        [2] = function()
            if self._delegate.onTotalSelectCallback then
                self._delegate:onTotalSelectCallback()
            end
        end,
        [3] = function()
            if self._delegate.onDeleteCallback then
                self._delegate:onDeleteCallback()
            end
        end,
    }
    local bgSize = self._background:getContentSize()
    local height = bgSize.height
    local pos = {
        {anchorPoint = Layout.left_bottom, offsetX = 20}, 
        {anchorPoint = Layout.center_bottom, offsetX = 0}, 
        {anchorPoint = Layout.right_bottom, offsetX = 20}
    }
    for i = 1, table.getn(titles) do
        local button = CommonUI:createTextButton(self, titles[i], "ui/login/login-bt.png")
        local btnSize = button:getContentSize()
        Layout:layout(button, bgSize, pos[i].anchorPoint, cc.p(pos[i].offsetX, 0.5 * (bgSize.height - btnSize.height)))
        button.onClicked = callbacks[i]
    end
end

function M:_toSendMailLayer()
    local sendMailLayer = require("ui.mail.layer-manager.SendMailLayer").new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(sendMailLayer)
end

return M