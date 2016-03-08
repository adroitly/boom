local M = class("libs.widget.ProgressBar", function()
	return cc.Node:create()
end)

--[[
    * 描述：从左往右类型进度条
    * 参数bgImage：背景图片
    * 参数progressImage：进度图片

    * 其他：进度采用百分比0~100
--]]
function M:ctor(bgImage, progressImage)
	assert(bgImage and progressImage)
	
	local sprite = cc.Sprite:create(bgImage)
	self:addChild(sprite)

	local size = sprite:getContentSize()
	self:setContentSize(size)

	self._progressTimer = cc.ProgressTimer:create(cc.Sprite:create(progressImage))
    self._progressTimer:setBarChangeRate(cc.p(1,0))
    self._progressTimer:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self._progressTimer:setMidpoint(cc.p(0, 1))
    self:addChild(self._progressTimer)

    self._currentProgress = 0
end

function M:getPercentage()
	return self._currentProgress
end

function M:setPercentage(percentage)
	percentage = math.min(percentage, 100)
	percentage = math.max(percentage, 0)
	
	if self._currentProgress==percentage then 
		return
	end

	self._currentProgress = percentage
	self._progressTimer:setPercentage(percentage)
end

return M

