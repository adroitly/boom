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

#ifndef __RBP_REF_H__
#define __RBP_REF_H__

#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>
#include <atomic>

namespace rbp
{
    template <typename DerivedT>
    class Ref : boost::noncopyable
    {
    public:
        typedef boost::intrusive_ptr<DerivedT> Ptr;

        Ref()
        {
            _refCount = 1;
        }

        virtual ~Ref()
        {
        }

        void retain()
        {
            _refCount.fetch_add(1);
        }

        void release()
        {
            if (_refCount.fetch_sub(1) == 1)
            {
                delete this;
            }
        }

    private:
        std::atomic<int32_t> _refCount;
    };

    template <typename T>
    inline void intrusive_ptr_add_ref(Ref<T>* obj)
    {
        obj->retain();
    }

    template <typename T>
    inline void intrusive_ptr_release(Ref<T>* obj)
    {
        obj->release();
    }

    template <typename T, typename... Args>
    inline boost::intrusive_ptr<T> makeRef(Args&&... args)
    {
        return boost::intrusive_ptr<T>(new T(std::forward<Args>(args)...), false);
    }
}

#endif
