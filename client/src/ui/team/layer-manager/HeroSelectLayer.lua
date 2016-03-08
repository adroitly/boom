
local HeroSelectCell = require("ui.team.layer-manager.HeroSelectCell")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroDataManager = require("player-data.HeroDataManager")
local M = class("ui.team.layer-manager.HeroSelectLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_initHerosData()
    self:_createBackground()
    self:_createTableView()
    self:_createConfirmButton()
end

function M:_initHerosData()
    self._herosList = {}
    self._herosList = HeroDataManager:getBackpackHeroNoTeamList()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "武将")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createConfirmButton()
    local confirmButton = CommonUI:createTextButton(self, "确定", "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom)
    confirmButton.onClicked = function()
        if not self._selectedHeroIndex then
            CommonUI:lightTips(__Localized("您还没有选择武将"))
            return
        end
        local heroData = self._herosList[self._selectedHeroIndex + 1]
        local SoldierSelectLayer = require("ui.team.layer-manager.SoldierSelectLayer")
        local layer = SoldierSelectLayer.new(heroData)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
        self:removeFromParent()
    end
end

function M:_createTableView()
    local cellCount = table.getn(self._herosList)
    if cellCount == 0 then
        return
    end
    local cellSize = HeroSelectCell.HeroSelectCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    local tableView = require("share.TableView").new(viewSize, self)
    self:addChild(tableView)
    tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:onTableViewCellTouched(tableView, cell)
    if self._selectedHeroIndex then
        local preCell = tableView:cellAtIndex(self._selectedHeroIndex)
        if preCell then
            preCell:setSelected(false)
        end
    end
    cell:setSelected(true)
    self._selectedHeroIndex = cell:getIdx()
end

function M:onTableViewCellSize(tableView, idx)
    return HeroSelectCell.HeroSelectCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local heroData = self._herosList[idx + 1]
    local cell = tableView:dequeueCell()
    if not cell then
        cell = HeroSelectCell.new()
    end
    cell:resetHeroData(heroData)
    local isSelected = self._selectedHeroIndex and self._selectedHeroIndex == idx or false
    cell:setSelected(isSelected)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._herosList)
end


return M