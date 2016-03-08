local RankConfig = require("ui.rank.data-manager.RankConfig")
local M = class("ui.rank.layer-manager.RankTitleCell", function()
    return cc.TableViewCell:new()
end)

M.RankTitleCellSize = cc.size(750, 123)

function M:reset(rankType, ranking)
    self._totalTitleLabel:setString(RankConfig.RankName[rankType])
    Layout:layout(self._totalTitleLabel, M.RankTitleCellSize, Layout.left_center, cc.p(50, 0))

    local rankingStr = ranking <= 0 and __Localized("暂无") or ranking
    local rankStr = RankConfig.RankOwnName[rankType] .. ":" .. rankingStr
    self._ownTitleLabel:setString(rankStr)
    Layout:layout(self._ownTitleLabel, M.RankTitleCellSize, Layout.left_center, cc.p(400, 0))
end

function M:ctor()
    self:_createBackground()
    self:_createInfoLabels()
    self:_createArrow()
end

function  M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.RankTitleCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createArrow()
    local sprite = cc.Sprite:create("ui/city/arrow.png")
    self:addChild(sprite)
    Layout:layout(sprite, M.RankTitleCellSize, Layout.right_center, cc.p(50, 0))
end

function M:_createInfoLabels()
    self._totalTitleLabel = CommonUI:createLabel("", 30)
    self:addChild(self._totalTitleLabel)

    self._ownTitleLabel = CommonUI:createLabel("", 30)
    self:addChild(self._ownTitleLabel)
end

return M