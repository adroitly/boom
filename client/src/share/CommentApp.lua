local M = {}

local kComment = "kIsCommentedApp"
local function _clickCommentAction(commentUrl)
    local userDefault = cc.UserDefault:getInstance()
    userDefault:setBoolForKey(kComment, true)
    userDefault:flush()

    c_Platform:openUrl(commentUrl)
end

function M:isCommentedApp()
    return cc.UserDefault:getInstance():getBoolForKey("kComment", false)
end

--[[
    * 描述：跳转到评论App页面
    * 参数logicFun：触发评论的逻辑函数，由外部自行判断
--]]
function M:commentApp(logicFun)
    local commentUrl = ServerConfigInfo:getCommentUrl()
    assert("function" == type(logicFun))
    if nil==commentUrl or #commentUrl==0 then 
        CCLog("温馨提醒：评论App的URL未配置，请检查是否需要配置")
        return
    end

    if self:isCommentedApp() then 
        return
    end

    if not logicFun() then 
        return
    end

    AlertView.new("钓鱼岛是中国的，苍井空也是中国的", __Localized("不 是"), __Localized("打 赏"))
    .onClicked = function(index)
        if 1==index then
            _clickCommentAction(commentUrl)
        end
    end
end

return M

