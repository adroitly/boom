local WikiConfig = require("config.WikiConfig")
local WikiConfigReader = require("ui.wiki.data-manager.WikiConfigReader")
local M = {}

-- 一级标题数据
local function _newH1TitleData(id)
    local data = {}
    data.h1ID = id
    -- 二级标题ID列表
    data.h2IDList = {}
    return data
end

-- 根据\n以及|分隔符拆分
function M:formatFormStr(formStr)
    local tbl = {}
    local t1 = String:split(formStr, "\n")
    for idx, v1 in ipairs(t1) do
        local t2 = String:split(v1, "|")
        local data = {}
        local colCount = 0
        for _, v in ipairs(t2) do
            table.insert(data, v)
        end
        table.insert(tbl, data)
    end
    return tbl
end

function M:getDataList()
    if not self._dataList then
        self._dataList = self:_formatConfigToList()
    end
    return self._dataList
end

function M:findMatchTitle(str)
    local matchList = {}
    local dataList = self:getDataList()
    for _, data in pairs(dataList) do
        for _, id in pairs(data.h2IDList) do
            local h2Title = WikiConfigReader:getH2Title(id)
            local res = string.match(h2Title, str)
            if res then
                table.insert(matchList, id)
            end
        end
    end
    return matchList
end

function M:_formatConfigToList()
    local tbl = {}
    for _, data in pairs(WikiConfig) do
        local id = data.id
        local h1Title = WikiConfigReader:getH1Title(id)
        if not tbl[h1Title] then
            tbl[h1Title] = _newH1TitleData(id)
        end
        table.insert(tbl[h1Title].h2IDList, id)
    end
    for _, data in pairs(tbl) do
        -- 对二级标题排序
        table.sort(data.h2IDList, function(aID, bID)
            return aID < bID
        end)
    end
    return tbl
end


return M