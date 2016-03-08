local M = {}

local function s_link(t, action)
    if t.raw == nil then
        t.raw = action
    else
        if t._type == "seq" then
            t.raw = cc.Sequence:create(t.raw, action)
        elseif t._type == "spa" then
            t.raw = cc.Spawn:create(t.raw, action)
        end
    end
    return t
end

local cls_table = {
    moveTo    = cc.MoveTo,
    scaleTo   = cc.ScaleTo,
    rotateTo  = cc.RotateTo,
    fadeIn    = cc.FadeIn,
    fadeTo    = cc.FadeTo,
    fadeOut   = cc.FadeOut,
    moveBy    = cc.MoveBy,
    delayTime = cc.DelayTime,
    callFunc  = cc.CallFunc,
    bezierTo  = cc.BezierTo,
}

local meta_table = {}
meta_table.__index = function(t, k)
    if k == "run" then
        return function(node)
            node:runAction(t.raw)
            return t
        end
    end

    if k == "action" then
        return function(action)
            if type(action) == "table" then
                return s_link(t, action.raw)
            else
                return s_link(t, action)
            end
        end
    end

    local cls = cls_table[k]
    if cls then
        return function(...)
            return s_link(t, cls:create(...))
        end
    end
    return rawget(t, k)
end

--[[
    * 描述：快捷的动画方式
    * 例子：Action:Sequence().fadeOut(1.5).callFunc(callback).run(self)
]]
function M:Sequence()
    local t = { _type = "seq" }
    setmetatable(t, meta_table)
    return t
end

function M:Spawn()
    local t = { _type = "spa" }
    setmetatable(t, meta_table)
    return t
end

function M:delayCall(node, time, func)
    M:Sequence().delayTime(time).callFunc(func).run(node)
end


return M



