local ServerListUtils = require("ui.login.ServerListUtils")
local M = class("ui.login.ServerListChoiseLayer", function(list, onClickFun)
    return cc.LayerColor:create(cc.c4b(0, 0, 0, 150))
end)

local kBarHeight        = 80
local kBarPageCount     = 10

local kBarTag           = 1
local kContentViewTag   = 2

function M:ctor(list, onClickFun)
    assert(list and onClickFun)
    self._onClickServerIdFun = onClickFun
    self._serverList = list 
    self:_reloadShowData(0)

    -- 返回按钮
    local backButton = CommonUI:createTextButton(self, "", "ui/common/button-back.png")
    local backButtonSize = backButton:getContentSize()
    local backPosition = cc.p(backButtonSize.width/2 + 10, Screen.height-backButtonSize.height/2 - 10)
    backButton:setPosition(backPosition)
    backButton.onClicked = function()
        self:removeFromParent()
    end

    -- 标题
    local titleLabel = CommonUI:createLabel(__Localized("服务器列表"), 40)
    self:addChild(titleLabel)
    titleLabel:setPosition(cc.p(Screen.cx, backPosition.y))

    -- 推荐栏
    local serverData = ServerListUtils:getRecommendServer(self._serverList)
    local text = string.format("推荐服务器：%s", serverData.name)
    local recommendButton = CommonUI:createTextButton(self, text, "ui/login/login-up.png")
    local recommendButtonSize = cc.size(Screen.width, recommendButton:getContentSize().height)
    recommendButton:setContentSize(recommendButtonSize)
    recommendButton:setPosition(cc.p(Screen.cx, 40))
    recommendButton:needsLayout()
    recommendButton:setTag(serverData.id)
    recommendButton.onClicked = function(node)
        self:_onClickId(node:getTag())
    end

    -- 选择栏
    local selectBarSize = cc.size(Screen.width, kBarHeight)
    local selectBar = GridView.new(selectBarSize, self, 1)
    selectBar:setPosition(cc.p(0, Screen.height - backButtonSize.height - selectBarSize.height - 10))
    self:addChild(selectBar)
    selectBar:setScrollType(GridView.ScrollType.Horizontal)
    selectBar:setTag(kBarTag)

    -- table 
    local rect = selectBar:getBoundingBox() 
    local contentSize = cc.size(Screen.width, rect.y - recommendButtonSize.height)
    local contentView = GridView.new(contentSize, self, 2)
    self:addChild(contentView)
    contentView:setPosition(cc.p(0, recommendButtonSize.height))
    contentView:setTag(kContentViewTag)
    self._contentView = contentView

    Touch:registerTouchOneByOne(self, true)
end

function M:onTouchBegan(touch, event)
    return true 
end

function M:onGridViewCellCount(gridView)
    local tag = gridView:getTag()
    if kBarTag == tag then
        return math.floor(#self._serverList/kBarPageCount) + 1
    elseif kContentViewTag == tag then
         return #self._currentShowData
    end
end

function M:onGridViewLineHeight(gridView)
    local tag = gridView:getTag()
    if kBarTag == tag then
        return Screen.width / 4
    elseif kContentViewTag == tag then
        return 100
    end
end

function M:onGridViewCellAtIndex(gridView, atIndex)
    local tag = gridView:getTag()
    if kBarTag == tag then
        return self:_reloadBarCell(gridView, atIndex)
    elseif kContentViewTag == tag then
        return self:_reloadContentCell(gridView, atIndex)
    end
end

function M:_reloadBarCell(gridView, atIndex)
    local cell = gridView:dequeueCell()
    if nil == cell then
        cell = require("ui.login.ServerListChoiseBarCell").new(function(index)
            self:_onClickBarCell(index)
        end)
    end

    local startIndex, endIndex = self:_getStartEndIndex(atIndex)
    local string = string.format("%d-%d", startIndex, endIndex)
    cell:reloadCell(string, atIndex)
    return cell
end
    
function M:_reloadContentCell(gridView, atIndex)
    local cell = gridView:dequeueCell()
    if nil == cell then
        cell = require("ui.login.ServerListChoiseCell").new(function(index)
            self:_onClickContentViewCell(index)
        end)
    end

    local stateTable = 
    {
        [Enum.ServerListState.New]      = __Localized("新服"),
        [Enum.ServerListState.Fluency]  = __Localized("流畅"),
        [Enum.ServerListState.Hot]      = __Localized("火爆"),
        [Enum.ServerListState.Maintain] = __Localized("维护"),
        [Enum.ServerListState.Unknow]   = __Localized("未知"),
        [Enum.ServerListState.Recommend]  = __Localized("推荐"),
    }
    local serverData = self._currentShowData[atIndex + 1]
    local string = string.format("%d-%s  %s", atIndex+1, serverData.name, stateTable[serverData.state])
    cell:reloadCell(string, atIndex)
    return cell
end

function M:_getStartEndIndex(atIndex)
    local startIndex = 1 + atIndex * kBarPageCount
    local endIndex = (1 + atIndex) * kBarPageCount
    endIndex = math.min(endIndex, #self._serverList)
    return startIndex, endIndex
end

function M:_onClickBarCell(atIndex)
    self:_reloadShowData(atIndex)

    self._contentView:reloadData()
end

function M:_onClickContentViewCell(atIndex)
    local serverData = self._currentShowData[atIndex + 1]
    self:_onClickId(serverData.id)
end

function M:_reloadShowData(atIndex)
    local startIndex, endIndex = self:_getStartEndIndex(atIndex)
    self._currentShowData = {}
    for i=startIndex,endIndex do
        table.insert(self._currentShowData, self._serverList[i])
    end
end

function M:_onClickId(id)
    self._onClickServerIdFun(id)
    self:removeFromParent()
end

return M

