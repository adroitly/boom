local BackgroundLayer = require("ui.common.BackgroundLayer")
local CollectCell = require("ui.collection.layer-manager.CollectCell")
local CollectDataManager = require("ui.collection.data-manager.CollectDataManager")
local CollectConfig = require("ui.collection.data-manager.CollectConfig")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.collection.MainLayer", function()
    return cc.Layer:create()
end)

function M:ctor()
    self._selectedTag = CollectConfig.CollectType.Friend
    self:_createBackground()
    self:_createTableView()
    self:_createRatioButtonLayer()
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    Listener:addListener(self)
end

function M:onExit()
    Listener:removeListener(self)
end

function M:onListenCollectDataChanged()
    CommonUI:showLoadingLayer(false)
    self._dataList = CollectDataManager:getDataListByType(self._selectedTag)
    self._tableView:reloadData()
end

function M:onViewCenterToPositionChanged()
    self:removeFromParent()
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "收藏")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTableView()
    self._dataList = CollectDataManager:getDataListByType(CollectConfig.CollectType.Friend)
    local cellSize = CollectCell.CollectCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    self._tableView = GridView.new(viewSize, self, 1)
    -- self._tableView = require("share.TableView").new(viewSize, self)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
    self:addChild(self._tableView)
end

function M:onGridViewCellTouched(tableView, index)
    local collectData = self._dataList[index + 1]
    local coor = collectData:getCoor()
    local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:changeViewCenterByTwoDCoor(coor.i, coor.j)
end

function M:onGridViewLineHeight(tableView, idx)
    return CollectCell.CollectCellSize.height
end

function M:onGridViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = CollectCell.new()
    end
    cell:reset(self._dataList[idx + 1])
    return cell
end

function M:onGridViewCellCount(tableView)
    return table.getn(self._dataList)
end

function M:_createRatioButtonLayer()
    local setInfo = {
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "朋友", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "敌人", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "资源", 30},
        { "ui/login/login-up.png", "ui/login/login-down.png", "ui/login/login-down.png", "标记", 30},
    }
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    local btnSize = tempSprite:getContentSize()
    local buttonRadioLayer = ButtonRadioLayer.new(setInfo)
    buttonRadioLayer:setLayout(cc.size(Screen.width, btnSize.height))
    self:addChild(buttonRadioLayer)
    buttonRadioLayer:setPosition(cc.p(0, 0))
    buttonRadioLayer.onClicked = function(sender, index)
        self:_onTagSelected(sender, index)
    end
end

function M:_onTagSelected(sender, index)
    self._selectedTag = index + 1
    self._dataList = CollectDataManager:getDataListByType(self._selectedTag)
    self._tableView:reloadData()
end

return M