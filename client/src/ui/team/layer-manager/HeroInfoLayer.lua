local BackgroundLayer = require("ui.common.BackgroundLayer")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local HeroAttribute = require("ui.team.data-manager.HeroAttribute")
local SoldierDataManager = require("player-data.SoldierDataManager")
local HeroDataManager = require("player-data.HeroDataManager")
local SoldierConfigReader = require("config-reader.SoldierConfigReader")
local MapConfig = require("ui.map.data-manager.MapConfig")
local GoOutInfo = require("ui.map.data-manager.GoOutInfo")
local CountryConfigReader = require("config-reader.CountryConfigReader")

local M = class("ui.team.layer-manager.HeroInfoLayer" , function ()
	return cc.Layer:create()
end)

function M:ctor()
	self:_createBackgound()
	self:_createHeroIcon()
	self:_createInfoLayer()
	self:_createSkillLayer()
	self:_createDesc()
end


function M:reloadLayerByArmyData(armyData)
	self._isOutside = true
	local heroData = armyData:getHeroData()
	self._teamData = armyData:getTeamData()
	self:_reloadData(heroData)
end

function M:reloadLayerByTeamData(teamData)
	self._teamData = teamData
	assert(teamData)
	local heroId = self._teamData:getHeroId()
	assert(heroId)
	local heroData = HeroDataManager:getHeroDataById(heroId)
	assert(heroData)
	self:_reloadData(heroData)
end

function M:reloadLayerByHeroData(heroData)
	self._heroData = heroData
	self:_reload(heroData)

end

function M:reloadOtherPlayerData(otherPlayerData)
	local nickName = otherPlayerData:getNickname()
	local leaderName = otherPlayerData:getGuildLeaderName()
	local countryId = otherPlayerData:getCountry()
	local countryName = CountryConfigReader:getCountryName(countryId)
	local guildName = otherPlayerData:getGuildName()
	local titleName = otherPlayerData:getGuildTitle()
	self._playNameSprite:setText(nickName)
	self._guildNameSprite:setText(guildName)
	self._countrySprite:setText(countryName)
	self._leaderSprite:setText(leaderName)
	self._guildTitleSprite:setText(titleName)
end

function M:_reloadData(heroData)
	self._heroData = heroData
	local soldierType = self._teamData:getSoldierType()
	assert(soldierType)
	local soliderCount = self._teamData:getSoldierNumber()
	assert(soliderCount)
	self:_reload(heroData, soldierType, soliderCount)
	self:_reloadTeamNodes(soldierType, soliderCount)
end

function M:_reloadTeamNodes(soldierType, soliderCount)
	local grainCount = SoldierConfigReader:getFood(soldierType) * soliderCount
	self._grainSprite:setText(__Localized("粮草:")..grainCount)
	local energy = self._heroData:getHeroEnergy()
	if self._isOutside then
		energy = self._heroData:getHeroEnergyOutside()
		self._isOutside = false
	end
	local energyCount = math.floor(energy)
	self._energySprite:setText(__Localized("士气")..energyCount)
end

function M:_reload(heroData, soldierType, soliderCount)
	local heroType = heroData:getHeroType()
	local heroLevel = heroData:getHeroLevel()
	local heroSkills = HeroConfigRead:getSkill(heroType)
	local recommendID = HeroConfigRead:getRecommendSoldier(heroType)
	local commanderCount = HeroAttribute:getCommander(heroType, heroLevel)
	local forceCount = HeroAttribute:getForce(heroType, heroLevel)
	local brainsCount = HeroAttribute:getBrains(heroType, heroLevel)
	local recommendName = SoldierConfigReader:getNameByType(recommendID)
	local heroDesc = HeroConfigRead:getDesc(heroType)
	local constitution = HeroAttribute:getConstitution(heroType, heroLevel)

	self._heroIcon:reload(self._heroData)
	self._commander:setText(__Localized("统帅:")..commanderCount)
	self._force:setText(__Localized("武力:")..forceCount)
	self._brains:setText(__Localized("智力:")..brainsCount)
	self._injury:setText(__Localized("体质:")..constitution)
	self._descLabel:setString(heroDesc)

	if soldierType then
		local soliderName = SoldierConfigReader:getName(soldierType)
		self._soldierSprite:setText(soliderName..soliderCount)
		self._background:reloadLayer(__Localized("部队信息"))
		self:_armyDataLayerUpdate()
		self:_positionUpdate(true)
	else
		self._soldierSprite:setText(__Localized("推荐:")..recommendName)
		self._background:reloadLayer(__Localized("武将信息"))
		self:_positionUpdate(false)
	end
	self._skillsLayer:reload(heroSkills, heroLevel)
end

-- 需要做位移的移动
function M:_positionUpdate(isTeam)
	self._energySprite:setVisible(isTeam)
	self._grainSprite:setVisible(isTeam)
	local soldierSize = self._soldierSprite:getContentSize()
	if isTeam then
		self._soldierSprite:setPosition(soldierSize.width, soldierSize.height)
	else
		self._soldierSprite:setPosition(Screen.width / 2, soldierSize.height)
	end
