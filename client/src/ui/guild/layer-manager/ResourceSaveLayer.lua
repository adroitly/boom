local BackgroundLayer = require("ui.common.BackgroundLayer")
local ResourceOperateCell = require("ui.guild.layer-manager.ResourceOperateCell")
local M = class("ui.guild.layer-manager.ResourceSaveLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self:_createBackground()
    self:_createTableView()
    self:_createButton()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "存入资源")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createButton()
    local confirmButton = CommonUI:createTextButton(self, "存入资源", "ui/login/login-bt.png")
    Layout:layout(confirmButton, Screen.size, Layout.center_bottom, cc.p(0, 10))
end

function M:_createTableView()
    self._titleTypeList = {
        Enum.ResourceType.Food, 
        Enum.ResourceType.Wood, 
        Enum.ResourceType.Stone, 
        Enum.ResourceType.Coin, 
        Enum.ResourceType.Jade
    }
    local cellSize = ResourceOperateCell.ResourceOperateCellSize
    local viewHeight = table.getn(self._titleTypeList) * cellSize.height
    local leftHeight = Screen.size.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight
    local height = math.min(viewHeight, leftHeight)
    local viewSize = cc.size(cellSize.width, height)
    local tableView = require("share.TableView").new(viewSize, self)
    self:addChild(tableView)
    tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), Screen.height - BackgroundLayer.TitleHeight - height))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return ResourceOperateCell.ResourceOperateCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = ResourceOperateCell.new(Enum.ResourceOperateType.Save)
    end
    cell:reset(self._titleTypeList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._titleTypeList)
end

return M