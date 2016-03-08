local ResourceOperateCell = require("ui.guild.layer-manager.ResourceOperateCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildDonateRatioConfigRead = require("ui.guild.data-manager.GuildDonateRatioConfigRead")
local BackpackConfigRead = require("ui.backpack.data-manager.BackpackConfigRead")
local GuildLevelConfigRead = require("ui.guild.data-manager.GuildLevelConfigRead")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.ResourceDonateLayer", function()
    return cc.Layer:create()
end)

local kGuildDonate  = "guild_donate"
local kGuildInfo    = "guild_info"
function M:ctor()
    self._donateValueList = {}

    self:_createBackground()
    self:_createInfoLabels()
    self:_createResourceRatioLabels()
    self:_createProgress()
    self:_createTableView()
    self:_createMaskLayer()
    self:_createButtons()

    self:_updateInfoLabels()

    GuildLayerManager:addLayer(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)

    self:_getGuildInfo()
end

function M:_getGuildInfo()
    local guildId = PlayerData:getGuildId()
    SocketManager:send(kGuildInfo, {guild_id = guildId})
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("捐献"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createMaskLayer()
    local node = cc.Node:create()
    node:setAnchorPoint(cc.p(0.5, 0.5))
    node:setContentSize(cc.size(Screen.width, BackgroundLayer.BottomHeight))
    self:addChild(node)
    function node:onTouchBegan(touch, event)
        return Touch:isTouchHitted(node, touch)
    end
    Touch:registerTouchOneByOne(node, true)
    node:setPosition(cc.p(Screen.width * 0.5, BackgroundLayer.BottomHeight * 0.5))
end

function M:_updateInfoLabels()
    -- 置为零
    for k, v in pairs(self._titleTypeList) do
        self._donateValueList[v] = 0
    end

    local memberData = PlayerData:getGuildMemberData()
    local str = string.format("我的贡献:%d", memberData:getTotalDonate())
    str = __Localized(str)
    self._personalDonateLabel:setString(str)
    Layout:layout(self._personalDonateLabel, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))

    local guildData = PlayerData:getGuildData()
    str = string.format("势力贡献:%d", guildData:getDonate())
    str = __Localized(str)
    self._guildDonateLabel:setString(str)
    Layout:layout(self._guildDonateLabel, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
    self._guildDonateLabel:setVisible(false)

    local level = guildData:getLevel()
    str = string.format("势力等级:Lv.%d", level)
    str = __Localized(str)
    self._guildLevel:setString(str)
    Layout:layout(self._guildLevel, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight + self._personalDonateLabel:getContentSize().height))

    local nextLevel = level + 1
    if nextLevel >= GuildLevelConfigRead:getLevelMax() then
        nextLevel = level
    end
    str = string.format("势力等级:Lv.%d", nextLevel)
    str = __Localized(str)
    self._guildNextLevel:setString(str)
    Layout:layout(self._guildNextLevel, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight + self._personalDonateLabel:getContentSize().height))
    local currentExp = guildData:getExp()
    local preExp = GuildLevelConfigRead:getNeedExp(nextLevel - 1)
    local exp = GuildLevelConfigRead:getNeedExp(nextLevel)
    local offsetExp = currentExp - preExp
    local needExp = exp - preExp
    if nextLevel == level then
        offsetExp = needExp
    end
    local percentage = math.floor(offsetExp / needExp * 100)
    self._progressTimer:setPercentage(percentage)
    local str = string.format("%d/%d", offsetExp, needExp)
    self._progressLabel:setString(str)
end

function M:_createInfoLabels()
    self._personalDonateLabel = CommonUI:createLabel("我的贡献:99999", 40)
    self:addChild(self._personalDonateLabel)
    Layout:layout(self._personalDonateLabel, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))

    self._guildDonateLabel = CommonUI:createLabel("我的贡献:99999", 40)
    self:addChild(self._guildDonateLabel)
    Layout:layout(self._guildDonateLabel, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))

    self._guildLevel = CommonUI:createLabel("势力等级", 40)
    self:addChild(self._guildLevel)
    Layout:layout(self._guildLevel, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight + self._personalDonateLabel:getContentSize().height))

    self._guildNextLevel = CommonUI:createLabel("势力等级", 40)
    self:addChild(self._guildNextLevel)
    Layout:layout(self._guildNextLevel, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight + self._personalDonateLabel:getContentSize().height))
end

