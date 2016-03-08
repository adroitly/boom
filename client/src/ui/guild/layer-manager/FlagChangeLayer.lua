local BackgroundLayer = require("ui.common.BackgroundLayer")
local FlagData = require("ui.guild.data-manager.FlagData")
local FlagChangeCell = require("ui.guild.layer-manager.FlagChangeCell")
local GuildLayerManager = require("ui.guild.layer-manager.GuildLayerManager")
local M = class("ui.guild.layer-manager.FlagChangeLayer", function()
    return cc.Layer:create()
end)

local kGuildSetting = "guild_setting"

local kLineLimitCount = 3

function M:ctor()
    self:_initFlagData()
    self:_createBackground()
    self:_createSelectedFlag()
    self:_createChangeButton()
    self:_createTableView()

    local flag = PlayerData:getGuildData():getFlag()
    self:_changeFlag(flag)

    Event:registerNodeEvent(self)
    GuildLayerManager:addLayer(self)
end

function M:onExit()
    GuildLayerManager:removeLayer(self)
end

function M:_createBackground()
    local background = BackgroundLayer.new(self, __Localized("旗帜"))
    background:setBackButtonCallback(function()
        self:removeFromParent()
    end)
end

function M:_initFlagData()
    local addNewLine = function()
        self._flagDataList[#self._flagDataList + 1] = {}
    end
    local getCurrentLineCount = function()
        return table.getn(self._flagDataList[#self._flagDataList])
    end
    local addDataToList = function(flagData)
        table.insert(self._flagDataList[#self._flagDataList], flagData)
    end
    self._flagDataList = {}
    addNewLine()
    
    local flagCount = 10
    for i = 1, flagCount do
        local dataCount = getCurrentLineCount()
        if dataCount == kLineLimitCount then
            addNewLine()
        end
        local flagData = FlagData.new(i)
        addDataToList(flagData)
    end
    self._cellCount = math.ceil(flagCount / kLineLimitCount)
end

function M:_getFlagFileNameByIdx(idx)
    if idx == 0 then
        return "ui/guild/guild-flag-0.png"
    end
    for i, flagDataList in pairs(self._flagDataList) do
        for j, flagData in pairs(flagDataList) do
            if flagData:getIdx() == idx then
                return flagData:getFileName()
            end
        end
    end
end

function M:_changeFlag(idx)
    local fileName = self:_getFlagFileNameByIdx(idx)
    self._selectedFlag:setTexture(fileName)
    self._selectedFlagIdx = idx
end

function M:_createSelectedFlag()
    local flag = PlayerData:getGuildData():getFlag()
    self._selectedFlag = cc.Sprite:create("ui/test.png")
    self:addChild(self._selectedFlag)
    Layout:layout(self._selectedFlag, Screen.size, Layout.center_top, cc.p(0, BackgroundLayer.TitleHeight + 20))
end

function M:_createChangeButton()
    self._changeButton = CommonUI:createTextButton(self, __Localized("更换"), "ui/login/login-bt.png")
    self._changeButton.onClicked = function()
        if not self._selectedFlagIdx then
            return
        end
        local flag = PlayerData:getGuildData():getFlag()
        if self._selectedFlagIdx == flag then
            return
        end
        SocketManager:send(kGuildSetting, {flag = self._selectedFlagIdx})
    end
    local offsetPoxY = BackgroundLayer.TitleHeight + self._selectedFlag:getContentSize().height + 40
    Layout:layout(self._changeButton, Screen.size, Layout.center_top, cc.p(0, offsetPoxY))
end

function M:_createTableView()
    local cellSize = FlagChangeCell.FlagChangeCellSize
    local viewSize = cc.size(cellSize.width, Screen.height - BackgroundLayer.TitleHeight)
    local tableView = require("share.TableView").new(viewSize, self)
    self:addChild(tableView)
    local posY = Screen.height - BackgroundLayer.TitleHeight - viewSize.height - self._selectedFlag:getContentSize().height - self._changeButton:getContentSize().height - 60
    tableView:setPosition(cc.p((Screen.width - viewSize.width) * 0.5, posY))
end

function M:onTableViewCellTouched(tableView, cell)
end

function M:onTableViewCellSize(tableView, idx)
    return FlagChangeCell.FlagChangeCellSize.height, 0
end

function M:onTableViewCellAtIndex(tableView, idx)
    local cell = tableView:dequeueCell()
    if not cell then
        cell = FlagChangeCell.new()
    end
    local flagDataList = self._flagDataList[idx + 1]
    cell:reset(flagDataList)
    cell:setSelectedCallback(function(index)
        self:_changeFlag(index)
    end)
    return cell
end

function M:onTableViewCellCount(tableView)
    return self._cellCount
end

return M

