local M = {}

--[[
    * 描述：间隔时间型定时器
    * 参数target：table数据类型
    * 参数interval：间隔时间触发
--]]
function M:addTimer(target, interval)
    assert(target.onUpdate, "target必须实现onUpdate方法")
    assert(interval)
    self._timers[target] = { elapseTime = 0, interval = interval }
end

function M:removeTimer(target)
    self._timers[target] = nil 
end

---------------------------- 接口分割线 ----------------------------

function M:onUpdate(dt)
    for target,data in pairs(self._timers) do
        data.elapseTime = data.elapseTime + dt 
        if data.elapseTime > data.interval then 
            target:onUpdate(dt)
            data.elapseTime = data.elapseTime - data.interval
        end
    end
end

function M:__init()
    assert(Timer, "Timer未被初始化")
    self._timers = {}

    Timer:addTimer(self)
end

M:__init()

return M