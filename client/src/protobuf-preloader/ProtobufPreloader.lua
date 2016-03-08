local M = {}

local protobuf = require("libs.socket.protobuf")

-- 在此添加res/protocol/common/中的文件
local PreloadFileList = {
    "building_info",
    "user_info",
    "player_base_info",
    "player_base_info1",
    "player_base_info2",
    "item_info", 
    "hero_info",
    "soldier_info",
    "army_info",
    "guild_skill_info",
    "guild_custom_title_info",
    "guild_info",
    "guild_member_info",
    "guild_own_info",
    "produce_building_info",
    "castle_product_soldier_info",
    "castle_product_item_info",
    "com_package_item",

    "com_package",
    "outside_army_info",
    "hero_seek_2_info",
    "hero_seek_3_info",
    "rank_info",
    "collect_info",
    "country_war_info",
    "country_war_record",
    "country_war_fight_info",
}

local function loadFileData(fileName)
    local path = string.format("res/protocol/%s.pb", fileName)
    return ccex.loadData(path)
end

function M:preload()
    for _, file in ipairs(PreloadFileList) do
        local data = loadFileData(file)
        if #data > 0 then
            protobuf.register(data)
        end
    end
end

return M