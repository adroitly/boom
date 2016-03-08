
local M = class("ui.guild.layer-manager.FlagChangeCell", function()
    return cc.TableViewCell:new()
end)

M.FlagChangeCellSize = cc.size(Screen.width, 140)
local kFlagSize = cc.size(120, 120)
local kLineLimitCount = 3

function M:setSelectedCallback(callback)
    self._selectedCallback = callback
end

function M:reset(flagDataList)
    self:_resetFlags(flagDataList)
end

function M:ctor()
    self:setContentSize(M.FlagChangeCellSize)
    self:_createFlags()
end

function M:_createFlags()
    self._flags = {}
    for i = 1, kLineLimitCount do
        self._flags[i] = Button.new("ui/army-select.png")
        self:addChild(self._flags[i])
        self._flags[i]:setPosition(self:_getFlagPosition(i))
    end
end

function M:_resetFlags(flagDataList)
    local index = 1
    for i, flagData in pairs(flagDataList) do
        local idx = flagData:getIdx()
        local fileName = flagData:getFileName()
        self._flags[index]:changeNormalSprite(fileName)
        self._flags[index]:setVisible(true)
        self._flags[index].onClicked = function()
            self._selectedCallback(idx)
        end
        index = index + 1
    end
    for i = index, kLineLimitCount do
        self._flags[i]:setVisible(false)
    end
end

function M:_getFlagPosition(index)
    local paddingX = (M.FlagChangeCellSize.width - kFlagSize.width * kLineLimitCount) / (kLineLimitCount + 1)
    local posX = index * paddingX + kFlagSize.width * (index - 0.5)
    return cc.p(posX, M.FlagChangeCellSize.height * 0.5)
end

return M