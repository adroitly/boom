local M = class("ui.guild.data-manager.FlagData")

local function _flagFileNameList()
    return {
        [0] = "ui/guild/guild-flag-0.png",
        [1] = "ui/guild/guild-flag-1.png",
        [2] = "ui/guild/guild-flag-2.png",
        [3] = "ui/guild/guild-flag-3.png",
        [4] = "ui/guild/guild-flag-4.png",
        [5] = "ui/guild/guild-flag-5.png",
        [6] = "ui/guild/guild-flag-6.png",
        [7] = "ui/guild/guild-flag-7.png",
        [8] = "ui/guild/guild-flag-8.png",
        [9] = "ui/guild/guild-flag-9.png",
        [10] = "ui/guild/guild-flag-10.png",
    }
end
function M:ctor(idx)
    assert(idx)
    self._idx = idx
end

function M:getIdx()
    return self._idx
end

function M:getFileName()
    local fileNameList = _flagFileNameList()
    return fileNameList[self._idx]
end

return M