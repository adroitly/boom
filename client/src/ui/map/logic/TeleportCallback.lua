
local MapConfig = require("ui.map.data-manager.MapConfig")
local M = {}

function M:action(msgTable)
    local playerId = msgTable.player_id
    local armyId = msgTable.army_id
    local x = msgTable.from_x
    local y = msgTable.from_y
    assert(playerId and armyId and x and y)

    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyData(playerId, armyId)
    if not armyData then 
        return
    end

    -- 刷新数据
    local coor = MapConfig:coordinate(x, y)
    armyData:setFromCoordinate(coor)
    armyData:setStatus(Enum.GoOutOperation.Wait)

    -- 更新位置，改为待机
    local pos = MapConfig:getPositionFromCoordinate(coor)
    armyData:setPosition(pos)
    local armySpriteManager = MapManager:getArmySpriteManager()
    armySpriteManager:updateArmySpritePosition(armyData, pos)
    armySpriteManager:playWaitAnimate(armyData)

end

return M