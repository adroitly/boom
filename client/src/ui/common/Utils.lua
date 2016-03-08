local M = {}

function M:getUniqueId(x, y)
    assert(x and y)
    return x .. "." .. y 
end

-- 截取字符串，超出宽度部分返回省略号
function M:cutStringByWidth(maxWidth, string, fontSize, fontName)
    local tempLabel = cc.Label:create()
    tempLabel:setSystemFontSize(fontSize)
    tempLabel:setSystemFontName(fontName)
    tempLabel:setHorizontalAlignment(Enum.TextHAlignment.Center)
    tempLabel:setString("...")
    local currentWidth = tempLabel:getContentSize().width

    local charList = self:getCharToTable(string)
    local finalStr = ""
    for i = 1, table.getn(charList) do
        local char = charList[i]
        tempLabel:setString(char)
        local width = tempLabel:getContentSize().width
        if width + currentWidth > maxWidth then
            finalStr = finalStr .. "..."
            break
        end
        currentWidth = currentWidth + width
        finalStr = finalStr .. char
    end
    return finalStr
end

-- 拆封字符串，用table存储
-- 如 test = "123,123,23;123,123,321;123421,2313,123"
-- 转化为 test = {[1] = {123,123,23}, [2] = {123,123,321}, [3] = {123421,2313,123}}
function M:formatStringToTable(str)
    str = tostring(str)
    local tbl = {}
    local t1 = String:split(str, ";")
    for _, v in ipairs(t1) do
        local t2 = String:split(v, ",")
        table.insert(tbl, t2)
    end
    return tbl
end

-- 拆封字符串，用table存储
-- 如 test = "123,123,23;123,123,321;123421,2313,123"
-- 转化为 test = {[1] = {123,123,23}, [2] = {123,123,321}, [3] = {123421,2313,123}}
-- 转化的table内部全是数字
function M:formatStringToNumberTable(str)
    str = tostring(str)
    local tbl = {}
    local t1 = String:split(str, ";")
    for _,value in ipairs(t1) do
        local datatb = String:split(value, ",")
        local data = {}
        for _,valueStr in ipairs(datatb) do
            table.insert(data, tonumber(valueStr))
        end
        table.insert(tbl, data)
    end
    return tbl
end

-- 将中文和英文用table存储起来
function M:getCharToTable(str)
    local list = {}
    for uchar in string.gfind(str, "[%z\1-\127\194-\244][\128-\191]*") do
        list[#list + 1] = uchar
    end
    return list
end

-- 将String table保存成String
function M:mergeTableToChar(strTable, fromIndex, endIndex)
    local str = ""
    if nil == endIndex then
        endIndex = #strTable
    end
    for i=fromIndex,endIndex do
        str = string.format("%s%s", str, strTable[i])
    end
    return str
end

return M