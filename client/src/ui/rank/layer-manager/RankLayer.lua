local BackgroundLayer = require("ui.common.BackgroundLayer")
local RankConfig = require("ui.rank.data-manager.RankConfig")
local RankCell = require("ui.rank.layer-manager.RankCell")
local RankData = require("ui.rank.data-manager.RankData")
local M = class("ui.rank.layer-manager.RankLayer", function()
    return cc.Layer:create()
end)

local kRank = "rank"
local kPageMaxCount = 18

function M:ctor(rankType, ownRanking, ownValue)
    self._rankDataList = {}
    self._curPage = 0
    self._hasRequest = false
    self._ownRanking = ownRanking
    self._ownValue = ownValue
    self._rankType = rankType
    self:_createBackground()
    self:_createTitle()
    self:_createOwnRanking()
    self:_createTableView()
    Event:registerNodeEvent(self)
end

function M:onEnter()
    SocketManager:addObserver(self)
end

function M:onEnterTransitionFinish()
    self:_sendRankInfoRequest()
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:_initRankDataList(msgTable)
    self._rankDataList[self._curPage] = {}
    for _, rankInfo in ipairs(msgTable.ranks) do
        local rankData = RankData.new(rankInfo)
        table.insert(self._rankDataList[self._curPage], rankData)
    end
end

function M:_sendRankInfoRequest()
    local curPageList = self._rankDataList[self._curPage]
    local rankCount = curPageList == nil and 0 or table.getn(curPageList)
    local curPageCount = math.floor((rankCount - 1) % kPageMaxCount + 1)
    if curPageCount ~= kPageMaxCount then
        return
    end
    self._hasRequest = true
    self._curPage = self._curPage + 1
    SocketManager:send(kRank, {rank_id = self._rankType, page = self._curPage})
    CommonUI:showLoadingLayer(true)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kRank then
        self._hasRequest = false
        self:_initRankDataList(msgTable)
        self._tableView:reloadData()
        self:_updateContentOffset()
        CommonUI:showLoadingLayer(false)
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, RankConfig.RankName[self._rankType])
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTitle()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight))
    local bgSize = background:getContentSize()

    local nameLabel = CommonUI:createLabel(__Localized("名称"), 30)
    background:addChild(nameLabel)
    Layout:layout(nameLabel, bgSize, Layout.center, cc.p(250, 0))

    local valueLabel = CommonUI:createLabel(RankConfig.RankValueName[self._rankType], 30)
    background:addChild(valueLabel)
    Layout:layout(valueLabel, bgSize, Layout.center, cc.p(-250, 0))
end

function M:_createOwnRanking()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_bottom)
    local bgSize = background:getContentSize()

    local rankingStr = RankConfig.RankOwnName[self._rankType]
    rankingStr = rankingStr .. ":" .. (self._ownRanking <= 0 and __Localized("暂无") or self._ownRanking)
    local rankingLabel = CommonUI:createLabel(rankingStr, 30)
    background:addChild(rankingLabel)
    Layout:layout(rankingLabel, bgSize, Layout.center, cc.p(200, 0))

    local valueLabel = CommonUI:createLabel(tostring(self._ownValue), 30)
    background:addChild(valueLabel)
    Layout:layout(valueLabel, bgSize, Layout.center, cc.p(-250, 0))
end

function M:_createTableView()
    local cellSize = RankCell.RankCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - cellSize.height * 2)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), cellSize.height))
end

function M:onTableViewCellTouched(tableView, cell)
    if self._rankType == RankConfig.RankType.Guild then
        local idx = cell:getIdx()
        local rankData = self:_getRankDataByIndex(idx)
        local layer = require("ui.rank.layer-manager.RankGuildLayer").new(rankData)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
end

function M:onTableViewCellSize(tableView, idx)
    return RankCell.RankCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = RankCell.new(self._rankType)
    end
    cell:reset(self._rankType, self:_getRankDataByIndex(idx))
    return cell
end

function M:onTableViewCellCount(tableView)
    return self:_getRankDataCount()
end

function M:onScrollViewDidScroll(tableView)
    local offset = tableView:getContentOffset()
    if offset.y >= 0 and not self._hasRequest then
        if self:_getCurrentPageCount() == kPageMaxCount then
            self._preContentSize = tableView:getContentSize()
            self:_sendRankInfoRequest()
        end
    end
end

function M:_getCurrentPageCount()
    return table.getn(self._rankDataList[self._curPage])
end

function M:_getRankDataByIndex(index)
    local page = math.ceil((index + 1) / kPageMaxCount)
    local idx = math.floor(index % kPageMaxCount + 1)
    return self._rankDataList[page][idx]
end

function M:_getRankDataCount()
    local count = 0
    for k, rankDataList in ipairs(self._rankDataList) do
        count = count + table.getn(rankDataList)
    end
    return count
end

function M:_updateContentOffset()
    if not self._preContentSize then
        return
    end
    local curContentSize = self._tableView:getContentSize()
    local preContentSize = self._preContentSize
    local offsetY = preContentSize.height - curContentSize.height
    self._tableView:setContentOffset(cc.p(0, offsetY))
    self._preContentSize = nil
end

return M