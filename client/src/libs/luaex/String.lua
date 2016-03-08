local M = {}

local function _checkVersion(value)
    if "0"==string.sub(value, 1, 1) and 1~=string.len(value) then
        assert(false, "版本类型比较不支持0开头，比如1.01") 
    end
end

--[[
    * 描述：分割字符串
    * 参数split_char：分隔符
    * 例子：split("1:2:a", ":") = { "1", "2", "a" }
--]]
function M:split(str, split_char)
    local t = {}
    local str_len = #str
    local i = 1
    while true do
        local a, b = string.find(str, split_char, i, true)
        if a == nil then
            if i < str_len + 1 then
                t[#t + 1] = string.sub(str, i, str_len)
            end
            break
        end

        if i < a then
            t[#t + 1] = string.sub(str, i, a - 1)
        end
        i = b + 1
    end
    return t
end

function M:has(str, sub_str)
    return string.find(str, sub_str, 1, true) ~= nil
end

--[[
    * 描述：首字母大写
    * 例子：upperFirstChar("exit") = "Exit"
--]]
function M:upperFirstChar(string)
    return string.upper(string.sub(string, 1, 1)) .. string.sub(string, 2, -1)
end

--[[
    * 描述：比较版本号大小
    * 参数split_char：分隔符
    * 返回值：0等于，1大于，-1小于
    * 例子：compareVersion("1.9", "1.10", ".")     = -1
           compareVersion("10:0:1", "9:0:1", ":") = 1
--]]
function M:compareVersion(value1, value2, split_char)
    if value1==value2 then 
        return 0
    end

    local a1 = String:split(value1, split_char)
    local a2 = String:split(value2, split_char)
    assert(#a1 == #a2)

    for index=1,#a1 do
        _checkVersion(a1[index])
        _checkVersion(a2[index])
        local v1 = tonumber(a1[index])
        local v2 = tonumber(a2[index])        
        if v1 > v2 then 
            return 1 
        end

        if v1 < v2 then 
            return -1
        end
    end
    assert(false, "如果调用到这句说明有错了")
end

--[[
    * 描述：查找字符串包含key的所有索引
    * 例子：findSubIndexs("1<p>2<p>3", <p>) = { {2, 4}, {6, 8} }
--]]
function M:findSubIndexs(string, findKey)
    assert(string, findKey)
    local res = {}
    local index = 1
    while true do
        local beginIndex, endIndex = string.find(string, findKey, index)
        if nil==beginIndex then 
            break
        end

        index = endIndex + 1
        table.insert(res, { beginIndex, endIndex } )
    end
    return res
end

--[[
    * 描述：通过beginKey和endKey解析string
    * 例子：parseSubs("first<p>middle</p>last", "<p>", "</p>") = { {"first", false}, {"middle", true}, {"last"， false} }
    * 格式：{{解析字符串, 是否属于beginKey和endKey之间}}
--]]
function M:parseSubs(string, beginKey, endKey)
    assert(string and beginKey and endKey)
    local res = {}
    local index = 1
    while true do
        local beginIndex, endIndex = string.find(string, beginKey, index)
        if nil==beginIndex then
            local stringLen = string.len(string)
            if index>=stringLen then 
                break
            end

            local subString = string.sub(string, index, stringLen)
            table.insert(res, {subString, false})
            break
        end

        if index ~= beginIndex then 
            local subString = string.sub(string, index, beginIndex-1)
            table.insert(res, {subString, false})
        end

        index = endIndex + 1
        local beginInex2, endIndex2 = string.find(string, endKey, index)
        if nil==beginInex2 then 
            local subString = string.sub(string, index, stringLen)
            table.insert(res, {subString, false})
            break
        end

        local subString = string.sub(string, endIndex+1, beginInex2-1)
        table.insert(res, {subString, true})
        index = endIndex2 + 1
    end

    return res 
end

--[[
    * 描述：返回匹配beginKey和endKey之间内的所有数据
    * 例子1：find("<pro.1>对敌人造成<action.1.5>当前兵力的伤害", "<", ">") = {"pro.1", "action.1.5"}
    * 例子2：find("<p>你好</p>,<p>你好2</p>", "<p>", "</p>") = {"你好", "你好2"}
--]]
function M:findSubs(string, beginKey, endKey)
    assert(string and beginKey and endKey)

    local res = {}
    local index = 1
    while true do
        local beginIndex, endIndex = string.find(string, beginKey, index)
        if nil==beginIndex then
            break
        end

        index = endIndex + 1
        local beginInex2, endIndex2 = string.find(string, endKey, index)
        if nil==beginInex2 then 
            break
        end

        local subString = string.sub(string, endIndex+1, beginInex2-1)
        table.insert(res, subString)
        index = endIndex2 + 1
    end

    return res
end

return M
