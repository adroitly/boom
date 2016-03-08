/*
 The MIT License (MIT)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef __CCEX_TIMERMANAGER_H__
#define __CCEX_TIMERMANAGER_H__

#include "cocos2d.h"
#include <memory>

namespace ccex
{
    class TimerStepInfo
    {
    public:
        TimerStepInfo()
        {
            _tag       = 0;
            _totalTime = 0;
            _stepTime  = 0;
            _timerId   = 0;
        }

        uint64_t getTimerId() const         { return _timerId;   }
        int getTag() const                  { return _tag;       }
        float getTotalTime() const          { return _totalTime; }
        float getStepTime() const           { return _stepTime;  }

    private:
        friend class TimerManager;
        uint64_t    _timerId;
        int         _tag;
        float       _totalTime;
        float       _stepTime;
    };

    class TimerManager;
    struct TimerManagerDelegate
    {
        virtual void timerManagerFire(TimerManager* manager, const TimerStepInfo& info) = 0;
    };

    class TimerInfo;
    class TimerManager : public cocos2d::Ref
    {
    public:
        static TimerManager* getInstance();
        ~TimerManager();

        // 添加定时器, 返回ID, 之后可以使用这个ID停止定时器, 可以指定间隔秒数
        uint64_t startTimer(TimerManagerDelegate* delegate, float interval, int tag);
        uint64_t startTimer(TimerManagerDelegate* delegate, float interval);

        // 最短间隔的定时器
        uint64_t startFastestTimer(TimerManagerDelegate* delegate, int tag);
        uint64_t startFastestTimer(TimerManagerDelegate* delegate);

        // 判断是否已生成定时器
        bool hasTimerId(uint64_t timerId) const;
        bool hasTimerDelegate(TimerManagerDelegate* delegate) const;
        bool hasTimerDelegate(TimerManagerDelegate* delegate, int tag) const;

        // 停止定时器
        void stopTimerId(uint64_t timerId);
        void stopTimerDelegate(TimerManagerDelegate* delegate);
        void stopTimerDelegate(TimerManagerDelegate* delegate, int tag);
        
        virtual void update(float t);

    private:
        TimerManager();
        typedef std::shared_ptr<TimerInfo> TimerInfoPtr;
        TimerInfoPtr createTimerInfo(TimerManagerDelegate* delegate, int tag);
        void startPublicTimer();
        void stopPublicTimerIfEmpty();
        void fireTimer(const TimerInfoPtr& timerInfo, float t);
        
    private:
        std::vector<TimerInfoPtr> _timerInfos;
        uint64_t                  _nextTimerId;
        bool                      _ticking;
    };
}

#endif
