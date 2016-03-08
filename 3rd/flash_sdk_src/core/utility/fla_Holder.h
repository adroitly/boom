//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_HOLDER__
#define __FLA_HOLDER__


namespace fla
{
    template <typename T, int N = 1>
    class Holder;
    
    template <int N>
    struct Int2Type {};
    

    // 存放一个数
    template <typename T>
    class Holder<T, 1>
    {
    public:
        Holder()                                        {}
        Holder(const T& v)                : val(v)      {}
        
        Holder& operator = (const T& v);
        Holder& operator = (const Holder<T, 1>& rhs);
        bool operator == (const Holder& rhs) const;
        
        T& get(Int2Type<0>);
        
        const T& get(Int2Type<0>) const;
        
        operator T() const    {   return val;    }
        operator T()          {   return val;    }
        
        T   val;
    };
    
    
    // 存放两个数
    template <typename T>
    class Holder<T, 2>
    {
    public:
        bool operator == (const Holder& rhs) const
        {
            return
            this->start == rhs.start &&
            this->end == rhs.end;
        }
        
        template <typename TT>
        Holder(const Holder<TT, 2>& rhs)
        {
            this->start = rhs.start;
            this->end = rhs.end;
        }
        
        Holder()                            {}

        T& get(Int2Type<0>)                 {   return this->start;   }
        const T& get(Int2Type<0>) const     {   return this->start;   }

        T& get(Int2Type<1>)                 {   return this->end;     }
        const T& get(Int2Type<1>) const     {   return this->end;     }

        template <typename ScaleT>
        auto operator * (ScaleT scale) const -> Holder<decltype(scale * T()), 2>
        {
			typedef decltype(scale * T()) TT;
            Holder<TT, 2> result;
            result.start = start * scale;
            result.end = start * scale;
            return result;
        }
        
        template <typename ScaleT>
        auto operator / (ScaleT scale) const -> Holder<decltype(scale / T()), 2>
        {
            typedef decltype(scale * start) TT;
            Holder<TT, 2> result;
            result.start = start / scale;
            result.end = start / scale;
            return result;
        }
        
        T   start;
        T   end;
    };
    
    template <typename T>
    inline Holder<T, 1>& Holder<T, 1>::operator = (const T& v)
    {
        val = v;
        return *this;
    }
    
    template <typename T>
    inline Holder<T, 1>& Holder<T, 1>::operator = (const Holder<T, 1>& rhs)
    {
        val = rhs.val;
        return *this;
    }
    
    template <typename T>
    inline bool Holder<T, 1>::operator == (const Holder& rhs) const
    {
        return val == rhs.val;
    }
    
    template <typename T>
    inline T& Holder<T, 1>::get(Int2Type<0>)
    {
        return val;
    }
    
    template <typename T>
    inline const T& Holder<T, 1>::get(Int2Type<0>) const
    {
        return val;
    }
}



#endif
