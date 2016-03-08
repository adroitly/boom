local FamousCityConfigReader = require("config-reader.FamousCityConfigReader")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.rank.layer-manager.RankGuildCell", function()
    return cc.TableViewCell:new()
end)
M.RankGuildCellSize = cc.size(750, 123)
function M:reset(buildingData)
    local buildingId = buildingData:getBuildingId()
    local buildingName = FamousCityConfigReader:getName(buildingId)
    self._nameLabel:setString(buildingName)

    local coor = buildingData:getHomeCoor()
    local twoDCoor = MapConfig:localTo2D(coor)
    local coorStr = string.format("坐标：%d,%d", twoDCoor.i, twoDCoor.j)
    self._coorLabel:setString(coorStr)
end

function M:ctor()
    self:_createBackground()
    self:_createName()
    self:_createCoor()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.RankGuildCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createName()
    self._nameLabel = CommonUI:createLabel("洛阳城", 30)
    self:addChild(self._nameLabel)
    Layout:layout(self._nameLabel, M.RankGuildCellSize, Layout.center, cc.p(250, 0))
end

function M:_createCoor()
    self._coorLabel = CommonUI:createLabel("坐标：400,400", 30)
    self:addChild(self._coorLabel)
    Layout:layout(self._coorLabel, M.RankGuildCellSize, Layout.center, cc.p(-250, 0))
end

return M