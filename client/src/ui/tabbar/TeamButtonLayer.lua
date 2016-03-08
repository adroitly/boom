
local M = class("ui.tabbar.TeamButtonLayer", function()
    return cc.Layer:create()
end)

function M:createLayer(parent)
    local layer = M.new()
    parent:addChild(layer)
end

function M:ctor()
    self._isShow = false
    self._isShowDone = true
    self:_createTeamButton()
    self:_createLayerButtons()

    Touch:registerTouchOneByOne(self, false)
end


function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch, event)
    if not self:_hitTest(touch, self._teamButton) then
        self:_showButtons(false)
    end
end

function M:onTouchCancelled(touch, event)
end

function M:_hitTest(touch, node)
    return Touch:isTouchHitted(node, touch)
end


function M:_createTeamButton()
    self._teamButton = Button.new("ui/main-page/main-button04.png")
    self:addChild(self._teamButton)
    Layout:layout(self._teamButton, Screen.size, Layout.center_bottom)
    self._teamButton.onClicked = function()
        if not self._isShowDone then
            return
        end
        self:_showButtons(not self._isShow)
    end
end

function M:_createLayerButtons()
    self._layerButtonsList = {}
    local startPosX, startPosY = self._teamButton:getPosition()
    local config = self:_getButtonsConfig()
    for k, btnConfig in ipairs(config) do
        local button = CommonUI:createTextButton(self, btnConfig.title,"ui/team/ui_but_0001a.png", "ui/team/ui_but_0001b.png")
        button:setPosition(cc.p(startPosX, startPosY))
        button:setVisible(false)
        table.insert(self._layerButtonsList, button)
        button.onClicked = function()
            self:_showButtons(false)
            local Layer = btnConfig.layer
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(Layer.new())
        end
    end
end

function M:_showButtons(isShow)
    if self._isShow == isShow then
        return
    end
    self._isShowDone = false
    local startPosX, startPosY = self._teamButton:getPosition()
    local config = self:_getButtonsConfig()
    for k, btn in ipairs(self._layerButtonsList) do
        local callback = function()
            btn:setEnabled(isShow)
            btn:setVisible(isShow)
            self._isShow = isShow
            self._isShowDone = true
        end
        btn:setEnabled(false)
        btn:setVisible(true)
        local targetPos = isShow and config[k].pos or cc.p(startPosX, startPosY)
        local moveTo = cc.MoveTo:create(0.2, targetPos)
        Action:Sequence().action(moveTo).callFunc(callback).run(btn)
    end
end

function M:_getButtonsConfig()
    local btnSize = self._teamButton:getContentSize()
    local startPosX, startPosY = self._teamButton:getPosition()
    local config = {
        {
            title = __Localized("编辑"), 
            pos = cc.p(startPosX - btnSize.width, startPosY + btnSize.height), 
            layer = require("ui.team.layer-manager.EditTeamLayer")
        },
        {
            title = __Localized("撤销"), 
            pos = cc.p(startPosX, startPosY + btnSize.height), 
            layer = require("ui.team.layer-manager.RevokeTeamLayer")
        },
        {
            title = __Localized("出征"), 
            pos = cc.p(startPosX + btnSize.width, startPosY + btnSize.height), 
            layer = require("ui.team.layer-manager.OutTeamLayer")
        },
    }
    return config
end

return M