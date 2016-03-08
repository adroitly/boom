local M = class("ui.guild.layer-manager.GuildQuitLayer", function()
    return cc.Layer:create()
end)
local kGuildQuit = "guild_quit"
function M:ctor()
    self:_createAlertView()
end

function M:_createAlertView()
    AlertView.new(__Localized("您确定要退出势力吗？"), __Localized("取 消"), __Localized("退 出"))
    .onClicked = function(index)
        if 1==index then 
            SocketManager:send(kGuildQuit, {})
        end
    end
end

return M