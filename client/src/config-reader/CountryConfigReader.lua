local CountryConfig = require("config.CountryConfig")

local M ={}

local function _getCountryData(id, key)
	local config = CountryConfig[id][key]
	return config
end

function M:getCountryName(id)
	return _getCountryData(id, "country")
end

return M