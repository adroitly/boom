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

#ifndef __CCEX_REFCACHE_H__
#define __CCEX_REFCACHE_H__

#include "cocos2d.h"

namespace ccex
{
    class RefSet : public cocos2d::Ref
    {
    public:
        static RefSet* create();
        void add(Ref* obj);
        Ref* reuse();

    private:
        std::vector<cocos2d::RefPtr<Ref>> _refs;
    };

    class RefCache : public cocos2d::Ref
    {
    public:
        static RefCache* getInstance();
        static void destroyInstance();

        static RefCache* create();

        void add(Ref* obj, const std::string& key);
        Ref* get(const std::string& key) const;
        void remove(const std::string& key);
        void removeAll();

    private:
        std::unordered_map<std::string, cocos2d::RefPtr<Ref>> _refs;
    };
}

#endif
