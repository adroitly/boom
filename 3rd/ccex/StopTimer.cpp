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

#include "StopTimer.h"
using namespace cocos2d;

namespace ccex
{
    StopTimer* StopTimer::create()
    {
        StopTimer* timer = new StopTimer();
        timer->autorelease();
        return timer;
    }

    StopTimer::StopTimer()
    {
        _duration = 0;
        _elapse = 0;
        _isTicking = false;
        _delegate = nullptr;
    }

    StopTimer::~StopTimer()
    {
        stop();
    }

    void StopTimer::update(float t)
    {
        _elapse += t;
        if (_elapse > _duration)
        {
            onTimeoutHappen(_elapse);
            if (_delegate)
            {
                _delegate->stopTimerTimeoutHappen(this, _elapse);
            }
            stop();
        }
    }

    void StopTimer::startTimeout(float duration)
    {
        _duration = duration;
        _elapse = 0;

        if (_isTicking == false)
        {
            _isTicking = true;

#if COCOS2D_VERSION >= 0x00030000
            Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
#else
            CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
#endif
        }
    }

    void StopTimer::stop()
    {
        if (_isTicking)
        {
            _isTicking = false;

#if COCOS2D_VERSION >= 0x00030000
            Director::getInstance()->getScheduler()->unscheduleUpdate(this);
#else
            CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
#endif
        }
    }
}
