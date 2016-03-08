
local BackpackDataManager = require("player-data.BackpackDataManager")
local OfficerConfigRead = require("ui.guild.data-manager.OfficerConfigRead")
local M = class("ui.map.MapTopLayer", function()
	return cc.Layer:create()
end)

M.MapTopLayerSize = cc.size(Screen.width, 149)

local kUserInfo = "user_info"

local m_titleResourceTypeList = {
        Enum.ResourceType.Food,
        Enum.ResourceType.Wood,
        Enum.ResourceType.Stone,
        Enum.ResourceType.Coin,
        Enum.ResourceType.Jade,
        Enum.ResourceType.Gold,
	}

local function _getNumber(number)
	if number < 1000 then
		return number
	elseif number < (1000 * 1000) then
		return  string.format("%.1fk", number / 1000 )
	else
		return  string.format("%.1fM", number / (1000 * 1000))
	end
end

local function _getSpriteFrameFileName(backpackType)
	return string.format("%s.png", backpackType)
end

function M:onListenBackpackDataChange(backpackType)
	local index = 1
	for _,itemType in pairs(m_titleResourceTypeList) do
		if itemType == backpackType then
			local backpackData = BackpackDataManager:getBackpackDataByType(itemType)
			if nil ~= backpackData then
				self._resourceLabels[index]:setString(_getNumber(backpackData:getItemNumber()))
			end
			return
		end
		index = index + 1
	end
end


function M:ctor()
	self:_registerScriptHandler()
	self:_initLayer()
	self:_updateAllTitle()
end
function M:onTouchBegan(touch,event)
	return Touch:isTouchHitted(self, touch)
end

function M:_registerScriptHandler()
	SocketManager:addObserver(self)
	Listener:addListener(self)
    self:registerScriptHandler(function(event)
		if "exit" == event then
			Listener:removeListener(self)
			SocketManager:removeObserver(self)
			self:_removeLevelTimerId()
		end
    end)
    Touch:registerTouchOneByOne(self, true)
end
function M:onSocketClientDidCallback(cmd, msgTable, key)
	if kUserInfo == cmd then
		self:_updateUserInfo()
	end
end
function M:_updateAllTitle()
	local index = 1
	for _,itemType in pairs(m_titleResourceTypeList) do
		local backpackData = BackpackDataManager:getBackpackDataByType(itemType)
		if nil ~= backpackData then
			self._resourceLabels[index]:setString(_getNumber(backpackData:getItemNumber()))
		else
			self._resourceLabels[index]:setString("0")
		end
		index = index + 1
	end

end

function M:_initLayer()
	self:setContentSize(M.MapTopLayerSize)
	self:_createBackground()
	self:_createPlayerHead()
	self:_createExpNodes()
    self:_createLevelLabel()
	self:_updateUserInfo()
	self:_createRechargeButton()
	self:_createResourceNodes()
end


function M:_createBackground()
	self._background = cc.Sprite:create("ui/main-page/bg-maintop.png")
    self:addChild(self._background)
    Layout:layout(self._background, M.MapTopLayerSize, Layout.center_top)
end

function M:_removeLevelTimerId()
	TimerInterval:removeTimer(self)
end

function M:_updateUserInfo()
	self:_removeLevelTimerId()
	TimerInterval:addTimer(self, 1)
end

function M:onUpdate()
	self:_updateUserLevel()
end

function M:_updateUserLevel()
	local currentLevel = PlayerData:getUserInfoData():getLevel()
	local officeName = OfficerConfigRead:getOfficerName(currentLevel)
	officeName = string.format(__Localized("官职:%s"), officeName)
	officeName = __Localized(officeName)
	self._officerLabel:setString(officeName)

	local levelName = string.format(__Localized("等级:%d"), currentLevel)
	self._levelLabel:setString(levelName)

	self:_updateProgress(currentLevel)
end

function M:_updateProgress(currentLevel)
	local needTime = PlayerData:getUserInfoData():getLevelUpEndTime() - PlayerData:getServerTime()
	if needTime <= 0 or currentLevel == 90 then
		self:_onUpgradeNoTime(currentLevel)
		return
	end
    local costTime = OfficerConfigRead:getCostTime(currentLevel)
    local percentage = (1 - needTime / costTime) * 100
    self._expProgressTimer:setPercentage(percentage)
    self:_updateExpLabel(currentLevel, percentage)
end

function M:_updateExpLabel(currentLevel, percentage)
	local nextExp = OfficerConfigRead:getNextExp(currentLevel)
    local nowExp = math.floor(nextExp * percentage / 100)
	local str = string.format("%d/%d", nowExp, nextExp)
	self._expLabel:setString(str)
end

function M:_onUpgradeNoTime(currentLevel)
    self._expProgressTimer:setPercentage(100)
    self:_updateExpLabel(currentLevel, 100)
