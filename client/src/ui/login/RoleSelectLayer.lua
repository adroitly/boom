local M = class("ui.login.RoleSelectLayer", function()
    return cc.Layer:create()
end)
-- 男
-- 23500    曹操
-- 23400    刘备
-- 20100    吕布
-- 23900    孙权
-- 女
-- 26200    貂蝉
-- 25400    黄月英

local kKingId = {
    [Enum.Sex.Male] = {20100, 23400, 23500, 23900},
    [Enum.Sex.Female] = {25400, 26200}
}

local function _getPosition(idx)
    local space = 200
    local pos = {
        cc.p(0, -space),
        cc.p(space, 0),
        cc.p(0, space),
        cc.p(-space, 0)
    }
    return pos[idx]
end

local function _getFileName(icon)
    return string.format("ui/city/inner-city-king-%d.png", icon)
end

local function _newRoleData(icon, sprite)
    return {icon = icon, sprite = sprite}
end

function M:showMaleView(isShow)
    self._selectedSex = isShow and Enum.Sex.Male or Enum.Sex.Female
    self._maleLayer:setVisible(isShow)
    if not self._femaleLayer then
        self:_createFemaleRoleLayer()
    end
    self._femaleLayer:setVisible(not isShow)
end

function M:getSelectedSex()
    return self._selectedSex
end

function M:getSelectedIcon()
    local list = self:_getRoleList(self._selectedSex)
    return list[1].icon
end

function M:ctor()
    self._selectedSex = Enum.Sex.Male
    self:_createMaleRoleLayer()
    self:_createSelectArrows()

    Touch:registerTouchOneByOne(self, true)
end

function M:onTouchBegan(touch, event)
    self._currentTouchX = touch:getLocation().x
    return true
end

function M:onTouchMoved(touch, event)
end

function M:onTouchEnded(touch, event)
    local dis = 50
    local offsetX = self._currentTouchX - touch:getLocation().x
    if offsetX > dis then
        self:_turnLeft()
    elseif offsetX < -dis then
        self:_turnRight()
    end
    self._currentTouchX = nil

end

function M:onTouchCancelled(touch, event)
    self:onTouchEnded(touch, event)
end


function M:_createSelectArrows()
    local lArrow = CommonUI:createTextButton(self, "", "ui/city/arrow.png")
    lArrow:setRotation(180)
    lArrow:setPosition(cc.p(Screen.cx - 200, Screen.cy - 100))
    lArrow.onClicked = function()
        self:_turnLeft()
    end

    local rArrow = CommonUI:createTextButton(self, "", "ui/city/arrow.png")
    rArrow:setPosition(cc.p(Screen.cx + 200, Screen.cy - 100))
    rArrow.onClicked = function()
        self:_turnRight()
    end
end

function M:_createMaleRoleLayer()
    self._maleLayer = cc.Layer:create()
    self:addChild(self._maleLayer)

    self._maleRoleList = {}
    local list = kKingId[Enum.Sex.Male]
    for idx, id in ipairs(list) do
        local sprite = cc.Sprite:create(_getFileName(id))
        self._maleLayer:addChild(sprite)
        table.insert(self._maleRoleList, _newRoleData(id, sprite))
    end
    self:_updateRolePos(Enum.Sex.Male)
end

function M:_createFemaleRoleLayer()
    self._femaleLayer = cc.Layer:create()
    self:addChild(self._femaleLayer)

    self._femaleRoleList = {}
    local list = kKingId[Enum.Sex.Female]
    for idx, id in ipairs(list) do
        local sprite = cc.Sprite:create(_getFileName(id))
        self._femaleLayer:addChild(sprite)
        table.insert(self._femaleRoleList, _newRoleData(id, sprite))
    end
    self:_updateRolePos(Enum.Sex.Female)
end

function M:_updateRolePos(sex)
    local list = self:_getRoleList(sex)
    for idx, roleData in ipairs(list) do
        local pos = _getPosition(idx)
        local sprite = roleData.sprite
        sprite:setScale(idx == 1 and 1 or 0.6)
        sprite:setPosition(cc.p(Screen.cx + pos.x, Screen.cy + pos.y + 100))
    end
end

function M:_getRoleList(sex)
    if sex == Enum.Sex.Male then
        return self._maleRoleList
    end
    return self._femaleRoleList
end

function M:_turnLeft()
    local list = self:_getRoleList(self._selectedSex)
    local roleData = list[1]
    table.remove(list, 1)
    table.insert(list, roleData)
    self:_updateRolePos(self._selectedSex)
end

function M:_turnRight()
    local list = self:_getRoleList(self._selectedSex)
    local roleData = list[#list]
    table.remove(list, #list)
    table.insert(list, 1, roleData)
    self:_updateRolePos(self._selectedSex)
end

return M