end

function M:_getTeamState()
	local state = self._teamData:getState()
	return state
end

function M:_getTeamPosition()
	local coor = self._teamData:getCooridnate()
    local twoDCoor = MapConfig:localTo2D(coor)
	return twoDCoor
end

function M:_armyDataLayerUpdate()
	local zeroHeight = Screen.height - Screen.height / 8 - self._heroIconSize.height * 3 + Screen.height / 6
	self:_createGuildNodes(zeroHeight)
	self:_createTeamStateNodes(zeroHeight)
end

function M:_createGuildNodes(zeroHeight)
	local playerName = PlayerData:getNickName()
	local guildData = PlayerData:getGuildData()
	local memberData = PlayerData:getGuildMemberData()
	local leaderName = guildData:getLeaderName()
	local countryId = PlayerData:getUserInfoData():getCountryId()
	local countryName = CountryConfigReader:getCountryName(countryId)
	local guildName = guildData:getName()
	local titleName = memberData:getTitle()
	self._playNameSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", playerName)
	local spriteSize = self._playNameSprite:getContentSize()
	local PosiX = Screen.width / 2
	local PosiY = Screen.height - BackgroundLayer.TitleHeight - spriteSize.height / 2
	self._playNameSprite:setPosition(cc.p(PosiX, PosiY))

	self._guildTitleSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", titleName)
	self._guildTitleSprite:setPosition(spriteSize.width / 2, zeroHeight + spriteSize.height / 2)

	self._guildNameSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", guildName)
	self._guildNameSprite:setPosition(spriteSize.width / 2, zeroHeight + spriteSize.height + spriteSize.height / 2)

	self._countrySprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", countryName)
	self._countrySprite:setPosition(spriteSize.width / 2, zeroHeight + spriteSize.height * 2 + spriteSize.height / 2)

	self._leaderSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", leaderName)
	self._leaderSprite:setPosition(spriteSize.width / 2, zeroHeight + spriteSize.height * 3 + spriteSize.height / 2)
end

function M:_createTeamStateNodes(zeroHeight)
	local teamPosi = self:_getTeamPosition()
	local positionX = teamPosi.i or ""
	local positionY = teamPosi.j or ""
	local state = self:_getTeamState()
	local station = "空地"
	local stateName = ""

	self._positionSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", __Localized("坐标:")..positionX..","..positionY)
	local spriteSize = self._positionSprite:getContentSize()
	self._positionSprite:setPosition(Screen.width - spriteSize.width / 2, zeroHeight + spriteSize.height / 2)

	self._stationSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", __Localized("所在区域:")..station)
	self._stationSprite:setPosition(Screen.width - spriteSize.width / 2, zeroHeight + spriteSize.height + spriteSize.height / 2)

	self._stateSprite = CommonUI:createTextSprite(self, "ui/login/register-bt.png", __Localized("状态:")..stateName)
	local stateSpriteSize = self._stateSprite:getContentSize()
	self._stateSprite:setPosition(Screen.width - spriteSize.width / 2, zeroHeight + spriteSize.height * 2 + stateSpriteSize.height / 2)

	if state == 1 then
		station = __Localized("内城")
		stateName = __Localized("")
		self._positionSprite:setVisible(false)
		self._stateSprite:setVisible(false)
		self._stationSprite:setPosition(Screen.width - spriteSize.width / 2, zeroHeight + spriteSize.height / 2)
		-- self:_createHeroPosLayer("洛阳")
	elseif state == 2 then
		station = __Localized("外城")
		stateName = __Localized("移动")
	elseif state == 3 then
		station = __Localized("驻守")
	end
	self._stationSprite:setText(__Localized("所在区域:")..station)
	self._stateSprite:setText(__Localized("状态:")..stateName)
end

