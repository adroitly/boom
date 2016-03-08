local M = class("ui.login.ServerListChoiseCell", function()
    return GridViewCell.new()
end)

function M:ctor(onClickFun)
    -- self._button = CommonUI:createTextButton(self, "", "ui/login/login-up.png")
    self._button = ButtonText.new("ui/login/login-up.png")
    self:addChild(self._button)
    self._button:setLabel("-", 30)
    
    self._button.onClicked = function(button)
        local atIndex = self._button:getTag()
        onClickFun(atIndex)
    end

    self._button:setSwallowTouches(false)
end

function M:reloadCell(text, atIndex)
    self._button:setText(text)
    self._button:setTag(atIndex)
end

return M


