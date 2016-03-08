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

#ifndef __ASYNC_OPERATIONQUEUE_H__
#define __ASYNC_OPERATIONQUEUE_H__

#include <memory>
#include <boost/noncopyable.hpp>
#include <functional>
#include <cassert>
#include <stdint.h>
#include "detail/traits.hpp"

namespace async
{
    class Operation
    {
    public:
        typedef std::shared_ptr<Operation> Ptr;
        virtual void action() = 0;
        virtual ~Operation()
        {
        }

        void setTag(int tag)
        {
            _tag = tag;
        }

        int getTag() const
        {
            return _tag;
        }

    private:
        int _tag;
    };

    enum class OperationResultType
    {
        Cancel,
        Finish,
    };

    struct OperationCallBack
    {
        virtual void operationOnCompletion(const Operation::Ptr& operation, OperationResultType type) = 0;
    };

    class OperationQueue : boost::noncopyable
    {
    public:
        OperationQueue(int maxConcurrentOperationCount);
        ~OperationQueue();

        void setMaxConcurrentOperationCount(int count);

        uint64_t peekNextOperationId() const;
        uint64_t addOperation(const Operation::Ptr& operation, OperationCallBack* callback);
        uint64_t addOperation(const Operation::Ptr& operation);
        Operation::Ptr findOperation(const std::function<bool(const Operation::Ptr&)>& fun);

        template <typename Fun, typename Callback>
        uint64_t async(const Fun& fun, const Callback& callback);

        template <typename Fun>
        uint64_t async(const Fun& fun);

        size_t size() const;
        bool isEmpty() const;

        bool cancel(const uint64_t& Id);
        bool cancel(OperationCallBack* callback);
        bool cancel(const Operation::Ptr& operation);
        bool cancelAll();

        void dispatchCallbacks(size_t maxCallbackCount);

        void suspendFuture();
        void resumeAll();

    private:
        class Impl;
        Impl* _impl;
    };

    //////////////////////////////////////////////////////////////////////////////////////
    class CallBackOperation : public Operation, public OperationCallBack
    {
    public:
        virtual void callBack() = 0;

    private:
        void operationOnCompletion(const Operation::Ptr& operation, OperationResultType type) override;
    };

    template <typename Fun, typename Callback>
    class FunctionOperation : public CallBackOperation
    {
    public:
        typedef std::shared_ptr<FunctionOperation> Ptr;
        FunctionOperation(const Fun& fun, const Callback& callback) : _fun(fun), _callback(callback)
        {
        }

        virtual void action() override
        {
            _result.fromCall(_fun);
        }

        virtual void callBack() override
        {
            _result.toCall(_callback);
        }

    private:
        typedef typename function_traits<Fun>::result_type result_type;
        SingleHolder<result_type> _result;
        Fun _fun;
        Callback _callback;
    };

    template <typename Fun, typename Callback>
    inline typename FunctionOperation<Fun, Callback>::Ptr MakeOperation(const Fun& fun, const Callback& callback)
    {
        return std::make_shared<FunctionOperation<Fun, Callback>>(fun, callback);
    }

    template <typename Fun, typename Callback>
    uint64_t OperationQueue::async(const Fun& fun, const Callback& callback)
    {
        auto ptr = MakeOperation(fun, callback);
        return addOperation(ptr, ptr.get());
    }

    template <typename Fun>
    uint64_t OperationQueue::async(const Fun& fun)
    {
        auto callback = []
        {
        };
        auto ptr = MakeOperation(fun, callback);
        return addOperation(ptr);
    }
    ///////////////////////////////////////////////
}

#endif
