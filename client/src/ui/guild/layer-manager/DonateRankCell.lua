
local M = class("ui.guild.layer-manager.DonateRankCell", function()
    return cc.TableViewCell:new()
end)

M.DonateRankCellSize = cc.size(750, 123)

function M:reset(rank, memberData)
    self._rankLabel:setString("" .. rank)
    Layout:layout(self._rankLabel, M.DonateRankCellSize, Layout.center, cc.p(320, 0))

    local nicknameStr = memberData:getNickname()
    self._nicknameLabel:setString(nicknameStr)
    Layout:layout(self._nicknameLabel, M.DonateRankCellSize, Layout.center, cc.p(100, 0))

    self._totalDonateLabel:setString("" .. memberData:getTotalDonate())
    Layout:layout(self._totalDonateLabel, M.DonateRankCellSize, Layout.center, cc.p(-100, 0))

    local title = memberData:getTitle()
    local titleName = PlayerData:getGuildData():getTitleNameByTitle(title)
    self._titleLabel:setString(titleName)
    Layout:layout(self._titleLabel, M.DonateRankCellSize, Layout.center, cc.p(-280, 0))

end

function M:ctor()
    self:_createBackground()
    self:_createInfoLabels()
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/mail/mail-title-bg.png")
    self:addChild(background)
    self:setContentSize(M.DonateRankCellSize)
    background:setAnchorPoint(cc.p(0, 0))
end

function M:_createInfoLabels()
    self._rankLabel = CommonUI:createLabel("1", 30)
    self:addChild(self._rankLabel)
    
    self._nicknameLabel = CommonUI:createLabel("我是XXXX", 30)
    self:addChild(self._nicknameLabel)
    
    self._totalDonateLabel = CommonUI:createLabel("9999999", 30)
    self:addChild(self._totalDonateLabel)
    
    self._titleLabel = CommonUI:createLabel("上将军", 30)
    self:addChild(self._titleLabel)
end
return M
