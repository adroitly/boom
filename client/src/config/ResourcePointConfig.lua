--[[ SheetEditor v1.0
资源点ID,名称,攻击,城防,城防兵力,城防血量,城防恢复速度,生产资源ID/上限/单个生产时间,
*id,name,cityAtk,cityDef,cityAmount,cityHp,cityDefSpeed,proResSpeed,
sorted = { 0, 'a' }
--]]

local M = {
    [10001] = {
        id = 10001,
        name = "粮田",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        proResSpeed = "50801,10,5",
    },
    [10021] = {
        id = 10021,
        name = "石矿厂",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        proResSpeed = "50803,10,5",
    },
    [10041] = {
        id = 10041,
        name = "玉矿厂",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        proResSpeed = "50805,10,5",
    },
    [10061] = {
        id = 10061,
        name = "铸币厂",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        proResSpeed = "50804,10,5",
    },
    [10081] = {
        id = 10081,
        name = "木材厂",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        proResSpeed = "50802,10,5",
    },
    [10101] = {
        id = 10101,
        name = "战略要地",
        cityAtk = 0,
        cityDef = 0,
        cityAmount = 0,
        cityHp = 10,
        cityDefSpeed = 0,
        proResSpeed = "50806,10,5",
    },
}
return M
