local M = {}

M.LeftTop = "leftTop"
M.RightTop = "rightTop"
M.LeftBottom = "leftBottom"
M.RightBottom = "rightBottom"

function M:getDefalutDirection()
	return M.RightTop
end

-- 根据当前位置和目标位置得到移动方向
function M:getDirection(prePos, nextPos)
	if prePos.x > nextPos.x then
		if prePos.y > nextPos.y then
			return M.LeftBottom
		else
			return  M.LeftTop
		end
	else
		if prePos.y > nextPos.y then
			return  M.RightBottom
		else
			return  M.RightTop
		end
	end
end

-- 根据移动方向获取动画方向，返回动画方向名称以及是否需要翻转
function M:getConvertDir(dir)
	if dir == M.LeftTop then
		return "up", true
	elseif dir == M.LeftBottom then
		return "down", true
	elseif dir == M.RightTop then
		return "up", false
	elseif dir == M.RightBottom then
		return "down", false
	end
end

return M