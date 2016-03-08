local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildLayerCell = require("ui.guild.layer-manager.GuildLayerCell")
local FlagData = require("ui.guild.data-manager.FlagData")
local GuildLevelConfigRead = require("ui.guild.data-manager.GuildLevelConfigRead")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildLayer", function()
    return cc.Layer:create()
end)

local kGuildSetting = "guild_setting"
local KGuildCustomTitle = "guild_custom_title"
function M:ctor()
    self:_createBackground()
    self:_createGuildInfo()
    self:_createBillboardInfo()
    self:_createTableView()

    GuildLayerManager:addLayer(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildSetting then
        if msgTable.code == 0 then
            self:_updateSetting()
        end
    end
end

function M:_updateSetting()
    local guildData = PlayerData:getGuildData()
    local billboardStr = guildData:getNote()
    self._billboardLabel:setVisible(true)
    self._billboardLabel:setString(billboardStr)

    local flag = guildData:getFlag()
    local flagData = FlagData.new(flag)
    self._flagIcon:setTexture(flagData:getFileName())
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("势力"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createGuildInfo()
    self._guildInfoBg = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(self._guildInfoBg)
    Layout:layout(self._guildInfoBg, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))

    local guildData = PlayerData:getGuildData()
    local flag = guildData:getFlag()
    local bgSize = self._guildInfoBg:getContentSize()

    local flagData = FlagData.new(flag)
    self._flagIcon = cc.Sprite:create(flagData:getFileName())
    self._guildInfoBg:addChild(self._flagIcon)
    Layout:layout(self._flagIcon, bgSize, Layout.left_center, cc.p(40, 0))

    local posX = self._flagIcon:getPositionX()
    local flagWidth = self._flagIcon:getContentSize().width
    local initPosX = posX + flagWidth * 0.5 + 20

    local posY = bgSize.height * 0.5
    local leaderNameStr = string.format("君王名称：%s", guildData:getLeaderName())
    leaderNameStr = __Localized(leaderNameStr)
    local leaderNameLabel = CommonUI:createLabel(leaderNameStr, 28)
    self._guildInfoBg:addChild(leaderNameLabel)
    leaderNameLabel:setAnchorPoint(cc.p(0, 0.5))
    leaderNameLabel:setPosition(cc.p(initPosX, posY))
    local leaderNameLabelPosY = leaderNameLabel:getPositionY()
    posY = leaderNameLabelPosY
    local maxMemberNum = GuildLevelConfigRead:getMemberMax(guildData:getLevel())
    local memberStr = string.format("成员：%d/%d", guildData:getMemberNum(), maxMemberNum)
    memberStr = __Localized(memberStr)
    local memberCountLabel = CommonUI:createLabel(memberStr, 28)
    self._guildInfoBg:addChild(memberCountLabel)
    memberCountLabel:setAnchorPoint(cc.p(0, 0.5))
    memberCountLabel:setPosition(cc.p(initPosX + leaderNameLabel:getContentSize().width + 50, posY))

    posY = leaderNameLabelPosY + leaderNameLabel:getContentSize().height * 0.5 + 20
    local guildNameStr = string.format("势力名称：%s", guildData:getName())
    guildNameStr = __Localized(guildNameStr)
    local nameLabel = CommonUI:createLabel(guildNameStr, 28)
    self._guildInfoBg:addChild(nameLabel)
    nameLabel:setAnchorPoint(cc.p(0, 0))
    nameLabel:setPosition(cc.p(initPosX, posY))

    local levelStr = string.format("Lv.%d", guildData:getLevel())
    local levelLabel = CommonUI:createLabel(levelStr, 28)
    self._guildInfoBg:addChild(levelLabel)
    levelLabel:setAnchorPoint(cc.p(0, 0))
    levelLabel:setPosition(cc.p(initPosX + nameLabel:getContentSize().width + 100, nameLabel:getPositionY()))

    posY = leaderNameLabelPosY - leaderNameLabel:getContentSize().height * 0.5 - 20
    local countryId = guildData:getCountryId()
    local countryName = CountryConfigReader:getCountryName(countryId)
    countryName = string.format("国家: %s", countryName)
    local countryLabel = CommonUI:createLabel(countryName, 28)
    self._guildInfoBg:addChild(countryLabel)
    countryLabel:setAnchorPoint(cc.p(0, 1))
    countryLabel:setPosition(cc.p(initPosX, posY))
end

function M:_createBillboardInfo()
    self._billboardBg = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(self._billboardBg)
    Layout:layout(self._billboardBg, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + self._guildInfoBg:getContentSize().height))

    local billboardStr = PlayerData:getGuildData():getNote()
    self._billboardLabel = CommonUI:createLabel(billboardStr, 24)
    self._billboardBg:addChild(self._billboardLabel)
    self._billboardLabel:setWidth(self._billboardBg:getContentSize().width - 20)
    Layout:layout(self._billboardLabel, self._billboardBg:getContentSize(), Layout.center)

    local guildData = PlayerData:getGuildData()
    self._billboardLabel:setString(guildData:getNote())
end

local function _callbacksTable()
    return {
        {title = __Localized("成员"), Layer = require("ui.guild.layer-manager.GuildMemberLayer")}, 
        {title = __Localized("捐献"), Layer = require("ui.guild.layer-manager.ResourceDonateLayer")}, 
        {title = __Localized("技能"), Layer = require("ui.guild.layer-manager.GuildSkillLayer")}, 
        {title = __Localized("管理"), Layer = require("ui.guild.layer-manager.GuildManagerLayer")}
    }
end

function M:_createTableView()
    local cellSize = GuildLayerCell.GuildLayerCellSize
    local offsetHeight = self._guildInfoBg:getContentSize().height + self._billboardBg:getContentSize().height
    local viewHeight = Screen.height - BackgroundLayer.TitleHeight - offsetHeight
    local viewSize = cc.size(cellSize.width, viewHeight)
    local tableView = require("share.TableView").new(viewSize, self)
    self:addChild(tableView)
    local posY = self._billboardBg:getPositionY() - self._billboardBg:getContentSize().height * 0.5 - viewSize.height
    local posX = 0.5 * (Screen.size.width - viewSize.width)
    tableView:setPosition(cc.p(posX, posY))
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    local Layer = _callbacksTable()[idx + 1].Layer
    local layer = Layer.new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(layer)
end

function M:onTableViewCellSize(tableView, idx)
    return GuildLayerCell.GuildLayerCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = GuildLayerCell.new()
    end
    local title = _callbacksTable()[idx + 1].title
    cell:reset(title)
    return cell
end

function M:onTableViewCellCount(tableView)
    local count = table.getn(_callbacksTable())
    return count
end
return M