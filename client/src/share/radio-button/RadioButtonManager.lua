local RadioButton = require("share.radio-button.RadioButton")
local RadioTextButton = require("share.radio-button.RadioTextButton")

local M = {}
--[[
    规则
    tbl = {normalImg = "xxx.png", selectImg = "xxx.png", pos = cc.p(0, 0), title = "xxx"}
]]--
function M:createRadioButtons(parent, tbl, callback)
    local count = table.getn(tbl)
    local buttonList = {}
    for index, v in ipairs(tbl) do
        local button = self:_createRadioButton(v)
        parent:addChild(button)
        button.onSelected = function()
            self:_onButtonSelected(buttonList, index, isSelected)
            if callback then
                callback(index)
            end
        end
        table.insert(buttonList, button)
    end
    -- 默认第一个为选中状态
    buttonList[1]:setSelected(true)
end

function M:_createRadioButton(data)
    local button
    if data.title then
        button = RadioTextButton.new(data.title, data.normalImg, data.selectImg)
    else
        button = RadioButton.new(data.normalImg, data.selectImg)
    end
    button:setPosition(data.pos)
    return button
end

function M:_onButtonSelected(buttonList, index, isSelected)
    for i, button in ipairs(buttonList) do
        if index ~= i then
            button:setSelected(false)
            button:setEnabled(true)
        else
            button:setEnabled(false)
        end
    end
end

return M