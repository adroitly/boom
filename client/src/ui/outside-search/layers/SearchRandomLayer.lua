local BackgroundLayer = require("ui.common.BackgroundLayer")
local RandomConfigReader = require("config-reader.RandomConfigReader")
local M = class("ui.outside-search.layers.SearchRandomLayer", function()
    return cc.Layer:create()
end)

function M:ctor(randomResourceData)
    local items = randomResourceData:getItems()
    local resourceId = randomResourceData:getResourceId()
    local item = items[1]
    local packageItemData = require("ui.backpack.data-manager.PackageItemData").new(item)

    self:_createBackground()
    self:_createNameLabel(resourceId)
    self:_createNumberLabel(packageItemData)
    self:_createDescLabel(resourceId)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("资源信息"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_createNumberLabel(packageItemData)
    local number = packageItemData:getNumber()
    local numberText = string.format(__Localized("总数量:%s"), number)
    local label = CommonUI:createLabel(numberText, 24)
    self:addChild(label)
    label:setPosition(cc.p(Screen.width / 2 , Screen.height - BackgroundLayer.TitleHeight * 4))

end

function M:_createNameLabel(resourceId)
    local nameText = RandomConfigReader:getName(resourceId)
    local label = CommonUI:createLabel(nameText, 40)
    self:addChild(label)
    label:setPosition(cc.p(Screen.width / 2, Screen.height - BackgroundLayer.TitleHeight * 2))
end

function M:_createDescLabel(resourceId)
    local desc = RandomConfigReader:getDesc(resourceId)
    local descText = string.format(__Localized("描述:%s"), desc)
    local label = CommonUI:createLabel(descText, 24)
    label:setAlignment(1)
    label:setWidth(Screen.width)
    self:addChild(label)
    label:setPosition(cc.p(Screen.width / 2, Screen.height - BackgroundLayer.TitleHeight * 5))
end

return M