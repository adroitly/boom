local M = class("ui.notice.notice-manager.ScrollNoticeManager", function()
    return cc.Node:create()
end)

local m_liveTime = 5

function M:addNotice(scrollNoticeData)
    table.insert(self._scrollNoticeDataList, scrollNoticeData)
    self:_sortData()
end

function M:getShowingScrollNoticeData()
    return self._showingScrollNoticeData
end

function M:ctor()
    self:_init()
    Event:registerNodeEvent(self)
end

function M:onExit()
    Timer:removeTimer(self)
    self._scrollNoticeDataList = nil
end

function M:onUpdate(dt)
    local scrollNoticeData = self._scrollNoticeDataList[1]
    if nil == scrollNoticeData then
        self:_showNoticeAction(nil)
        return
    end
    if self._showScrollNoticeData ~= scrollNoticeData then
        self._showScrollNoticeData = scrollNoticeData
        self._showScrollNoticeData:updateStartShowTime()
        self:_showNoticeAction(scrollNoticeData)
    end
    if scrollNoticeData:getShowedTime() >= m_liveTime then
        if scrollNoticeData:getCount() > 1 then
            scrollNoticeData:lessCount()
            scrollNoticeData:updateStartShowTime()
            scrollNoticeData:setShowed(false)
        else
            table.remove(self._scrollNoticeDataList, 1)
            self._showScrollNoticeData = nil
            self:_checkShowEnd()
        end
    end
end

function M:_sortData()
    local function _sort(a, b)
        local compire
        if a:getPriority() == b:getPriority() then
            return a:getInsertTime() < b:getInsertTime()
        else
            return a:getPriority() > b:getPriority()
        end
        return compire
    end
    --
    local showingScrollNoticeData = self._scrollNoticeDataList[1]
    table.remove(self._scrollNoticeDataList, 1)
    table.sort(self._scrollNoticeDataList, _sort)
    table.insert(self._scrollNoticeDataList, 1, showingScrollNoticeData)
end

function M:_init()
    self._scrollNoticeDataList = {}
    Timer:addTimer(self)
end

function M:_checkShowEnd()
    local noticeNumber = table.getn(self._scrollNoticeDataList)
    if 0 == noticeNumber then
        self:_showNoticeAction(nil)
    end
end

function M:_showNoticeAction(scrollNoticeData)
    self._showingScrollNoticeData = scrollNoticeData
end

return M