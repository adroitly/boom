local BackgroundLayer = require("ui.common.BackgroundLayer")
local MessageBoardCell = require("ui.message-board.layer-manager.MessageBoardCell")
local MessageBoardData = require("ui.message-board.data-manager.MessageBoardData")
local M = class("ui.message-board.layer-manager.MessageBoardLayer", function()
    return cc.Layer:create()
end)

-- 外交 
local kTotalTag         = 1
local kOwnCountryTag    = 2
local kMyselfTag        = 3

local kMessageBoardListRequest = "message_board_list"
local kMessageBoardAdd = "message_board_add"

local kPageMaxCount = 18
local kAddMessageLevelNeed = 30

function M:ctor()
    self._curPage = 1
    self._currentTag = kTotalTag
    self._totalMessageList = {}

    self:_createBackground()
    self:_createTableView()
    self:_createRadioButtons()
    self:_createAddMessageButton()

    SocketManager:addObserver(self)
    self:registerScriptHandler(function(event)
        if event == "exit" then
            SocketManager:removeObserver(self)
        end
    end)

    self:_getTheNewestBoardListRequest()
end


function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == kMessageBoardListRequest then
        self._hasRequest = false
        CommonUI:showLoadingLayer(false)
        self:_initMessageList(msgTable)
        self._tableView:reloadData()
        self:_updateContentOffset()
    end
    if cmd == kMessageBoardAdd then
        self:_getTheNewestBoardListRequest()
    end
end

local function _addDataToList(list, data)
    local page = table.getn(list)
    if page == 0 then
        table.insert(list, {})
        page = table.getn(list)
    end
    local messageCount = table.getn(list[page])
    if messageCount == kPageMaxCount then
        table.insert(list, {})
        page = table.getn(list)
    end
    table.insert(list[page], data)
end

function M:_initMessageList(msgTable)
    self._totalMessageList[self._curPage] = {}
    for _, v in ipairs(msgTable.messages) do
        local data = MessageBoardData.new(v)
        table.insert(self._totalMessageList[self._curPage], data)
    end

    self._ownCountryMessageList = {}
    self._myselfMessageList = {}
    for _, pageMessageList in ipairs(self._totalMessageList) do
        for __, data in ipairs(pageMessageList) do
            if PlayerData:isSameCountry(data:getCountryId()) then
                _addDataToList(self._ownCountryMessageList, data)
            end
            if PlayerData:isOwner(data:getPlayerId()) then
                _addDataToList(self._myselfMessageList, data)
            end
        end
    end
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

function M:_getTheNewestBoardListRequest()
    SocketManager:send(kMessageBoardListRequest, {page = 1, country = 0})
    CommonUI:showLoadingLayer(true)
end

function M:_getMoreMessageBoardListRequest()
    local messageCount = self:_getCurrentPageMessageCount()
    if messageCount ~= kPageMaxCount then
        return
    end
    self._hasRequest = true
    self._preContentSize = self._tableView:getContentSize()
    self._curPage = self._curPage + 1
    SocketManager:send(kMessageBoardListRequest, {page = self._curPage, country = 0})
    CommonUI:showLoadingLayer(true)
end

function M:_getCurrentPageMessageCount()
    local messageCount = 0
    local messageList = self:_getTagMessageList()
    local curPageList = messageList[table.getn(messageList)]
    if not curPageList then
        return messageCount
    end
    return table.getn(curPageList)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("外交"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

local function _getSeqPositionX(positionCount, width, index)
    local space = (Screen.width - positionCount * width) / (positionCount + 1)
    return space * index + width * (index - 0.5)
end

function M:_createRadioButtons()
    local tempSprite = cc.Sprite:create("ui/login/login-up.png")
    local size = tempSprite:getContentSize()
    local posY = size.height * 0.5
    local tbl = {
        {normalImg = "ui/login/login-up.png", selectImg = "ui/login/login-down.png", pos = cc.p(_getSeqPositionX(4, size.width, 1), posY), title = "全部留言"},
        {normalImg = "ui/login/login-up.png", selectImg = "ui/login/login-down.png", pos = cc.p(_getSeqPositionX(4, size.width, 2), posY), title = "本国留言"},
        {normalImg = "ui/login/login-up.png", selectImg = "ui/login/login-down.png", pos = cc.p(_getSeqPositionX(4, size.width, 3), posY), title = "我的留言"},
    }
    local RadioButtonManager = require("share.radio-button.RadioButtonManager")
    RadioButtonManager:createRadioButtons(self, tbl, function(index)
        self:_radioButtonCallback(index)
    end)
end

function M:_createAddMessageButton()
    local button = CommonUI:createTextButton(self, "发布留言", "ui/login/login-up.png", "ui/login/login-down.png")
    local size = button:getContentSize()
    button:setPosition(cc.p(_getSeqPositionX(4, size.width, 4), size.height * 0.5))
    button.onClicked = function()
        local layer = require("ui.message-board.layer-manager.OwnMessageBoardLayer").new()
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end
    if PlayerData:getUserInfoData():getLevel() < kAddMessageLevelNeed then
        button:setEnabled(false)
    end
end

function M:_radioButtonCallback(index)
    if self._currentTag == index then
        return
    end
    self._currentTag = index
    self._tableView:reloadData()
end

function M:_createTableView()
    local cellSize = MessageBoardCell.MessageBoardCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight - BackgroundLayer.BottomHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    local messageData = self:_getMessageDataByIndex(idx)
    local layer = require("ui.message-board.layer-manager.OperateMenuLayer").new(messageData:getNickname())
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(layer)
end

function M:onTableViewCellSize(tableView, idx)
    return MessageBoardCell.MessageBoardCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = MessageBoardCell.new()
    end
    cell:reset(self:_getMessageDataByIndex(idx))
    return cell
end

function M:onTableViewCellCount(tableView)
    return self:_getTagMessageCount()
end

function M:onScrollViewDidScroll(tableView)
    local offset = tableView:getContentOffset()
    if offset.y >= 0 and not self._hasRequest then
        if self:_getCurrentPageMessageCount() >= kPageMaxCount then
            self:_getMoreMessageBoardListRequest()
        end
    end
end

function M:_getMessageDataByIndex(index)
    local page = math.ceil((index + 1) / kPageMaxCount)
    local idx = math.floor(index % kPageMaxCount + 1)
    local messageList = self:_getTagMessageList()
    return messageList[page][idx]
end

function M:_getTagMessageCount()
    local messageList = self:_getTagMessageList()
    local count = 0
    for _, pageMessageList in ipairs(messageList) do
        count = count + table.getn(pageMessageList)
    end
    return count
end

function M:_getTagMessageList()
    if self._currentTag == kTotalTag then
        return self._totalMessageList
    elseif self._currentTag == kOwnCountryTag then
        return self._ownCountryMessageList
    elseif self._currentTag == kMyselfTag then
        return self._myselfMessageList
    end
end

return M