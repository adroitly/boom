local M = class("ui.country-war.data-manager.CountryWarRecordData")

local function _isValid(msgTable)
    assert(msgTable and msgTable.src_country_id and msgTable.target_country_id and msgTable.time and msgTable.result)
end

function M:ctor(msgTable)
    _isValid(msgTable)
    Table:copy(self, msgTable)
end

function M:getSrcCountryId()
    return self.src_country_id
end

function M:getTargetCountryId()
    return self.target_country_id
end

function M:getTime()
    return self.time
end

function M:getResult()
    return self.result
end

return M