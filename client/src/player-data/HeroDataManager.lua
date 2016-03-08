local HeroData = require("player-data.HeroData")

local M = {}

-- 登录时的初始化数据
function M:initHerosListFromServer(msgTable)
    local list = {}
    for _, value in pairs(msgTable) do
        local heroId = value.hero_id
        list[heroId] = HeroData:newHeroData(value)
    end
    return list
end

function M:resetToNoneState(heroId)
    local heroData = self:getHeroDataById(heroId)
    heroData:resetToNoneState()
end

function M:resetToSurviceState(heroId)
    local heroData = self:getHeroDataById(heroId)
    heroData:resetToSurviceState()
end

local function _postEvent(heroId)
    Listener:postEvent(Listener.EventName.onListenHeroDataChange, heroId)
end

-- 更新或添加单个武将数据
function M:updateHeroData(msgTable)
    -- Print:Table(msgTable, "updateHeroData")
    local heroId = msgTable.hero_id
    local herosList = PlayerData:getHeros()
    if not herosList[heroId] then
        herosList[heroId] = HeroData:newHeroData(msgTable)
    else
        herosList[heroId]:updateHeroData(msgTable)
    end
    _postEvent(heroId)
end

function M:removeHeroDataByIds(msgTable)
    for _,heroIds in pairs(msgTable) do
        for _,heroId in pairs(heroIds) do
            self:removeHeroDataById(heroId)
            _postEvent(heroId)
        end
    end
    
end

function M:removeHeroDataById(heroId)
    local herosList = PlayerData:getHeros()
    herosList[heroId] = nil
end

function M:getHeroTypeById(heroId)
    local herosList = PlayerData:getHeros()
    local heroData = herosList[heroId]
    if heroData then
        return heroData:getHeroType()
    end
end

function M:getHeroDataById(heroId)
    local herosList = PlayerData:getHeros()
    return herosList[heroId]
end

local function _tableSort(heroData1, heroData2)
    local compare = false
    if heroData1:getHeroLevel() == heroData2:getHeroLevel() then
        compare = heroData1:getHeroType() < heroData2:getHeroType()
    else
        compare = heroData1:getHeroLevel() > heroData2:getHeroLevel()
    end
    return compare
end

function M:getBackpackHeroList(level)
    local heroList = PlayerData:getHeros()
    local targetHeroList = {}
    if nil == level then
        for _,heroData in pairs(heroList) do
            if heroData:isLive() then
                table.insert(targetHeroList, heroData)
            end
        end
    else
        for _,heroData in pairs(heroList) do
            if heroData:isLive() and level == heroData:getHeroLevel()  then
                table.insert(targetHeroList, heroData)
            end
        end
    end

    table.sort(targetHeroList, _tableSort)
    return targetHeroList
end

function M:getBackpackHeroNoTeamList(level)
    local backpackHeroList = self:getBackpackHeroList(level)
    local targetHeroList = {}
    for _,heroData in pairs(backpackHeroList) do
        if Enum.HeroState.None == heroData:getHeroState() then
            table.insert(targetHeroList, heroData)
        end
    end
    return targetHeroList
end

return M