function M:_createHeroPosLayer(posName)
	local textFieldPosX = require("share.TextField").new(26)
	local textFieldPosY = require("share.TextField").new(26)
	textFieldPosX:setPlaceHolder(__Localized("请输入"))
	textFieldPosY:setPlaceHolder(__Localized("请输入"))

	local posLayer = cc.LayerColor:create(cc.c4b(255, 255, 0, 160) , Screen.width , 150)
	posLayer:setPosition(0, 0)
	local affirmButton = CommonUI:createTextButton(posLayer, "出征","ui/login/register-bt.png", "ui/login/login-bt.png")
	local iconSize = affirmButton:getContentSize()
	affirmButton:setPosition(Screen.width - 100 , iconSize.height / 2)
	affirmButton.onClicked = function ()
		local inputXStr = textFieldPosX:getString()
		local inputYStr = textFieldPosY:getString()
		local inputX = tonumber(inputXStr)
		local inputY = tonumber(inputYStr)
		if inputX and inputY then
			-- local twoDCoor = MapConfig:coordinate(inputX, inputY)
			-- self._goOutInfo = GoOutInfo:newDefalutInfo(twoDCoor)
			-- local armyId = self._teamData:getArmyId()
			-- local playerId = PlayerData:getPlayerId()
			-- local armyGoData = {player_id = playerId, army_id = armyId}
			-- SocketManager:send(Command.ArmyGo, armyGoData)
		else
			CommonUI:lightTips(__Localized("输入中有非数字"))
		end
	end
	local posNameLabel = CommonUI:createLabel(posName.."坐标")
	local posNameLabelSize = posNameLabel:getContentSize()
	local posNameLabelPosi = cc.p(100 , iconSize.height / 2)
	posNameLabel:setPosition(posNameLabelPosi)
	posLayer:addChild(posNameLabel)
	self:addChild(posLayer)

	textFieldPosX:setPosition(posNameLabelPosi.x + posNameLabelSize.width / 2 + 50 , iconSize.height / 2)
	textFieldPosY:setPosition(posNameLabelPosi.x + posNameLabelSize.width / 2 + 150 , iconSize.height / 2)
	posLayer:addChild(textFieldPosX)
	posLayer:addChild(textFieldPosY)
end

function M:_createDesc(heroType)
	local layerHeight = Screen.height / 8
	local descLayer = cc.LayerColor:create(cc.c4b(125, 125, 125, 125) , Screen.width , layerHeight)
	descLayer:setPosition(0 , layerHeight)
	local titleLabel = CommonUI:createLabel("武将背景描述")
	local titleLabelSize = titleLabel:getContentSize()
	descLayer:addChild(titleLabel)
	titleLabel:setPosition(Screen.width / 2 , layerHeight - titleLabelSize.height / 2)
	self._descLabel = CommonUI:createLabel(__Localized("test") , 20)
	local descLabelSize = self._descLabel:getContentSize()
	self._descLabel:setDimensions(Screen.width, layerHeight / 2)
	self._descLabel:setPosition(Screen.width / 2 , layerHeight / 2 - descLabelSize.height)
	descLayer:addChild(self._descLabel)
	self:addChild(descLayer)

end

function M:_createHeroIcon()
	self._heroIcon = require("ui.common.HeroIcon").new()
	self._heroIconSize = self._heroIcon:getContentSize()
	self._heroIcon:setPosition(cc.p(Screen.width / 2 , Screen.height - Screen.height / 8 - self._heroIconSize.height / 2 - 20))
	self:addChild(self._heroIcon)
end

function M:_createInfoLayer()
	local layerHeight = Screen.height / 6
	local layer = cc.LayerColor:create(cc.c4b(255, 255, 0, 160) , Screen.width , layerHeight)
	layer:setPosition(0 , Screen.height - Screen.height / 8 - self._heroIconSize.height * 3)
	self:addChild(layer)
	self._commander = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("统帅:0"))
	local commanderSize = self._commander:getContentSize()
	local layerTopHeight = commanderSize.height
	self._commander:setPosition(commanderSize.width, layerHeight - layerTopHeight / 2)

	self._force = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("武力:"..0))
	local forceSize = self._force:getContentSize()
	self._force:setPosition(commanderSize.width + forceSize.width, layerHeight - layerTopHeight / 2)

	self._brains = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("智力:"..0))
	local brainsSize = self._brains:getContentSize()
	self._brains:setPosition(Screen.width / 2, layerHeight - layerTopHeight / 2)

	self._injury = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("伤势:"..0))
	local injurySize = self._injury:getContentSize()
	self._injury:setPosition(Screen.width / 2  + injurySize.width, layerHeight - layerTopHeight / 2)

	self._soldierSprite = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("推荐:".."女兵"))
	local soldierSize = self._soldierSprite:getContentSize()
	self._soldierSprite:setPosition(soldierSize.width, soldierSize.height)

	self._grainSprite = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("粮草:"..0))
	local grainSize = self._grainSprite:getContentSize()
	self._grainSprite:setPosition(Screen.width / 2 - grainSize.width, grainSize.height)

	self._energySprite = CommonUI:createTextSprite(layer , "ui/login/login-bt.png", __Localized("士气:"..0))
	local energySize = self._energySprite:getContentSize()
	self._energySprite:setPosition(Screen.width / 2 , energySize.height)

	self._InfoLayerSize = {
	width = Screen.width,
	height = layerHeight }
end


function M:_createSkillLayer()
	self._skillsLayer = require("ui.team.layer-manager.UserSkillLayer").new()
	self:addChild(self._skillsLayer)
	self._skillsLayer:setPosition(cc.p(0, Screen.height / 2))
end

function M:_createBackgound()
	self._background = BackgroundLayer.new(self)
	self._background:setBackButtonCallback(function ()
        self:removeFromParent()
    end)
end

return M