local BackgroundLayer = require("ui.common.BackgroundLayer")
local RankConfig = require("ui.rank.data-manager.RankConfig")
local RankGuildCell = require("ui.rank.layer-manager.RankGuildCell")
local RankCell = require("ui.rank.layer-manager.RankCell")
local BuildingData = require("ui.map.data-manager.BuildingData")
local M = class("ui.rank.layer-manager.RankGuildLayer", function()
    return cc.Layer:create()
end)

local kCityBuildingInfoGet = "city_building_info_get"

function M:ctor(rankData)
    self._rankData = rankData
    self._buildingDataList = {}
    self:_createBackground()
    self:_createTitle()
    -- self:_createGuildInfo()
    self:_createTableView()
    Event:registerNodeEvent(self)
end

function M:onEnter()
    SocketManager:addObserver(self)
end

function M:onEnterTransitionFinish()
    self:_sendCityInfoGetRequest()
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:_sendCityInfoGetRequest()
    local guildId = self._rankData:getId()
    SocketManager:send(kCityBuildingInfoGet, {guild_id = guildId})
    CommonUI:showLoadingLayer(true)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kCityBuildingInfoGet then
        CommonUI:showLoadingLayer(false)
        for _, buildingInfo in ipairs(msgTable.buildingInfos) do
            local uniqueId = Utils:getUniqueId(buildingInfo.x, buildingInfo.y)
            local buildingData = BuildingData.new(buildingInfo, uniqueId)
            table.insert(self._buildingDataList, buildingData)
        end
        self._tableView:reloadData()
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, RankConfig.RankName[RankConfig.RankType.Guild])
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTitle()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
    local bgSize = background:getContentSize()

    -- local nameLabel = CommonUI:createLabel(__Localized("名称"), 30)
    local nameLabel = CommonUI:createLabel(__Localized("名城"), 30)
    background:addChild(nameLabel)
    Layout:layout(nameLabel, bgSize, Layout.center, cc.p(250, 0))

    -- local valueLabel = CommonUI:createLabel(RankConfig.RankValueName[RankConfig.RankType.Guild], 30)
    local valueLabel = CommonUI:createLabel(__Localized("坐标"), 30)
    background:addChild(valueLabel)
    Layout:layout(valueLabel, bgSize, Layout.center, cc.p(-250, 0))
end

function M:_createGuildInfo()
    local cell = RankCell.new(RankConfig.RankType.Guild)
    self:addChild(cell)
    local cellSize = cell:getContentSize()
    Layout:layout(cell, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + cellSize.height))
    cell:reset(RankConfig.RankType.Guild, self._rankData)
    cell:setExpanded(true)
end

function M:_createTableView()
    local cellSize = RankGuildCell.RankGuildCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - cellSize.height)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), 0))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return RankGuildCell.RankGuildCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = RankGuildCell.new()
    end
    cell:reset(self._buildingDataList[idx + 1])
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._buildingDataList)
end

return M