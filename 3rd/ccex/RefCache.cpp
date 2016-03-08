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

#include "RefCache.h"
using namespace cocos2d;

namespace ccex
{
    RefSet* RefSet::create()
    {
        RefSet* ptr = new RefSet();
        ptr->autorelease();
        return ptr;
    }

    void RefSet::add(Ref* obj)
    {
        _refs.push_back(obj);
    }

    Ref* RefSet::reuse()
    {
        if (_refs.empty())
        {
            return nullptr;
        }
        auto back = _refs.back();
        back->retain();
        back->autorelease();
        _refs.pop_back();
        return back;
    }

    static RefCache* s_cache;
    RefCache* RefCache::getInstance()
    {
        if (s_cache == nullptr)
        {
            s_cache = new RefCache();
        }
        return s_cache;
    }

    void RefCache::destroyInstance()
    {
        if (s_cache)
        {
            delete s_cache;
            s_cache = nullptr;
        }
    }

    RefCache* RefCache::create()
    {
        RefCache* ref = new RefCache();
        ref->autorelease();
        return ref;
    }

    void RefCache::add(Ref* obj, const std::string& key)
    {
        _refs[key] = obj;
    }

    Ref* RefCache::get(const std::string& key) const
    {
        auto iter = _refs.find(key);
        if (iter != _refs.end() && iter->first == key)
        {
            return iter->second;
        }
        return nullptr;
    }

    void RefCache::remove(const std::string& key)
    {
        _refs.erase(key);
    }

    void RefCache::removeAll()
    {
        _refs.clear();
    }
}
