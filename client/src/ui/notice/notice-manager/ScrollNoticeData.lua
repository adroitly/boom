local ElementText = require("ui.common.richlabel.ElementText")
local M = class("ui.notice.notice-manager.ScrollNoticeData")

local m_colorStart = "["
local m_textStart = " "
local m_colorEnd = "]"

function M:ctor(count)
    self.insertTime = PlayerData:getServerTime()
    self.count = count
    self.isShow = false
end

function M:createByMsg(msg, count)
    assert(msg and count)
    local class = M.new(count)
    class.text = msg
    return class
end

function M:createByServer(msgTable)
    local class = M.new(1)
    assert(msgTable.priority and msgTable.text)
    Table:copy(class, msgTable)
    return class
end

function M:setShowed(state)
    self.isShow = state
end

function M:isShowed()
    return self.isShow
end


function M:getCount()
    return self.count
end

function M:lessCount()
    self.count = self.count - 1
end

function M:getInsertTime()
    return self.insertTime
end


function M:updateStartShowTime()
    self.startShowTime = PlayerData:getServerTime()
end

function M:getStartShowTime()
    return self.startShowTime or 0
end

function M:getShowedTime()
    if 0 == self:getStartShowTime() then
        return 0
    end
    return PlayerData:getServerTime() - self:getStartShowTime()
end

function M:getText()
    return self.text
end

function M:getPriority()
    return self.priority
end

local function _pushElement(elementList, showTextTable, lastIndex, index, color)
    local text = Utils:mergeTableToChar(showTextTable, lastIndex + 1, index - 1)
    local element = ElementText:createLabel(text, 24, color)
    table.insert(elementList, element)
end

function M:getElementList()
    local elementList = {}
    local showTextTable = Utils:getCharToTable(self:getText())
    local lastIndex = 0
    local lastColor = Enum.Color.Normal
    local isEnd = true
    for index,char in ipairs(showTextTable) do
        if m_colorStart == char then
            local color = true == isEnd and Enum.Color.Normal or lastColor
            _pushElement(elementList, showTextTable, lastIndex, index, color)
            lastIndex = index
            isEnd = false
        elseif m_textStart == char then
            local color = Utils:mergeTableToChar(showTextTable, lastIndex + 1, index - 1)
            lastColor = Enum.Color[String:upperFirstChar(color)]
            lastIndex = index
        elseif m_colorEnd == char then
            _pushElement(elementList, showTextTable, lastIndex, index, lastColor)
            lastIndex = index
            isEnd = true
        end
    end
    _pushElement(elementList, showTextTable, lastIndex, #showTextTable + 1, Enum.Color.Normal)
    return elementList
end



return M