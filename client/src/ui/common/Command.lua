
-- 服务器接口命令
local Command = 
{
    ConnectSuccess     = "StatusServerConnectSuccess",
    ConnectFailed      = "StatusServerConnectFaild",
    ConnectIng         = "StatusServerConnectIng",
    Register           = "register",
    Login              = "login",
       
    BuildingInfo       = "building_info",
    
    AttackArmy         = "attack_army",
    AttackBuilding     = "attack_building",
    AttackCode         = "attack_code",
    Arrive             = "arrive",
    Situation          = "situation",
    BuildingOccupy     = "building_occupy",
    BuildingGuard      = "building_guard",
    BuildingUnguard    = "building_unguard",
    BuildingLost       = "building_lost", 
    ViewChange         = "view_change",
    ViewDataGet        = "view_data_get",
    AttackAlert        = "attack_alert",
    ArmyGoBack         = "army_go_back",
    ArmyGo             = "army_go",
    ArmyDisappear      = "army_disappear",
    ArmyLost           = "army_lost",
    PackageDisappear   = "package_disappear",

    HeroInfo           = "hero_info",
    HeroDelete         = "hero_delete",
    ArmyInfo           = "army_info", 
    ItemInfo           = "item_info",
    SoldierInfo        = "soldier_info",
    OutsideArmyInfo    = "outside_army_info",

    SituationPackage   = "situation_package",
    RandPackageGet     = "rand_package_get",

    TestTeleport       = "test_teleport",

    ArmyPromote        = "army_promote",
    ArmyPromoteSpeed   = "army_promote_immediately",
    ArmyGoBackUseItem  = "army_go_back_use_item",
    ArmyPromoteOutside = "army_promote_immediately_outside",
    ArmyAddFoodOutside = "army_add_food_outside",
    ArmyAddSoldierOutside = "army_add_soldier_outside",

    ServiceUse         = "service_use",
    CountryWarOpen     = "country_war_open", 
}

return Command





