local M = {}

function M:showLostHpAnimate(baseSpriteManager, uniqueId, lostHp)
    assert(baseSpriteManager and uniqueId and lostHp)
    local sprite = baseSpriteManager:findSpriteByUniqueId(uniqueId)
    if sprite then 
        require("ui.common.PopBlood"):popBlood(sprite, lostHp)
    end
end

return M