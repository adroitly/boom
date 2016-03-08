local M = class("ui.login.ServerListChoiseBarCell", function(onClickFun)
    return GridViewCell.new()
end)

function M:ctor(onClickFun)
    self._button = CommonUI:createTextButton(self, "", "ui/login/login-up.png")
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


