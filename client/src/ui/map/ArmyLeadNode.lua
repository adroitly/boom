local HeroDataManager = require("player-data.HeroDataManager")
local M = class("ui.map.ArmyLeadNode", function()
    return cc.Node:create()
end)

function M:onListenHeroDataChange(heroId)
    local tmpHeroId = self._heroIcon:getHeroId()
    if tmpHeroId == heroId then
        local heroData = HeroDataManager:getHeroDataById(heroId)
        self._heroIcon:reload(heroData)
    end
end

function M:ctor(armyData)
    assert(armyData)

    local teamData = armyData:getTeamData()
    local heroId = teamData:getHeroId()
    local heroData = HeroDataManager:getHeroDataById(heroId)

    self._selectSprite = cc.Sprite:create("ui/army-select.png")
    self:addChild(self._selectSprite)
    self._selectSprite:setScale(1.2)

    self._heroIcon = require("ui.common.HeroIcon").new()
    self._heroIcon:reload(heroData)
    self._heroIcon:setupClick(function()
        assert(self._clickCallFun)
        self._clickCallFun(self)
    end)
    self:addChild(self._heroIcon)

    self:setSelected(false)
    self:_registerClickHandler()
end

function M:getContentSize()
    return self._heroIcon:getContentSize()
end

function M:setClickCallfun(callFun)
    self._clickCallFun = callFun    
end

function M:setSelected(isSelected)
    self._selectSprite:setVisible(isSelected)
end

function M:_registerClickHandler()
    self:registerScriptHandler(function(event)
        if "exit" == event then
            Listener:removeListener(self)
        end
    end)
    Listener:addListener(self)
end

return M

