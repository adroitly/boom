
local PersonalMailData = require("ui.mail.data-manager.PersonalMailData")
local M = class("ui.mail.layer-manager.PersonalMailFrame", function()
    return cc.Sprite:create()
end)
local kPlayerBaseInfo2 = "player_base_info2"

function M:ctor(personalMailData)
    self._personalMailData = personalMailData

    self._dialogFrame, self._messageLabel = self:_createDialogFrame()
    self._headIcon = self:_createHeadIcon()

    self:_adjustPosition()
end

function M:_createHeadIcon()
    local frame
    if not self:_isOwner() then
        local iconName = PersonalMailData:getIcon(self._personalMailData) .. ".png"
        frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
    else
        frame = PlayerData:getPlayerIconFrame()
    end
    local icon = Button.new()
    icon:changeNormalSpriteWithFrame(frame)
    self:addChild(icon)
    icon.onClicked = function()
        CommonUI:showLoadingLayer(true)
        local fromPlayerId = PersonalMailData:getFromPlayerId(self._personalMailData)
        SocketManager:send(kPlayerBaseInfo2, {target_id = fromPlayerId})
    end
    return icon
end

function M:_createDialogFrame()
    local width = 400
    local height = 100
    local paddingX = 20
    local paddingY = 20
    local tempSprite = cc.Sprite:create("ui/mail/mail-chat.png")
    local frameBackground = ccui.Scale9Sprite:create("ui/mail/mail-chat.png", cc.rect(0, 0, tempSprite:getContentSize().width, tempSprite:getContentSize().height), cc.rect(30, 50, 50, 5))
    local message = PersonalMailData:getMessage(self._personalMailData)
    local messageLabel = CommonUI:createLabel(message, 24)
    messageLabel:setHorizontalAlignment(0)
    
    local labelWidth = messageLabel:getContentSize().width
    if labelWidth > width then
        labelWidth = width
        messageLabel:setDimensions(width, 0)
    end
    local frameWidth = labelWidth + paddingX * 2
    local frameHeight = messageLabel:getContentSize().height + paddingY * 2
    frameBackground:setContentSize(cc.size(frameWidth, frameHeight))
    -- Layout:layout(messageLabel, cc.size(frameWidth, frameHeight), Layout.left_top, cc.p(paddingX + 5, paddingY))

    self:addChild(frameBackground)
    self:addChild(messageLabel)
    return frameBackground, messageLabel
end

function M:_isOwner()
    local fromPlayerId = PersonalMailData:getFromPlayerId(self._personalMailData)
    local isOwner = PlayerData:isOwner(fromPlayerId)
    return isOwner
end

function M:_adjustPosition()
    local headSize = self._headIcon:getContentSize()
    local frameSize = self._dialogFrame:getContentSize()
    local height = headSize.height > frameSize.height and headSize.height or frameSize.height
    local width = headSize.width + frameSize.width
    local size = cc.size(width, height)
    self:setContentSize(size)

    local isOwner = self:_isOwner()
    if isOwner then
        -- self._headIcon:setAnchorPoint(cc.p(1, 0.5))
        Layout:layout(self._headIcon, size, Layout.right_top)
        self._dialogFrame:setFlippedX(true)
        Layout:layout(self._dialogFrame, size, Layout.right_center, cc.p(headSize.width, 0))
        Layout:layout(self._messageLabel, size, Layout.right_center, cc.p(headSize.width + 25, 0))
        
    else
        self._headIcon:setAnchorPoint(cc.p(0, 0.5))
        Layout:layout(self._headIcon, size, Layout.left_center)
        self._dialogFrame:setAnchorPoint(cc.p(0, 0.5))
        Layout:layout(self._dialogFrame, size, Layout.left_center, cc.p(headSize.width, 0))
        Layout:layout(self._messageLabel, size, Layout.left_center, cc.p(headSize.width + 25, 0))
    end
end

return M