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

#include "TimerManager.h"
#include <cmath>
#include <climits>
using namespace cocos2d;

namespace ccex
{
    template <typename T>
    static inline void s_unscheduleUpdateForTarget(T* obj)
    {
        auto director = cocos2d::Director::getInstance();
        director->getScheduler()->unscheduleUpdate(obj);
    }

    template <typename T>
    static inline void s_scheduleUpdateForTarget(T* obj, int priority, bool paused)
    {
        auto director = cocos2d::Director::getInstance();
        director->getScheduler()->scheduleUpdate(obj, priority, paused);
    }

    struct TimerInfo
    {
        typedef std::shared_ptr<TimerInfo> Ptr;
        TimerInfo()
        {
            delegate = 0;
            theoryInterval = 0;
            remainNextTime = 0;
            fireEachStep = false;
        }

        TimerStepInfo stepInfo;
        TimerManagerDelegate* delegate;
        float theoryInterval;
        float remainNextTime;
        bool fireEachStep;  //  是否最快的定时器，也就是每次都触发
    };

    //////////////////////////////////////////////////////////////////////

    TimerManager* TimerManager::getInstance()
    {
        static TimerManager s_timerManager;
        return &s_timerManager;
    }

    TimerManager::TimerManager()
    {
        _ticking = false;
        _nextTimerId = 0;
    }

    TimerManager::~TimerManager()
    {
        if (_ticking)
        {
            s_unscheduleUpdateForTarget(this);
        }
    }

    uint64_t TimerManager::startTimer(TimerManagerDelegate* delegate, float interval, int tag)
    {
        auto timerInfo = createTimerInfo(delegate, tag);

        if (std::abs(interval) < std::numeric_limits<float>::min())
        {
            timerInfo->fireEachStep = true;
        }
        else
        {
            timerInfo->theoryInterval = interval;
            timerInfo->remainNextTime = interval;
        }

        _timerInfos.push_back(timerInfo);

        this->startPublicTimer();

        return timerInfo->stepInfo._timerId;
    }

    uint64_t TimerManager::startTimer(TimerManagerDelegate* delegate, float interval)
    {
        return startTimer(delegate, interval, 0);
    }

    uint64_t TimerManager::startFastestTimer(TimerManagerDelegate* delegate, int tag)
    {
        return startTimer(delegate, 0, tag);
    }

    uint64_t TimerManager::startFastestTimer(TimerManagerDelegate* delegate)
    {
        return startTimer(delegate, 0, 0);
    }

    TimerInfo::Ptr TimerManager::createTimerInfo(TimerManagerDelegate* delegate, int tag)
    {
        _nextTimerId++;

        auto timerInfo = std::make_shared<TimerInfo>();
        timerInfo->stepInfo._timerId = _nextTimerId;
        timerInfo->stepInfo._tag = tag;
        timerInfo->delegate = delegate;
        return timerInfo;
    }

    void TimerManager::startPublicTimer()
    {
        assert(!_timerInfos.empty());
        if (_ticking == false)
        {
            _ticking = true;
            s_scheduleUpdateForTarget(this, 0, false);
        }
    }

    void TimerManager::stopPublicTimerIfEmpty()
    {
        if (_timerInfos.empty() && _ticking)
        {
            _ticking = false;
            s_unscheduleUpdateForTarget(this);
        }
    }

    void TimerManager::fireTimer(const TimerInfo::Ptr& timerInfo, float t)
    {
        if (timerInfo->delegate)
        {
            timerInfo->delegate->timerManagerFire(this, timerInfo->stepInfo);
        }
        timerInfo->stepInfo._stepTime = 0;
    }

    void TimerManager::update(float t)
    {
        auto tmpTimerInfos = _timerInfos;

        // 循环时候，用户有可能会使用stopTimerId函数，引起_timerInfos改变，
        // 所以这里用tmpTimerInfos遍历
        for (auto& info : tmpTimerInfos)
        {
            info->stepInfo._stepTime += t;
            info->stepInfo._totalTime += t;

            if (info->fireEachStep)
            {
                fireTimer(info, t);
            }
            else
            {
                info->remainNextTime -= t;
                if (info->remainNextTime <= 0)
                {
                    info->remainNextTime += info->theoryInterval;
                    if (info->remainNextTime <= 0)
                    {
                        info->remainNextTime = info->theoryInterval;
                    }
                    fireTimer(info, t);
                }
            }
        }
    }

    typedef std::vector<TimerInfo::Ptr> TimerInfoArray;
    inline TimerInfoArray::iterator s_findTimerInfo(const TimerInfoArray& infos, uint64_t timerId)
    {
        auto nonConst = const_cast<TimerInfoArray&>(infos);
        return std::find_if(nonConst.begin(),
                            nonConst.end(),
                            [&](const TimerInfo::Ptr& info)
                            {
                                return info->stepInfo.getTimerId() == timerId;
                            });
    }

    inline TimerInfoArray::iterator s_findTimerInfo(const TimerInfoArray& infos, TimerManagerDelegate* delegate)
    {
        auto nonConst = const_cast<TimerInfoArray&>(infos);
        return std::find_if(nonConst.begin(),
                            nonConst.end(),
                            [&](const TimerInfo::Ptr& info)
                            {
                                return info->delegate == delegate;
                            });
    }

    inline TimerInfoArray::iterator s_findTimerInfo(const TimerInfoArray& infos,
                                                    TimerManagerDelegate* delegate,
                                                    int tag)
    {
        auto nonConst = const_cast<TimerInfoArray&>(infos);
        return std::find_if(nonConst.begin(),
                            nonConst.end(),
                            [&](const TimerInfo::Ptr& info)
                            {
                                return info->delegate == delegate && info->stepInfo.getTag() == tag;
                            });
    }

    bool TimerManager::hasTimerId(uint64_t timerId) const
    {
        auto iter = s_findTimerInfo(_timerInfos, timerId);
        return iter != _timerInfos.end();
    }

    bool TimerManager::hasTimerDelegate(TimerManagerDelegate* delegate) const
    {
        auto iter = s_findTimerInfo(_timerInfos, delegate);
        return iter != _timerInfos.end();
    }

    bool TimerManager::hasTimerDelegate(TimerManagerDelegate* delegate, int tag) const
    {
        auto iter = s_findTimerInfo(_timerInfos, delegate, tag);
        return iter != _timerInfos.end();
    }

    void TimerManager::stopTimerId(uint64_t timerId)
    {
        auto iter = s_findTimerInfo(_timerInfos, timerId);
        if (iter != _timerInfos.end())
        {
            _timerInfos.erase(iter);
        }
        stopPublicTimerIfEmpty();
    }

    void TimerManager::stopTimerDelegate(TimerManagerDelegate* delegate)
    {
        auto iter = std::remove_if(_timerInfos.begin(),
                                   _timerInfos.end(),
                                   [&](const TimerInfo::Ptr& info)
                                   {
                                       return info->delegate == delegate;
                                   });
        _timerInfos.erase(iter, _timerInfos.end());
        stopPublicTimerIfEmpty();
    }

    void TimerManager::stopTimerDelegate(TimerManagerDelegate* delegate, int tag)
    {
        auto iter = s_findTimerInfo(_timerInfos, delegate, tag);
        if (iter != _timerInfos.end())
        {
            _timerInfos.erase(iter);
        }
        stopPublicTimerIfEmpty();
    }
}
