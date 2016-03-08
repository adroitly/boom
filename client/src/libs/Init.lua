
--[[
    * 描述：请在main函数入口require该接口
]]

-- Lua 扩展
require("libs.luaex.Init")

-- cocos2d-x 扩展
require("libs.ccex.Init")

-- cocos2d-x 控件封装
require("libs.widget.Init")

-- flash 封装
require("libs.flash.Init")

Log = function(...)
    print(string.format(...))
end

Traceback = function()
    Log(debug.traceback())
end

Xpcallback = function(msg)
    local tracebackInfo = debug.traceback()
    local errorMsg = tostring(msg)

    Log("----------------------------------------")
    Log("LUA ERROR: " .. errorMsg .. "\n")
    Log(tracebackInfo)
    Log("----------------------------------------")

    XpcallbackLayer = require("libs.ccex.ui.XpcallbackLayer")
    XpcallbackLayer:showErrorMsg(errorMsg, tracebackInfo)
    return msg
end

