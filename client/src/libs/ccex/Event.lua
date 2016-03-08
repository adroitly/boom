local String = require("libs.luaex.String")
local M = {}

--[[
    * 描述：注册Node通知，包括exit、enter、enterTransitionFinish、exitTransitionStart、cleanup
    * 函数实现：onExit、onEnter、onEnterTransitionFinish、onExitTransitionStart、onCleanup
]]
function M:registerNodeEvent(node)
    assert(node)
    cc.Node.registerScriptHandler(node, function(event)
        local eventName = String:upperFirstChar(event)
        local method = "on" .. eventName
        if node[method] then 
            node[method](node)
        end
    end)
end

return M


