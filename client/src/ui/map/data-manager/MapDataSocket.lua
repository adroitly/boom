local HeroDataManager = require("player-data.HeroDataManager")

local BackpackDataManager 		= require("player-data.BackpackDataManager")
local SoldierDataManager 		= require("player-data.SoldierDataManager")

local ArmyInfoCallback 		= require("ui.map.logic.ArmyInfoCallback")
local BuildingInfoCallback	= require("ui.map.logic.BuildingInfoCallback")
local AttackArmyCallback 	= require("ui.map.logic.AttackArmyCallback")
local TeleportCallback 		= require("ui.map.logic.TeleportCallback")
local AttackBuildingCallback 	= require("ui.map.logic.AttackBuildingCallback")
local AttackCodeCallback 		= require("ui.map.logic.AttackCodeCallback")
local BuildingOccupyCallback 	= require("ui.map.logic.BuildingOccupyCallback")
local BuildingGuardCallback 	= require("ui.map.logic.BuildingGuardCallback")

local ArmyGoBackCallback 		= require("ui.map.logic.ArmyGoBackCallback")
local RandomResourceCallback 	= require("ui.map.logic.RandomResourceCallback")
local RandPackageGetCallback 	= require("ui.map.logic.RandPackageGetCallback")
local OutsideArmyInfoCallback 	= require("ui.map.logic.OutsideArmyInfoCallback")
local ArmyDisappearCallback 	= require("ui.map.logic.ArmyDisappearCallback")
local PackageDisappearCallback 	= require("ui.map.logic.PackageDisappearCallback")
local ArmyLostCallback 			= require("ui.map.logic.ArmyLostCallback")
local BuildingLostCallback 		= require("ui.map.logic.BuildingLostCallback")
local CountryWarOpenCallback 	= require("ui.map.logic.CountryWarOpenCallback")

local M = {}

function M:socketCallback(cmd, msgTable)
	local commons = 
	{
		[Command.HeroInfo] 		= function(msgTable) HeroDataManager:updateHeroData(msgTable) end,
		[Command.HeroDelete] 	= function(msgTable) HeroDataManager:removeHeroDataByIds(msgTable) end,
		[Command.ArmyInfo] 		= function(msgTable) ArmyInfoCallback:action(msgTable) end,
		[Command.ItemInfo] 		= function(msgTable) BackpackDataManager:updateBackpackData(msgTable) end,
		[Command.SoldierInfo] 	= function(msgTable) SoldierDataManager:updateSoldierData(msgTable) end,
		[Command.AttackArmy] 	= function(msgTable) AttackArmyCallback:action(msgTable) end,
		[Command.TestTeleport] 	= function(msgTable) TeleportCallback:action(msgTable) end,
		[Command.AttackBuilding] 	= function(msgTable) AttackBuildingCallback:action(msgTable) end,
		[Command.AttackCode]		= function(msgTable) AttackCodeCallback:action(msgTable) end,
		[Command.BuildingOccupy] 	= function(msgTable) BuildingOccupyCallback:action(msgTable) end,
		[Command.BuildingGuard]  	= function(msgTable) BuildingGuardCallback:action(msgTable) end,
		[Command.OutsideArmyInfo] 	= function(msgTable) OutsideArmyInfoCallback:action(msgTable) end,
		[Command.ArmyGoBack] 		= function(msgTable) ArmyGoBackCallback:action(msgTable) end,
		[Command.SituationPackage] 	= function(msgTable) RandomResourceCallback:action(msgTable) end,
		[Command.RandPackageGet]   	= function(msgTable) RandPackageGetCallback:action(msgTable) end,
		[Command.BuildingInfo] 		= function(msgTable) BuildingInfoCallback:action(msgTable) end,
		[Command.ArmyDisappear] 	= function(msgTable) ArmyDisappearCallback:action(msgTable) end,
		[Command.PackageDisappear] 	= function(msgTable) PackageDisappearCallback:action(msgTable) end,
		[Command.Arrive] 			= function(msgTable) MapManager:getArmyDataManager():arriveCommonCallback(msgTable) end,
		[Command.ArmyLost]		    = function(msgTable) ArmyLostCallback:action(msgTable) end,
		[Command.BuildingLost]		= function(msgTable) BuildingLostCallback:action(msgTable) end,
		[Command.CountryWarOpen] 	= function(msgTable) CountryWarOpenCallback:action(msgTable) end,
	}

	Function:safeCall(commons, cmd, msgTable)
end

return M