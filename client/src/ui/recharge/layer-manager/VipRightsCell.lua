
local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local M = class("ui.recharge.layer-manager.VipRightsCell", GridViewCell)

M.VipRightsCellSize = cc.size(Screen.width, 780)

function M:reset(vipLv)
    local descTbl = VipConfigReader:getDescTbl(vipLv)
    local str = ""
    for k, desc in ipairs(descTbl) do
        str = str .. desc .. "\n"
    end
    self._descLabel:setString(str)
    Layout:layout(self._descLabel, M.VipRightsCellSize, Layout.center)

    local titleStr = string.format("VIP%d", vipLv)
    self._titleLabel:setString(titleStr)
    Layout:layout(self._titleLabel, M.VipRightsCellSize, Layout.center_top, cc.p(0, 20))
end

function M:ctor()
    self:setAnchorPoint(cc.p(0.5, 0.5))
    self:setContentSize(M.VipRightsCellSize)
    self:_createBackground()
    self:_createDescLabel()
    self:_createTitleLabel()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-bg-0002.png")
    self:addChild(background)
    Layout:layout(background, M.VipRightsCellSize, Layout.center)
end

function M:_createDescLabel()
    self._descLabel = CommonUI:createLabel("", 30)
    self:addChild(self._descLabel)
end

function M:_createTitleLabel()
    self._titleLabel = CommonUI:createLabel("", 40)
    self:addChild(self._titleLabel)
end

return M