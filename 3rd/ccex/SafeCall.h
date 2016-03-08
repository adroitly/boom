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

#ifndef __CCEX_SAFECALL_H__
#define __CCEX_SAFECALL_H__

#include "ccex_ObjWeakable.h"

namespace ccex
{
    namespace safe_call
    {
        template <typename ActionT>
        class CallHolder
        {
        public:
            CallHolder() : _action(nullptr) {}

            template <typename T, typename Fun>
            void set(T* target, Fun fun)
            {
                _target = target->getWeakId();
                _action = (ActionT)fun;
            }

            template <typename... Args>
            void call(Args... args)
            {
                if (_action)
                {
                    auto target = _target.lock();
                    if (target)
                    {
                        (target->*_action)(args...);
                    }
                }
            }

            void reset() { _action = nullptr; }

        private:
            ObjWeakId<Object> _target;
            ActionT _action;
        };
    }

    template <int N>
    class SafeCall;

    // 0 个参数
    template <>
    class SafeCall<0>
    {
    public:
        template <typename T, typename B>
        void set(T* target, void (B::*action)())
        {
            _impl.set(target, action);
        }

        void call()     { _impl.call();  }
        void reset()    { _impl.reset(); }

    private:
        typedef void (CCObject::*action_type)();
        safe_call::CallHolder<action_type> _impl;
    };

    // 1 个参数
    template <>
    class SafeCall<1>
    {
    public:
        template <typename T, typename B, typename Obj>
        void set(T* target, void (B::*action)(Obj*))
        {
            _impl.set(target, action);
        }

        template <typename Obj>
        void call(Obj* obj)
        {
            _impl.call(obj);
        }

        void reset() { _impl.reset(); }

    private:
        typedef void (Object::*action_type)(Object*);
        safe_call::CallHolder<action_type> _impl;
    };

    // 2 个参数
    template <>
    class SafeCall<2>
    {
    public:
        template <typename T, typename B, typename Obj1, typename Obj2>
        void set(T* target, void (B::*action)(Obj1*, Obj2*))
        {
            _impl.set(target, action);
        }

        template <typename Obj1, typename Obj2>
        void call(Obj1* obj1, Obj2* obj2)
        {
            _impl.call(obj1, obj2);
        }

        void reset() { _impl.reset(); }

    private:
        typedef void (Object::*action_type)(Object*, Object*);
        safe_call::CallHolder<action_type> _impl;
    };
}

#endif
