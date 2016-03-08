
local BaseSpritesManagerUtils = require("ui.map.layer-manager.BaseSpritesManagerUtils")

local M = {}

local function _showBuff(buildingData, skillId)
    if skillId > 0 then
        print("警告：显示建筑物Buff动画未处理")
    end
end

function M:action(msgTable)
    local x = msgTable.x
    local y = msgTable.y
    local cityDef = msgTable.city_amount
    local lostCityDef = msgTable.lost_city_amount
    local skillId = msgTable.skill_id
    assert(x and y and cityDef and lostCityDef and skillId)

    local uniqueId = Utils:getUniqueId(x, y)
    local buildingDataManager = MapManager:getBuildingDataManager()
    local buildingData = buildingDataManager:findData(uniqueId)
    if not buildingData then
        return
    end

    -- 刷新建筑物城防
    buildingData:updateCityDef(cityDef)

    -- 显示扣血动画
    local buildingSpriteManager = MapManager:getBuildingSpriteManager()
    buildingSpriteManager:updateCityDef(buildingData)
    BaseSpritesManagerUtils:showLostHpAnimate(buildingSpriteManager, uniqueId, lostCityDef)

    -- 显示buff
    _showBuff(buildingData, skillId)
end

return M