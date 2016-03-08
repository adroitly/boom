--[[
    * 描述：精灵播放基础类，根据项目需求扩展
]]

local SpritePlistCache = require("libs.widget.SpriteAnimatePlistCache")
local M = class("libs.widget.SpriteAnimate", function()
    return cc.Sprite:create()
end)

local kDefaultFrameRate = 1.0 / 24.0
local function _getCurrentAnimateKey(state, index)
    return string.format("%s%d.png", state, index) 
end

local function _getDefaultAnimateState(animateKeys)
    for animateKey,_ in pairs(animateKeys) do
        return string.sub(animateKey, 1, #animateKey-5)
    end
end

function M:init(plistPath)
    assert(plistPath)
    self._elapsedTime   = 0
    self._currentIndex  = 1
    self._frameRate     = kDefaultFrameRate
    self._currentAnimateCount = 1

    self:reloadPlist(plistPath)
end

function M:reloadPlist(plistPath)
    self._currentIndex  = 1
    self._plistPath = plistPath
    cc.SpriteFrameCache:getInstance():addSpriteFrames(plistPath)
    
    self._animateKeys = SpritePlistCache:getAnimateKeys(plistPath)
    
    local defaultAnimateState = _getDefaultAnimateState(self._animateKeys)
    self:changeState(defaultAnimateState)

    local animateKey = _getCurrentAnimateKey(self._animateState, self._currentIndex)
    local spriteFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame(animateKey)
    assert(spriteFrame, string.format("动画配置文件错误，key=%s不存在", animateKey))
    self:setContentSize(spriteFrame:getOriginalSize())
end

function M:update(dt)
    self._elapsedTime = self._elapsedTime + dt
    if self._elapsedTime > self._frameRate then
        self._elapsedTime = self._elapsedTime - self._frameRate
        self._currentIndex = self._currentIndex + 1

        self:_playNextFrame()
    end
end

function M:changeState(state)
    assert(state)
    self:_checkStateExist(state)

    self._animateState = state
    self._currentIndex  = 1
    self._currentAnimateCount = self:_getCurrentAnimateCount()
    assert(self._currentAnimateCount > 0)
end

function M:getState()
    return self._animateState
end

function M:setFrameRate(frameRate)
    self._frameRate = frameRate
end

function M:setFinishCallback(callback)
    self._finishCallfun = callback
end

function M:getCurrentIndex()
    return self._currentIndex
end

function M:_playNextFrame()
    local isFinish = self._currentIndex > self._currentAnimateCount and true or false 
    self._currentIndex = isFinish and 1 or self._currentIndex

    local animateKey = _getCurrentAnimateKey(self._animateState, self._currentIndex)
    local spriteFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame(animateKey)

    -- 有可能内存不足时会删除资源，需要重新加载资源
    if not spriteFrame then 
        cc.SpriteFrameCache:getInstance():addSpriteFrames(self._plistPath)
        spriteFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame(animateKey)
        assert(spriteFrame, string.format("动画文件错误2，key=%s不存在", animateKey))
    end
    self:setSpriteFrame(spriteFrame)

    if isFinish and self._finishCallfun then
        self._finishCallfun()
    end
end

function M:_getCurrentAnimateCount()
    local index = 1
    while true do
        local animateKey = _getCurrentAnimateKey(self._animateState, index)
        local res = self._animateKeys[animateKey]
        if res then
            index = index + 1
        else 
            return index - 1
        end
    end
end

function M:_checkStateExist(state)
    local animateKey = _getCurrentAnimateKey(state, 1)
    assert(self._animateKeys[animateKey])
end

return M