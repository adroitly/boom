local M = class("ui.backpack.layer-manager.BackpackHeroListCell", function()
    return GridViewCell.new()
end)
function M:ctor()
    self:_createHeroIcon()
end

function M:getContentSize()
    return self._heroIcon:getContentSize()
end

function M:reloadData(heroData)
    self._heroIcon:reload(heroData)
    if nil == heroData then
        self:setVisible(false)
    else
        self:setVisible(true)
    end
end

function M:_createHeroIcon()
    self._heroIcon = require("ui.common.HeroIcon").new()
    self._heroIcon:setSwallow(false)
    self._heroIcon:setupClick(function()
        local scene = cc.Director:getInstance():getRunningScene()
        local layer = require("ui.backpack.layer-manager.HeroIconClickLayer").new(self._heroIcon:getHeroData())
        scene:addChild(layer)
    end)
    self:addChild(self._heroIcon)
end
return M
