//
//  GamePay.h
//  big-devil
//
//  Created by JiangPaifeng on 15/6/1.
//
//

#ifndef __BOOM__GamePay__
#define __BOOM__GamePay__

#include <functional>
#include <string>

class GamePay
{
public:
    typedef std::function<void(const char*, double)>            OnFinishFunc; // payCode, mount
    typedef std::function<void(const char*, int, const char*)>  OnErrorFunc;  // payCode, errorCode, msg
    
    static GamePay* getInstance();
    
    void pay(const char* payCode);
    void onFinish(const char* payCode, double mount);
    void onError(int errorCode, const char* msg);
    int getCashWithCode(const char* payCode) const;
    
    void setFinishCallback(OnFinishFunc func);
    void setErrorCallback(OnErrorFunc func);
    
private:
    std::string     _currentPayCode;
    
    OnFinishFunc    _onFinishFunc;
    OnErrorFunc     _onErrorFunc;
};

#endif /* defined(__BOOM__GamePay__) */
