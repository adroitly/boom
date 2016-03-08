local M = {}

local function s_getFullPath(path)
    local dir = cc.FileUtils:getInstance():getWritablePath()
    local fullPath = lkit.path.join(dir, path)
    local dirOnly = lkit.path.split(fullPath)
    lkit.fsys.let_dir_exists(dirOnly)
    return fullPath
end

local function s_writeFile(filePath, content)
    if app.saveDataWithClearText then 
        game.saveDecryptString(content, s_getFullPath(filePath))
        return 
    end 

    local f = assert(io.open(s_getFullPath(filePath), "w"))
    f:write(content);
    f:close()
end

local function s_readFile(filePath)
    if app.saveDataWithClearText then 
        return game.readDecryptFile(s_getFullPath(filePath))  
    end 

    local buf = nil 
    local f = io.open(s_getFullPath(filePath), "r")
    if f then
        buf = f:read("*all");
        f:close()
    end 
    return buf 
end

function M.saveTable(path, table)
    local content = Table:serialize(table)
    s_writeFile(path, content)
end

function M.loadTable(path)
    local content = s_readFile(path) 
    if content and #content > 0 then 
        local noError, result = xpcall(function() -- 容错
            return loadstring(content)()
        end, function()
            print(debug.traceback()) -- error info 
        end)

        if noError then 
            return result 
        end 
    end 
    return nil 
end

return M