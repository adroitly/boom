local BackgroundLayer = require("ui.common.BackgroundLayer")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local M = class("ui.team.layer-manager.SoldierInfoLayer" , function ()
    return cc.Layer:create()
end)

local kSpaceY = 20

function M:ctor(soldierType)
    self._currentHeight = 0
    self:_createBackgound()
    self:_createIcon(soldierType)
    self:_createNameLabel(soldierType)
    self:_createRestrainLabel(soldierType)
    self:_createLevelLabel(soldierType)
end

function M:_createBackgound()
    local background = BackgroundLayer.new(self, __Localized("兵种信息"))
    background:setBackButtonCallback(function ()
        self:removeFromParent()
    end)
    self._currentHeight = BackgroundLayer.TitleHeight + kSpaceY
end

function M:_createIcon(soldierType)
    local resType = SoldierConfigReader:getType(soldierType)
    local path = string.format("%d.png", resType)
    local frame = CommonUI:createSpriteFrameTinyName("soldier",path)
    local headIcon = cc.Sprite:createWithSpriteFrame(frame)
    self:addChild(headIcon)
    Layout:layout(headIcon, Screen.size, Layout.center_top, cc.p(0, self._currentHeight))
    self._currentHeight = self._currentHeight + headIcon:getContentSize().height + kSpaceY
end

function M:_createNameLabel(soldierType)
    local name = SoldierConfigReader:getName(soldierType)
    local label = CommonUI:createLabel(name, 30)
    self:addChild(label)
    Layout:layout(label, Screen.size, Layout.center_top, cc.p(0, self._currentHeight))
    self._currentHeight = self._currentHeight + label:getContentSize().height + kSpaceY
end

function M:_createRestrainLabel(soldierType)
    -- local restrain = SoldierConfigReader:getRestrain(soldierType)
    -- local tbl = String:split(restrain, ";")
    local restrainSoldierName = string.format(__Localized("克制兵种：%s"), SoldierConfigReader:getRestraindesc(soldierType))
    -- for k, rsType in ipairs(tbl) do
    --     local soldierName = SoldierConfigReader:getNameByType(tonumber(rsType))
    --     if k == 1 then
    --         restrainSoldierName = restrainSoldierName .. soldierName
    --     else
    --         restrainSoldierName = restrainSoldierName .. "、" .. soldierName
    --     end
    -- end
    local label = CommonUI:createLabel(restrainSoldierName, 30)
    self:addChild(label)
    Layout:layout(label, Screen.size, Layout.center_top, cc.p(0, self._currentHeight))
    self._currentHeight = self._currentHeight + label:getContentSize().height + kSpaceY
end

function M:_createLevelLabel(soldierType)
    local spaceX = 20
    local curLevel = SoldierConfigReader:getLevel(soldierType)
    local curLevelStr = "当前等级：" .. curLevel
    local curLevelLabel = CommonUI:createLabel(curLevelStr, 38)
    self:addChild(curLevelLabel)
    Layout:layout(curLevelLabel, Screen.size, Layout.left_top, cc.p(spaceX, self._currentHeight))
    curLevelLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)
    local curLevelInfoStr = self:_getAttrInfoString(soldierType)
    local curLevelInfoLabel = CommonUI:createLabel(curLevelInfoStr, 30)
    self:addChild(curLevelInfoLabel)
    Layout:layout(curLevelInfoLabel, Screen.size, Layout.left_top, cc.p(spaceX, self._currentHeight + curLevelLabel:getContentSize().height))
    curLevelInfoLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)

    local nextLevelSoldierType = soldierType + 1
    local isHasConfigData = SoldierConfigReader:isHasConfigData(nextLevelSoldierType)
    if not isHasConfigData then
        Layout:layout(curLevelLabel, Screen.size, Layout.center_top, cc.p(0, self._currentHeight))
        curLevelLabel:setHorizontalAlignment(Enum.TextHAlignment.Center)
        Layout:layout(curLevelInfoLabel, Screen.size, Layout.center_top, cc.p(0, self._currentHeight + curLevelLabel:getContentSize().height))
        curLevelInfoLabel:setHorizontalAlignment(Enum.TextHAlignment.Center)
        return
    end

    local nextLevel = SoldierConfigReader:getLevel(nextLevelSoldierType)
    local nextLevelStr = "下一等级：" .. nextLevel
    local nextLevelLabel = CommonUI:createLabel(nextLevelStr, 38)
    self:addChild(nextLevelLabel)
    local labelWidth = nextLevelLabel:getContentSize().width
    Layout:layout(nextLevelLabel, Screen.size, Layout.left_top, cc.p(Screen.width - labelWidth - spaceX, self._currentHeight))
    nextLevelLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)

    local nextLevelInfoStr = self:_getAttrInfoString(nextLevelSoldierType)
    local nextLevelInfoLabel = CommonUI:createLabel(nextLevelInfoStr, 30)
    self:addChild(nextLevelInfoLabel)
    labelWidth = nextLevelInfoLabel:getContentSize().width
    Layout:layout(nextLevelInfoLabel, Screen.size, Layout.left_top, cc.p(Screen.width - labelWidth - spaceX, self._currentHeight + nextLevelLabel:getContentSize().height))
    nextLevelInfoLabel:setHorizontalAlignment(Enum.TextHAlignment.Left)
end

function M:_getAttrInfoString(soldierType)
    local infoStr = ""
    local attack = SoldierConfigReader:getAttack(soldierType)
    infoStr = "攻击：" .. attack .. "\n"
    local hp = SoldierConfigReader:getHP(soldierType)
    infoStr = infoStr .. "生命：" .. hp .. "\n"
    local defense = SoldierConfigReader:getDefense(soldierType)
    infoStr = infoStr .. "防御：" .. defense .. "\n"
    local hitRatio = SoldierConfigReader:getHitRatio(soldierType)
    infoStr = infoStr .. "命中：" .. hitRatio .. "\n"
    local dodge = SoldierConfigReader:getDodge(soldierType)
    infoStr = infoStr .. "闪避：" .. dodge .. "\n"
    return infoStr
end


return M