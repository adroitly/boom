local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildMemberCell = require("ui.guild.layer-manager.GuildMemberCell")
local GuildMemberData = require("player-data.GuildMemberData")
local GuildMemberOperateLayer = require("ui.guild.layer-manager.GuildMemberOperateLayer")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildMemberLayer", function()
    return cc.Layer:create()
end)

local kGuildMemberList = "guild_member_list"
local kGuildMemberOperate = "guild_member_operate"
local kGuildMemberInfo = "guild_member_info"

function M:ctor()
    self._memberDataList = {}

    self:_createBackground()
    self:_createInfoLabels()
    self:_createTableView()

    self:_sendMemberListRequest()

    GuildLayerManager:addLayer(self)
    Listener:addListener(self)
    Touch:registerTouchOneByOne(self, true)
    Event:registerNodeEvent(self)
    SocketManager:addObserver(self)
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
    SocketManager:send(kGuildMemberList, {})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildMemberList then
        self._memberDataList = {}
        for _, v in pairs(msgTable.guild_members) do
            local data = GuildMemberData.new(v)
            table.insert(self._memberDataList, data)
        end
        self:_sortMemberList()
        self._tableView:reloadData()
    end
    if cmd == kGuildMemberOperate then
        if not CommonUI:errorAlertView(msgTable.code) then
            AlertView.new(__Localized("操作成功"))
        end
    end
    if cmd == kGuildMemberInfo then
        for k, data in pairs(self._memberDataList) do
            if data:getPlayerId() == msgTable.player_id then
                if msgTable.is_delete == 1 then
                    self._memberDataList[k] = nil
                    self:_sortMemberList()
                    self._tableView:reloadData()
                    return
                end
                data:updateMemberData(msgTable)
                self:_sortMemberList()
                self._tableView:reloadData()
                return
            end
        end
    end
end

function M:_sortMemberList()
    table.sort(self._memberDataList, function(a, b)
        return a:getTitle() < b:getTitle()
    end)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("成员"))
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

    local titleLabel = CommonUI:createLabel(__Localized("封号"), 30)
    background:addChild(titleLabel)
    Layout:layout(titleLabel, bgSize, Layout.center, cc.p(320, 0))

    local nicknameLabel = CommonUI:createLabel(__Localized("玩家名称"), 30)
    background:addChild(nicknameLabel)
    Layout:layout(nicknameLabel, bgSize, Layout.center, cc.p(180, 0))

    local officeLabel = CommonUI:createLabel(__Localized("官职"), 30)
    background:addChild(officeLabel)
    Layout:layout(officeLabel, bgSize, Layout.center)

    local donateLabel = CommonUI:createLabel(__Localized("贡献"), 30)
    background:addChild(donateLabel)
    Layout:layout(donateLabel, bgSize, Layout.center, cc.p(-150, 0))

    local onlineLabel = CommonUI:createLabel(__Localized("在线"), 30)
    background:addChild(onlineLabel)
    Layout:layout(onlineLabel, bgSize, Layout.center, cc.p(-280, 0))
end

function M:_createTableView()
    local cellSize = GuildMemberCell.GuildMemberCellSize
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
    local localPosX = cell:getPositionX() + GuildMemberCell.GuildMemberCellSize.width
    local localPosY = cell:getPositionY() + GuildMemberCell.GuildMemberCellSize.height
    local worldPos = cell:getParent():convertToWorldSpace(cc.p(localPosX, localPosY))
    if self._operateLayer then
        self._operateLayer:setVisible(true)
        return
    end
    self._operateLayer = GuildMemberOperateLayer:createWithParent(self, worldPos, self._memberDataList[idx + 1])
end

function M:onTableViewCellSize(tableView, idx)
    return GuildMemberCell.GuildMemberCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = GuildMemberCell.new()
    end
    cell:reset(self._memberDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._memberDataList)
end

return M