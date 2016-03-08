local MapConfig             = require("ui.map.data-manager.MapConfig")
local ResourcePointUtils    = require("ui.map.data-manager.ResourcePointUtils")
local BattleUtils           = require("ui.map.logic.BattleUtils")
local CountryWarOpenCallback        = require("ui.map.logic.CountryWarOpenCallback")

local M = {}

local function _newDialogLayer(dialogLayer)
    local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:newDialogLayer(dialogLayer)
end

local function _removeDialogLayer()
    local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:removeDialogLayer()
end

local function _touchArmy(point)
    local armySpriteManager = MapManager:getArmySpriteManager()
    local sprite, armyData = armySpriteManager:findSpriteDataWithPoint(point)
    return sprite, armyData
end

local function _touchRandomResource(point)
    local randomResourceSpriteManger = MapManager:getRandomResourceSpriteManager()
    return randomResourceSpriteManger:findRandomResourceData(point)
end

local function _touchBuilding(point)
    local buildingSpriteManager = MapManager:getBuildingSpriteManager()
    return buildingSpriteManager:findBuldingData(point)
end

local function _showClickArmyDialog(sprite, armyData)
    local dialogLayer = require("ui.map-subview.ClickArmyDialog"):newClickArmyDialog(sprite, armyData)
    _newDialogLayer(dialogLayer)
end

local function _showClickCastleDialog(buildingData)
    local dialogLayer = require("ui.map-subview.ClickCastleDialog"):newClickCastleDialog(buildingData)
    _newDialogLayer(dialogLayer)
end

-------------------------------- 军队选中状体再次点击其他地方逻辑处理 ---------------------------------------
local function _selectArmy(sprite, curArmyData, selectedArmyData)
    -- 相同军队取消选中状态
    if curArmyData:getPlayerId()==selectedArmyData:getPlayerId() and
        curArmyData:getArmyId()==selectedArmyData:getArmyId() then
        M:setMyArmySelect(selectedArmyData, false)
        return
    end

    -- 我军军队，切换选中状态
    if curArmyData:getPlayerId()==selectedArmyData:getPlayerId() then
        M:setMyArmySelect(selectedArmyData, false)
        M:setMyArmySelect(curArmyData, true)
        return
    end

    -- 同势力则取消当前选中状态
    if PlayerData:isSameGuild(curArmyData:getGuildId()) then
        M:setMyArmySelect(selectedArmyData, false)
        return
    end

    -- 敌人则攻击
    local armyDataManager = MapManager:getArmyDataManager()
    armyDataManager:attackArmyWithArmyData(selectedArmyData, curArmyData)
    M:setMyArmySelect(selectedArmyData, false)
end

local function _changeArmyStatus(armyData, goOutOperationType, toCoor)
    assert(armyData and goOutOperationType and toCoor)
    local armyDataManager = MapManager:getArmyDataManager()
    armyDataManager:changeStatus(armyData:getPlayerId(),
                    armyData:getArmyId(),
                    goOutOperationType,
                    toCoor)
end

local function _selectBuilding(buildingData, selectedArmyData)
    -- 自己主城则回城
    local isMyHomeCastle = ResourcePointUtils:isMyHomeCastle(buildingData)
    if isMyHomeCastle then
        _changeArmyStatus(selectedArmyData, Enum.GoOutOperation.GoHome, buildingData:getHomeCoor())
        return
    end

    -- 自己的附属资源点或同势力则驻守
    local isMyBuilding = PlayerData:isOwner(buildingData:getOwnerId())
    local isSameGuild = PlayerData:isSameGuild(buildingData:getGuildId())
    if isMyBuilding or isSameGuild then
        _changeArmyStatus(selectedArmyData, Enum.GoOutOperation.Aid, buildingData:getHomeCoor())
        return
    end

    -- 其他玩家城堡，不同国家并且在国战期间则攻击，否则显示按钮框
    if ResourcePointUtils:isCastleType(buildingData:getBuildingId()) then
        local resCountryId = buildingData:getCountryId()
        local isSameCountry = PlayerData:isSameCountry(resCountryId)
        if (not isSameCountry) and (CountryWarOpenCallback:isCountryWarOpen()) then
            _changeArmyStatus(selectedArmyData, Enum.GoOutOperation.AttackBuilding, buildingData:getHomeCoor())
        else
            _showClickCastleDialog(buildingData)
        end
        return
    end

    -- 其他势力则占领
    _changeArmyStatus(selectedArmyData, Enum.GoOutOperation.OccupyBuilding, buildingData:getHomeCoor())
