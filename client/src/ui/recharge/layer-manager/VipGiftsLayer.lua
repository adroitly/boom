local BackgroundLayer = require("ui.common.BackgroundLayer")
local VipConfigReader = require("ui.recharge.data-manager.VipConfigReader")
local VipGiftsCell = require("ui.recharge.layer-manager.VipGiftsCell")
local M = class("ui.recharge.layer-manager.VipGiftsLayer", function()
    return cc.Layer:create()
end)

local kVipGiftRecevie = "vip_gift_recevie"

function M:ctor()
    self:_createBackground()
    self:_createTableView()

    Event:registerNodeEvent(self)
end

function M:onEnter()
    SocketManager:addObserver(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kVipGiftRecevie then
        CommonUI:showLoadingLayer(false)
        if not CommonUI:errorAlertView(msgTable.code) then
            CommonUI:lightTips(__Localized("领取成功"))
            local offset = self._tableView:getContentOffset()
            self._tableView:reloadData()
            self._tableView:setContentOffset(offset)
        end
    end
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("Vip礼包"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createTableView()
    local cellSize = VipGiftsCell.VipGiftsCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), 0))
end

function M:onTableViewCellTouched(tableView, cell)
    -- local idx = cell:getIdx()
    -- local receiveLv = idx + 1
    -- local vipLv = PlayerData:getUserInfoData():getVip()
    -- if vipLv >= receiveLv then
    --     CommonUI:showLoadingLayer(true)
    --     SocketManager:send(kVipGiftRecevie, {gift_lv = receiveLv})
    -- else
    --     local layer = require("ui.recharge.layer-manager.RechargeLayer").new()
    --     local scene = cc.Director:getInstance():getRunningScene()
    --     scene:addChild(layer)
    -- end
end

function M:onTableViewCellSize(tableView, idx)
    return VipGiftsCell.VipGiftsCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = VipGiftsCell.new()
    end
    local curCellVipLv = idx + 1
    local giftLv = PlayerData:getUserInfoData():getVipGiftRecevieLevel()
    cell:reset(curCellVipLv, curCellVipLv <= giftLv)
    return cell
end

function M:onTableViewCellCount(tableView)
    return VipConfigReader:getMaxLevel()
end

return M