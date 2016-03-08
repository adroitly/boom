local GuildDataManager = require("player-data.GuildDataManager")
local M = class("ui.guild.MainLayer", function()
    return cc.Layer:create()
end)

local kGuildInfo            = "guild_info"
local kGuildInfoList        = "guild_info_list"

function M:ctor()
    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
        if event == "enterTransitionFinish" then
            self:_checkGuildState()
        end
    end)
end

function M:_checkGuildState()
    if PlayerData:isHasGuild() then
        self:_getGuildInfo()
    else
        self:_gotoOtherLegueLayer()
    end
end

function M:_getGuildInfo()
    local guildId = PlayerData:getGuildId()
    SocketManager:send(kGuildInfo, {guild_id = guildId})
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kGuildInfo then
        self:_gotoGuildLayer()
    end
end

function M:_gotoGuildLayer()
    local GuildLayer = require("ui.guild.layer-manager.GuildLayer")
    local guildLayer = GuildLayer.new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(guildLayer)
    self:removeFromParent()
end

function M:_gotoOtherLegueLayer()
    local OtherGuildLayer = require("ui.guild.layer-manager.OtherGuildLayer")
    local otherGuildLayer = OtherGuildLayer.new()
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(otherGuildLayer)
    self:removeFromParent()
end

return M