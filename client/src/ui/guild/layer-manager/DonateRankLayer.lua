local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildMemberData = require("player-data.GuildMemberData")
local DonateRankCell = require("ui.guild.layer-manager.DonateRankCell")
local GuildMemberOperateLayer = require("ui.guild.layer-manager.GuildMemberOperateLayer")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.DonateRankLayer", function()
    return cc.Layer:create()
end)

local kGuildMemberInfos = "guild_member_list"
local kMemberOperate = "guild_member_operate"
function M:ctor()
    self._memberDataList = {}

    self:_createBackground()
    self:_createInfoLabels()
    self:_createTableView()

    self:_sendMemberListRequest()

    Listener:addListener(self)
    SocketManager:addObserver(self)
    Touch:registerTouchOneByOne(self, true)
    Event:registerNodeEvent(self)

    GuildLayerManager:addLayer(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
    Listener:removeListener(self)
    GuildLayerManager:removeLayer(self)
end

function M:onListenGuildMemberOperate()
    self:_removeOperateLayer()
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch,event)
    if not self._operateLayer then
        return
    end
    for i = 1, table.getn(self._memberDataList) do
        local cell = self._tableView:cellAtIndex(i - 1)
        if cell and self:_hitTest(touch, cell)then
            return
        end
    end
    if not self:_hitTest(touch, self._operateLayer:getBackground()) then
        self:_removeOperateLayer()
    end
end

function M:onTouchCancelled(touch,event)
end

function M:_hitTest(touch, node)
    return Touch:isTouchHitted(node, touch)
end


function M:_sendMemberListRequest()
    SocketManager:send(kGuildMemberInfos, {})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildMemberInfos then
        self._memberDataList = {}
        for _, v in pairs(msgTable.guild_members) do
            local data = GuildMemberData.new(v)
            table.insert(self._memberDataList, data)
        end
        table.sort(self._memberDataList, function(a, b)
            if a:getTotalDonate() > b:getTotalDonate() then
                return true
            end
            if a:getTotalDonate() == b:getTotalDonate() then
                return a:getTitle() < b:getTitle()
            end
            return false
        end)
        self._tableView:reloadData()
    end
    if cmd == kMemberOperate then
        if msgTable.code ~= 0 then
            local str = string.format(__Localized("成员操作失败，错误码为：%d"), msgTable.code)
            AlertView.new(str)
            return
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("捐献排行"))
    Touch:removeTouchOneByOne(background)
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createInfoLabels()
    local offsetPosY = BackgroundLayer.TitleHeight
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, offsetPosY))
    local bgSize = background:getContentSize()
    self._infoBackground = background

    local rankLabel = CommonUI:createLabel(__Localized("排行"), 30)
    background:addChild(rankLabel)
    Layout:layout(rankLabel, bgSize, Layout.center, cc.p(320, 0))

    local nicknameLabel = CommonUI:createLabel(__Localized("玩家名称"), 30)
    background:addChild(nicknameLabel)
    Layout:layout(nicknameLabel, bgSize, Layout.center, cc.p(100, 0))

    local totalDonateLabel = CommonUI:createLabel(__Localized("总捐献"), 30)
    background:addChild(totalDonateLabel)
    Layout:layout(totalDonateLabel, bgSize, Layout.center, cc.p(-100, 0))

    local titleLabel = CommonUI:createLabel(__Localized("封号"), 30)
    background:addChild(titleLabel)
    Layout:layout(titleLabel, bgSize, Layout.center, cc.p(-280, 0))
end

function M:_createTableView()
    local cellSize = DonateRankCell.DonateRankCellSize
    local infoBgSize = self._infoBackground:getContentSize()
    local leftHeight = Screen.size.height - BackgroundLayer.TitleHeight - infoBgSize.height
    local viewSize = cc.size(cellSize.width, leftHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), Screen.height - BackgroundLayer.TitleHeight - leftHeight - infoBgSize.height))
end

function M:_removeOperateLayer()
    if self._operateLayer then
        self._operateLayer:removeFromParent()
        self._operateLayer = nil
    end
end

function M:onTableViewCellTouched(tableView, cell)
    self:_removeOperateLayer()
    local idx = cell:getIdx()
    local localPosX = cell:getPositionX() + DonateRankCell.DonateRankCellSize.width
    local localPosY = cell:getPositionY() + DonateRankCell.DonateRankCellSize.height
    local worldPos = cell:getParent():convertToWorldSpace(cc.p(localPosX, localPosY))
    if self._operateLayer then
        self._operateLayer:setVisible(true)
        return
    end
    self._operateLayer = GuildMemberOperateLayer:createWithParent(self, worldPos, self._memberDataList[idx + 1])
end

function M:onTableViewCellSize(tableView, idx)
    return DonateRankCell.DonateRankCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = DonateRankCell.new()
    end
    cell:reset(idx + 1, self._memberDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._memberDataList)
end


return M