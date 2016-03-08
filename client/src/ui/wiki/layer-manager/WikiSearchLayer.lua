local WikiTitleCell = require("ui.wiki.layer-manager.WikiTitleCell")
local WikiDataManager = require("ui.wiki.data-manager.WikiDataManager")
local BackgroundLayer = require("ui.common.BackgroundLayer")
local WikiConfigReader = require("ui.wiki.data-manager.WikiConfigReader")
local M = class("ui.wiki.layer-manager.WikiSearchLayer", function()
    return cc.Layer:create()
end)

function M:ctor(searchStr)
    self._wikiIdList = {}
    self:_createBackground()
    self:_createSearchTextInput()
    self:_createTableView()
    self:_searchByStr(searchStr)
end

function M:_createBackground()
    local backgroundLayer = BackgroundLayer.new(self, "搜索")
    backgroundLayer:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createSearchTextInput()
    self._tfBackground = cc.Sprite:create("ui/mail/mail-input.png")
    self:addChild(self._tfBackground)
    Layout:layout(self._tfBackground, Screen.size, Layout.left_top, cc.p(0, BackgroundLayer.TitleHeight))

    local TextInput = require("ui.common.InputUI")
    local searchTextInput = TextInput.new(26)
    searchTextInput:setPlaceHolder(__Localized("请输入想问的问题"))
    searchTextInput:setMaxLength(14)
    searchTextInput:setAnchorPoint(cc.p(0, 0.5))
    self._tfBackground:addChild(searchTextInput)
    Layout:layout(searchTextInput, self._tfBackground:getContentSize(), Layout.left_center, cc.p(10, 0))

    local searchButton = CommonUI:createTextButton(self, __Localized("搜索"), "ui/login/login-bt.png")
    Layout:layout(searchButton, Screen.size, Layout.right_top, cc.p(0, BackgroundLayer.TitleHeight))
    searchButton.onClicked = function()
        local searchStr = searchTextInput:getString()
        self:_searchByStr(searchStr)
    end
end

function M:_searchByStr(str)
    self._wikiIdList = WikiDataManager:findMatchTitle(str)
    self._tableView:reloadData()
end

function M:_createTableView()
    local viewSize = cc.size(WikiTitleCell.WikiTitleCellSize.width, Screen.height - BackgroundLayer.TitleHeight - self._tfBackground:getContentSize().height)
    self._tableView = require("share.TableView").new(viewSize, self)
    self:addChild(self._tableView)
end

function M:onTableViewCellTouched(tableView, cell)
    local idx = cell:getIdx()
    local id = self._wikiIdList[idx + 1]
    local layer = require("ui.wiki.layer-manager.WikiContentLayer").new(id)
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(layer)
end

function M:onTableViewCellSize(tableView, idx)
    return WikiTitleCell.WikiTitleCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = WikiTitleCell.new()
    end
    local id = self._wikiIdList[idx + 1]
    print("=========>", id)
    local h2Title = WikiConfigReader:getH2Title(id)
    cell:reset(h2Title)
    return cell
end

function M:onTableViewCellCount(tableView)
    return table.getn(self._wikiIdList)
end

return M