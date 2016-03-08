local M = {}

function M:random(min, max)
    return (min + (max - min) * math.random())
end

--[[
    * 描述：返回 minValue <= currentValue <= maxValue
--]]
function M:inRange(currentValue, maxValue, minValue)
    assert(currentValue and maxValue and minValue)
    assert(maxValue >= minValue)
    local tmp = math.min(currentValue, maxValue)
    return math.max(tmp, minValue)
end

--[[
* 描述：获取position位置
丨------------- width ----------------丨
丨                                    丨
丨space          space          space 丨
丨----丨position丨----丨position丨---- 丨
丨                                    丨
]]
function M:positionWithSpace(positionCount, space, width, posIndex)
    local spaceWidth = (positionCount + 1) * space
    local widthCell = (width- spaceWidth) / positionCount
    local radiusWidth = widthCell / 2

    return space*(posIndex+1) + radiusWidth*(posIndex*2 + 1)
end

--[[
* 描述：通过偏移位置，获取当前在第几个Page Index                                  丨
]]
function M:pageIndexAtOffset(viewWidth, offset)
    local pageIndex = (viewWidth/2 - offset) / viewWidth
    return math.floor(pageIndex) 
end

return M