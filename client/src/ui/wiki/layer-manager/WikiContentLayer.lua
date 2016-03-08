local WikiDataManager = require("ui.wiki.data-manager.WikiDataManager")
local WikiConfigReader = require("ui.wiki.data-manager.WikiConfigReader")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local M = class("ui.wiki.layer-manager.WikiContentLayer", function()
    return cc.Layer:create()
end)

local kSpace = 40

local function _newRowLabelData()
    local rowLabelData = {}
    rowLabelData.labelList = {}
    rowLabelData.height = 0
    return rowLabelData
end

function M:ctor(id)
    self._currentHeight = 0
    self:_createBackground()
    self:_createScrollView()
    self:_createTitle(id)
    self:_createDesc(id)
    self:_createFormLabels(id)
    self:_updateScrollView(id)
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "问题")
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createScrollView()
    local viewSize = cc.size(Screen.width - 80, Screen.height - BackgroundLayer.TitleHeight)
    self._scrollView = cc.ScrollView:create(viewSize)
    self:addChild(self._scrollView)
    self._scrollView:setPosition(cc.p(0, 0))
    self._scrollView:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
end

function M:_createTitle(id)
    local titleStr = WikiConfigReader:getH2Title(id)
    self._titleLabel = CommonUI:createLabel(titleStr, 30)
    self._scrollView:getContainer():addChild(self._titleLabel)
    self:_currentHeightAdd(self._titleLabel:getContentSize().height)
end

function M:_createDesc(id)
    local descStr = WikiConfigReader:getDesc(id)
    if not descStr then
        return
    end
    local viewSize = self._scrollView:getViewSize()
    self._descLabel = CommonUI:createLabel(descStr, 24)
    self._descLabel:setWidth(viewSize.width)
    self._descLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)
    self._scrollView:getContainer():addChild(self._descLabel)
    self:_currentHeightAdd(self._descLabel:getContentSize().height)
end

function M:_createFormLabels(id)
    local formStr = WikiConfigReader:getForm(id)
    if not formStr then
        return
    end
    local formTbl = WikiDataManager:formatFormStr(formStr)
    local width = self._scrollView:getViewSize().width
    self._formLabelList = {}
    local nRows = table.getn(formTbl)
    -- 第一行为系数，不需要显示
    for rowIdx = 2, nRows do
        local rowLabelData = _newRowLabelData()
        local rowsValue = formTbl[rowIdx]
        for colIdx, colValue in ipairs(rowsValue) do
            local label = CommonUI:createLabel(colValue, 24)
            label:setWidth(width * tonumber(formTbl[1][colIdx]))
            self._scrollView:getContainer():addChild(label)
            table.insert(rowLabelData.labelList, label)
            local labelHeight = label:getContentSize().height
            rowLabelData.height = math.max(rowLabelData.height, labelHeight)
        end
        table.insert(self._formLabelList, rowLabelData)
        self:_currentHeightAdd(rowLabelData.height + kSpace)
    end
    -- 添加首行头部间隔
    self:_currentHeightAdd(kSpace)
end

function M:_updateTitlePosition()
    self._titleLabel:setAnchorPoint(cc.p(0, 0.5))
    local titleSize = self._titleLabel:getContentSize()
    local posY = self:_getInitY() - titleSize.height * 0.5
    self._titleLabel:setPosition(cc.p(0, posY))
end

function M:_updateDescLabelPosition()
    if not self._descLabel then
        return
    end
    self._descLabel:setAnchorPoint(cc.p(0, 0.5))
    local descSize = self._descLabel:getContentSize()
    local titleSize = self._titleLabel:getContentSize()
    local posY = self:_getInitY() - descSize.height * 0.5 - titleSize.height
    self._descLabel:setPosition(cc.p(0, posY))
end

