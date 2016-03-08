local M = {}

M.CollectType = {
    Friend      = 1,
    Enemy       = 2,
    Resource    = 3,
    Mark        = 4,
}

-- 类型|姓名|buildingID|level|x|y|
function M:encodeToString(collectType, playerName, buildingId, buildingLevel, coor)
    assert(collectType, playerName, buildingId, buildingLevel, coor)
    return string.format("%d|%s|%d|%d|%d|%d", collectType, playerName, buildingId, buildingLevel, coor.i, coor.j)
end

function M:decodeToData(str)
    assert(str)
    local tbl = String:split(str, "|")
    return {
        collectType = tonumber(tbl[1]),
        playerName = tbl[2],
        buildingId = tonumber(tbl[3]),
        buildingLevel = tonumber(tbl[4]),
        i = tonumber(tbl[5]),
        j = tonumber(tbl[6]),
    }
end

return M