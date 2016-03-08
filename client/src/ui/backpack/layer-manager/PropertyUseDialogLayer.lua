local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.backpack.layer-manager.PropertyUseDialogLayer", function()
    return cc.LayerColor:create(cc.c4b(0, 0, 0, 160))
end)

function M:ctor(backpackId)
    self:_createBg()
    local name = BackpackConfigRead:getName(backpackId)
    local desc = BackpackConfigRead:getDesc(backpackId)
    local backpackData = BackpackDataManager:getBackpackDataByType(backpackId)
    local number = 0
    if backpackData then
        number = backpackData:getItemNumber()
    end
    local nameLabel = CommonUI:createLabel(name, 24)
    nameLabel:setAnchorPoint(cc.p(0.5, 0))
    local descLabel = CommonUI:createLabel(desc, 24)
    descLabel:setWidth(Screen.width * 0.8)
    descLabel:setAlignment(0)
    local numberLabel = CommonUI:createLabel(string.format(__Localized("背包剩余:%d"), number), 24)
    numberLabel:setAnchorPoint(cc.p(0, 1))

    local descLabelSize = descLabel:getContentSize()
    local nameLabelSize = nameLabel:getContentSize()

    nameLabel:setPosition(cc.p(Screen.cx, Screen.cy + descLabelSize.height / 2 + nameLabelSize.height))
    descLabel:setPosition(cc.p(Screen.cx, Screen.cy))
    numberLabel:setPosition(cc.p(Screen.width * 0.1, Screen.cy - descLabelSize.height / 2 - nameLabelSize.height))

    self:addChild(nameLabel)
    self:addChild(descLabel)
    self:addChild(numberLabel)

    local buttonPosHeight = Screen.cy - descLabelSize.height - nameLabelSize.height * 2
    self:_createConfirmButton(number, buttonPosHeight)
    self:_createCancelButton(buttonPosHeight)
    Director:getRunningScene():addChild(self)
    self:setLocalZOrder(Enum.ZOrder.Dialog)
    Event:registerNodeEvent(self)
    self:_init()
end

function M:_init()
    Touch:registerTouchOneByOne(self, true)
    Touch:addKeyboardTouch(self)
end
function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        self:removeFromParent()
    end
end

function M:_createConfirmButton(number, height)
    local confirmButton = CommonUI:createTextButton(self, __Localized("使 用"), "ui/login/login-up.png")
    local buttonSize = confirmButton:getContentSize()
    if 0 == number then
        confirmButton:setEnabled(false)
        confirmButton:setLabel("道具不足")
    end
    confirmButton.onClicked = function()
        self.onClicked(true)
        self:removeFromParent()
    end
    confirmButton:setPosition(cc.p(Screen.width * 0.75, height - buttonSize.height))
end

function M:_createCancelButton(height)
    local cancelButton = CommonUI:createTextButton(self, __Localized("取 消"), "ui/login/login-up.png")

    local buttonSize = cancelButton:getContentSize()

    cancelButton:setPosition(cc.p(Screen.width * 0.25, height - buttonSize.height))
    cancelButton.onClicked = function()
        self.onClicked(false)
        self:removeFromParent()
    end
end

function M:_createBg()
    -- 背景图
    local bgSprite = cc.Sprite:create("ui/common/alert-view-bg.png")
    bgSprite:setPosition(Screen.center)
    self:addChild(bgSprite)
end

function M:onTouchBegan(touch, event)
    return true
end

return M
