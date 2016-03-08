local CountryWarData = require("ui.country-war.data-manager.CountryWarData")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.country-war.layer-manager.CountryWarInfoLayer", function()
    return cc.Layer:create()
end)

local kCountryWarFightInfoGet = "country_war_fight_info_get"
local kPerUpdateTime = 10
local kRatio = 100
function M:createWarInfoButton(parent)
    local ToggleTextButton = require("share.toggle-button.ToggleTextButton")
    local button = ToggleTextButton.new("国战信息", "ui/login/login-up.png", "ui/login/login-down.png")
    parent:addChild(button)
    local MapTopLayer = require("ui.map.MapTopLayer")
    local position = cc.p(Screen.width * 0.5, Screen.height - MapTopLayer.MapTopLayerSize.height - button:getContentSize().height * 0.5)
    button:setPosition(position)
    button.onSelected = function(isSelected)
        if isSelected then
            local layer = M.new()
            layer:setBackgroundPosition(cc.p(position.x, position.y - button:getContentSize().height * 0.5))
            parent:addChild(layer)
        end
        Listener:postEvent(Listener.EventName.onListenCountryWarInfoShow, isSelected)
    end
    return button
end

function M:ctor(position)
    self._infoLabelList = {}
    self:_createBackground()
    self:_createSelfScoreLabel()
    self:_createVsLabel()
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    TimerInterval:addTimer(self, kPerUpdateTime)
    Listener:addListener(self)
    SocketManager:addObserver(self)
    self:_getCountryWarInfo()
end

function M:onExit()
    TimerInterval:removeTimer(self)
    Listener:removeListener(self)
    SocketManager:removeObserver(self)
end

function M:onListenCountryWarInfoShow(isShow)
    if not isShow then
        self:removeFromParent()
    end
end

function M:onUpdate(dt)
    self:_getCountryWarInfo()
end

function M:_getCountryWarInfo()
    SocketManager:send(kCountryWarFightInfoGet, {})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kCountryWarFightInfoGet then
        self:_updateCountryWarInfo(msgTable)
    end
end

function M:setBackgroundPosition(pos)
    self._backgroundPos = pos
end

function M:_updateCountryWarInfo(msgTable)
    for index, label in ipairs(self._infoLabelList) do
        label:removeFromParent()
    end
    self._infoLabelList = {}

    local height = 0
    local maxWidth = 0
    local selfScore = 0
    local space = 20
    for k, info in pairs(msgTable.info_list) do
        local relation = info.relation
        local countryId = info.country_id
        local score = info.fight_score
        if PlayerData:getCountryId() == countryId then
            selfScore = score
        end
        if relation ~= Enum.CountryWarRelation.None then
            local countryName = CountryConfigReader:getCountryName(countryId)
            local str = countryName .. "：" .. math.floor(score / kRatio)
            local label = CommonUI:createLabel(str)
            self._background:addChild(label)
            table.insert(self._infoLabelList, label)
            height = height + label:getContentSize().height
            maxWidth = math.max(label:getContentSize().width, maxWidth)
        end
    end
    height = height == 0 and self._selfScoreLabel:getContentSize().height or height
    local labelCount = table.getn(self._infoLabelList)
    local unitHeight = 0
    if labelCount > 0 then
        unitHeight = height / labelCount
    end
    -- 加上上下间隔
    local size = cc.size(500, height + space * 2) 
    self._background:setContentSize(size)
    self._background:setPosition(cc.p(self._backgroundPos.x, self._backgroundPos.y - size.height * 0.5))

    -- 敌对国家
    for index, label in ipairs(self._infoLabelList) do
        Layout:layout(label, size, Layout.left_bottom, cc.p(size.width - maxWidth - space, unitHeight * (index - 1) + space))
    end

    -- 自己国家
    local countryId = PlayerData:getCountryId()
    local countryName = CountryConfigReader:getCountryName(countryId)
    local str = countryName .. "：" .. math.floor(selfScore / kRatio)
    self._selfScoreLabel:setString(str)
    Layout:layout(self._selfScoreLabel, size, Layout.left_center, cc.p(space, 0))
    Layout:layout(self._vsLabel, size, Layout.center)
end

function M:_createBackground()
    local tempSprite = cc.Sprite:create("ui/login/login-down.png")
    local tempSize = tempSprite:getContentSize()
    self._background = ccui.Scale9Sprite:create("ui/login/login-down.png", cc.rect(0, 0, tempSize.width, tempSize.height), cc.rect(20, 20, tempSize.width - 40, tempSize.height - 40))
    self:addChild(self._background)
end

function M:_createSelfScoreLabel()
    self._selfScoreLabel = CommonUI:createLabel(" ")
    self._background:addChild(self._selfScoreLabel)
end

function M:_createVsLabel()
    self._vsLabel = CommonUI:createLabel("Vs")
    self._background:addChild(self._vsLabel)
end
return M