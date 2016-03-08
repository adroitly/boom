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

#ifndef __CCEX_DISPATCHMANAGER_H__
#define __CCEX_DISPATCHMANAGER_H__

#include "cocos2d.h"
#include <vector>
#include <functional>

namespace ccex
{
    class DispatchManager : public cocos2d::Ref
    {
    public:
        typedef std::function<void(float delta)> FunType;

        static DispatchManager* getInstance();

        uint64_t addFun(const FunType& fun);

        void removeFun(uint64_t Id);

        void clear();
        bool isEmpty() const;

    private:
        DispatchManager();
        void dispatchCallbacks(float delta);

    private:
        struct Item
        {
            FunType fun;
            uint64_t Id;
        };
        std::vector<Item> _funs;
        uint64_t _nextId;
    };
}

#endif
