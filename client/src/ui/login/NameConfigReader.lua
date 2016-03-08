local NameConfig = require("config.NameConfig")
local M = {}

M.NameKey = 
{
    Surname = 1,
    Name = 2
}

local function _getSurnameTable()
    return Utils:formatStringToTable(NameConfig[M.NameKey.Surname].surname)
end

local function _getNameTable()
    return Utils:formatStringToTable(NameConfig[M.NameKey.Name].surname)
end

function M:getSurnameByIndex(index)
    local surnameTable = _getSurnameTable()
    return surnameTable[index][1]
end

function M:getNameByIndex(index)
    local nameTable = _getNameTable()
    return nameTable[index][1]
end

function M:getMaxCountSurname()
    local surnameTable = _getSurnameTable()
    return table.getn(surnameTable)
end

function M:getMaxCountName()
    local nameTable = _getNameTable()
    return table.getn(nameTable)
end
return M