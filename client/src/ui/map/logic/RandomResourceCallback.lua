
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = {}

-- 随机资源
function M:action(msgTable)
    -- Print:Table(msgTable, "situtaion package =")
    local x = msgTable.x 
    local y = msgTable.y 
    assert(x and y)

    local uniqueId = Utils:getUniqueId(x, y)
    local randomResourceManager = MapManager:getRandomResourceManager()
    local randomResourceData = randomResourceManager:findData(uniqueId)
    if randomResourceData then 
        randomResourceData:refresh(msgTable)
    else 
        randomResourceData = require("ui.map.data-manager.RandomResourceData").new(msgTable, uniqueId)
        randomResourceManager:addData(randomResourceData, uniqueId)
    end

    -- 刷新界面
    local randomResSpriteManager = MapManager:getRandomResourceSpriteManager()
    randomResSpriteManager:updateData(randomResourceData)
end

return M