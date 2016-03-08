-- http://www.tuicool.com/articles/JRFFviY
-- 必须前置
local function _getNativePackageKeys()
    local pakcageKeys = {} 
    local loaded = package.loaded 
    for k, v in pairs(loaded) do 
        pakcageKeys[k] = true 
    end 
    return pakcageKeys
end

local function _clearPackage(nativeKeys)
    local loaded = package.loaded
    for k, v in pairs(loaded) do 
        if nativeKeys[k] == nil then 
            loaded[k] = nil 
        end 
    end 
end

if not __app_loaded then
    __app_loaded = _getNativePackageKeys()
    local paths = { "src", "res"}
    local packagePath = game.getPackagePath()
    local resourcePath = game.getResourcePath() 
    for _, v in ipairs(paths) do 
        local path = lkit.path.join(resourcePath, v) 
        cc.FileUtils:getInstance():addSearchPath(path)

        path = lkit.path.join(packagePath, v)
        cc.FileUtils:getInstance():addSearchPath(path)
    end
else
    _clearPackage(__app_loaded)
end
-----------------------------------------------------------------------------
require "cocos.init"
require "libs.Init"
require "AppSettings"
require "c-interface.CInterface"
require "ui.common.GlobalClass"

local function main()
    -- 预加载pbc的公共文件
    local ProtobufPreloader = require("protobuf-preloader.ProtobufPreloader")
    ProtobufPreloader:preload()

    math.randomseed(os.time())
    
    ccex.RefCache:getInstance():removeAll()

    collectgarbage("collect")
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    -- --turn on display FPS
    cc.Director:getInstance():setAnimationInterval(1.0/60.0)
    cc.Director:getInstance():setDisplayStats(false)

    Screen:setupDesignSize(768, 1136)

    SocketManager:disconnect()
    local layer = require(app.firstUILayer).new()
    local gameScene = cc.Scene:create()
    gameScene:addChild(layer)

    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(gameScene)
    else
        cc.Director:getInstance():runWithScene(gameScene)
    end
end

local status, msg = xpcall(main, Xpcallback)
if not status then
    error(msg)
end


