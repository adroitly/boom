local TimeTools = require("ui.common.TimeTools")
local M = class("ui.message-board.layer-manager.MessageBoardCell", function()
    return cc.TableViewCell:new()
end)

M.MessageBoardCellSize = cc.size(752, 193)

function M:reset(messageBoardData)
    local nicknameStr = messageBoardData:getNickname()
    self._nicknameLabel:setString(nicknameStr)
    Layout:layout(self._nicknameLabel, M.MessageBoardCellSize, Layout.left_top, cc.p(20, 10))

    local contentStr = messageBoardData:getContent()
    self._contentLabel:setString(contentStr)
    Layout:layout(self._contentLabel, M.MessageBoardCellSize, Layout.left_top, cc.p(20, 50))

    local time = messageBoardData:getTime()
    local timeStr = TimeTools:getFormatTimeString(time)
    self._timeLabel:setString(timeStr)
    Layout:layout(self._timeLabel, M.MessageBoardCellSize, Layout.right_bottom, cc.p(20, 10))
end

function M:ctor()
    self:_createBackground()
    self:_createNicknameLabel()
    self:_createContentLabel()
    self:_createTimeLabel()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/team/ui-un-0012a.png")
    self:addChild(background)
    self:setContentSize(M.MessageBoardCellSize)
    background:setAnchorPoint(cc.p(0, 0))
    return background
end

function M:_createNicknameLabel()
    self._nicknameLabel = CommonUI:createLabel("aksdjlakjsd", 32)
    self:addChild(self._nicknameLabel)
end

function M:_createContentLabel()
    self._contentLabel = CommonUI:createLabel("", 24)
    local size = M.MessageBoardCellSize
    self._contentLabel:setWidth(size.width - 40)
    self:addChild(self._contentLabel)
    self._contentLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)
    
end

function M:_createTimeLabel()
    self._timeLabel = CommonUI:createLabel("20:20:20", 24)
    self:addChild(self._timeLabel)
end

return M