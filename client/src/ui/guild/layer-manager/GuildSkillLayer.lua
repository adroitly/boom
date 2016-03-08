local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildSkillCell = require("ui.guild.layer-manager.GuildSkillCell")
local GuildSkillConfigRead = require("ui.guild.data-manager.GuildSkillConfigRead")
local GuildDataManager = require("player-data.GuildDataManager")
local GuildSkillData = require("ui.guild.data-manager.GuildSkillData")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildSkillLayer", function()
    return cc.Layer:create()
end)

local kGuildSkillUpgrade = "guild_skill_upgrade"

function M:ctor()
    self:_initGuildSkillDataList()
    self:_createBackground()
    self:_createInfoTitleBar()
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

-- 初始时的技能
function M:_initGuildSkillDataList()
    self._guildSkillDataList = {}
    local guildData = PlayerData:getGuildData()
    local guildSkillDataList = guildData:getGuildSkillDataList()
    for _, skillData in pairs(guildSkillDataList) do
        table.insert(self._guildSkillDataList, skillData)
    end
    table.sort(self._guildSkillDataList, function(a, b)
        return a:getSkillType() < b:getSkillType()
    end)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildSkillUpgrade then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips("升级成功")
            self:_updateDonateValue()
            self:_initGuildSkillDataList()
            local offset = self._tableView:getContentOffset()
            self._tableView:reloadData()
            self._tableView:setContentOffset(offset)
        end
    end
end

function M:_createInfoTitleBar()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))

    self._donateLabel = CommonUI:createLabel("", 30)
    background:addChild(self._donateLabel)
    Layout:layout(self._donateLabel, background:getContentSize(), Layout.center)
    self:_updateDonateValue()
end

function M:_updateDonateValue()
    local donate = PlayerData:getGuildMemberData():getTotalDonate()
    local guildData = PlayerData:getGuildData()
    local str = string.format("我的贡献:%d", donate)
    self._donateLabel:setString(str)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("技能"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTableView()
    local cellSize = GuildSkillCell.GuildSkillCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - 123)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p((Screen.width - viewSize.width) * 0.5, 0))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return GuildSkillCell.GuildSkillCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = GuildSkillCell.new()
    end
    cell:reset(self._guildSkillDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._guildSkillDataList)
end

return M