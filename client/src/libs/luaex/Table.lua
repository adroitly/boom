
local M = {}


function M.has_value(t, obj)
    for i, v in pairs(t) do
        if v == obj then
            return true 
        end
    end
    return false 
end 


-- 浅拷贝
function M:copy(r, t)
    r = r or {}
    for k, v in pairs(t) do
        r[k] = v
    end
    return r
end

-- 深拷贝
function M:deepCopy(r, t)
    r = r or {}
    for k, v in pairs(t) do
        if type(v) == "table" then
            r[k] = self:deepCopy({}, v)
        else
            r[k] = v
        end
    end
    return r
end

-- 序列化
function M:serialize(t)
    local mark = {}
    local value = {}
    
    local function ser_table(tbl,parent)
        mark[tbl]=parent
        local tmp={}
        for k,v in pairs(tbl) do
            local key= type(k)=="number" and "["..k.."]" or k
            if type(v)=="table" then
                local dotkey= parent..(type(k)=="number" and key or "."..key)
                if mark[v] then
                    table.insert(value,dotkey.."="..mark[v])
                else
                    table.insert(tmp, key.."="..ser_table(v,dotkey))
                end
            else
                local s = type(v) == "string" and '"'..v..'"' or tostring(v)
                table.insert(tmp, key.."="..s)
            end
        end
        return "{"..table.concat(tmp,",").."}"
    end
 
    return "do local ret="..ser_table(t,"ret")..table.concat(value," ").." return ret end"
end

return M
 

