local M = {}

function M:findParent(node, func, includeSelf)
    local parent = includeSelf and node or node:getParent()
    while parent do
        if func(parent) then
            break
        end
        parent = parent:getParent()
    end
    return parent
end

return M


