local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local ArmyData = require("ui.map.data-manager.ArmyData")
local ArmyDirection = require("ui.map.layer-manager.ArmyDirection")
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = class("ui.map.layer-manager.ArmySpriteNode", function()
	return cc.Node:create()
end)
	
function M:ctor()
	-- local size = self._animationSprite:getContentSize()
	local size = cc.size(MapConfig.tileHeight, MapConfig.tileHeight)
	self:setContentSize(size)
	self:setAnchorPoint(cc.p(0.5, 0.35))
	self._contentSizeCache = size

	local pos = cc.p(size.width/2, size.height/2)
	self._selectSprite = cc.Sprite:create("ui/army-select-test.png")
    self:addChild(self._selectSprite)
    self._selectSprite:setPosition(cc.p(pos.x, pos.y*0.4))	

	self._animationSprite = self:_createAnimationSprite()
	self:addChild(self._animationSprite)
	self._animationSprite:setPosition(pos)

	local armyCountLabel = CommonUI:createLabel("1000", 30)
	self:addChild(armyCountLabel)
	armyCountLabel:setPosition( cc.p(size.width/2, -10) )
	self._armyCountLabel = armyCountLabel
	-- self._armyCountLabel:setTextColor(cc.c4b(0, 0, 0, 255))

	local Constant = require("ui.map.layer-manager.ArmyDirection")
	self:wait(Constant.RightTop)

	self:setLocalZOrder(Enum.ZOrder.Army)
	self._x, self._y = self:getPosition()
end

function M:getContentSizeCache()
	return self._contentSizeCache
end

function M:getArmyPosition()
	return self._x, self._y
end

function M:setArmyPosition(pos)
	self._x = pos.x
	self._y = pos.y
	self:setPosition(pos)
end

function M:setArmyCount(count)
	local text = string.format("%d", count)
	self._armyCountLabel:setString(text)
end

function M:update(dt)
	self._animationSprite:update(dt)
end

function M:attack(armyDir)
	self._animationSprite:playAnim(Enum.ArmyAnimName.Attack, armyDir)
end

function M:wait(armyDir)
	self._animationSprite:playAnim(Enum.ArmyAnimName.Wait, armyDir)
end

function M:walk(armyDir)
	self._animationSprite:playAnim(Enum.ArmyAnimName.Walk, armyDir)
end

function M:die(armyDir)
	self._animationSprite:playAnim(Enum.ArmyAnimName.Die, armyDir)
end

function M:getCurrentDirection()
	return self._animationSprite:getArmyDir()
end

function M:reloadData(armyData)
	if self._armyData==armyData then
		return
	end
	self:setSelected(armyData:isSelected())

	local teamData = armyData:getTeamData()
	local soldierType = teamData:getSoldierType()
	local resType = SoldierConfigReader:getType(soldierType)
	local plist = string.format("army/%d/%d.plist", resType, resType)
	self._animationSprite:reloadData(plist)

	self._armyData = armyData
	self:setArmyPosition(armyData:getPosition())
	self:setVisible(true)
	self:setArmyCount(armyData:getArmyCount())
end

function M:setSelected(isSelected)
    self._selectSprite:setVisible(isSelected)
end

function M:_createAnimationSprite()
	local resId = 18000
	local plist = string.format("army/%d/%d.plist", resId, resId)
	return require("ui.map.layer-manager.ArmyAnimationSprite").new(plist)
end

return M