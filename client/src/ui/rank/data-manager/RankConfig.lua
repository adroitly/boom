local M = {}
M.RankCount = 8
M.RankType = {
    Country         = 1,
    Score           = 2,
    Guild           = 3,
    Officer         = 4,
    Coin            = 5,
    Food            = 6,
    Jade            = 7,
    Stone           = 8,
    Wood            = 9,
}

M.RankName = {
    [M.RankType.Country]        = "国战国家积分排行榜",
    [M.RankType.Score]          = "国战个人积分排行榜",
    [M.RankType.Guild]          = "势力排行榜",
    [M.RankType.Officer]        = "官职排行榜",
    [M.RankType.Coin]           = "财富排行榜",
    [M.RankType.Food]           = "农业排行榜",
    [M.RankType.Jade]           = "玉商排行榜",
    [M.RankType.Wood]           = "伐木排行榜",
    [M.RankType.Stone]          = "采矿排行榜",
}
M.RankOwnName = {
    [M.RankType.Country]        = "国家排名",
    [M.RankType.Score]          = "我的排名",
    [M.RankType.Guild]          = "我的势力排名",
    [M.RankType.Officer]        = "我的排名",
    [M.RankType.Coin]           = "我的排名",
    [M.RankType.Food]           = "我的排名",
    [M.RankType.Jade]           = "我的排名",
    [M.RankType.Wood]           = "我的排名",
    [M.RankType.Stone]          = "我的排名",
}
M.RankValueName = {
    [M.RankType.Country]        = "积分",
    [M.RankType.Score]          = "积分",
    [M.RankType.Guild]          = "占领名城",
    [M.RankType.Officer]        = "等级",
    [M.RankType.Coin]           = "铜币",
    [M.RankType.Food]           = "粮食",
    [M.RankType.Jade]           = "元气玉",
    [M.RankType.Wood]           = "木料",
    [M.RankType.Stone]          = "石料",
}
return M