local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local BackpackDataManager = require("player-data.BackpackDataManager")
local M = class("ui.backpack-layer-manager.PropertyUseShowCell", function()
    return GridViewCell.new()
end)

local m_socketCmdKey = "item_use"

function M:ctor()
    self:_createButtonNodes()
    Event:registerNodeEvent(self)
end

function M:reloadData(backpackId)
    self._backpackId = backpackId
    self._backpackButton:reloadByBackpackId(backpackId)
end

function M:onExit()
    TimerInterval:removeTimer(self)
    SocketManager:removeObserver(self)
end

function M:onEnterTransitionFinish()
    self:onUpdate()
    TimerInterval:addTimer(self, 1)
    SocketManager:addObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if m_socketCmdKey == cmd then
        assert(msgTable.code)
        self:_onServerUpdate(msgTable.code)
    end
end

function M:_onServerUpdate(code)
    CommonUI:showLoadingLayer(false)
    if not self._sendCell then
        return
    end
    if 0 == code then
        CommonUI:lightTips(string.format(__Localized("使用%s成功"), BackpackConfigRead:getName(self._backpackId)))
    else
        CommonUI:lightTips(string.format(__Localized("使用%s失败"), BackpackConfigRead:getName(self._backpackId)))
    end
    self._sendCell = false
end

function M:_createButtonNodes()
    self._backpackButton = require("ui.backpack.layer-manager.BackpackButton"):newIconButton()
    self._backpackButton:setSwallowTouches(false)
    self:addChild(self._backpackButton)
    self._timeSprite = CommonUI:createTextSprite(self._backpackButton, "ui/backpack/timeliness-time-bg.png", "", 24)
    self._timeSprite:setLocalZOrder(1)
    self._timeSprite:setVisible(false)
    Layout:layout(self._timeSprite, self._backpackButton:getContentSize(), Layout.center_bottom)
    self._backpackButton.onClicked = function()
        self:_onButtonClick()
    end
end

function M:_onButtonClick()
    require("ui.backpack.layer-manager.PropertyUseDialogLayer").new(self._backpackId)
    .onClicked = function(isConfirm)
        if isConfirm then
            self:_useItem()
        end
    end
end


function M:_useItem()
    self._sendCell = true
    local serverData = {item_type = self._backpackId}
    SocketManager:send(m_socketCmdKey, serverData)
    CommonUI:showLoadingLayer(true)
end

function M:onUpdate()
    self:_updateTimeLabel()
end

function M:_updateTimeLabel()

    local callbacks = {
        -- [Enum.MainPageBackpackType.NatureBuff] = function()
        --     return self:_updateNatureBuff()
        -- end,
        -- [Enum.MainPageBackpackType.Stealth] = function()
        --     return self:_updateStealth()
        -- end,
        [Enum.MainPageBackpackType.Getaway] = function()
            return self:_updateHeroGetaway()    -- 金蝉脱壳
        end,

    }
    Function:safeCall(callbacks, self._backpackId)
end

function M:_updateHeroGetaway()
    local time = PlayerData:getUserInfoData():getHeroGetawayTime()
    if time - PlayerData:getServerTime() <= 0 then
        self._timeSprite:setVisible(false)
    else
        self._timeSprite:setVisible(true)
        local timeText = Function:timeToDateString(time - PlayerData:getServerTime())
        self._timeSprite:setText(timeText)
    end
end

function M:_updateStealth()
    --body
end

function M:_updateNatureBuff()

end

return M