end

local function _touchOtherArmy(sprite, armyData)
    _removeDialogLayer()
    _showClickArmyDialog(sprite, armyData)
end

----------------------------------------------------------------------------------------

local function _armyHasSelectedLogic(point, selectedArmyData)
    -- 再次选中军队
    local sprite, armyData = _touchArmy(point)
    if sprite and armyData then
        _selectArmy(sprite, armyData, selectedArmyData)
        return
    end

    -- 随机资源则拾取
    local randomResourceData = _touchRandomResource(point)
    if randomResourceData then
        local toCoor = MapConfig:getCoordinateFromPosition(point)
        _changeArmyStatus(selectedArmyData, Enum.GoOutOperation.Pickup, toCoor)
        M:setMyArmySelect(selectedArmyData, false)
        return
    end

    -- 建筑物
    local buildingData = _touchBuilding(point)
    if buildingData then
        if not BattleUtils:canAttackFamousCity(buildingData) then
            return
        end

        M:setMyArmySelect(selectedArmyData, false)
        _selectBuilding(buildingData, selectedArmyData)
        return
    end

    -- 空地则移动，且取消选中状态
    local toCoor = MapConfig:getCoordinateFromPosition(point)
    _changeArmyStatus(selectedArmyData, Enum.GoOutOperation.Move, toCoor)
    M:setMyArmySelect(selectedArmyData, false)
end

local function _armyUnSelectedLogic(point)
    -- 选中自家军队
    local sprite, armyData = _touchArmy(point)
    if sprite and armyData and PlayerData:isOwner(armyData:getPlayerId()) then
        M:setMyArmySelect(armyData, true)
        return
    end

    -- 选中他家军队
    if sprite and armyData then
        _touchOtherArmy(sprite, armyData)
        return
    end

    -- 随机资源
    local randomResourceData = _touchRandomResource(point)
    if randomResourceData then
        local mapLayerManager = MapManager:getMapLayerManager()
        local dialogLayer = require("ui.map-subview.ClickRandomResDialog"):newClickRandomResDialog(
                                    mapLayerManager, point, randomResourceData)
        _newDialogLayer(dialogLayer)
        return
    end

    -- 建筑物
    local buildingData = _touchBuilding(point)
    if buildingData then
        local mapLayerManager = MapManager:getMapLayerManager()
        local ResourcePointUtils = require("ui.map.data-manager.ResourcePointUtils")
        if ResourcePointUtils:isCastleType(buildingData:getBuildingId()) then
            _showClickCastleDialog(buildingData)
        else
            local dialogLayer = require("ui.map-subview.ClickBuildingDialog"):newClickCampDialog(
                                            mapLayerManager, point, buildingData)
            _newDialogLayer(dialogLayer)
        end
        return
    end

    -- 空地
    local mapLayerManager = MapManager:getMapLayerManager()
    mapLayerManager:touchGround(point)
end

------------------------------------------------------------------------
function M:touchMapLayer(point)
    -- 当前是否有选中军队
    local armyDataManager = MapManager:getArmyDataManager()
    local armyData = armyDataManager:findArmyDataSelected()
    if armyData then
        _armyHasSelectedLogic(point, armyData)
    else
        _armyUnSelectedLogic(point)
    end
end

function M:setMyArmySelect(armyData, isSelected)
    armyData:setSelected(isSelected)

    -- 军队选中
    local armySpriteManager = MapManager:getArmySpriteManager()
    local armySpriteNode = armySpriteManager:findArmySpriteNode(armyData)
    if armySpriteNode then
        armySpriteNode:setSelected(armyData:isSelected())
    end

    -- 取消Dialog
    if isSelected then
        _showClickArmyDialog(armySpriteNode, armyData)
    else
        _removeDialogLayer()
    end

    -- 指示器
    local armyLeadLayer = MapManager:getArmyLeadLayer()
    armyLeadLayer:setArmyLeadSelect(armyData)
end

return M


