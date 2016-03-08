local ArmyDirection = require("ui.map.layer-manager.ArmyDirection")
local M = class("ui.map.layer-manager.ArmyAnimationSprite", function()
        return SpriteAnimate.new()
end)

local kDefaultFrameRate = 1 / 6
function M:ctor(plist)
    self:init(plist)
    self:setFrameRate(kDefaultFrameRate)

    self:setFinishCallback(function()
        self:_finishCallback()  
    end)

    self:reloadData(plist)
end

function M:reloadData(plist)
    self:reloadPlist(plist)

    self._resId = self:_getResId(plist)
end

function M:attack(dir)
    self:playAnim(Enum.ArmyAnimName.Attack, dir)
end

function M:wait(dir)
    self:playAnim(Enum.ArmyAnimName.Wait, dir)
end

function M:walk(dir)
    self:playAnim(Enum.ArmyAnimName.Walk, dir)
end

function M:die(dir)
    self:playAnim(Enum.ArmyAnimName.Die, dir)
end

function M:getArmyDir()
    return self._armyDir
end

function M:playAnim(animName, armyDir)
    self._armyDir = armyDir
    self._animName = animName

    local convertDir, isFlip = ArmyDirection:getConvertDir(armyDir)
    self:setFlippedX(isFlip)
    
    local formatAnimName = string.format("%s_%s_%s_", self._resId, animName, convertDir)
    local state = self:getState()
    if state == formatAnimName then
        return
    end
    self:changeState(formatAnimName)
end

function M:_finishCallback()
    if Enum.ArmyAnimName.Attack == self._animName then 
        self:wait(self:getArmyDir())
    end
end

function M:_getResId(plist)
    local _, _, _, resId = string.find(plist, "(.+)/(.+).plist")
    return resId
end

return M