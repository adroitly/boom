--[[ SheetEditor v1.0
ID,等级,美术资源,攻击,城防,城防兵力,城防血量,城防恢复速度,恢复时间(秒）,城防恢复消耗,驻守,积分,官职条件,保护上限,储存上限,主城升级消耗,生产资源ID/上限/单个生产时间,士兵类型,sw,
*id,*level,resId,cityAtk,cityDef,cityAmount,cityHp,cityDefSpeed,cityDefTime,cityDefCondition,garrison,integral,officeCondition,safeConfine,storageConfine,upgradeCondition,proResSpeed,typeSold,gradelimit,
sorted = { 0, 'a' }
--]]

local M = {
    [1] = {
        id = 1,
        level = 1,
        resId = 14000,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,100;50802,100;50803,100;50804,100;50805,100",
        garrison = 5,
        integral = 100,
        officeCondition = 9,
        safeConfine = 5000,
        storageConfine = 100000000,
        upgradeCondition = "50801,100;50802,100;50803,100;50804,100;50805,100",
        proResSpeed = "50801,100,5;50802,100,5;50803,100,5;50804,100,5;50805,100,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [2] = {
        id = 2,
        level = 2,
        resId = 14001,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,101;50802,101;50803,101;50804,101;50805,101",
        garrison = 5,
        integral = 200,
        officeCondition = 20,
        safeConfine = 6000,
        storageConfine = 200000000,
        upgradeCondition = "50801,101;50802,101;50803,101;50804,101;50805,101",
        proResSpeed = "50801,101,5;50802,101,5;50803,101,5;50804,101,5;50805,101,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [3] = {
        id = 3,
        level = 3,
        resId = 14002,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,102;50802,102;50803,102;50804,102;50805,102",
        garrison = 5,
        integral = 300,
        officeCondition = 30,
        safeConfine = 7000,
        storageConfine = 300000000,
        upgradeCondition = "50801,102;50802,102;50803,102;50804,102;50805,102",
        proResSpeed = "50801,102,5;50802,102,5;50803,102,5;50804,102,5;50805,102,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [4] = {
        id = 4,
        level = 4,
        resId = 14003,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,103;50802,103;50803,103;50804,103;50805,103",
        garrison = 5,
        integral = 400,
        officeCondition = 40,
        safeConfine = 8000,
        storageConfine = 400000000,
        upgradeCondition = "50801,103;50802,103;50803,103;50804,103;50805,103",
        proResSpeed = "50801,103,5;50802,103,5;50803,103,5;50804,103,5;50805,103,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [5] = {
        id = 5,
        level = 5,
        resId = 14004,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,104;50802,104;50803,104;50804,104;50805,104",
        garrison = 5,
        integral = 500,
        officeCondition = 50,
        safeConfine = 9000,
        storageConfine = 500000000,
        upgradeCondition = "50801,104;50802,104;50803,104;50804,104;50805,104",
        proResSpeed = "50801,104,5;50802,104,5;50803,104,5;50804,104,5;50805,104,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [6] = {
        id = 6,
        level = 6,
        resId = 14005,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,105;50802,105;50803,105;50804,105;50805,105",
        garrison = 5,
        integral = 600,
        officeCondition = 60,
        safeConfine = 10000,
        storageConfine = 600000000,
        upgradeCondition = "50801,105;50802,105;50803,105;50804,105;50805,105",
        proResSpeed = "50801,105,5;50802,105,5;50803,105,5;50804,105,5;50805,105,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [7] = {
        id = 7,
        level = 7,
        resId = 14006,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,106;50802,106;50803,106;50804,106;50805,106",
        garrison = 5,
        integral = 700,
        officeCondition = 70,
        safeConfine = 11000,
        storageConfine = 700000000,
        upgradeCondition = "50801,106;50802,106;50803,106;50804,106;50805,106",
        proResSpeed = "50801,106,5;50802,106,5;50803,106,5;50804,106,5;50805,106,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [8] = {
        id = 8,
        level = 8,
        resId = 14007,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,107;50802,107;50803,107;50804,107;50805,107",
        garrison = 5,
        integral = 800,
        officeCondition = 80,
        safeConfine = 12000,
        storageConfine = 800000000,
        upgradeCondition = "50801,107;50802,107;50803,107;50804,107;50805,107",
        proResSpeed = "50801,107,5;50802,107,5;50803,107,5;50804,107,5;50805,107,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [9] = {
        id = 9,
        level = 9,
        resId = 14008,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,108;50802,108;50803,108;50804,108;50805,108",
        garrison = 5,
        integral = 900,
        officeCondition = 89,
        safeConfine = 13000,
        storageConfine = 900000000,
        upgradeCondition = "50801,108;50802,108;50803,108;50804,108;50805,108",
        proResSpeed = "50801,108,5;50802,108,5;50803,108,5;50804,108,5;50805,108,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
    [10] = {
        id = 10,
        level = 10,
        resId = 14009,
        cityAtk = 10,
        cityDef = 100,
        cityAmount = 1000,
        cityHp = 10,
        cityDefSpeed = 5,
        cityDefTime = 900,
        cityDefCondition = "50801,109;50802,109;50803,109;50804,109;50805,109",
        garrison = 5,
        integral = 1000,
        officeCondition = 90,
        safeConfine = 14000,
        storageConfine = 1000000000,
        upgradeCondition = "50801,109;50802,109;50803,109;50804,109;50805,109",
        proResSpeed = "50801,109,5;50802,109,5;50803,109,5;50804,109,5;50805,109,5",
        typeSold = "18000;18100;18200;18300;18400;18500;18600;18700;18800",
        gradelimit = 10,
    },
}
return M