local HotUpdater = require("libs.hot-updater.HotUpdater")
local M = class("ui.login.CheckVersionLayer", function()
    return cc.Layer:create()
end)

function M:checkVersion(successFun)
    local layer = M.new(successFun)
    local curRunScene = Director:getRunningScene()
    curRunScene:addChild(layer)
end

function M:ctor(successFun)
    assert(successFun)
    self._successFun = successFun
    CommonUI:showLoadingLayer(true)

    self._progressLabel = CommonUI:createLabel("0", 40)
    self:addChild(self._progressLabel)
    self._progressLabel:setPosition(cc.p(Screen.cx, 240))

    self._percentLabel = CommonUI:createLabel("0", 40)
    self:addChild(self._percentLabel)
    self._percentLabel:setPosition(cc.p(Screen.cx, 300))    

    Event:registerNodeEvent(self)
end

function M:onEnter()
    Listener:addListener(self)
    self:_startCheck()
end

function M:onExit()
    Listener:removeListener(self)
end

function M:_startCheck()
    local versionListUrl = string.format("http://ipas.fzxgame.cn/three/config/%s/version-list.json", 
            Platform:getDowloadResourceDir()) 
    HotUpdater:check(versionListUrl,
        function(downloadList)
            Listener:postEvent("onCheckVersionListSuccess", downloadList)
        end, 
        function(errorCode)
            Listener:postEvent("onCheckVersionListFailed", errorCode)
        end)
end

function M:onCheckVersionListSuccess(downloadList)
    if #downloadList==0 then 
        self:_newestVersion()
    else 
        self:_haveNewVerison(downloadList)
    end
end

function M:onCheckVersionListFailed(errorCode)
    local text = string.format(__Localized("检查资源列表失败，错误码=%d，请重新尝试"), errorCode)

    AlertView.new(text).onClicked = function(index)
        self:_startCheck()
    end
end

function M:_newestVersion()
    CommonUI:lightTips("当前资源是最新版本")
    CommonUI:showLoadingLayer(false)

    self._successFun()
    self:removeFromParent()
end

function M:_haveNewVerison(downloadList)
    local packageSize = HotUpdater:getPackageSizeKB(downloadList)/1024
    packageSize = math.max(packageSize, 0.1)
    local string = string.format(__Localized("共%d文件需要下载，总大小%0.1fM"), 
            #downloadList, packageSize)

    AlertView.new(string).onClicked = function(index)
        self:_dowloadPackage(downloadList)
    end
end

function M:_setProgressLabel(currentIndex, allIndex)
    local string = string.format("下载完成进度%d/%d", currentIndex, allIndex)
    self._progressLabel:setString(string)
end

function M:_dowloadPackage(downloadList)
    self:_setProgressLabel(0, #downloadList)
    HotUpdater:downloadPackage(downloadList, function(currentIndex, allIndex)
        self:_setProgressLabel(currentIndex, allIndex)

        if currentIndex==allIndex then 
            CommonUI:showLoadingLayer(false)
            self:removeFromParent()
            
            require("main")
        end
    end, 
    function(code)
        local string = string.format("下载资源失败, 错误码=%d", code)
        CommonUI:tips(string)
    end, 
    function(percent)
        local per = Math:inRange(percent, 100, 0)
        local string = string.format("下载进度=%d", per)
        self._percentLabel:setString(string)
    end)
end

return M
