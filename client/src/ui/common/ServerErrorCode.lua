
-- 服务器返回的错误码，必须与服务器保持统一

local ServerErrorCode = 
{
    SUCCESS     = 0, 
    FAIL        = 1,

    SUCCESS     = 0,        -- 成功
    FAIL        = 1,        -- 失败
    BOX_FAIL    = 2,        -- 格子和对应的目标id不一样
    ATTACK_DISTANCE_FAIL = 3,        -- 攻击距离不在范围
    ATTACK_BUILDING_FAIL = 4,        -- 攻击了一个没有血量，也没有驻守的建筑
    ATTACK_MY_ARMY_DEATH = 5,        -- 自己的军队死亡
    ATTACK_TO_ARMY_DEATH = 6,        -- 敌人的军队死亡

    NO_OPERATE  = 8,            -- 无用（无效果）操作
    BUILDING_HP = 10,           -- 占领的时候，building hp 大于0
    BUILDING_GARRISONS_SIZE = 11,        -- 占领的时候，已经有人驻守
    ARMY_DEATH  = 12,           -- 驻守的时候，军队被人打死了
    BUILDING_OCCUPY_OTHER   = 13,          -- 自己的盟友已经占领了这座城

    ATTACK_MYSELF_BUILDING = 13,    -- 不能攻击自己建筑
    ATTACK_FRIEND_BUILDING = 14,    -- 不能攻击同势力建筑

    ITEM_NOT_ENOUGH = 15,           -- item 不足
    INPUT_TOO_LONG  = 16,           -- 输入太长
    COUNT_NOT_ENOUGH = 17,          -- 次数不够

    ARMY_DEAD = 18,                 -- 军队已经死亡
    ARMY_STATE_ERROR = 19,          -- 军队状态不对，比如使用“木牛流马”道具的时候，军队需要在外城
    USER_LEVEL_LIMIT = 20,          -- 玩家等级限制

    MAX_LIVEL_LIMIT = 21,           -- 超过最大等级限制
    TIME_LIMIT = 22,                -- 时间限制
    NUMBER_LIMIT = 23,              -- 生产队列限制
    CASTLE_NOT_OCCUPIED = 24,       -- 主城不能占领
    SAME_COUNTRY = 25,              -- 相同国家

    HAD = 26,       -- 已领取
    AUCTION_SOLD = 27,          -- 已出售
    AUCTION_OFF = 28,       -- 已下架
    AUCTION_SOLD_ING = 29,          -- 出售中

    NOT_SAME_COUNTRY = 30,          -- 不同国家
    
    GUILD_JOINED_ERROR = 100,        -- 已加入势力
    GUILD_NOT_EXSITS = 101,          -- 势力不存在
    GUILD_USER_NOT_ENOUGH_LEVEL = 102,           -- 玩家等级不足 不能加入势力
    GUILD_NOT_EXSITS_APPLY_LIST = 103,          -- 玩家已不在 申请势力列表 中
    GUILD_MAX_GUILD_SKILL = 104,        -- 势力技能已满级
    GUILD_SKILL_UPING = 105,        -- 正在升级中 无需再次请求升级
    GUILD_NOT_ENOUGH_CB = 106,          -- 势力贡献值不足
    GUILD_NOT_ENOUGH_LEVEL = 107,       -- 势力等级不足
    GUILD_NO_ALLOW_KING_EXIT = 108,         -- 不允许君王退出势力
    GUILD_NOT_JOIN = 109,       -- 未加入势力
    GUILD_NO_AUTH = 110,         -- 无操作权限
    GUILD_APPLYS_LIST_LIMIT = 111,           -- 申请列表限制

    GUILD_QUIT_FAILED_HAD_GRARRISON = 112,           -- 有军队驻守名城，不能退出军队
    GUILD_NOT_SAME = 113,        -- 不同势力
    GUILD_SAME = 114,            -- 同势力
    
    USER_IS_NULL = 200,          -- 用户不存在
    USER_EXIST = 201,        -- 用户存在
    SESSION_EXPIRE = 202,        -- session 过期
    NAME_EXIST = 203,        -- 用户名存在
    USER_FULL = 204,         -- 服务器满，不能注册

    ARMY_CANCEL_FAIL = 300,          -- 军队解散失败
    ARMY_CREATE_FAIL = 301,          -- 军队创建失败
    HERO_IN_SERVICE = 302,           -- 军队创建时， 英雄已经在编队中
    HERO_IS_DEATH = 303,         -- 军队创建时， 英雄已经受伤了，不能创建
    SOLDIER_NOT_ENOUGTH = 304,           -- 军队创建时， 士兵不够
    ARMY_LIMIT = 305,        -- 出军数量超过5支

    HERO_LEVEL_LIMIT = 306,          -- 英雄等级限制

    HERO_FAIL = 400,         -- 军队解散失败

    LOGIN_OTHER = 1000,          -- 其他设备登陆
}

return ServerErrorCode





