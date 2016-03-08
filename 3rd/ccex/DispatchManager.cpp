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

#include "DispatchManager.h"
using namespace cocos2d;

namespace ccex
{
    static inline Scheduler* getShareScheduler()
    {
        return cocos2d::Director::getInstance()->getScheduler();
    }

    static inline void scheduleSelector(Scheduler* scheduler,
                                        SEL_SCHEDULE selector,
                                        Ref* target,
                                        float interval,
                                        bool paused)
    {
        scheduler->schedule(selector, target, interval, paused);
    }

    DispatchManager* DispatchManager::getInstance()
    {
        static DispatchManager* s_manager = NULL;
        if (s_manager == NULL)
        {
            s_manager = new DispatchManager();
        }
        return s_manager;
    }

    DispatchManager::DispatchManager()
    {
        _nextId = 0;
        auto scheduler = getShareScheduler();
        scheduleSelector(scheduler, schedule_selector(DispatchManager::dispatchCallbacks), this, 0, false);
        scheduler->pauseTarget(this);
    }

    void DispatchManager::dispatchCallbacks(float delta)
    {
        for (auto& item : _funs)
        {
            if (item.fun)
            {
                item.fun(delta);
            }
        }
    }

    bool DispatchManager::isEmpty() const
    {
        return _funs.empty();
    }

    void DispatchManager::clear()
    {
        _funs.clear();
        getShareScheduler()->pauseTarget(this);
    }

    uint64_t DispatchManager::addFun(const FunType& fun)
    {
        _nextId++;

        Item item;
        item.fun = fun;
        item.Id = _nextId;
        _funs.push_back(item);
        getShareScheduler()->resumeTarget(this);

        return _nextId;
    }

    void DispatchManager::removeFun(uint64_t Id)
    {
        for (auto iter = _funs.begin(); iter != _funs.end(); ++iter)
        {
            if (iter->Id == Id)
            {
                _funs.erase(iter);
                break;
            }
        }

        if (_funs.empty())
        {
            getShareScheduler()->pauseTarget(this);
        }
    }
}
