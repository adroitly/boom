
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local M = class("ui.common.HeroIcon" , function()
	return cc.Node:create()
end)

function M:getContentSize()
	return self._iconSize
end

function M:setupClick(callback)
	self._clickbutton.onClicked = callback
end

function M:setupLongTouch(callback)
	self._clickbutton.onLongTouch = callback
end

function M:getHeroId()
	return self._heroData:getHeroId()
end

function M:getHeroData()
	return self._heroData
end

function M:setSwallow(swallow)
	Touch:removeTouchOneByOne(self._clickbutton)
	Touch:registerTouchOneByOne(self._clickbutton, swallow)
end


function M:reload(heroData)
	self._heroData = heroData
	self:_updateButtonShow()
	self:_updateHeroState()
	self:_updateHeroName()
	self:_updateHeroLevel()

end

--[[
heroData 主将的ID
callback 回调函数
--]]

function M:ctor(heroData, callback)
	self._heroData = heroData
	-- self:_loadImageToCacahe("ui/common/HeroIcon.plist", "ui/common/HeroIcon.png")
	self:_createIconButton()
	if(nil ~= callback) then
		self:setupClick(callback)
	end
	self:_createHeroInfo()
	self:_createHeroStateLabel()
	self:_createLockSprite()
end

function M:_updateHeroState()
	local heroState = self:_getHeroState()
	if Enum.HeroState.None == heroState then
		self._heroStateLabel:setString("")
	else
		self._heroStateLabel:setString("编")
	end

	self._lockSprite:setVisible(self:_heroIsLoak())
end

function M:_updateButtonShow()
	local heroType = self:_getHeroType()
	local normalName = heroType and self:_getNormalIconName(heroType) or nil
	local normalSprite = {}
	-- TEST
	if nil == normalName then 
		normalSprite = ccui.Scale9Sprite:create("ui/army-select.png")
	else
		normalSprite = ccui.Scale9Sprite:createWithSpriteFrameName(normalName)
	end
	self._clickbutton:setBackgroundSpriteForState(normalSprite, cc.CONTROL_STATE_NORMAL)

	-- TEST
	if nil == normalName then
		highligtedSprite = ccui.Scale9Sprite:create("ui/army-select.png")
	else
		highligtedSprite = ccui.Scale9Sprite:createWithSpriteFrameName(normalName)
	end
	self._clickbutton:setBackgroundSpriteForState(highligtedSprite, cc.CONTROL_STATE_HIGH_LIGHTED)
end

function M:_updateHeroName()
	local heroType = self:_getHeroType()
	local heroName = heroType and HeroConfigRead:getName(heroType) or ""
	self._showLabel:setString(heroName)
end

function M:_updateHeroLevel()
	local heroLevel = self:_getHeroLevel()
	local starName = string.format("X%d",heroLevel)
	self._starLabel:setString(starName)
end

function M:_heroIsLoak()
	return nil ~= self._heroData and self._heroData:isLock() or false
end
function M:_getHeroState()
	return nil ~= self._heroData and self._heroData:getHeroState() or Enum.HeroState.None
end

function M:_getHeroType()
	return nil ~= self._heroData and self._heroData:getHeroType() or nil
end
function M:_getHeroLevel()
	return nil ~= self._heroData and self._heroData:getHeroLevel() or 0
end

function M:_createLockSprite()
	self._lockSprite = cc.Sprite:create("ui/common/lock.png")
	self._clickbutton:addChild(self._lockSprite, 1)
	Layout:layout(self._lockSprite, self._clickbutton:getContentSize(), Layout.left_top)
	self._lockSprite:setVisible(false)
end


function M:_createHeroStateLabel()
	self._heroStateLabel = CommonUI:createLabel("未", 22)
	self._clickbutton:addChild(self._heroStateLabel, 1)
	Layout:layout(self._heroStateLabel, self._clickbutton:getContentSize(), Layout.right_top)
	self._heroStateLabel:setString("")
end

function M:_createHeroInfo()
	local heroName = "test"
	self._showLabel = CommonUI:createLabel(heroName, 34)
	self._starLabel = CommonUI:createLabel("X0", 30)
	local posX, posY = self._clickbutton:getPosition()
	local starSprite = cc.Sprite:create("ui/common/star.png")

	local buttonSize = self._clickbutton:getContentSize()
	local showLabelSize = self._showLabel:getContentSize()
	local starLabelSize = self._starLabel:getContentSize()
	local starSpriteSize = starSprite:getContentSize()
	local starPosiX = posX - starSpriteSize.width / 2
	local starPosiY = posY - buttonSize.height / 2 + starSpriteSize.height / 2

	starSprite:setPosition(cc.p(starPosiX - 10, starPosiY))
	self:addChild(starSprite)

	self._starLabel:setPosition(starPosiX + starSpriteSize.width / 2 + starLabelSize.width / 2, starPosiY)
	self:addChild(self._starLabel)

	self._showLabel:setPosition(cc.p(posX, posY - buttonSize.height / 2 - showLabelSize.height / 2))
	self:addChild(self._showLabel)
	
	self._iconSize = 
				{
					width = buttonSize.width,
					height = buttonSize.height + starLabelSize.height
				}
end

function M:_createIconButton()
	local iconName = "ui/army-select.png"
	self._clickbutton = Button.new(iconName , iconName)
	self:addChild(self._clickbutton)
end

function M:_getHighIconName(ID)
	local iconName = ID..".png"
	local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
	return nil ~= frame and iconName or nil
end

function M:_getNormalIconName(ID)
	local iconName = ID..".png"
	local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
	return nil ~= frame and iconName or nil
end

function M:_loadImageToCacahe(plistName, imageName)
	local cache = cc.SpriteFrameCache:getInstance()  
    cache:addSpriteFrames(plistName, imageName)
end

return M