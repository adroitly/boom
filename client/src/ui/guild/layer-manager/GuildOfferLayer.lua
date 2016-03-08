local BackgroundLayer = require("ui.common.BackgroundLayer")
local GuildMemberData = require("player-data.GuildMemberData")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local GuildMemberOperateLayer = require("ui.guild.layer-manager.GuildMemberOperateLayer")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.GuildOfferLayer", function()
    return cc.Layer:create()
end)

local kGuildMemberList = "guild_member_list"
local kMemberOperate = "guild_member_operate"
local kGuildMemberInfo = "guild_member_info"
local kGuildCustomTitle = "guild_custom_title"
function M:ctor()
    self:_createBackground()
    self:_createScrollView()
    self:_sendMemberListRequest()

    GuildLayerManager:addLayer(self)
    Listener:addListener(self)
    SocketManager:addObserver(self)
    Touch:registerTouchOneByOne(self, true)
    Event:registerNodeEvent(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
    Listener:removeListener(self)
    GuildLayerManager:removeLayer(self)
end

function M:onListenGuildMemberOperate()
    self:_removeOperateLayer()
end

function M:_sendMemberListRequest()
    SocketManager:send(kGuildMemberList, {})
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("册封"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createScrollView()
    self._scrollView = cc.ScrollView:create()
    local viewSize = cc.size(Screen.size.width, Screen.size.height - BackgroundLayer.TitleHeight)
    self._scrollView:setViewSize(viewSize)
    self._scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
    self:addChild(self._scrollView)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildMemberList then
        self:_initMemberList(msgTable)
        self._scrollView:getContainer():removeAllChildren()
        self:_createMemberView()
    end
    if cmd == kMemberOperate then
    end
    if cmd == kGuildMemberInfo then
        self:_updateMemberData(msgTable)
    end
    if cmd == kGuildCustomTitle then
        if not CommonUI:errorAlertView(msgTable.code) then
            self._scrollView:getContainer():removeAllChildren()
            self:_createMemberView()
        end
    end
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
    if not self:_hitTest(touch, self._operateLayer:getBackground()) then
        self:_removeOperateLayer()
    end
end

function M:onTouchCancelled(touch,event)
end

function M:_hitTest(touch, node)
    return Touch:isTouchHitted(node, touch)
end


function M:_updateMemberData(msgTable)
    local isDeleted = 1
    local tempData = nil
    for _, list in pairs(self._memberDataList) do
        for k, data in pairs(list) do
            if data:getPlayerId() == msgTable.player_id then
                tempData = list[k]
                list[k] = nil
            end
        end
    end
    if msgTable.is_delete ~= isDeleted then
        tempData:updateMemberData(msgTable)
        self:_addDataToList(tempData)
    end
    self._scrollView:getContainer():removeAllChildren()
    self:_createMemberView()

end

function M:_initMemberList(msgTable)
    self._memberDataList = {}
    for _, v in pairs(msgTable.guild_members) do
        local data = GuildMemberData.new(v)
        self:_addDataToList(data)
    end
end

function M:_addDataToList(data)
    local title = data:getTitle()
    if not self._memberDataList[title] then
        self._memberDataList[title] = {}
    end
    table.insert(self._memberDataList[title], data)
end

function M:_createMemberList(title, memberList, contentSize, currentHeight, paddingY)
    local titleFrame, totalHeight, titleHeight = self:_createTitleFrame(title)
    self._scrollView:getContainer():addChild(titleFrame)
    local firstPadding = currentHeight == 0 and 0 or paddingY
    Layout:layout(titleFrame, contentSize, Layout.center_top, cc.p(0, currentHeight + titleHeight))
    currentHeight = currentHeight + totalHeight
    for _, data in pairs(memberList) do
        local frame = self:_createFrameByMemberData(data)
        self._scrollView:getContainer():addChild(frame)
        Layout:layout(frame, contentSize, Layout.center_top, cc.p(0, currentHeight))
        local localPosX = frame:getPositionX() + frame:getContentSize().width * 0.5
        local localPosY = frame:getPositionY() + frame:getContentSize().height * 0.5
        local worldPos = frame:getParent():convertToWorldSpace(cc.p(localPosX, localPosY))
        frame.onClicked = function()
            self:_removeOperateLayer()
            self:_createOperateLayer(cc.p(worldPos.x, worldPos.y), data)
        end
        currentHeight = currentHeight + frame:getContentSize().height
    end
    currentHeight = currentHeight + paddingY
    return currentHeight
end

function M:_removeOperateLayer()
    if self._operateLayer then
        self._operateLayer:removeFromParent()
        self._operateLayer = nil
    end
end

function M:_createFrameByMemberData(memberData)
    local title = memberData:getTitle()
    local titleName = PlayerData:getGuildData():getTitleNameByTitle(title)
    local nickname = memberData:getNickname()
    local level = memberData:getLevel()
    local levelStr = OfficerConfigRead:getOfficerName(level)
    local totalDonate = memberData:getTotalDonate()
    local onlineTime = memberData:getPreOnlineTime()
    local frame = self:_createFrame(titleName, nickname, levelStr, totalDonate, onlineTime)
    return frame
end

function M:_createOperateLayer(worldPos, memberData)
    if self._operateLayer then
        self._operateLayer:setVisible(true)
        return
    end
    self._operateLayer = GuildMemberOperateLayer:createWithParent(self, worldPos, memberData)
end

function M:_createMemberView()
    local noblemenList = self._memberDataList[Enum.GuildTitle.Noblemen] or {}
    local nobilityList = self._memberDataList[Enum.GuildTitle.Nobility] or {}
    local normalList = self._memberDataList[Enum.GuildTitle.Normal] or {}
    -- 除去君王
    local memberCount = table.getn(noblemenList) + table.getn(nobilityList) + table.getn(normalList)
    local paddingY = 30
    -- 临时创建，获取尺寸用
    local _, totalHeight = self:_createTitleFrame("temp")
    local tempFrame = self:_createFrame("temp", "temp", "temp", "temp", "temp")
    local contentHeight = totalHeight * 3 + paddingY * 2 + memberCount * tempFrame:getContentSize().height
    local viewSize = self._scrollView:getViewSize()
    contentHeight = math.max(viewSize.height, contentHeight)

    local contentSize = cc.size(viewSize.width, contentHeight)
    self._scrollView:setContentSize(contentSize)
    local currentHeight = 0
    currentHeight = self:_createMemberList(Enum.GuildTitle.Noblemen, noblemenList or {}, contentSize, currentHeight, paddingY)
    currentHeight = self:_createMemberList(Enum.GuildTitle.Nobility, nobilityList or {}, contentSize, currentHeight, paddingY)
    currentHeight = self:_createMemberList(Enum.GuildTitle.Normal, normalList or {}, contentSize, currentHeight, paddingY)
    self._scrollView:setContentOffset(cc.p(0,  viewSize.height - contentHeight))
end

function M:_createTitleFrame(title)
    local titleName = PlayerData:getGuildData():getTitleNameByTitle(title)
    local frame = self:_createFrame(__Localized("封号"), __Localized("玩家名称"), __Localized("官职"), __Localized("贡献"), __Localized("在线"))
    local sprite = cc.Sprite:create("ui/login/login-bt.png")
    frame:addChild(sprite)
    local frameSize = frame:getContentSize()
    Layout:layout(sprite, frameSize, Layout.left_top, cc.p(0, -sprite:getContentSize().height))

    local textInput = require("ui.common.InputUI").new(30)
    textInput:setString(titleName or title)
    textInput:setMaxLength(8)
    sprite:addChild(textInput)
    Layout:layout(textInput, sprite:getContentSize(), Layout.center)
    textInput:setDetachIMECallback(function()
        local titleName = textInput:getString()
        if titleName == "" then
            AlertView.new(__Localized("职位名称不能为空"))
            return
        end
        SocketManager:send(kGuildCustomTitle, {title = title, name = titleName})
    end)

    local totalHeight = frameSize.height + sprite:getContentSize().height
    return frame, totalHeight, sprite:getContentSize().height
end

function M:_createFrame(title, nickname, office, donate, online)
    local background = Button.new("ui/mail/mail-title-bg.png")
    background:setZoomOnTouchDown(false)
    local bgSize = background:getContentSize()

    local titleLabel = CommonUI:createLabel(title, 30)
    background:addChild(titleLabel)
    Layout:layout(titleLabel, bgSize, Layout.center, cc.p(320, 0))

    local nicknameLabel = CommonUI:createLabel(nickname, 30)
    background:addChild(nicknameLabel)
    Layout:layout(nicknameLabel, bgSize, Layout.center, cc.p(180, 0))

    local officeLabel = CommonUI:createLabel(office, 30)
    background:addChild(officeLabel)
    Layout:layout(officeLabel, bgSize, Layout.center)

    local donateLabel = CommonUI:createLabel(donate, 30)
    background:addChild(donateLabel)
    Layout:layout(donateLabel, bgSize, Layout.center, cc.p(-150, 0))

    local onlineLabel = CommonUI:createLabel(online, 30)
    background:addChild(onlineLabel)
    Layout:layout(onlineLabel, bgSize, Layout.center, cc.p(-280, 0))
    return background
end

return M