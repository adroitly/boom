local M = {}

function M:getRunningScene()
    return cc.Director:getInstance():getRunningScene()
end

function M:createScene(layer)
    local scene = cc.Scene:create()
    scene:addChild(layer)
    return scene
end

function M:replaceSceneWithLayer(layer)
    collectgarbage("collect")
    local scene = self:createScene(layer)
    cc.Director:getInstance():replaceScene(scene)
    return layer
end

function M:replaceSceneWithClass(LayerClass, ...)
    collectgarbage("collect")
    if type(LayerClass) == "string" then
        LayerClass = require(LayerClass)
    end
    return self:replaceSceneWithLayer(LayerClass.new(...))
end

return M

