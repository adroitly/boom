--[[ SheetEditor v1.0
ID,名称,描述,类型概率,掉落信息,描述,
*id,name,description,probability,dropitem,desc,
sorted = { 0, 'a' }
--]]

local M = {
    [51001] = {
        id = 51001,
        name = "粮食",
        description = "一大捆麦穗堆起来",
        probability = 1500,
        dropitem = "1,50401,100,1000;1,50801,200,1000;1,50801,300,1000;1,50801,400,1000;1,50801,500,1000;1,50801,600,1000;1,50801,700,1000;1,50801,800,1000;1,50801,900,1000;1,50801,1000,1000",
        desc = "派遣部队拾取该资源后可直接获得。",
    },
    [51002] = {
        id = 51002,
        name = "木材",
        description = "一堆建筑用的木材，游戏的主要建筑用料",
        probability = 1500,
        dropitem = "1,50802,100,1000;1,50802,200,1000;1,50802,300,1000;1,50802,400,1000;1,50802,500,1000;1,50802,600,1000;1,50802,700,1000;1,50802,800,1000;1,50802,900,1000;1,50802,1000,1000",
        desc = "派遣部队拾取该资源后可直接获得。",
    },
    [51003] = {
        id = 51003,
        name = "石料",
        description = "很多的碎石对方起来的小山",
        probability = 1500,
        dropitem = "1,50803,100,1000;1,50803,200,1000;1,50803,300,1000;1,50803,400,1000;1,50803,500,1000;1,50803,600,1000;1,50803,700,1000;1,50803,800,1000;1,50803,900,1000;1,50803,1000,1000",
        desc = "派遣部队拾取该资源后可直接获得。",
    },
    [51004] = {
        id = 51004,
        name = "铜币",
        description = "一堆青铜铸造的铜币，游戏的主要货币之一",
        probability = 1500,
        dropitem = "1,50804,100,1000;1,50804,200,1000;1,50804,300,1000;1,50804,400,1000;1,50804,500,1000;1,50804,600,1000;1,50804,700,1000;1,50804,800,1000;1,50804,900,1000;1,50804,1000,1000",
        desc = "派遣部队拾取该资源后可直接获得。",
    },
    [51005] = {
        id = 51005,
        name = "元气玉",
        description = "很多块元气玉堆成的小山",
        probability = 1500,
        dropitem = "1,50805,100,1000;1,50805,200,1000;1,50805,300,1000;1,50805,400,1000;1,50805,500,1000;1,50805,600,1000;1,50805,700,1000;1,50805,800,1000;1,50805,900,1000;1,50805,1000,1000",
        desc = "派遣部队拾取该资源后可直接获得。",
    },
    [51006] = {
        id = 51006,
        name = "银宝箱",
        description = "打开后随机获得一定数量的粮食/木材/石料/铜币/元气玉中的任一种资源",
        probability = 2500,
        dropitem = "1,50401,1,1000;",
        desc = "派遣部队拾取道具后在背包中使用。",
    },
}
return M
