local M = {}
-- 获取时间差
-- 返回时间差字符串，例如 x年前
function M:getTimeDiffString(nowTime, preTime)
    local timeDiff = nowTime - preTime
    local nTime = 0
    if timeDiff > self:getYearSec() then
        nTime = timeDiff / self:getYearSec()
        nTime = math.floor(nTime)
        return nTime .. "年前"
    end
    if timeDiff > self:getMonthSec() then
        nTime = timeDiff / self:getMonthSec()
        nTime = math.floor(nTime)
        return nTime .. "月前"
    end
    if timeDiff > self:getDaySec() then
        nTime = timeDiff / self:getDaySec()
        nTime = math.floor(nTime)
        return nTime .. "天前"
    end
    if timeDiff > self:getHourSec() then
        nTime = timeDiff / self:getHourSec()
        nTime = math.floor(nTime)
        return nTime .. "小时前"
    end
    if timeDiff > (self:getMinuteSec() * 5) then
        nTime = timeDiff / self:getMinuteSec()
        nTime = math.floor(nTime)
        return nTime .. "分钟前"
    end
    return "刚刚"
end

-- 秒转文字时间，60 = 1分钟
function M:getTimeStringBySec(sec)
    local str = ""
    local day = 0
    if sec > self:getDaySec() then
        day = sec / self:getDaySec()
        day = math.floor(day)
        str = day .. "天"
    end
    local temp = sec - self:getDaySec() * day
    local hour = temp / self:getHourSec()
    hour = math.floor(hour)
    if hour > 0 then
        str = str .. hour .. "小时"
    end

    temp = temp - self:getHourSec() * hour
    local min = temp / self:getMinuteSec()
    min = math.floor(min)
    if min > 0 then
        str = str .. min .. "分钟"
    end

    local sec = temp - self:getMinuteSec() * min
    if sec > 0 then
        str = str .. sec .. "秒"
    end
    return str
end

-- XX天00：00：00
function M:getTimeCountDownString(diffTime)
    local str = ""
    local day = 0
    if diffTime > self:getDaySec() then
        day = diffTime / self:getDaySec()
        day = math.floor(day)
        str = day .. "天"
    end
    local temp = diffTime - self:getDaySec() * day
    local hour = temp / self:getHourSec()
    hour = math.floor(hour)

    temp = temp - self:getHourSec() * hour
    local min = temp / self:getMinuteSec()
    min = math.floor(min)

    local sec = temp - self:getMinuteSec() * min
    str = string.format("%s%02d:%02d:%02d", str, hour, min, sec)
    return str
end

function M:isSameDay(nowTime, targetTime)
    local oneDaySecond = 24 * 60 * 60
    local GMT8Second = 8 * 60 * 60
    local day1 = math.floor((nowTime + GMT8Second) / oneDaySecond)
    local day2 = math.floor((targetTime + GMT8Second) / oneDaySecond)
    return day1 == day2
end

function M:getFormatTimeString(time)
    return os.date("%Y-%m-%d %H:%M:%S", time)
end

function M:getMinuteSec()
    return 60
end

function M:getHourSec()
    return self:getMinuteSec() * 60
end

function M:getDaySec()
    return self:getHourSec() * 24
end

function M:getMonthSec()
    return self:getDaySec() * 30
end

function M:getYearSec()
    return self:getDaySec() * 365
end


return M