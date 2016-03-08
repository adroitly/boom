//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_REFDICT_H__
#define __FLA_REFDICT_H__

#include <boost/noncopyable.hpp>

namespace fla
{
    template <typename T>
    class RefDict : boost::noncopyable
    {
    public:
        ~RefDict();
        void set(T* obj, const std::string& key);
        T* get(const std::string& key) const;
        void remove(const std::string& key);
        void clear();

        template <typename Fun>
        void removeIf(Fun&& fun);

    private:
        std::map<std::string, T*> _refs;
    };

    template <typename T>
    RefDict<T>::~RefDict()
    {
        clear();
    }

    template <typename T>
    void RefDict<T>::clear()
    {
        for (auto& iter : _refs)
        {
            assert(iter.second);
            iter.second->release();
        }
        _refs.clear();
    }

    template <typename T>
    void RefDict<T>::remove(const std::string& key)
    {
        auto iter = _refs.find(key);
        if (iter != _refs.end())
        {
            assert(iter->second);
            iter->second->release();
            _refs.erase(iter);
        }
    }

    template <typename T>
    T* RefDict<T>::get(const std::string& key) const
    {
        auto iter = _refs.find(key);
        if (iter != _refs.end())
        {
            assert(iter->second);
            return iter->second;
        }
        return nullptr;
    }

    template <typename T>
    void RefDict<T>::set(T* obj, const std::string& key)
    {
        assert(obj);

        auto iter = _refs.lower_bound(key);
        if (iter != _refs.end() && iter->first == key)
        {
            if (iter->second != obj)
            {
                assert(iter->second);
                iter->second->release();
                iter->second = obj;
                iter->second->retain();
            }
        }
        else
        {
            obj->retain();
            _refs.insert(iter, std::make_pair(key, obj));
        }
    }

    template <typename T>
    template <typename Fun>
    void RefDict<T>::removeIf(Fun&& fun)
    {
        for (auto iter = _refs.begin(); iter != _refs.end();)
        {
            if (fun(iter->second))
            {
                iter->second->release();
                iter = _refs.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

#endif
