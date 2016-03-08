local PayRatioConfig = require("config.PayRatioConfig")
local M = {}

local function _getPayRatioConfig()
    return PayRatioConfig[1]
end

local function _getConfigValueTable(key)
    local config = _getPayRatioConfig()
    return Utils:formatStringToNumberTable(config[key])
end

local function _formatConfigToTbl(key)
    local valueTbl = _getConfigValueTable(key)
    local tbl = {}
    for _, t in pairs(valueTbl) do
        tbl.id = t[1]
        tbl.count = t[2]
    end
    return tbl
end

function M:getGuildCreate()
    return _formatConfigToTbl("createGuild")
end

function M:getOneRecruitAlcohol()
    return _getConfigValueTable("hero_seek_1_1")
end

function M:getOneGoldAlcohol()
    return _getConfigValueTable("hero_seek_1_2")
end

function M:getTenAlcohol()
    return _getConfigValueTable("hero_seek_1_3")
end

function M:getRecruitSearch()
    return _getConfigValueTable("hero_seek_2_change")
end

function M:getSeekSearch()
    return _getConfigValueTable("hero_seek_3_change")
end

-- 招贤招揽(5好感度价格)(hero_seek_2_confirm)
function M:getRecruitConfirm()
    return _getConfigValueTable("hero_seek_2_confirm")
end

function M:getSeekConfirm()
    return _getConfigValueTable("hero_seek_3_confirm")
end

function M:getOneProduceResourceSpeedUpPay()
    return _formatConfigToTbl("speed_up_1_1")
end

function M:getTotalProduceResourceSpeedUpPay()
    return _formatConfigToTbl("speed_up_1_2")
end

function M:getOneProduceSoldierSpeedUpPay()
    return _formatConfigToTbl("speed_up_2_1")
end

function M:getTotalProduceSoldierSpeedUpPay()
    return _formatConfigToTbl("speed_up_2_2")
end

function M:getOneHeroEnergySpeed()
    return _formatConfigToTbl("speed_up_4_1")
end

function M:getOneDoctorSpeedUpPay()
    return _formatConfigToTbl("speed_up_3_1")
end

function M:getAllDoctorSpeedUpPay()
    return _formatConfigToTbl("speed_up_3_2")
end



return M