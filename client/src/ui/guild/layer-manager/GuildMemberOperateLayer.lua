local OtherPlayerData = require("ui.user-info.datas.OtherPlayerData")
local M = class("ui.guild.layer-manager.GuildMemberOperateLayer", function()
    return cc.Layer:create()
end)

local kMemberOperate = "guild_member_operate"
local kPlayerBaseInfo2 = "player_base_info2"
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")

function M:createWithParent(parent, pos, memberData)
    local layer = M.new(memberData)
    parent:addChild(layer)
    local pos = parent:convertToNodeSpace(pos)
    local background = layer:getBackground()
    local bgSize = background:getContentSize()
    local posX = pos.x - bgSize.width * 0.5
    local posY = pos.y - bgSize.height * 0.5
    if posY - bgSize.height * 0.5 < 0 then
        posY = bgSize.height * 0.5
    end

    background:setPosition(cc.p(posX, posY))

    return layer
end

function M:ctor(memberData)
    self:_createOperateButton(memberData)

    GuildLayerManager:addLayer(self)
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
            GuildLayerManager:removeLayer(self)
        end
    end)
    Touch:registerTouchOneByOne(self, false)
end

function M:getBackground()
    return self._background
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kPlayerBaseInfo2 then
        local otherPlayerData = OtherPlayerData.new(msgTable)
        local layer = require("ui.user-info.layers.OtherPlayerInfoLayer").new(otherPlayerData)
        cc.Director:getInstance():getRunningScene():addChild(layer)
        Listener:postEvent(Listener.EventName.onListenGuildMemberOperate)
    end
end

function M:_createOperateButton(memberData)
    local tempSprite = cc.Sprite:create("ui/login/login-bt.png")
    self._background = ccui.Scale9Sprite:create("ui/login/login-bt.png", cc.rect(0, 0, tempSprite:getContentSize().width, tempSprite:getContentSize().height), cc.rect(30, 30, 40, 20))
    self:addChild(self._background)
    local tbl = self:_getOperateTable(memberData)
    local paddingX = 10
    local paddingY = 10
    local count = table.getn(tbl)
    tempSprite = cc.Sprite:create("ui/login/login-button.png")
    local size = cc.size(paddingX * 2 + tempSprite:getContentSize().width, paddingY * (count + 1) + tempSprite:getContentSize().height * count)
    self._background:setContentSize(size)
    self._operateButtons = {}
    for i, v in pairs(tbl) do
        local title = v[2]
        local button = CommonUI:createTextButton(self._background, title, "ui/login/login-button.png")
        table.insert(self._operateButtons, button)
        Layout:layout(button, size, Layout.center_top, cc.p(0, paddingY * i + button:getContentSize().height * (i - 1)))
        button.onClicked = function()
            local playerId = memberData:getPlayerId()
            local operateType = v[1]
            -- 查看
            if operateType ~= Enum.GuildMemberOperate.LookOver then
                SocketManager:send(kMemberOperate, {target_id = playerId, operate_type = operateType})
                Listener:postEvent(Listener.EventName.onListenGuildMemberOperate)
            else
                self:_lookOtherPlayerInfo(memberData)
            end
            
        end
    end
end

function M:_lookOtherPlayerInfo(memberData)
    local playerId = memberData:getPlayerId()
    SocketManager:send(kPlayerBaseInfo2, {target_id = playerId})
end

function M:_getOperateTable(memberData)
    local ownTitle = PlayerData:getGuildMemberData():getTitle()
    local otherTitle = memberData:getTitle()
    if ownTitle == Enum.GuildTitle.Leader then
        return self:_getLeaderOperate(otherTitle)
    elseif ownTitle == Enum.GuildTitle.Noblemen then
        return self:_getNoblemenOperate(otherTitle)
    elseif ownTitle == Enum.GuildTitle.Nobility then
        return self:_getNobilityOperate(otherTitle)
    elseif ownTitle == Enum.GuildTitle.Normal then
        return self:_getNormalOperate(otherTitle)
    end
end

function M:_getLeaderOperate(otherTitle)
    if otherTitle == Enum.GuildTitle.Leader then
        return {{Enum.GuildMemberOperate.LookOver, __Localized("查看")}}
    elseif otherTitle == Enum.GuildTitle.Noblemen then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
            {Enum.GuildMemberOperate.Nobility, __Localized("降为爵")},
            {Enum.GuildMemberOperate.Normal, __Localized("降为普通成员")},
            {Enum.GuildMemberOperate.Transfer, __Localized("禅让")},
            {Enum.GuildMemberOperate.KickOut, __Localized("踢出")},
        }
    elseif otherTitle == Enum.GuildTitle.Nobility then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
            {Enum.GuildMemberOperate.Noblemen, __Localized("升为候")},
            {Enum.GuildMemberOperate.Normal, __Localized("降为普通成员")},
            {Enum.GuildMemberOperate.Transfer, __Localized("禅让")},
            {Enum.GuildMemberOperate.KickOut, __Localized("踢出")},
        }
    elseif otherTitle == Enum.GuildTitle.Normal then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
            {Enum.GuildMemberOperate.Noblemen, __Localized("升为候")},
            {Enum.GuildMemberOperate.Nobility, __Localized("升为爵")},
            {Enum.GuildMemberOperate.Transfer, __Localized("禅让")},
            {Enum.GuildMemberOperate.KickOut, __Localized("踢出")},
        }
    end
end

function M:_getNoblemenOperate(otherTitle)
    if otherTitle == Enum.GuildTitle.Leader or 
        otherTitle == Enum.GuildTitle.Noblemen then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
        }
    elseif otherTitle == Enum.GuildTitle.Nobility then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
            {Enum.GuildMemberOperate.Normal, __Localized("降为普通成员")},
            {Enum.GuildMemberOperate.KickOut, __Localized("踢出")},
        }
    elseif otherTitle == Enum.GuildTitle.Normal then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
            {Enum.GuildMemberOperate.Nobility, __Localized("升为爵")},
            {Enum.GuildMemberOperate.KickOut, __Localized("踢出")},
        }
    end
end

function M:_getNobilityOperate(otherTitle)
    if otherTitle == Enum.GuildTitle.Normal then
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
            {Enum.GuildMemberOperate.KickOut, __Localized("踢出")},
        }
    else
        return {
            {Enum.GuildMemberOperate.LookOver, __Localized("查看")},
        }
    end
end

function M:_getNormalOperate(otherTitle)
    return {{Enum.GuildMemberOperate.LookOver, __Localized("查看")}}
end

function M:onTouchBegan(touch, event)
    return true
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch,event)
    if not self:_hitTest(touch, self._background) then
        self:setVisible(false)
    end
end

function M:onTouchCancelled(touch,event)
end

function M:_hitTest(touch, node)
    return Touch:isTouchHitted(node, touch)
end


return M