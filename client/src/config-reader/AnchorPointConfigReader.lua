local AnchorPointConfig = require("config.AnchorPointConfig")
local M = {}
local function _print(data, anchorPointId, key)
    if nil == data then
        print("AnchorPointConfigReader找不到ID = %s，key = %s", anchorPointId, key)
    end
end

local function _getAnchorPointData(anchorPointId, key)
    local data = AnchorPointConfig[anchorPointId][key]
    _print(data, anchorPointId, key)
    return data
end

function M:getAnchorPointX(anchorPointId)
    return _getAnchorPointData(anchorPointId, "anchorPointX")
end
function M:getAnchorPointY(anchorPointId)
    return _getAnchorPointData(anchorPointId, "anchorPointY")
end

function M:getAnchorPoint(anchorPointId)
    return cc.p(self:getAnchorPointX(anchorPointId), self:getAnchorPointY(anchorPointId))
end

return M