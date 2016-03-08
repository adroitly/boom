//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_LIGHT_STRING__
#define __CLOVER_LIGHT_STRING__

#include <cstdint>
#include <cstddef>
#include <cassert>
#include <cstring>
#include <boost/noncopyable.hpp>

namespace clover
{
    class light_string : boost::noncopyable
    {
    public:
        light_string() : _str(nullptr)
        {
        }

        light_string(const char* str, size_t size)
        {
            assign(str, size);
        }

        explicit light_string(const char* str)
        {
            assign(str, str ? strlen(str) : 0);
        }

        ~light_string()
        {
            safe_free();
        }
        
        const char* c_str() const
        {
            return _str ? _str : "";
        }

        void reset(const char* str, size_t size)
        {
            safe_free();
            assign(str, size);
        }

        void reset(const char* str)
        {
            reset(str, str ? strlen(str) : 0);
        }

        size_t size() const
        {
            if (_str == nullptr)
            {
                return 0;
            }
            return *head();
        }

        bool empty() const
        {
            return _str == nullptr;
        }

        const char* begin() const
        {
            return _str;
        }

        const char* end() const
        {
            return _str + size();
        }

        char operator[](size_t idx) const
        {
            return _str[idx];
        }

    private:
        size_t* head() const;
        void safe_free();
        void assign(const char* str, size_t size);

    private:
        char* _str;
    };

    static_assert(sizeof(char*) == sizeof(light_string), "");

    inline bool operator==(const light_string& lhs, const char* rhs)
    {
        return strcmp(lhs.c_str(), rhs) == 0;
    }

    inline bool operator==(const char* lhs, const light_string& rhs)
    {
        return rhs == lhs;
    }

    inline bool operator==(const light_string& lhs, const light_string& rhs)
    {
        return lhs.size() == rhs.size() && (lhs == rhs.c_str());
    }

    inline bool operator!=(const light_string& lhs, const char* rhs)
    {
        return !(lhs == rhs);
    }

    inline bool operator!=(const char* lhs, const light_string& rhs)
    {
        return !(lhs == rhs);
    }

    inline bool operator!=(const light_string& lhs, const light_string& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
