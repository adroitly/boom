
local M = class("ui.guild.layer-manager.GuildLayerCell", function()
    return cc.TableViewCell:new()
end)

M.GuildLayerCellSize = cc.size(750, 123)

function M:reset(title)
    self._titleLabel:setString(title)
end

function M:ctor()
    self:_createBackground()
    self:_createTitleLabel()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.GuildLayerCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createTitleLabel()
    self._titleLabel = CommonUI:createLabel("", 40)
    self:addChild(self._titleLabel)
    Layout:layout(self._titleLabel, M.GuildLayerCellSize, Layout.center)
end


return M