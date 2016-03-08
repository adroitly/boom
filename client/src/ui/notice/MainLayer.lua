local ScrollNoticeData = require("ui.notice.notice-manager.ScrollNoticeData")
local RichLabel = require("ui.common.richlabel.RichLabel")
local M = class("ui.notice.MainLayer", function()
    return cc.Layer:create()
end)

local m_moveTime = 0.2
local m_moveHeight = 40
local m_labelPosiHeight = 150


local m_socketCmdKey = "broadcast"
--[[
msg
[color msg]
]]
function M:addScrollNotice(msg, count)
    assert(msg and count)
    self._scrollNoticeManager:addNotice(ScrollNoticeData:createByMsg(msg, count))
end

function M:ctor()
    self:_createRichLabel()
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    SocketManager:addObserver(self)
    self._scrollNoticeManager = require("ui.notice.notice-manager.ScrollNoticeManager").new()
    self:addChild(self._scrollNoticeManager)
    Timer:addTimer(self)
end

function M:onExit()
    SocketManager:removeObserver(self)
    Timer:removeTimer(self)
end

function M:onUpdate(dt)
    local function _updateShow(showNoticeData)
        self:_showScrollNoticeData(showNoticeData)
        self._showingNoticeData = showNoticeData
        if showNoticeData then
            showNoticeData:setShowed(true)
        end
    end
    local showNoticeData = self._scrollNoticeManager:getShowingScrollNoticeData()
    if self._showingNoticeData ~= showNoticeData then
        _updateShow(showNoticeData)
    elseif showNoticeData and false == showNoticeData:isShowed() then
        _updateShow(showNoticeData)
    end
end

function M:onSocketClientDidCallback(cmd, msgTable, key)
    if m_socketCmdKey == cmd then
        self._scrollNoticeManager:addNotice(ScrollNoticeData:createByServer(msgTable))
    end
end

function M:_createRichLabel()
    self._showRichLabel = RichLabel.new()
    self._showRichLabel:setViewWidth(Screen.width * 0.72)
    self:addChild(self._showRichLabel)

    self:_richLabelInitPosition(self._showRichLabel)
    self._showRichLabel:setAlignment(RichLabel.Alignment.Center)
    self._showRichLabel:setCascadeOpacityEnabled(true)

    self._moveRichLabel = RichLabel.new()
    self:_richLabelInitPosition(self._showRichLabel)
    self._moveRichLabel:setViewWidth(Screen.width * 0.72)
    self._moveRichLabel:setAlignment(RichLabel.Alignment.Center)
    self._moveRichLabel:setCascadeOpacityEnabled(true)
    self:addChild(self._moveRichLabel)
end

function M:_richLabelStopAction()
    self._moveRichLabel:stopAllActions()
    self._showRichLabel:stopAllActions()
    self:_richLabelInitPosition(self._moveRichLabel)
    self:_richLabelInitPosition(self._showRichLabel)
end

function M:_changeRichLabel()
    self._moveRichLabel:setElementList(self._showRichLabel:getElementList())
    self._moveRichLabel:reloadData()
end

function M:_moveRichLabelMove()
    self:_changeRichLabel()
    self:_moveAction(self._moveRichLabel, true)
end

function M:_showRichLabelMove()
    local nodeX, nodeY = self._showRichLabel:getPosition()
    self._showRichLabel:setPosition(cc.p(nodeX, nodeY - m_moveHeight))
    self:_moveAction(self._showRichLabel)
end

function M:_moveAction(node, isClear)
    local function _actionCallBack()
        if isClear then
            node:clearAllElement()
            node:reloadData()
        end
    end
    local moveUp = cc.MoveBy:create(m_moveTime, cc.p(0, m_moveHeight))
    local spawn
    if isClear then
        local fadeOut = cc.FadeOut:create(m_moveTime)
        spawn = cc.Spawn:create(fadeOut, moveUp)
    else
        spawn = cc.Spawn:create(moveUp)
    end
    local seq = cc.Sequence:create(spawn, cc.CallFunc:create(_actionCallBack))
    node:runAction(seq)
end

function M:_richLabelInitPosition(node)
    node:setPosition(cc.p(Screen.width * 0.15, Screen.height - m_labelPosiHeight))
end

function M:_showScrollNoticeData(scrollNoticeData)
    self:_richLabelStopAction()
    self:_moveRichLabelMove()

    if nil == scrollNoticeData then
        self._showRichLabel:clearAllElement()
        self._showRichLabel:reloadData()
        return
    end

    local elementList = scrollNoticeData:getElementList()
    self._showRichLabel:setElementList(elementList)
    self._showRichLabel:reloadData()
    self:_richLabelInitPosition(self._showRichLabel)
    self:_showRichLabelMove()
end

return M