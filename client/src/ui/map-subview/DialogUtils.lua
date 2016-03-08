local MapConfig = require("ui.map.data-manager.MapConfig")
local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
local CollectDataManager = require("ui.collection.data-manager.CollectDataManager")
local BuildingConfigReader = require("ui.produce.data-manager.BuildingConfigReader")
local M = {}

function M:getDialogRadius()
    return 120
end

function M:showCoordinate(parent, twoDCoor)
    local localCoor = MapConfig:twoDToLocal(twoDCoor)
    local string = string.format("2D坐标:%d,%d，本地坐标:%d,%d",
             twoDCoor.i, twoDCoor.j, localCoor.i, localCoor.j )
    local label = CommonUI:createLabel(string, 30)
    parent:addChild(label)

    local space = self:getDialogRadius()
    label:setPosition(cc.p(0, -space - 40))
end

-- 资源点显示按钮的规则是一致的
function M:showResourcePointButton(parent, resOwnerId, resGuildId, buildingData)
    assert(parent and resOwnerId and resGuildId)

    -- 点击自己资源点
    local space = self:getDialogRadius()
    -- local isMy = PlayerData:isOwner(resOwnerId)
    local isMy = PlayerData:getNickName() == buildingData:getOwnerName()
    if isMy then 
        self:_createEnterBt(parent, cc.p(-space, 0))
        local aidBt = CommonUI:createTextButton(parent, __Localized("援助"), "ui/common/ok.png")
        aidBt:setPosition(cc.p(space, 0))
        aidBt.onClicked = function()
            assert(parent.onAidAction, "请注册onAidAction")
            parent:onAidAction()
        end
        return
    end

    local coor = buildingData:getHomeCoor()
    local twoDCoor = MapConfig:localTo2D(coor)
    if not CollectDataManager:isDataCollected(twoDCoor) then
        local collectBt = CommonUI:createTextButton(parent, __Localized("收藏"), "ui/common/ok.png")
        collectBt:setPosition(cc.p(0, -space))
        collectBt.onClicked = function()
            assert(parent.onCollectAction, "请注册onCollectAction")
            parent:onCollectAction()
        end
    end

    -- 点击同势力的资源点
    local isSameGuild = PlayerData:isSameGuild(resGuildId)
    if isSameGuild then
        -- 名城可以进入
        if Enum.BuildingType.FamousCity == BuildingConfigReader:getBuildingType(buildingData:getBuildingId()) then
            self:_createEnterBt(parent, cc.p(-space, 0))
            self:_createSearchBt(parent, cc.p(0, space))
        else
            self:_createSearchBt(parent, cc.p(-space, 0))
        end
        local aidBt = CommonUI:createTextButton(parent, __Localized("援助"), "ui/common/ok.png")
        aidBt:setPosition(cc.p(space, 0))
        aidBt.onClicked = function()
            assert(parent.onAidAction, "请注册onAidAction")
            parent:onAidAction()
        end
        return
    end

    -- 其他
    self:_createSearchBt(parent, cc.p(-space, 0))

    local attackBt = CommonUI:createTextButton(parent, __Localized("攻击"), "ui/common/ok.png")
    attackBt:setPosition(cc.p(space, 0))
    attackBt.onClicked = function()
        assert(parent.onAttackAction, "请注册onAttackAction")
        parent:onAttackAction()
    end

    local occupyBt = CommonUI:createTextButton(parent, __Localized("占领"), "ui/common/ok.png")
    occupyBt:setPosition(cc.p(0, space))
    occupyBt.onClicked = function()
        assert(parent.onOccupyAction, "请注册onOccupyAction")
        parent:onOccupyAction()
    end
end

function M:_createSearchBt(parent, position)
    local searchBt = CommonUI:createTextButton(parent, __Localized("侦查"), "ui/common/ok.png")
    searchBt:setPosition(position)
    searchBt.onClicked = function()
        assert(parent.onSearchAction, "请注册onSearchAction")
        parent:onSearchAction()
    end
end

function M:_createEnterBt(parent, position)
    local enterBt = CommonUI:createTextButton(parent, __Localized("进入"), "ui/common/ok.png")
    enterBt:setPosition(position)
    enterBt.onClicked = function()
        assert(parent.onEnterAction, "请注册onEnterAction")
        parent:onEnterAction()
    end
end

function M:showOutTeamLayer(goOutOperation, localCoor, playerId, armyId)
    assert(goOutOperation and localCoor)

    local twoDCoor = MapConfig:localTo2D(localCoor)
    local goInfo = GoOutInfo:newGoOutInfo(goOutOperation, twoDCoor)
    if playerId and armyId then 
        GoOutInfo:externValue(goInfo, playerId, armyId)
    end

    local scene = cc.Director:getInstance():getRunningScene()
    local layer = require("ui.team.layer-manager.OutTeamLayer").new(goInfo)
    scene:addChild(layer)
end

return M