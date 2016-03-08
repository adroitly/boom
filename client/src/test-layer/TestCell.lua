local M = class("TestCell", function()
    return GridViewCell.new()
end)

function M:ctor()
    self._label = CommonUI:createLabel("AAAAAAAA")
    self:addChild(self._label)
end

function M:reload(idx)
    self._label:setString(idx)
end

return M
