local PersonalMailDataManager = require("player-data.PersonalMailDataManager")
local SystemMailDataManager = require("player-data.SystemMailDataManager")
local GameMailDataManager = require("player-data.GameMailDataManager")
local GuildDataManager = require("player-data.GuildDataManager")
local UserInfoDataManager = require("player-data.UserInfoDataManager")
local CollectDataManager = require("ui.collection.data-manager.CollectDataManager")
local ProduceBuildingDataManager = require("ui.produce.data-manager.ProduceBuildingDataManager")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = {}

-- 初始化
function M:startController()
    UserInfoDataManager:startDataListener()
    SystemMailDataManager:startMailListener()
    GameMailDataManager:startMailListener()
    PersonalMailDataManager:startMailListener()
    GuildDataManager:startDataListener()
    CollectDataManager:startDataListener()
    ProduceBuildingDataManager:startDataListener()
    GuildLayerManager:startManager()
end

-- 移除
function M:purgeController()
    GuildLayerManager:stopManager()
    ProduceBuildingDataManager:stopDataListener()
    CollectDataManager:stopDataListener()
    PersonalMailDataManager:stopMailListener()
    GameMailDataManager:stopMailListener()
    SystemMailDataManager:stopMailListener()
    GuildDataManager:stopDataListener()
    UserInfoDataManager:stopDataListener()
    PlayerData:save()
end

return M