local TimeTools = require("ui.common.TimeTools")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local GameMailData = require("ui.mail.data-manager.GameMailData")
local M = class("ui.mail.layer-manager.GameMailDetailsLayer", function()
    return cc.Layer:create()
end)

function M:ctor(mailData)
    self:_createBackground()
    self:_createTime(mailData)
    self:_createTitle(mailData)
    self:_createContent(mailData)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "战斗报告")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTime(mailData)
    local time = GameMailData:getTime(mailData)
    local timeStr = TimeTools:getFormatTimeString(time)
    local timeLabel = CommonUI:createLabel(timeStr, 30)
    self:addChild(timeLabel)
    Layout:layout(timeLabel, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
end

function M:_createTitle(mailData)
    local content = GameMailData:getMessage(mailData)
    local titleLabel = CommonUI:createLabel(content, 30)
    self:addChild(titleLabel)
    Layout:layout(titleLabel, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 40))
end

function M:_createContent(mailData)
    local contentBg = cc.Sprite:create("ui/mail/mail-bg.png")
    self:addChild(contentBg)
    Layout:layout(contentBg, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 90))

    local success = GameMailData:getSuccess(mailData)
    local resultString = success == Enum.GameMailResultType.Success and "胜" or "败"
    local contentLabel = CommonUI:createLabel(resultString, 200)
    contentBg:addChild(contentLabel)
    Layout:layout(contentLabel, contentBg:getContentSize(), Layout.center)
end

return M