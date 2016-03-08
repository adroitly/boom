local M = {}

local function s_setupDisplay(winSize)
    M.size               = { width = winSize.width, height = winSize.height}
    M.rect               = cc.rect(0, 0, winSize.width, winSize.height)
    M.width              = M.size.width
    M.height             = M.size.height
    M.cx                 = M.width / 2
    M.cy                 = M.height / 2
    M.center             = cc.p(M.cx, M.cy)
    M.left               = 0
    M.right              = M.width
    M.top                = M.height
    M.bottom             = 0
end

-- 等宽模式
local function s_fixedWidthMode(designWidth, designHeight)
    local openGLView = cc.Director:getInstance():getOpenGLView()
    openGLView:setDesignResolutionSize(designWidth, designHeight, cc.ResolutionPolicy.FIXED_WIDTH)
end

-- 居中模式
local function s_middleMode(designWidth, designHeight)
    local openGLView = cc.Director:getInstance():getOpenGLView()
    local frameSize = openGLView:getFrameSize()
    local scaleX = designWidth / frameSize.width
    local scaleY = designHeight / frameSize.height
    local scale = math.min(scaleX, scaleY)
    M.designWidth = designWidth
    M.designHeight = designHeight
    local DW = frameSize.width * scale
    local DH = frameSize.height * scale
    openGLView:setDesignResolutionSize(DW, DH, cc.ResolutionPolicy.NO_BORDER)
end

-- 设置屏幕的设计尺寸
function M:setupDesignSize(designWidth, designHeight)
    s_fixedWidthMode(designWidth, designHeight)

    s_setupDisplay(cc.Director:getInstance():getWinSize())
end

return M

