local ArmyData = require("ui.map.data-manager.ArmyData")
local ArmyDirection = require("ui.map.layer-manager.ArmyDirection")
local M = class("ui.map.layer-manager.ArmySpritesManager", function()
    return require("ui.map.layer-manager.BaseSpritesManager").new()
end)

local function _isSpriteMoving(curPos, targetPos)
	if math.floor(targetPos.x)==math.floor(curPos.x) and
			math.floor(targetPos.y)== math.floor(curPos.y) then
		return false
	end
	return true
end
 
local function _getDirection(sprite, targetPos)
	local curPosX, curPosY = sprite:getPosition()
	local prePos = cc.p(curPosX, curPosY)
	
	if not _isSpriteMoving(prePos, targetPos) then
		return sprite:getCurrentDirection()
	end
	return ArmyDirection:getDirection(prePos, targetPos)
end

function M:findArmySpriteNode(armyData)
	local uniqueId = armyData:getUniqueId()
	return self:findSpriteByUniqueId(uniqueId)
end

function M:updateArmyCount(armyData)
	if not armyData then 
		return
	end

	local sprite = self:findArmySpriteNode(armyData)
	if sprite then 
		local armyCount = armyData:getArmyCount()
		sprite:setArmyCount(armyCount)
	end
end

function M:removeArmySprite(armyData)
	if not armyData then 
		return
	end

	local uniqueId = armyData:getUniqueId()
	self:removeSpriteDataByUniqueId(uniqueId)
end

function M:updateArmySpritePosition(armyData, pos)
	local sprite = self:findArmySpriteNode(armyData)
	if sprite then 
		sprite:setArmyPosition(pos)
	end
end

function M:playAttackAnimate(armyData, pos)
	local sprite = self:findArmySpriteNode(armyData)
	if sprite then 
		local dir = _getDirection(sprite, pos)
		sprite:attack(dir)
	end
end

function M:playWaitAnimate(armyData)
	local sprite = self:findArmySpriteNode(armyData)
	if sprite then 
		local dir = sprite:getCurrentDirection()
		sprite:wait(dir)
	end
end

function M:armyDidCreate(armyData)
	self:updateData(armyData)

	local sprite = self:findArmySpriteNode(armyData)
	if not sprite then 
		return
	end

	local defalutDir = ArmyDirection:getDefalutDirection()
	sprite:wait(defalutDir)
end

function M:armyDidMove(armyData)
	local dir
	local sprite = self:findArmySpriteNode(armyData)
	if sprite then 
		local pos = armyData:getPosition()
		dir = _getDirection(sprite, pos)
	end

	self:updateData(armyData)

	if dir then 
		sprite:walk(dir)
	end
end

function M:setSpriteWait(armyData)
	local sprite = self:findArmySpriteNode(armyData)
	if sprite then 
		local dir = sprite:getCurrentDirection()
		sprite:wait(dir)
	end
end

function M:update(dt)
	self:iterativeDatas(function(data, sprite)
		sprite:update(dt)
	end)
end

------------ BaseSpritesManager delegate began
function M:cellPositionForData(armyData)
    return armyData:getPosition()
end

function M:cellUniqueIdForData(armyData)
    return armyData:getUniqueId()
end

function M:cellSpriteForData(armyData)
    return require("ui.map.layer-manager.ArmySpriteNode").new()
end

function M:cellReloadForData(armyData, sprite)
    sprite:reloadData(armyData)
end
------------ BaseSpritesManager delegate end

return M
