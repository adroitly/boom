local M = class("share.ToggleButton", function()
    return cc.Node:create()
end)

local kDefaultSize = cc.size(100, 100)
local kDefaultAnchorPoint = cc.p(0.5, 0.5)

local function _safeSetCenter(sprite, size)
    if sprite then
        sprite:setPosition(cc.p(size.width * 0.5, size.height * 0.5))
    end
end

local function _safeSetVisible(sprite, flag)
    if sprite then
        sprite:setVisible(flag)
    end
end

function M:ctor(normalName, selectedName)
    self:init(normalName, selectedName)
end

function M:init(normalName, selectedName)
    self:setAnchorPoint(kDefaultAnchorPoint)
    self:setContentSize(kDefaultSize)
    self:setEnabled(true)
    self:setSelected(false)
    self:_setupEventHandler()
    self:setNormalImage(normalName)
    self:setSelectedImage(selectedName)
end

function M:setContentSize(size)
    cc.Node.setContentSize(self, size)
    _safeSetCenter(self._normalSprite, size)
    _safeSetCenter(self._selectedSprite, size)
end

function M:setNormalImage(fileName)
    if fileName then
        local texture = cc.Director:getInstance():getTextureCache():addImage(fileName)
        self:setNormalTexture(texture)
    end
end

function M:setNormalTexture(texture)
    if self._normalSprite then
        self._normalSprite:setTexture(texture)
        local size = texture:getContentSize()
        local rect = cc.rect(0, 0, size.width, size.height)
        self:setContentSize(size)
    else
        self._normalSprite = cc.Sprite:createWithTexture(texture)
        self:setContentSize(self._normalSprite:getContentSize())
        self:addChild(self._normalSprite)
    end
end

function M:setSelectedImage(fileName)
    if fileName then
        local texture = cc.Director:getInstance():getTextureCache():addImage(fileName)
        self:setSelectedTexture(texture)
    end
end

function M:setSelectedTexture(texture)
    if self._selectedSprite then
        self._selectedSprite:setTexture(texture)
        local size = texture:getContentSize()
        local rect = cc.rect(0, 0, size.width, size.height)
        self:setContentSize(size)
    else
        self._selectedSprite = cc.Sprite:createWithTexture(texture)
        self:setContentSize(self._selectedSprite:getContentSize())
        self:addChild(self._selectedSprite)
    end
    _safeSetVisible(self._selectedSprite, false)
end

function M:setEnabled(isEnabled)
    if self._isEnabled == isEnabled then
        return
    end
    self._isEnabled = isEnabled
end

function M:isEnabled()
    return self._isEnabled
end

function M:setSelected(isSelected)
    if self._isSelected == isSelected then
        return
    end
    _safeSetVisible(self._selectedSprite, isSelected)
    _safeSetVisible(self._normalSprite, not isSelected)
    self._isSelected = isSelected
    if self.onSelected then
        self.onSelected(isSelected)
    end
end

function M:isSelected()
    return self._isSelected
end

function M:onTouchBegan(touch, event)
    local hidden = Node:findParent(self, function(parent)
        return not parent:isVisible()
    end, true)
    if not hidden and self:_hitTest(touch) then
        return true
    end
    return false
end

function M:onTouchMoved(touch,event)
    if not self:isEnabled() then
        return
    end
end

function M:onTouchEnded(touch,event)
    if self:isEnabled() and self:_hitTest(touch) then
        self:setSelected(not self._isSelected)
    end
end

function M:onTouchCancelled(touch,event)
end

function M:_setupEventHandler()
    Touch:registerTouchOneByOne(self, true)
end

function M:_setTexture(sprite, texture)
    if sprite then
        sprite:setTexture(texture)
        local size = texture:getContentSize()
        local rect = cc.rect(0, 0, size.width, size.height)
        self:setContentSize(size)
    else
        sprite = cc.Sprite:createWithTexture(texture)
        self:setContentSize(sprite:getContentSize())
        self:addChild(sprite)
    end
end

function M:_hitTest(touch)
    return Touch:isTouchHitted(self, touch)
end
return M

