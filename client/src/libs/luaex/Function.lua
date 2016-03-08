local M = {}

function M:safeCall(obj, funName, ...)
    if obj and obj[funName] then
        return obj[funName](...)
    end
end
-- 格式化时间，
-- 传入以秒为单位的时间转化成 XX:XX:XX 格式
-- 如:time = 3600 
-- 返回: 01:00:00
function M:timeToDateString(targetTime)
	assert(targetTime >= 0)
	local targetS = math.floor(targetTime % 60)
	local targetM = math.floor(targetTime / 60 % 60)
	local targetH = math.floor(targetTime / 60 / 60)
	return string.format(__Localized("%02d:%02d:%02d"), targetH, targetM, targetS)
end

return M