function M:_updateFormLabelsPosition(id)
    local formStr = WikiConfigReader:getForm(id)
    if not formStr then
        return
    end
    local viewSize = self._scrollView:getViewSize()
    local viewWidth = viewSize.width
    local formTbl = WikiDataManager:formatFormStr(formStr)
    local titleHeight = self._titleLabel:getContentSize().height
    local descHeight = self._descLabel and self._descLabel:getContentSize().height or 0
    local posY = self:_getInitY() - descHeight - titleHeight
    for _, rowLabelData in ipairs(self._formLabelList) do
        local labelList = rowLabelData.labelList
        local height = rowLabelData.height
        local y = posY - height * 0.5 - kSpace
        for idx, label in ipairs(rowLabelData.labelList) do
            local x = 0
            local ratio = self:_getRadioByIdx(id, idx)
            if idx == 1 then
                x = viewWidth * ratio * 0.5
                label:setHorizontalAlignment(Enum.TextHAlignment.Center)
            else
                label:setHorizontalAlignment(Enum.TextHAlignment.Left)
                x = viewWidth * ratio
                label:setAnchorPoint(cc.p(0, 0.5))
            end
            label:setPosition(cc.p(x, y))
        end
        posY = posY - height - kSpace
    end
end

function M:_updateFormPosition(id)
    if not self._formLabelList then
        return
    end
    local lineWidth = 2
    local titleHeight = self._titleLabel:getContentSize().height
    local descHeight = self._descLabel and self._descLabel:getContentSize().height or 0
    local formHeight = self._currentHeight - descHeight - titleHeight
    local posY = self:_getInitY() - descHeight - titleHeight
    local viewSize = self._scrollView:getViewSize()
    local nCols = 0
    local nRows = table.getn(self._formLabelList)
    -- 画横线
    for row, rowLabelData in ipairs(self._formLabelList) do
        -- 最后一行不需要
        if row == nRows then
            break
        end
        local rowLabelCount = table.getn(rowLabelData.labelList)
        nCols = math.max(rowLabelCount, nCols)
        local height = rowLabelData.height
        local drawNode = cc.DrawNode:create() 
        drawNode:drawLine(cc.p(0, 0), cc.p(viewSize.width, 0), cc.c4f(1, 1, 1, 1))
        self._scrollView:getContainer():addChild(drawNode)
        if row == 1 then
            posY = posY - height - kSpace * 1.5
        else
            posY = posY - height - kSpace
        end
        drawNode:setPosition(cc.p(0, posY))
    end
    local initY = 0
    local viewSize = self._scrollView:getViewSize()
    local viewHeight = viewSize.height
    local initY = viewHeight - self._currentHeight
    initY = initY > 0 and initY or 0
    -- 画列线
    for i = 2, nCols do
        local radio = self:_getRadioByIdx(id, i)
        local drawNode = cc.DrawNode:create() 
        drawNode:drawLine(cc.p(0, 0), cc.p(0, formHeight - kSpace), cc.c4f(1, 1, 1, 1))
        drawNode:setPosition(cc.p(radio * viewSize.width, initY + kSpace * 0.5))
        self._scrollView:getContainer():addChild(drawNode)
    end
    -- 画外框
    local rectDrawNode = cc.DrawNode:create()
    rectDrawNode:drawRect(cc.p(0, 0), cc.p(viewSize.width - lineWidth * 2, formHeight - kSpace), cc.c4f(1, 1, 1, 1))
    self._scrollView:getContainer():addChild(rectDrawNode)
    rectDrawNode:setPosition(cc.p(lineWidth, initY + kSpace * 0.5))
end

function M:_updateScrollView(id)
    local viewSize = self._scrollView:getViewSize()
    local viewHeight = viewSize.height
    self._scrollView:setContentSize(cc.size(viewSize.width, self._currentHeight))
    local offsetY = viewHeight - self._currentHeight
    if offsetY > 0 then
        self._scrollView:setContentSize(viewSize)
    else
        self._scrollView:setContentOffset(cc.p(0, offsetY))
    end
    self._scrollView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), Screen.height - BackgroundLayer.TitleHeight - viewHeight))
    self:_updateFormLabelsPosition(id)
    self:_updateDescLabelPosition()
    self:_updateTitlePosition()
    self:_updateFormPosition(id)
end

function M:_getRadioByIdx(id, idx)
    local formStr = WikiConfigReader:getForm(id)
    local formTbl = WikiDataManager:formatFormStr(formStr)
    if idx == 1 then
        return tonumber(formTbl[1][1])
    end
    local ratio = 0
    for i = idx - 1, 1, -1 do
        ratio = ratio + tonumber(formTbl[1][i])
    end
    return ratio
end

function M:_currentHeightAdd(value)
    self._currentHeight = self._currentHeight + value
end

function M:_getInitY()
    local viewSize = self._scrollView:getViewSize()
    local viewHeight = viewSize.height
    if viewHeight > self._currentHeight then
        return viewHeight
    end
    return self._currentHeight
end

return M