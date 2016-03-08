
local M = {}

local m_isCountryWarOpen = false
function M:action(msgTable)
    m_isCountryWarOpen = msgTable.is_open
    Listener:postEvent(Listener.EventName.onListenCountryWarOpened, msgTable.is_open)
end

function M:isCountryWarOpen()
    return m_isCountryWarOpen
end

return M