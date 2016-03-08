local VipConfig = require("config.VipConfig")
local M = {}

local function _getItemList(vipLv, itemStr)
    if vipLv == 1 then
        return {}
    end
    local pack = VipConfig[vipLv].pack
    local tbl = Utils:formatStringToNumberTable(pack)
    local list = {}
    for _, value in ipairs(tbl) do
        local data = {}
        data.id = value[1]
        data.count = value[2]
        table.insert(list, data)
    end
    return list
end

function M:getDescTbl(vipLv)
    local descStr = VipConfig[vipLv].desc
    return String:split(descStr, ";")
end

function M:getMaxLevel()
    return VipConfig[1].lvmax
end

function M:getReward(vipLv)
    return _getItemList(vipLv, VipConfig[vipLv].reward)
end

function M:getNeedRecharge(vipLv)
    return VipConfig[vipLv].recharge
end

function M:getProductionUp(vipLv)
    return VipConfig[vipLv].productionup
end

function M:getRecruitUp(vipLv)
    return VipConfig[vipLv].recruitup
end

function M:getTrainUp(vipLv)
    return VipConfig[vipLv].trainup
end

function M:getOfficersMax(vipLv)
    return VipConfig[vipLv].officersmax
end

function M:getGiftsPack(vipLv)
    return _getItemList(vipLv, VipConfig[vipLv].pack)
end

function M:getVipMax()
    return table.getn(VipConfig)
end

return M