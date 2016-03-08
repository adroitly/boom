-- Lua没有枚举型，统一这里设置

local Enum = {}

Enum.ArmyAnimName = {
    Attack  = "attack",
    Wait    = "wait",
    Walk    = "walk",
    Die     = "die",
}
Enum.TeamDataState =
{
    Inside  = 1,
    Outside = 2,
    Guard   = 3,
}

Enum.BuildingType = 
{
    Castle          = 1,
    ResourcePoint   = 2,
    Camp            = 3,
    FamousCity      = 4,
    Wild            = 14010,
}

Enum.GoOutOperation = 
{
    Wait           = 0,
    Move           = 1,
    AttackArmy     = 2,
    AttackBuilding = 3,     -- 攻击资源点、城堡等
    OccupyBuilding = 4,     -- 占领
    GoHome         = 5,     -- 回城
    Aid            = 6,     -- 援助
    Pickup         = 7,     -- 拾取随机资源
}

Enum.HeroState = 
{
    None    = 1,    -- 未编队
    Survice = 2,    -- 已编队
}

Enum.MailType = 
{
    UnRead = 1,
    Read   = 2,
    Deleted= 3,
}

Enum.GameMailResultType = 
{
    Success = 0,
    Failed  = 1,
}

Enum.ResourceOperateType = 
{
    Donate  = 1,
    Save    = 2,
    Take    = 3,
}

Enum.ResourceType = 
{
    Food          = 50801, -- 粮食
    Wood          = 50802, -- 木材
    Stone         = 50803, -- 石头
    Coin          = 50804, -- 铜币
    Jade          = 50805, -- 元气玉
    Gold          = 50806, -- 元宝
    BackToken     = 50708, -- 回城令
    SupplyFood    = 50704, -- 木牛流马，补粮食
    SupplyPromote = 50705, -- 孟德新书，补士气
    SupplySoldier = 50709, -- 补兵令,野外补兵
}

Enum.CheckBackpackType = 
{
    DoctorType           = 50601, -- 华佗再世
    OfficerType          = 50710, -- 洛书
    ProduceSoldierType   = 50201, -- 虎符
    ProduceResourcesType = 50101, -- 徭役令
    PlayerSolderType     = 50301, -- 战鼓

}

Enum.MainPageBackpackType = 
{
    -- NatureBuff = 50703,  -- 孙子兵法
    -- Stealth    = 50707,  -- 瞒天过海
    Getaway    = 50706,  -- 金蝉脱壳
}

Enum.SendMailType = 
{
    Normal      = 1,
    Personal    = 2,
    Guild       = 3,
}

Enum.GuildNewMemberOperate = 
{
    Agree       = 1,        -- 同意
    Refuse      = 2,        -- 拒绝
    AgreeTotal  = 3,        -- 全部同意
    RefuseTotal = 4,        -- 全部拒绝
}

Enum.GuildSetting = 
{
    AutoClose       = 1,        -- 自动加入关闭
    AutoOpen        = 2,        -- 自动加入开启
}

Enum.GuildTitle = 
{
    Leader          = 1,        -- 君王
    Noblemen        = 2,        -- 候
    Nobility        = 3,        -- 爵
    Normal          = 4,        -- 普通成员
}

Enum.GuildMemberOperate = 
{
    Transfer        = 1,        -- 禅让
    Noblemen        = 2,        -- 为候
    Nobility        = 3,        -- 为爵
    Normal          = 4,        -- 为普通成员
    KickOut         = 5,        -- 踢出
    LookOver        = 6,        -- 查看
}

-- 加速类型
Enum.SpeedUpType = 
{
    OneProduceResource   = 1,
    TotalProduceResource = 2,
    OneProduceSoldier    = 3,
    TotalProduceSoldier  = 4,
    OneHeroPromote       = 5,
    AllHeroPromote       = 6,
    OneDoctorHero        = 7,
    AllDoctorHero        = 8,
}

Enum.GuildSkillUpgradeTime = 
{
    UpgradeDone     = -1,       -- 势力技能升级完成状态
}

Enum.ProduceType = 
{
    Soldier = 1,
    Resource = 2,
}

Enum.TextVAlignment =
{
    Top = 0,
    Center = 1,
    Bottom = 2,
}

Enum.TextHAlignment = 
{
    Left = 0,
    Center = 1,
    Right = 2,
}

Enum.ZOrder = 
{
    BuildingMax = 200000,
    RandomRes   = 200001,
    Army        = 200002,
    Dialog      = 200003,
}

Enum.UpgradeHeroType = 
{
    StuffOne = 1,      -- 材料1
    StuffTwo = 2,      -- 材料2
    Target   = 3,      -- 升星目标,保证这个为最后，否则出错
}

Enum.Tag = 
{
    InnertCityLayer = 10000,
}

Enum.HomeButtonFileName = 
{
    MapLayer = "ui/main-page/main-button01.png",
    InnertCityLayer = "ui/main-page/main-button02.png",
}

Enum.ServerListState = 
{
    New         = 1,    -- 新服
    Fluency     = 2,    -- 流畅
    Hot         = 3,    -- 火爆
    Maintain    = 4,    -- 维护
    Unknow      = 5,    -- 未知 
    Recommend   = 6,    -- 推荐
}
-- resource_id = 1; // 1道具, 2士兵, 3武将
Enum.ResourceTypeId = 
{
    Item = 1,
    Soldier = 2,
    Hero = 3,
}

Enum.MarketConfig = 
{
    MaxSellNumber = 5,
    OnePageNumber = 18,
}

Enum.RichType = 
{
    Label = 1,
    Image = 2,
    Button = 3,
    TextButton = 4
}

Enum.TipsType = 
{
    ProduceResources = 1,
    ProduceSoldier = 2,
    LevelUp = 3,
    CityLevelUp = 4,
    Email = 5,
    PickMoney = 6,
}

Enum.Sex = 
{
    Male = 1,
    Female = 2,
}

Enum.LayerTag = 
{
    ProduceSoldier = 255,
    ProduceResources = 254,
    CastleUpgrade = 253,
    PlayerLevelUpgrade = 252
}

Enum.GuildCountryType = 
{
    OwnCountry = 1,
    AllCountry = 2,
}

Enum.CountryWarRelation = 
{
    None = 0,           -- 无
    FightTo = 1,        -- 宣战
    BeFight = 2,        -- 被宣战
}

Enum.CountryWarResultType = 
{
    Success = 0,
    Failed  = 1,
}

-- 几种常见的颜色集合
Enum.Color = 
{
    Red    = cc.c4b(255, 0, 0, 255),
    Green  = cc.c4b(0, 255, 0, 255),
    Blue   = cc.c4b(0, 0, 255, 255),
    Yellow = cc.c4b(255, 255, 0, 255),
    Black  = cc.c4b(0, 0, 0, 255),
    White  = cc.c4b(255, 255, 255, 255),
    Normal = cc.c4b(255, 255, 255, 255),
}

-------------------------------- Enum定义请写在上面 ---------------------------------------------

setmetatable(Enum, {__index = function(enum, key)
    assert(false, string.format("Enum.%s不存在", key))
end})


for key,value in pairs(Enum) do
    setmetatable(value, {__index = function(enum, subKey)
    assert(false, string.format("Enum.%s.%s不存在", key, subKey))
    end})
end

return Enum





