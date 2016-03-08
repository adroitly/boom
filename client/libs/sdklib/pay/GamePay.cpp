//
//  GamePay.cpp
//  big-devil
//
//  Created by JiangPaifeng on 15/6/1.
//
//

#include "GamePay.h"
#include "../GameSdk.h"

#include "cocos2d.h"

// 道具ID 与 payCode对应
static struct PayInfo
{
    const char* payCode;
    const char* itemID;
    int cash;  // 分
} items[] = {
    { "1", "super",        3000,   },  //超值礼包
    { "2", "shapeshift",   1200,   },  //主角变身大礼包
    { "3", "welcome",      10,     },  //新手礼包
    { "4", "skill_4",      900,    },  //解锁主角第4技能
    { "5", "gufu",         1500,    },  //随从古夫礼包
    { "6", "molong",       1500,    },  //随从魔龙礼包
    { "7", "huolonggui",   2000,   },  //随从火龙龟礼包
    { "8", "kulouwang",    2500,   },  //随从骷髅王礼包
    { "9", "revive",       200,    },  //主角复活
    { "10", "blood",       200,    },  //购买血瓶
    { "11", "upgrade",     200,    },  //主角付费升级
    { "12", "gold2w",      200,    },  // 2万金币
    { "13", "gold5w",      500,    },  // 5万金币
    { "14", "gold12w",     1000,    },  // 12万金币
    { "15", "column",      400,    },  //第3随从栏位
    
//    { "1",  "super",        1000,   },  //超值礼包
//    { "2",  "shapeshift",   1000,   },  //主角变身大礼包
//    { "3",  "skill_4",      600,    },  //解锁主角第4技能
//    { "4",  "gufu",         600,    },  //随从古夫礼包
//    { "5",  "molong",       800,    },  //随从魔龙礼包
//    { "6",  "huolonggui",   1000,   },  //随从火龙龟礼包
//    { "7",  "kulouwang",    1000,   },  //随从骷髅王礼包
//    { "8",  "revive",       200,    },  //主角复活
//    { "9",  "blood",        200,    },  //购买血瓶
//    { "10", "upgrade",      200,    },  //主角付费升级
//    { "11", "gold2w",       200,    },  // 2万金币
//    { "12", "gold5w",       400,    },  // 5万金币
//    { "13", "gold12w",      800,    },  // 12万金币
//    { "14", "column",       400,    },  //第3随从栏位
};

#if ANDROID
#include "MobClickCpp.h"

static void s_recordForUmeng(const char* payCode)
{
    for (auto& item : items)
    {
        if (strcmp(payCode, item.payCode) == 0)
        {
            umeng::MobClickCpp::pay(item.cash, 1, item.itemID, 1, item.cash);
        }
    }
}
#endif

GamePay* GamePay::getInstance()
{
    static GamePay* s_shared = nullptr;
    if (s_shared == nullptr)
    {
        s_shared = new GamePay();
    }
    return s_shared;
}

static PayInfo s_getPayInfoWithID(const char* itemId)
{
    for (auto it : items)
    {
        if (strcmp(itemId, it.itemID) == 0)
        {
            return it;
        }
    }
    return { "", "", 0 };
}

void GamePay::pay(const char* itemId)
{
    auto payInfo = s_getPayInfoWithID(itemId);
    _currentPayCode = payInfo.payCode;
    
    char cashStr[20] = { 0 };
    sprintf(cashStr, "%d", payInfo.cash);
    SdkUtils::pay(_currentPayCode.c_str(), cashStr);
}

int GamePay::getCashWithCode(const char* payCode) const 
{
    auto payInfo = s_getPayInfoWithID(payCode);
    return payInfo.cash;
}

void GamePay::onFinish(const char* payCode, double mount)
{
    assert(_currentPayCode == payCode);
    if (_onFinishFunc)
    {
        _onFinishFunc(payCode, mount);
    }
#if ANDROID
    s_recordForUmeng(payCode);
#endif
}

void GamePay::onError(int errorCode, const char* msg)
{
    assert(!_currentPayCode.empty());
    if (_onErrorFunc)
    {
        _onErrorFunc(_currentPayCode.c_str(), errorCode, msg);
    }
}

void GamePay::setFinishCallback(OnFinishFunc func)
{
    _onFinishFunc = func;
}

void GamePay::setErrorCallback(OnErrorFunc func)
{
    _onErrorFunc = func;
}