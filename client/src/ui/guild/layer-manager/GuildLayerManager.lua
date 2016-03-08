local M = {}

local kUserInfo = "user_info"

function M:startManager()
    self._preGuildId = 0
    self._guildLayerList = {}
    Listener:addListener(self)
end

function M:stopManager()
    self._guildLayerList = {}
    Listener:removeListener(self)
end

function M:addLayer(layer)
    self._guildLayerList[layer] = true
end

function M:removeLayer(layer)
    self._guildLayerList[layer] = nil
end

function M:onListenUserInfoDataChange()
    local guildId = PlayerData:getGuildId()
    if self._preGuildId == 0 and guildId ~= 0 then
        self._preGuildId = guildId
        return
    end
    if self._preGuildId ~= 0 and guildId == 0 then
        AlertView.new(__Localized("您已经不在势力")).onClicked = function()
            self._preGuildId = 0
            for layer, _ in pairs(self._guildLayerList) do
                layer:removeFromParent()
            end
            self._guildLayerList = {}
        end
    end
end

return M