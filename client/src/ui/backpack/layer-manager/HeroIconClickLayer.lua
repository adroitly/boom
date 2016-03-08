local HeroDataManager = require("player-data.HeroDataManager")
local M = class("ui.backpack.layer-manager.HeroIconClickLayer",function()
	return cc.Layer:create()
end)

local m_heroLockKey = "hero_lock"

function M:ctor(heroData)
	self._heroData = heroData
    self:setContentSize(cc.size(Screen.width, Screen.height))
	self:_createBackground()
	self:_createUpgradeButton()
	self:_createDetailButton()
	self:_createLockButton()
	self:_createBackButton()
	self:_createIconButton()
    Event:registerNodeEvent(self)
end


function M:onSocketClientDidCallback(cmd, msgTable, key)
    if cmd == m_heroLockKey then
		CommonUI:showLoadingLayer(false)
		assert(msgTable and msgTable.code)
	    if 0 == msgTable.code then
			self:_changeHeroData()
		else
			CommonUI:lightTips("更新失败")
		end
    end
end

function M:onTouchSlideMoveRight()
    self:removeFromParent()
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        self:removeFromParent()
    end
end

function M:onEnterTransitionFinish()
    SocketManager:addObserver(self)
    Touch:registerTouchOneByOne(self, true)
    Touch:addKeyboardTouch(self)
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
    SocketManager:removeObserver(self)
end


function M:onTouchBegan(touch, event)
    return true
end

function M:_changeHeroData()
	local lightTips = true == self._heroData:isLock() and "锁定成功" or "解锁成功"
	CommonUI:lightTips(__Localized(lightTips))
	local showText = true == self._heroData:isLock() and "解锁" or "锁定" 
	self._lockStateButton:setText(showText)
	self._heroIcon:reload(self._heroData)
end

function M:_createUpgradeButton()
	local upgradeButton = CommonUI:createTextButton(self, __Localized("升星"), "ui/login/login-button.png")
	upgradeButton.onClicked = function()
		self:_createUpgradeLayer()
		self:removeFromParent()
	end
	upgradeButton:setPosition(cc.p(Screen.width * 0.5 , Screen.height * 0.4))
end

function M:_createUpgradeLayer()
	local scene = cc.Director:getInstance():getRunningScene()
	local upgradeLayer = require("ui.hero-museum.layers.UpgradeHeroLayer").new(true)
	upgradeLayer:reload(Enum.UpgradeHeroType.Target, self._heroData)
	scene:addChild(upgradeLayer)
end

function M:_createIconButton()
    self._heroIcon = require("ui.common.HeroIcon").new()
    self._heroIcon:reload(self._heroData)
    self:addChild(self._heroIcon)
    self._heroIcon:setPosition(cc.p(Screen.width * 0.5, Screen.height * 0.6))
end

function M:_createDetailButton()
	local detailButton = CommonUI:createTextButton(self, __Localized("详情"), "ui/login/login-button.png")
	detailButton.onClicked = function()
		local scene = cc.Director:getInstance():getRunningScene()
		local heroInfoLayer = require("ui.team.layer-manager.HeroInfoLayer").new()
		heroInfoLayer:reloadLayerByHeroData(self._heroData)
		scene:addChild(heroInfoLayer)
		self:removeFromParent()
	end
	detailButton:setPosition(cc.p(Screen.width * 0.5 , Screen.height * 0.3))
end

function M:_createLockButton()
	local showText = true == self._heroData:isLock() and "解锁" or "锁定" 
	self._lockStateButton = CommonUI:createTextButton(self, __Localized(showText), "ui/login/login-button.png")
	self._lockStateButton.onClicked = function()
		local heroId = self._heroData:getHeroId()
		local lockState = self._heroData:isLock()
		local lock = true == lockState and 0 or 1 
		local sendData = {lock = lock,hero_id = heroId}
		SocketManager:send(m_heroLockKey, sendData)
		CommonUI:showLoadingLayer(true)
	end
	self._lockStateButton:setPosition(cc.p(Screen.width * 0.5, Screen.height * 0.2))
end

function M:_createBackButton()
    local button = CommonUI:createTextButton(self, __Localized("返回"), "ui/login/login-button.png")
    button.onClicked = function()
        self:removeFromParent()
    end
    button:setPosition(cc.p(Screen.width * 0.5, Screen.height * 0.1))
end

function M:_createBackground()
	local backgroundLayer = cc.LayerColor:create(cc.c4b(0, 0, 0, 160))
	self:addChild(backgroundLayer)
	self._contentSize = cc.size(Screen.width, Screen.height)
end

return M