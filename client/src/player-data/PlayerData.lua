local DataSave = require("share.DataSave")
local MapConfig = require("ui.map.data-manager.MapConfig")
local TeamDataManager = require("player-data.TeamDataManager")
local HeroDataManager = require("player-data.HeroDataManager")
local SoldierDataManager = require("player-data.SoldierDataManager")
local BackpackDataManager = require("player-data.BackpackDataManager")
local GuildDataManager = require("player-data.GuildDataManager")
local UserInfoData = require("player-data.UserInfoData")
local BuildingData = require("ui.map.data-manager.BuildingData")
local M = class("player-data.PlayerData")
local PlayerDataPath = "archive/data.bin"

function M:ctor()
	self._playerData = DataSave.loadTable(PlayerDataPath) or {}
	-- 好友邮件
	self._playerData.personalMailList = self._playerData.personalMailList or {}
	-- self._playerData.systemMailList = self._playerData.systemMailList or {}
	self._playerData.gameMailList = self._playerData.gameMailList or {}
end

function M:logout()
	self._playerData = {}
	self._playerData.personalMailList = {}
	-- self._playerData.systemMailList = {}
	self._playerData.gameMailList = {}
	self._systemMailList = {}
	self._herosList = nil 
	self._soldiersList = nil 
	self._teamList = nil 
	self._backpackItemList = nil
	self._guildData = nil
	self._guildMemberData = nil
	self._castleBuildingData = nil
	self._countryId = 0
end

function M:save()
	DataSave.saveTable(PlayerDataPath, self._playerData)
end

function M:initLoginInfo(info)
	self._systemMailList = {}
	assert(info.user_info)
	
	self._userInfoData = UserInfoData.new(info.user_info)
	self._curTime = os.time()

	self._herosList = HeroDataManager:initHerosListFromServer(info.heros)
	self._soldiersList = SoldierDataManager:initSoldiersListFromServer(info.soldiers)
	self._teamList = TeamDataManager:initTeamListFromServer(info.armies)
	-- test背包Item
	self._backpackItemList = BackpackDataManager:initBackpackData(info.items)
	
	GuildDataManager:initGuildData(info.guild_own_info)

	local uniqueId = Utils:getUniqueId(info.building_info.x, info.building_info.y)
	self._castleBuildingData = BuildingData.new(info.building_info, uniqueId)

	self:save()
end

function M:getUserInfoData()
    return self._userInfoData
end 

function M:getType()
	-- type类型：1测试，2账号登陆，3weixin登陆，4QQ登陆，5微博登陆
	return 1
end

function M:getPlayerId()
	return self._userInfoData:getPlayerId()
end

function M:getNickname()
	return self._userInfoData:getNickname()
end

function M:getHomeCoor()
	local homePos = self._userInfoData:getHomePos()
	return MapConfig:coordinate(homePos.x, homePos.y)
end

function M:getCastleBuildingData()
	return self._castleBuildingData
end

function M:getCastleLevel()
	return self._castleBuildingData:getLevel()
end

function M:getGuildData()
	return self._guildData
end

function M:resetGuildData(guildData)
	self._guildData = guildData
end

function M:resetGuildMemberData(guildMemberData)
	self._guildMemberData = guildMemberData
end

function M:getGuildMemberData()
	return self._guildMemberData
end

-- 获得势力Id
function M:getGuildId()
	return self._userInfoData:getGuildId()
end

function M:isHasGuild()
	return self._userInfoData:getGuildId() ~= 0
end

function M:isSameGuild(guildId)
	local ownGuildId = self:getGuildId()
	return self:isHasGuild() and ownGuildId == guildId
end


function M:isSameCountry(countryId)
	return self:getCountryId() ~= 0 and self:getCountryId() == countryId
end

function M:getCountryId()
	return self._userInfoData:getCountryId()
end

function M:isOwner(playerId)
	assert(playerId)
	return playerId == self:getPlayerId()
end

function M:getNickName()
	return self._userInfoData:getNickname()
end

function M:getServerTime()
	local interval = os.time() - self._curTime
	return self._userInfoData:getServerTime() + interval
end

function M:getHeros()
	return self._herosList
end

function M:getSoldiers()
	return self._soldiersList
end

function M:getTeamList()
	return self._teamList
end

function M:getBackpackItemList()
	return self._backpackItemList
end

function M:getPersonalMailList()
	return self._playerData.personalMailList
end

function M:getSystemMailList()
	return self._systemMailList
end

function M:getGameMailList()
	return self._playerData.gameMailList
end

function M:getPlayerIconFrame()
	local icon = PlayerData:getUserInfoData():getIcon()
    local iconName = icon .. ".png"
    local frame = CommonUI:createSpriteFrameTinyName("hero-icon", iconName)
    return frame
end

return M    
