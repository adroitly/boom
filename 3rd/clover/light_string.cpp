//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "./light_string.h"

namespace clover
{
    void light_string::assign(const char* str, size_t size)
    {
        if (str == nullptr || size == 0)
        {
            _str = 0;
        }
        else
        {
            const size_t headSize = sizeof(size_t);
            char* head = (char*)malloc(size + 1 + headSize);
            _str = head + headSize;
            strncpy(_str, str, size);
            _str[size] = 0;
            *((size_t*)head) = size;
        }
    }

    void light_string::safe_free()
    {
        if (_str != nullptr)
        {
            auto ptr = head();
            free(ptr);
        }
    }

    size_t* light_string::head() const
    {
        assert(_str);
        return (size_t*)(_str - sizeof(size_t));
    }
}
