local BackgroundLayer = require("ui.common.BackgroundLayer")
local RankTitleCell = require("ui.rank.layer-manager.RankTitleCell")
local RankConfig = require("ui.rank.data-manager.RankConfig")
local M = class("ui.rank.MainLayer", function()
    return cc.Layer:create()
end)

local kRankTypeList = {
    RankConfig.RankType.Country,
    RankConfig.RankType.Score,
    RankConfig.RankType.Guild,
    RankConfig.RankType.Officer,
    RankConfig.RankType.Coin,
    RankConfig.RankType.Food,
    RankConfig.RankType.Jade,
    RankConfig.RankType.Stone,
    RankConfig.RankType.Wood,
}

local kRankMy = "rank_my"

-- 排行榜主界面
function M:ctor()
    self._ownRankingList = {}
    self:_createBackground()
    Event:registerNodeEvent(self)
end

function M:onEnter()
    SocketManager:addObserver(self)
end

function M:onEnterTransitionFinish()
    CommonUI:showLoadingLayer(true)
    SocketManager:send(kRankMy, {})
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kRankMy then
        for index, rankType in ipairs(kRankTypeList) do
            self._ownRankingList[rankType] = {}
            local rankingIndexStr = "rank" .. index
            self._ownRankingList[rankType].ranking = msgTable[rankingIndexStr]
            local valueIndexStr = "rank" .. index .. "_value"
            self._ownRankingList[rankType].value = msgTable[valueIndexStr]
            if rankType == RankConfig.RankType.Officer and 
                self._ownRankingList[rankType].value == 0 then
                self._ownRankingList[rankType].value = 1
            end

        end
        self:_createTableView()
        CommonUI:showLoadingLayer(false)
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, "排行榜")
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTableView()
    local cellSize = RankTitleCell.RankTitleCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), 0))
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    local rankType = kRankTypeList[idx + 1]
    local layer = require("ui.rank.layer-manager.RankLayer").new(rankType, self._ownRankingList[rankType].ranking, self._ownRankingList[rankType].value)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(layer)
end

function M:onTableViewCellSize(tableView, idx)
    return RankTitleCell.RankTitleCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = RankTitleCell.new()
    end
    local rankType = kRankTypeList[idx + 1]
    cell:reset(rankType, self._ownRankingList[rankType].ranking)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(kRankTypeList)
end


return M