end

function M:_createPlayerHead()
    local frame = PlayerData:getPlayerIconFrame()
	self._playerButton = Button.new()
	self._playerButton:changeNormalSpriteWithFrame(frame)
	self:addChild(self._playerButton)

	self._playerButton.onClicked = function()
		local layer = require("ui.user-info.MainLayer").new()
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(layer)
	end
	Layout:layout(self._playerButton, M.MapTopLayerSize, Layout.left_top)
end

function M:_createExpNodes()
	local playerButtonSize = self._playerButton:getContentSize()
	local buttonX,buttonY = self._playerButton:getPosition()

	self._expProgressTimer = ProgressBar.new("ui/main-page/exp-progressbg.png", "ui/main-page/exp-progressup.png")
	local expSize = self._expProgressTimer:getContentSize()
	self._expProgressTimer:setPosition(cc.p(Screen.width * 0.5, M.MapTopLayerSize.height - self._background:getContentSize().height - expSize.height * 0.5))
	self:addChild(self._expProgressTimer)

	self._officerLabel = CommonUI:createLabel(__Localized("官职:丞相"), 24)
	self:addChild(self._officerLabel)

	local labelSize = self._officerLabel:getContentSize()
	local labelX = 0
	local labelY = - labelSize.height * 0.5
	self._officerLabel:setAnchorPoint(cc.p(0, 0.5))
	self._officerLabel:setPosition(cc.p(labelX, labelY))

	self._expLabel = CommonUI:createLabel("0/300", 20)
    self:addChild(self._expLabel)
    self._expLabel:setPosition(self._expProgressTimer:getPosition())
end

function M:_createLevelLabel()
	self._levelLabel = CommonUI:createLabel(__Localized("等级:90"), 24)
	self._levelLabel:setAnchorPoint(cc.p(0,0.5))
	self:addChild(self._levelLabel)
	local officerX, officerY = self._officerLabel:getPosition()
	local labelSize = self._levelLabel:getContentSize()
	self._levelLabel:setPosition(cc.p(0, officerY - labelSize.height))
end

function M:_createResourceNodes()
	local playerButtonSize = self._playerButton:getContentSize()

	local goldIngotSpritebg = cc.Sprite:create("ui/main-page/bg-resource.png")
	local goldIngotSprite = CommonUI:createSpriteWithFrame("stage-icon", _getSpriteFrameFileName(Enum.ResourceType.Gold))
	local goldIngotLabel = CommonUI:createLabel("0",24)

	local goldIngotSpritebgSize = goldIngotSpritebg:getContentSize()

	self:addChild(goldIngotSpritebg)
	Layout:layout(goldIngotSpritebg, M.MapTopLayerSize, Layout.right_top)

	goldIngotSpritebg:addChild(goldIngotSprite)
	Layout:layout(goldIngotSprite, goldIngotSpritebgSize, Layout.center)

	goldIngotSpritebg:addChild(goldIngotLabel)
	Layout:layout(goldIngotLabel, goldIngotSpritebgSize, Layout.center_bottom)

	local nodeWidth = (Screen.width - playerButtonSize.width - goldIngotSpritebgSize.width) / 5
	local backgroundSize = self._background:getContentSize()
	self._resourceLabels = {}
	for key = 1, 5 do
		local resourceSprite = CommonUI:createSpriteWithFrame("stage-icon", _getSpriteFrameFileName(m_titleResourceTypeList[key]))
		local resourceLabel = CommonUI:createLabel("233.7K", 24)

		local spriteSize = resourceSprite:getContentSize()
		local labelSize = resourceLabel:getContentSize()

		local posiX = playerButtonSize.width + nodeWidth * (key - 0.5)

		local posiY = M.MapTopLayerSize.height - backgroundSize.height * 0.5
		resourceSprite:setPosition(cc.p(posiX - spriteSize.width * 0.5, posiY))
		resourceLabel:setPosition(cc.p(posiX + labelSize.width * 0.5, posiY))

		self:addChild(resourceSprite)
		self:addChild(resourceLabel)

		table.insert(self._resourceLabels, resourceLabel)
	end
	table.insert(self._resourceLabels, goldIngotLabel)
end


function M:_createRechargeButton()
	local rechargeButton = Button.new("ui/main-page/button-recharge.png")
	self:addChild(rechargeButton)
	local buttonSize = rechargeButton:getContentSize()
	Layout:layout(rechargeButton, self:getContentSize(), Layout.right_bottom , cc.p(0, -buttonSize.height))
	rechargeButton.onClicked = function()
		local layer = require("ui.recharge.MainLayer").new()
		local scene = cc.Director:getInstance():getRunningScene()
		scene:addChild(layer)
	end
end

return M