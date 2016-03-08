local M = {}

function M:rectWithCenter(center, size)
    return cc.rect(center.x - size.width*0.5, center.y - size.height*0.5, size.width, size.height)
end

function M:centerAtRect(rect)
    return cc.p(rect.x + rect.width*0.5, rect.y + rect.height*0.5)
end

return M