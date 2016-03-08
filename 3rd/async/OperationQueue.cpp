/*
 The MIT License (MIT)

 Copyright (c) 2015 HJC hjcapple@gmail.com

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

#include "OperationQueue.h"
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <mutex>
#include <atomic>

// 安卓平台上面，有些机型不支持std::thread，切换成pthread
#if defined(ANDROID) && !defined(ASYSNC_USE_PTHREAD)
#define ASYSNC_USE_PTHREAD 1
#endif

#if ASYSNC_USE_PTHREAD == 1
#include <pthread.h>
namespace
{
    class Mutex : boost::noncopyable
    {
    public:
        Mutex()
        {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&_mutex, &attr);
            pthread_mutexattr_destroy(&attr);
        }

        ~Mutex()
        {
            pthread_mutex_destroy(&_mutex);
        }

        void lock()
        {
            pthread_mutex_lock(&_mutex);
        }

        void unlock()
        {
            pthread_mutex_unlock(&_mutex);
        }

    private:
        pthread_mutex_t _mutex;
    };

    class LockGuard : boost::noncopyable
    {
    public:
        LockGuard(Mutex& mutex) : _mutex(mutex)
        {
            mutex.lock();
        }

        ~LockGuard()
        {
            _mutex.unlock();
        }

    private:
        Mutex& _mutex;
    };

    class ThreadInfo
    {
    public:
        typedef pthread_t Id;

        static Id thisThreadId()
        {
            return pthread_self();
        }

        ThreadInfo()
        {
            _thread = 0;
            assert(!isRunning());
        }

        void run(void* (*fun)(void*), void* ctx)
        {
            pthread_create(&_thread, 0, fun, ctx);
            pthread_detach(_thread);
        }

        bool isThis(Id Id)
        {
            return _thread == Id;
        }

        void exit()
        {
            _thread = 0;
        }

        bool isRunning()
        {
            return _thread != 0;
        }

    private:
        pthread_t _thread;
    };
}
#else

#include <thread>
namespace
{
    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> LockGuard;

    class ThreadInfo
    {
    public:
        typedef std::thread::id Id;

        static Id thisThreadId()
        {
            return std::this_thread::get_id();
        }

        ThreadInfo()
        {
            _isRunning = false;
            assert(!isRunning());
        }

        void run(void* (*fun)(void*), void* ctx)
        {
            std::thread thread(fun, ctx);
            _threadId = thread.get_id();
            thread.detach();
            _isRunning = true;
        }

        bool isThis(Id Id)
        {
            return _threadId == Id;
        }

        void exit()
        {
            _isRunning = false;
        }

        bool isRunning()
        {
            return _isRunning;
        }

    private:
        std::thread::id _threadId;
        bool _isRunning;
    };
}

#endif

namespace async
{
    namespace
    {
        struct Record
        {
            enum class State
            {
                Doing,
                Waitting,
                Suspend,
            };

            typedef std::shared_ptr<Record> Ptr;
            Record(State state_) : callback(nullptr), state(state_), isCancel(false)
            {
                Id = 0;
            }

            Operation::Ptr operation;
            OperationCallBack* callback;
            uint64_t Id;
            State state;
            bool isCancel;
        };
    }

    class OperationQueue::Impl : boost::noncopyable
    {
    public:
        Impl(int maxConcurrentOperationCount);
        ~Impl();

        void setMaxConcurrentOperationCount(int count);

        uint64_t peekNextOperationId() const
        {
            return _nextOperationId + 1;
        }
        uint64_t addOperation(const Operation::Ptr& operation, OperationCallBack* callback);
        void dispatchCallbacks(size_t maxCallback);

        bool cancel(const std::function<bool(const Record::Ptr&)>& fun);
        Record::Ptr findRecord(const std::function<bool(const Record::Ptr&)>& fun);
        bool cancelAll();
        size_t sizeOfOperations();

        void retain();
        void release();

        void suspendFuture();
        void resumeAll();

    private:
        static void* onWorkerThread(void* data);
        bool startThread();
        void workerThread();
        void exitThread(ThreadInfo::Id threadId);
        Record::Ptr getFirstUndoInputRecord() const;
        void popupInputRecord(const uint64_t& requestId);
        bool cancelQueue(std::list<Record::Ptr>& vec,
                         Mutex& mutext,
                         const std::function<bool(const Record::Ptr&)>& fun);

    private:
        uint64_t _nextOperationId;
        std::list<Record::Ptr> _inputs;
        std::list<Record::Ptr> _outputs;
        std::vector<ThreadInfo> _threadIds;
        Mutex _inputMutex;
        Mutex _outputMutex;
        Record::State _defaultRecordState;
        std::atomic<int32_t> _refCount;
    };

    template <typename T>
    inline void s_addItem(std::list<T>& items, const T& item, Mutex& mutex)
    {
        LockGuard lock(mutex);
        items.push_back(item);
    }

    template <typename T>
    static T s_popItem(std::list<T>& items, Mutex& mutex)
    {
        LockGuard lock(mutex);
        if (items.empty())
        {
            return T();
        }
        auto item = items.front();
        items.pop_front();
        return item;
    }

    OperationQueue::Impl::Impl(int maxConcurrentOperationCount)
    {
        _refCount = 1;
        _nextOperationId = 0;
        _defaultRecordState = Record::State::Waitting;
        setMaxConcurrentOperationCount(maxConcurrentOperationCount);
    }

    void OperationQueue::Impl::retain()
    {
        _refCount.fetch_add(1);
    }

    void OperationQueue::Impl::release()
    {
        if (_refCount.fetch_sub(1) == 1)
        {
            delete this;
        }
    }

    void OperationQueue::Impl::suspendFuture()
    {
        _defaultRecordState = Record::State::Suspend;
    }

    void OperationQueue::Impl::resumeAll()
    {
        _defaultRecordState = Record::State::Waitting;
        LockGuard lock(_inputMutex);

        bool needTryStarThread = true;
        for (auto& record : _inputs)
        {
            if (record->state == Record::State::Suspend)
            {
                record->state = Record::State::Waitting;
                if (needTryStarThread)
                {
                    needTryStarThread = startThread();
                }
            }
        }
    }

    void OperationQueue::Impl::setMaxConcurrentOperationCount(int maxCount)
    {
        _threadIds.resize(maxCount);
    }

    size_t OperationQueue::Impl::sizeOfOperations()
    {
        size_t totalSize = 0;
        do
        {
            LockGuard lock(_inputMutex);
            totalSize += _inputs.size();
        } while (0);

        do
        {
            LockGuard lock(_outputMutex);
            totalSize += _outputs.size();
        } while (0);
        return totalSize;
    }

    bool OperationQueue::Impl::cancelAll()
    {
        bool result = false;
        do
        {
            LockGuard lock(_inputMutex);
            for (auto& record : _inputs)
            {
                result = true;
                record->isCancel = true;
                if (record && record->callback)
                {
                    record->callback->operationOnCompletion(record->operation, OperationResultType::Cancel);
                }
            }
            _inputs.clear();
        } while (0);

        do
        {
            LockGuard lock(_outputMutex);
            for (auto& record : _outputs)
            {
                result = true;
                if (record && record->callback)
                {
                    record->callback->operationOnCompletion(record->operation, OperationResultType::Finish);
                }
            }
            _outputs.clear();
        } while (0);
        return result;
    }

    OperationQueue::Impl::~Impl()
    {
        assert(_inputs.empty());
        assert(_outputs.empty());
    }

    uint64_t OperationQueue::Impl::addOperation(const Operation::Ptr& operation, OperationCallBack* callback)
    {
        _nextOperationId++;

        auto record = Record::Ptr(new Record(_defaultRecordState));
        record->operation = operation;
        record->callback = callback;
        record->Id = _nextOperationId;

        LockGuard lock(_inputMutex);
        _inputs.push_back(record);
        startThread();

        return _nextOperationId;
    }

    // startThread, 和exitThread需要在外面上锁
    void OperationQueue::Impl::exitThread(ThreadInfo::Id threadId)
    {
        for (auto& Id : _threadIds)
        {
            if (Id.isThis(threadId))
            {
                Id.exit();
                break;
            }
        }
    }

    void OperationQueue::Impl::popupInputRecord(const uint64_t& requestId)
    {
        auto iter = std::find_if(_inputs.begin(),
                                 _inputs.end(),
                                 [=](const Record::Ptr& item)
                                 {
                                     return item->Id == requestId;
                                 });
        if (iter != _inputs.end())
        {
            _inputs.erase(iter);
        }
    }

    void OperationQueue::Impl::workerThread()
    {
        for (;;)
        {
            Record::Ptr item;
            {
                LockGuard lock(_inputMutex);
                item = getFirstUndoInputRecord();
                if (!item)
                {
                    exitThread(ThreadInfo::thisThreadId());
                    return;
                }

                item->state = Record::State::Doing;

                if (item->isCancel)
                {
                    popupInputRecord(item->Id);
                    continue;
                }
            }

            item->operation->action();

            {
                LockGuard lock(_inputMutex);
                if (!item->isCancel && item->callback != nullptr)
                {
                    s_addItem(_outputs, item, _outputMutex);
                }
                popupInputRecord(item->Id);
            }
        }
    }

    bool OperationQueue::Impl::cancelQueue(std::list<Record::Ptr>& vec,
                                           Mutex& mutext,
                                           const std::function<bool(const Record::Ptr&)>& fun)
    {
        Record::Ptr record;

        do
        {
            LockGuard lock(mutext);
            auto iter = std::find_if(vec.begin(), vec.end(), fun);
            if (iter != vec.end())
            {
                record = *iter;
                record->isCancel = true;
                vec.erase(iter);
            }
        } while (0);

        // cancel成功，通知外面
        if (record && record->callback)
        {
            record->callback->operationOnCompletion(record->operation, OperationResultType::Cancel);
        }
        return record != nullptr;
    }

    void* OperationQueue::Impl::onWorkerThread(void* data)
    {
        auto impl = (OperationQueue::Impl*)data;
        impl->workerThread();
        impl->release();
        return nullptr;
    }

    // must lock on outside
    bool OperationQueue::Impl::startThread()
    {
        for (auto& Id : _threadIds)
        {
            if (!Id.isRunning())
            {
                this->retain();
                Id.run(&OperationQueue::Impl::onWorkerThread, this);
                return true;
            }
        }
        return false;
    }

    // must lock on outside
    Record::Ptr OperationQueue::Impl::getFirstUndoInputRecord() const
    {
        for (auto& item : _inputs)
        {
            if (item->state == Record::State::Waitting)
            {
                return item;
            }
        }
        return Record::Ptr();
    }

    void OperationQueue::Impl::dispatchCallbacks(size_t maxCallbackCount)
    {
        // 一次回调多个callback
        for (size_t i = 0; i < maxCallbackCount; i++)
        {
            auto item = s_popItem(_outputs, _outputMutex);
            if (item == nullptr)
            {
                break;
            }

            if (item->callback)
            {
                item->callback->operationOnCompletion(item->operation, OperationResultType::Finish);
            }
        }
    }

    Record::Ptr OperationQueue::Impl::findRecord(const std::function<bool(const Record::Ptr&)>& fun)
    {
        do
        {
            LockGuard lock(_inputMutex);
            for (auto& record : _inputs)
            {
                if (fun(record))
                {
                    return record;
                }
            }
        } while (0);

        do
        {
            LockGuard lock(_outputMutex);
            for (auto& record : _outputs)
            {
                if (fun(record))
                {
                    return record;
                }
            }
        } while (0);
        return Record::Ptr();
    }

    bool OperationQueue::Impl::cancel(const std::function<bool(const Record::Ptr&)>& fun)
    {
        if (cancelQueue(_inputs, _inputMutex, fun))
        {
            return true;
        }

        if (cancelQueue(_outputs, _outputMutex, fun))
        {
            return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////
    OperationQueue::OperationQueue(int maxConcurrentOperationCount)
    {
        assert(maxConcurrentOperationCount >= 1);
        _impl = new OperationQueue::Impl(maxConcurrentOperationCount);
    }

    OperationQueue::~OperationQueue()
    {
        _impl->cancelAll();
        _impl->release();
    }

    uint64_t OperationQueue::peekNextOperationId() const
    {
        return _impl->peekNextOperationId();
    }

    uint64_t OperationQueue::addOperation(const Operation::Ptr& operation, OperationCallBack* callback)
    {
        return _impl->addOperation(operation, callback);
    }

    uint64_t OperationQueue::addOperation(const Operation::Ptr& operation)
    {
        return _impl->addOperation(operation, nullptr);
    }

    bool OperationQueue::cancel(const uint64_t& Id)
    {
        return _impl->cancel([=](const Record::Ptr& record)
                             {
                                 return record->Id == Id;
                             });
    }

    bool OperationQueue::cancel(OperationCallBack* callback)
    {
        auto findInputQueue = [=](const Record::Ptr& record)
        {
            return record->callback == callback;
        };

        if (_impl->cancel(findInputQueue))
        {
            while (_impl->cancel(findInputQueue))
            {
                // do nothing
            }
            return true;
        }
        return false;
    }

    bool OperationQueue::cancelAll()
    {
        return _impl->cancelAll();
    }

    bool OperationQueue::cancel(const Operation::Ptr& operation)
    {
        return _impl->cancel([=](const Record::Ptr& record)
                             {
                                 return record->operation == operation;
                             });
    }

    void OperationQueue::dispatchCallbacks(size_t maxCallbackCount)
    {
        _impl->dispatchCallbacks(maxCallbackCount);
    }

    void OperationQueue::setMaxConcurrentOperationCount(int count)
    {
        _impl->setMaxConcurrentOperationCount(count);
    }

    size_t OperationQueue::size() const
    {
        return _impl->sizeOfOperations();
    }

    bool OperationQueue::isEmpty() const
    {
        return size() == 0;
    }

    void OperationQueue::suspendFuture()
    {
        _impl->suspendFuture();
    }

    void OperationQueue::resumeAll()
    {
        _impl->resumeAll();
    }

    Operation::Ptr OperationQueue::findOperation(const std::function<bool(const Operation::Ptr&)>& fun)
    {
        auto record = _impl->findRecord([&](const Record::Ptr& record)
                                        {
                                            return fun(record->operation);
                                        });
        if (record)
        {
            return record->operation;
        }
        return Operation::Ptr();
    }

    //////////////////////////
    void CallBackOperation::operationOnCompletion(const Operation::Ptr& operation, OperationResultType type)
    {
        (void)type;
        (void)operation;
        assert(operation.get() == this);
        callBack();
    }
}
