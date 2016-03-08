//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_PTRHOLDER_H__
#define __FLA_PTRHOLDER_H__

namespace fla
{
    template <typename T>
    class PtrHolder
    {
    public:
        PtrHolder()     { _ptr = nullptr;   }
        ~PtrHolder()    { ptr_free();       }

        PtrHolder(const PtrHolder& rhs);
        PtrHolder& operator=(const PtrHolder& rhs);

        bool hasValue() const   {   return _ptr != nullptr; }
        const T& value() const  {   return *_ptr;           }
        void setValue(const T& value);

    private:
        void ptr_free();
        T* _ptr;
    };
    
    template <typename T>
    void PtrHolder<T>::setValue(const T& value)
    {
        if (_ptr)
        {
            *_ptr = value;
        }
        else
        {
            _ptr = new T(value);
        }
    }
    
    template <typename T>
    PtrHolder<T>& PtrHolder<T>::operator=(const PtrHolder<T>& rhs)
    {
        if (this != &rhs)
        {
            if (rhs.hasValue())
            {
                setValue(rhs.value());
            }
            else
            {
                ptr_free();
                _ptr = nullptr;
            }
        }
        return *this;
    }
    
    template <typename T>
    PtrHolder<T>::PtrHolder(const PtrHolder<T>& rhs)
    {
        _ptr = nullptr;
        if (rhs.hasValue())
        {
            _ptr = new T(rhs.value());
        }
    }
    
    template <typename T>
    void PtrHolder<T>::ptr_free()
    {
        if (_ptr)
        {
            delete _ptr;
        }
    }
}

#endif