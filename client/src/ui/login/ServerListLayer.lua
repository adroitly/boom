local ServerListUtils = require("ui.login.ServerListUtils")
local ServerListChoiseLayer = require("ui.login.ServerListChoiseLayer")
local M = class("ui.login.ServerListLayer", function(loadSuccessCallback)
    return cc.Layer:create()
end)

function M:ctor(loadSuccessCallback)
    assert(loadSuccessCallback, "请设置获取服务器列表成功后的回调函数")
    self._loadSuccessCallback = loadSuccessCallback
    self:_startLoad()
end

function M:getIp()
    local serverData = ServerListUtils:findServerWithId(self._serverList, self._currentSelectId)
    return serverData.ip
end

function M:getPort()
    local serverData = ServerListUtils:findServerWithId(self._serverList, self._currentSelectId)
    return serverData.port
end

function M:getCurrentSelectId()
    return self._currentSelectId
end

function M:saveServerIdForLastLogin()
    ServerListUtils:saveServerIdForLastLogin(self._currentSelectId)
end

function M:_startLoad()
    CommonUI:showLoadingLayer(true)

    network.http.get({
        url = ServerConfigInfo:getServerList(), 
    }, function(info, result)
        if self._severListLoadedCallback then
            self:_severListLoadedCallback(info, result)
        end
    end)
end

function M:_loadFailed(errorMessage)
    local text = string.format(__Localized("获取服务器列表失败，错误信息=%s"), errorMessage)
    AlertView.new(text).onClicked = function(index)
        self:_startLoad()
    end
end

function M:_loadSuccess(info)
    local list = json.decode(info.data)
    if #list == 0 then
        AlertView.new(__Localized("获取服务器列表为空值")).onClicked = function(index)
            self:_startLoad()
        end
        return
    end

    -- Print:Table2(list, "sss")
    self:_loadListSuccess(list)

    CommonUI:showLoadingLayer(false)

    self._loadSuccessCallback()
end

function M:_loadListSuccess(list)
    self._serverList = list 

    self._currentSelectId = ServerListUtils:getLastLoginServerId(self._serverList)
    local serverData = ServerListUtils:findServerWithId(self._serverList, self._currentSelectId)

    self._showButton = CommonUI:createTextButton(self, serverData.name, "ui/login/login-up.png")
    self._showButton:setPosition(cc.p(Screen.cx, 200))
    self._showButton.onClicked = function()
        local choiseLayer = ServerListChoiseLayer.new(self._serverList, function(selectId)
            self:_resetSelectId(selectId)
        end)
        self:addChild(choiseLayer)
    end
end

function M:_resetSelectId(newId)
    self._currentSelectId = newId 
    local serverData = ServerListUtils:findServerWithId(self._serverList, self._currentSelectId)
    self._showButton:setText(serverData.name)
end

function M:_severListLoadedCallback(info, result)
    if result ~= "finish" then 
        self:_loadFailed(result)
        return
    end
    self:_loadSuccess(info)
end

return M

