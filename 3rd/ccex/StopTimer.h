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

#ifndef __CCEX_STOPTIMER_H__
#define __CCEX_STOPTIMER_H__

#include "cocos2d.h"

namespace ccex
{
    class StopTimer;
    struct StopTimerDelegate
    {
        virtual void stopTimerTimeoutHappen(const StopTimer* stopTimer, float deltaTime)
        {
        }
    };

    class StopTimer : public cocos2d::Ref
    {
    public:
        static StopTimer* create();
        StopTimer();
        ~StopTimer();

        void setDelegate(StopTimerDelegate* delegate)
        {
            _delegate = delegate;
        }

        void startTimeout(float duration);

        void stop();
        void reset()
        {
            _elapse = 0;
        }

        virtual void onTimeoutHappen(float deltaTime)
        {
        }
        
        float getDuration() const
        {
            return _duration;
        }
        
        void update(float t);

    private:
        float _duration;
        float _elapse;
        StopTimerDelegate* _delegate;
        bool _isTicking;
    };
}

#endif
