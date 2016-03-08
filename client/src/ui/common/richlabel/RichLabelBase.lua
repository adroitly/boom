local M = {}

local ElementText = require("ui.common.richlabel.ElementText")
local ElementSprite = require("ui.common.richlabel.ElementSprite")
local ElementButton = require("ui.common.richlabel.ElementButton")
local ElementTextButton = require("ui.common.richlabel.ElementTextButton")

local m_splitKey = "b"

--[[
从一串字符串中获取一个ElementList
str格式为<b></b>中间为格式代码
如：str = "<b>color = [10-255-20-255],fontSize = 25,text=XX玩家</b>获得<b>text = 名城,color = [10-110-250-255],underLine = true</b>很好"
]]
function M:getElementListByStr(str)
    local tableList = self:getTableByStr(str)
    return self:getElementListByTable(tableList)
end

--[[
从一串字符串解析成table
str格式为<b></b>中间为格式代码
如：str = "<b>color = [10-255-20-255],fontSize = 25,text=XX玩家</b>获得<b>text = 名城,color = [10-110-250-255],underLine = true</b>很好"
返回:

{
    { color = cc.c4b(10, 255, 20, 255), fontSize = 25, text = XX玩家 },
    { text = 获得 },
    { color = cc.c4b(10, 110, 250, 255), underLine = true, text = 名城 },
    { text = 很好 }
}

]]
function M:getTableByStr(str)
    str = self:_stringGsub(str)
    local tableList = {}
    local strTable = Utils:getCharToTable(str)
    local index = 1
    local startIndex = 1
    local tableData = {}
    while (index <= #strTable)
    do
        if self:_checkStart(strTable, index) then
            if startIndex ~= index then
                tableData = self:_getValueTable(strTable, startIndex, index - 1)
                table.insert(tableList, tableData)
            end
            index = index + 3
            startIndex = index
        elseif self:_checkEnd(strTable, index) then
            tableData = self:_getValueTable(strTable, startIndex, index - 1)
            table.insert(tableList, tableData)
            index = index + 4
            startIndex = index
        else
            index = index + 1
        end
    end
    tableData = self:_getValueTable(strTable, startIndex)
    table.insert(tableList, tableData)
    return tableList
end

function M:getElementByTable(table)
    local elementType = table.richType or Enum.RichType.Label
    if elementType == Enum.RichType.Label then
        local elementText = ElementText:createLabel(table.text, table.fontSize, table.color, table.fontName, table.strokeColor, table.strokeSize)
        elementText:setUnderLine(true == table.underLine)
        return elementText
    elseif elementType == Enum.RichType.Sprite then
        return ElementSprite:createSprite(table.fileName)
    elseif elementType == Enum.RichType.Button then
        return ElementButton:createSprite(table.nomal, table.high)
    elseif elementType == Enum.Right.TextButton then
        local elementText = ElementText:createLabel(table.text, table.fontSize, table.color, table.fontName, table.strokeColor, table.strokeSize)
        return ElementTextButton:createTextButton(elementText, table.nomal, table.high)
    end
end

function M:getElementListByTable(tableList)
    local elementList = {}
    for index,table in ipairs(tableList) do
        elementList[index] = self:getElementByTable(table)
    end
    return elementList
end

function M:getElementByJson(jsonStr)
    return self:getElementByTable(json.decode(jsonStr))
end

function M:getElementListByJson(jsonStr)
    return self:getElementListByTable(json.decode(jsonStr))
end


----------------私有方法----------------

function M:_stringGsub(str)
    str = string.gsub(str, " ,", ",")
    str = string.gsub(str, ", ", ",")
    str = string.gsub(str, " = ", "=")
    return str
end

function M:_getValueTable(strTable, startIndex, endIndex)
    local str = Utils:mergeTableToChar(strTable, startIndex, endIndex)
    local table = self:_getTable(str)
    return table
end

function M:_getTable(str)
    local table = {}
    local hasSplit = String:has(str, "text=")
    if false == hasSplit then
        local data = self:_getDataTable(str)
        table[data[1]] = data[2]
    else
        table = self:_putStrToTable(str)
    end
    return table
end

function M:_getDataTable(dataStr)
    local data = {}
    if String:has(dataStr, "=") then
        data = String:split(dataStr, "=")
    else
        data[1] = "text"
        data[2] = dataStr
    end
    data[1] = string.gsub(data[1], " ", "")
    return data
end

function M:_putStrToTable(str)
    local table = {}
    local dataTable = String:split(str, ",")
    for _,dataStr in ipairs(dataTable) do
        local data = self:_getDataTable(dataStr)
        if "color" == data[1] then
            local colorStr = string.sub(data[2], 2, string.len(data[2]) - 1)
            local colorValueTable = String:split(colorStr, "-")
            table[data[1]] = self:_getColor(colorValueTable)
        elseif "underLine" == data[1] then
            if "true" == data[2] then
                table[data[1]] = true
            end
        else
            table[data[1]] = data[2]
        end
    end
    return table
end

function M:_getColor(color)
    return cc.c4b(tonumber(color[1]), tonumber(color[2]), tonumber(color[3]), tonumber(color[4]))
end

function M:_checkStart(strTable, index)
    if strTable[index] == "<" and strTable[index + 1] == m_splitKey and strTable[index + 2] == ">" then
        return true
    end
    return false
end

function M:_checkEnd(strTable, index)
    if strTable[index] == "<" and strTable[index + 1] == "/" and strTable[index + 2] == m_splitKey and strTable[index + 3] == ">" then
        return true
    end
    return false
end

return M