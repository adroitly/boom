local M = class("ui.wiki.layer-manager.WikiTitleCell", function()
    return cc.TableViewCell:new()
end)

M.WikiTitleCellSize = cc.size(750, 123)

function M:reset(title)
    self._titleLabel:setString(title)
    Layout:layout(self._titleLabel, M.WikiTitleCellSize, Layout.left_center, cc.p(40, 0))
end

function M:ctor()
    self:_createBackground()
    self:_createTitleLabel()
end

function  M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.WikiTitleCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createTitleLabel()
    self._titleLabel = CommonUI:createLabel("", 32)
    self:addChild(self._titleLabel)
    
end

return M