function M:_createResourceRatioLabels()
    local resourceTypeList = {
        {Enum.ResourceType.Food, cc.p(0, 1), cc.p(0, Screen.height - 250)},
        {Enum.ResourceType.Wood, cc.p(0.5, 1), cc.p(Screen.width * 0.5, Screen.height - 250)},
        {Enum.ResourceType.Stone, cc.p(1, 1), cc.p(Screen.width, Screen.height - 250)},
        {Enum.ResourceType.Coin, cc.p(0, 1), cc.p(0, Screen.height - 280)},
        {Enum.ResourceType.Jade, cc.p(0.5, 1), cc.p(Screen.width * 0.5, Screen.height - 280)}
    }

    for _, v in pairs(resourceTypeList) do
        local ratio = GuildDonateRatioConfigRead:getPersonalDonateRatio(v[1])
        local str = string.format("1%s=%d贡献", BackpackConfigRead:getName(v[1]), ratio)
        local label = CommonUI:createLabel(str, 28)
        self:addChild(label)
        label:setAnchorPoint(v[2])
        label:setPosition(v[3])
    end
end

function M:_createProgress()
    local progressBackground = cc.Sprite:create("ui/hero-museum/progressbg.png")
    self:addChild(progressBackground)
    local progressSize = progressBackground:getContentSize()

    progressBackground:setPosition(cc.p(Screen.width * 0.5, Screen.height - 220))

    self._progressTimer = cc.ProgressTimer:create(cc.Sprite:create("ui/hero-museum/progressup.png"))
    Layout:layout(self._progressTimer, progressSize, Layout.center)
    self._progressTimer:setBarChangeRate(cc.p(1, 0))
    self._progressTimer:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self._progressTimer:setMidpoint(cc.p(0,1))
    self._progressTimer:setPercentage(0)
    progressBackground:addChild(self._progressTimer)

    self._progressLabel = CommonUI:createLabel("0/100", 36)
    Layout:layout(self._progressLabel, progressSize, Layout.center)
    progressBackground:addChild(self._progressLabel)
end

function M:_createButtons()
    local padding = 20
    local confirmButton = CommonUI:createTextButton(self, "确认捐献", "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom, cc.p(confirmButton:getContentSize().width + padding, 10))
    confirmButton.onClicked = function()
        self:_sendDonateRequest()
    end

    local cancelButton = CommonUI:createTextButton(self, "取消", "ui/login/login-bt.png")
    Layout:layout(cancelButton, Screen.size, Layout.center_bottom, cc.p(-confirmButton:getContentSize().width - padding, 10))
    cancelButton.onClicked = function()
        self:_cancelSelectedValue()
    end
end

function M:_cancelSelectedValue()
    for k, v in pairs(self._donateValueList) do
        self._donateValueList[k] = 0
    end
    local offset = self._tableView:getContentOffset()
    self._tableView:reloadData()
    self._tableView:setContentOffset(offset)
end

function M:_sendDonateRequest()
    local data = {}
    for k, v in pairs(self._donateValueList) do
        if v ~= 0 then
            local item_info = {item_type = k, item_number = v}
            table.insert(data, item_info)
        end
    end
    if table.getn(data) == 0 then
        CommonUI:lightTips("请选择需要捐献的物品")
        return
    end
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kGuildDonate, {pay_items = data})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildDonate then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            self:_updateInfoLabels()
            self._tableView:reloadData()
        end
    end
    if cmd == kGuildInfo then
        self:_updateInfoLabels()
    end
end

function M:_createTableView()
    self._titleTypeList = {
        Enum.ResourceType.Food, 
        Enum.ResourceType.Wood, 
        Enum.ResourceType.Stone, 
        Enum.ResourceType.Coin, 
        Enum.ResourceType.Jade
    }
    for k, v in pairs(self._titleTypeList) do
        self._donateValueList[v] = 0
    end
    local infoHeight = 200
    local cellSize = ResourceOperateCell.ResourceOperateCellSize
    local viewHeight = table.getn(self._titleTypeList) * cellSize.height
    local leftHeight = Screen.size.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight - infoHeight
    local height = math.min(viewHeight, leftHeight)
    local viewSize = cc.size(cellSize.width, height)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), Screen.height - BackgroundLayer.TitleHeight - height - infoHeight))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return ResourceOperateCell.ResourceOperateCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = ResourceOperateCell.new(Enum.ResourceOperateType.Donate)
    end
    local titleType = self._titleTypeList[idx + 1]
    local callback = function(value)
        self._donateValueList[titleType] = value
    end
    cell:reset(titleType, self._donateValueList[titleType], callback)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._titleTypeList)
end


return M
