
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = {}

function M:action(msgTable)
    local x = msgTable.x 
    local y = msgTable.y 
    assert(x and y)

    local uniqueId = Utils:getUniqueId(x, y)
    local buildingDataManager = MapManager:getBuildingDataManager()
    local buildingData = buildingDataManager:findData(uniqueId)
    if buildingData then 
        buildingData:refresh(msgTable)
    else 
        buildingData = require("ui.map.data-manager.BuildingData").new(msgTable, uniqueId)
        buildingDataManager:addData(buildingData, uniqueId)
    end

    local buildingSpriteManager = MapManager:getBuildingSpriteManager()
    buildingSpriteManager:updateData(buildingData)

    -- 更新主城信息
    local castleBuildingData = PlayerData:getCastleBuildingData()
    local castleUniqueId = castleBuildingData:getUniqueId()
    if castleUniqueId == uniqueId then
        castleBuildingData:refresh(msgTable)
    end
end

return M
