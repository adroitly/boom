
-- 统一所有的函数使用“：”，而不能使用“.”
-- 所有程序内的单例或函数接口都放这边
require "ui.common.__Localized"

Listener        = require("share.Listener")

Enum            = require("ui.common.Enum")
Platform        = require("ui.common.Platform")
Command         = require("ui.common.Command")
Utils           = require("ui.common.Utils")
ServerErrorCode = require("ui.common.ServerErrorCode")
CommonUI        = require("ui.common.CommonUI")
MapManager      = require("ui.map.MapManager")

SocketManager   = require("socket-manager.SocketManager")
AlertView       = require("share.AlertView")
PlayerData      = require("player-data.PlayerData").new()

GameController  = require("game-controller.GameController")
ServerConfigInfo = require("game-controller.ServerConfigInfo")

CCLog = function(...)
    if app.debug then 
        print(string.format(...))
    end 
end

