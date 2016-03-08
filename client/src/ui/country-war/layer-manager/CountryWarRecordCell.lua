local TimeTools = require("ui.common.TimeTools")
local CountryConfigReader = require("config-reader.CountryConfigReader")
local M = class("ui.country-war.layer-manager.CountryWarRecordCell", function()
    return cc.TableViewCell:new()
end)

M.WarRecordCellSize = cc.size(500, 50)

function M:reset(countryRecordData)
    local srcCountryId = countryRecordData:getSrcCountryId()
    local srcCountryName = CountryConfigReader:getCountryName(srcCountryId)
    local targetCountryId = countryRecordData:getTargetCountryId()
    local targetCountryName = CountryConfigReader:getCountryName(targetCountryId)

    local result = countryRecordData:getResult()
    local relationStr = ""
    local resultStr = "胜"
    if srcCountryId == self._recoredCountryId then
        relationStr = string.format("%s国向%s国宣战", srcCountryName, targetCountryName)
        if result == Enum.CountryWarResultType.Failed then
            resultStr = "负"
        end
    else
        relationStr = string.format("%s国被%s国宣战", targetCountryName, srcCountryName)
        if result == Enum.CountryWarResultType.Success then
            resultStr = "负"
        end
    end

    self._relationLabel:setString(relationStr)
    Layout:layout(self._relationLabel, M.WarRecordCellSize, Layout.left_center)

    self._resultLabel:setString(resultStr)
    Layout:layout(self._resultLabel, M.WarRecordCellSize, Layout.right_center)

    local time = countryRecordData:getTime()
    local timeStr = TimeTools:getFormatTimeString(time)
    self._timeLabel:setString(timeStr)
    Layout:layout(self._timeLabel, M.WarRecordCellSize, Layout.right_center, cc.p(50, 0))
end

function M:ctor(countryId)
    self._recoredCountryId = countryId
    self:_createInfo()
end

function M:_createInfo()
    self._relationLabel = CommonUI:createLabel("", 24)
    self:addChild(self._relationLabel)

    self._timeLabel = CommonUI:createLabel("", 24)
    self:addChild(self._timeLabel)

    self._resultLabel = CommonUI:createLabel("", 24)
    self:addChild(self._resultLabel)
end

return M