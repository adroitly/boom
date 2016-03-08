--[[ SheetEditor v1.0
资源点ID,名称,攻击,城防,城防兵力,城防血量,城防恢复速度,生产类型,
*id,name,cityAtk,cityDef,cityAmount,cityHp,cityDefSpeed,productionType,
sorted = { 0, 'a' }
--]]

local M = {
    [12001] = {
        id = 12001,
        name = "近程兵营",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        productionType = "18000;18100;18200",
    },
    [12011] = {
        id = 12011,
        name = "中程兵营",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        productionType = "18300;18400;18500",
    },
    [12021] = {
        id = 12021,
        name = "远程兵营",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        productionType = "18600;18700;18800",
    },
    [12031] = {
        id = 12031,
        name = "特殊兵营",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        productionType = "18900;",
    },
}
return M
