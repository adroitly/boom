local BackgroundLayer = require("ui.common.BackgroundLayer")
local WikiConfigReader = require("ui.wiki.data-manager.WikiConfigReader")
local WikiDataManager = require("ui.wiki.data-manager.WikiDataManager")
local WikiTitleCell = require("ui.wiki.layer-manager.WikiTitleCell")
local M = class("ui.wiki.MainLayer", function()
    return cc.Layer:create()
end)

local function _newTitleData(id, title)
    return {id = id, title = title}
end

function M:ctor()
    self._wikiTitleDataList = {}
    self._currentHeight = 0
    self._curentPageLevel = 1
    self:_createBackground()
    self:_createSearchTextInput()
    self:_createTitle()
    self:_createButton()
    self:_createTableView()
    self:_reloadData()
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "百科")
    backgroundLayer:setBackButtonCallback(function()
        if self._curentPageLevel == 1 then
            self:removeFromParent()
            return
        end
        self:_reloadData()
    end)
    self._currentHeight = self._currentHeight + BackgroundLayer.TitleHeight
end

function M:_createSearchTextInput()
    local tfBackground = cc.Sprite:create("ui/mail/mail-input.png")
    self:addChild(tfBackground)
    Layout:layout(tfBackground, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))

    local TextInput = require("ui.common.InputUI")
    self._searchTextInput = TextInput.new(26)
    self._searchTextInput:setPlaceHolder(__Localized("请输入想问的问题"))
    self._searchTextInput:setMaxLength(14)
    self._searchTextInput:setAnchorPoint(cc.p(0, 0.5))
    tfBackground:addChild(self._searchTextInput)
    Layout:layout(self._searchTextInput, tfBackground:getContentSize(), Layout.left_center, cc.p(10, 0))

    local searchButton = CommonUI:createTextButton(self, __Localized("搜索"), "ui/login/login-bt.png")
    Layout:layout(searchButton, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
    searchButton.onClicked = function()
        local searchStr = self._searchTextInput:getString()
        local layer = require("ui.wiki.layer-manager.WikiSearchLayer").new(searchStr)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
    end

    self._currentHeight = self._currentHeight + tfBackground:getContentSize().height
end

function M:_reloadData(id)
    local title = id and WikiConfigReader:getH1Title(id) or __Localized("常见问题")
    self._titleLabel:setString(title)

    self._wikiTitleDataList = {}
    local dataList = WikiDataManager:getDataList()
    local wikiDataList = dataList[title]
    if wikiDataList then
        -- 二级标题
        for _, id in ipairs(wikiDataList.h2IDList) do
            local h2Title = WikiConfigReader:getH2Title(id)
            local titleData = _newTitleData(id, h2Title)
            table.insert(self._wikiTitleDataList, titleData)
        end
        self._curentPageLevel = 2
    else
        -- 一级标题
        for title, data in pairs(dataList) do
            local titleData = _newTitleData(data.h1ID, title)
            table.insert(self._wikiTitleDataList, titleData)
        end
        -- 一级标题排序
        table.sort(self._wikiTitleDataList, function(a, b)
            return a.id < b.id
        end)
        self._curentPageLevel = 1
    end
    self._tableView:reloadData()
end

function M:_createTitle()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    Layout:layout(background, Screen.size, Layout.center_top, self._currentHeight)

    self._titleLabel = CommonUI:createLabel(__Localized("常见问题"))
    background:addChild(self._titleLabel)
    Layout:layout(self._titleLabel, background:getContentSize(), Layout.center)

    self._currentHeight = self._currentHeight + background:getContentSize().height
end

function M:_createButton()
    local button = CommonUI:createTextButton(self, "联系我们", "ui/login/login-up.png", "ui/login/login-down.png")
    Layout:layout(button, Screen.size, Layout.center_bottom)
    self._currentHeight = self._currentHeight + BackgroundLayer.BottomHeight
    button.onClicked = function()
        local layer = require("ui.wiki.layer-manager.ConnectOurLayer").new()
        Director:getRunningScene():addChild(layer)
    end
end


function M:_createTableView()
    local viewSize = cc.size(WikiTitleCell.WikiTitleCellSize.width, Screen.height - self._currentHeight)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
    self._tableView:setPosition(cc.p(0.5 * (Screen.width - viewSize.width), BackgroundLayer.BottomHeight))
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    local data = self._wikiTitleDataList[idx + 1]
    if self._curentPageLevel == 2 then
        local layer = require("ui.wiki.layer-manager.WikiContentLayer").new(data.id)
        local scene = cc.Director:getInstance():getRunningScene()
        scene:addChild(layer)
        return
    end
    self:_reloadData(data.id)
end

function M:onTableViewCellSize(tableView, idx)
    return WikiTitleCell.WikiTitleCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = WikiTitleCell.new()
    end
    local data = self._wikiTitleDataList[idx + 1]
    cell:reset(data.title)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._wikiTitleDataList)
end

return M