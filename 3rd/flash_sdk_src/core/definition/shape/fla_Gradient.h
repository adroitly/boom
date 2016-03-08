//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLAGRADIENT__
#define __FLAGRADIENT__


#include <vector>
#include "../../Base/fla_Color4.h"
#include "../../Utility/fla_Holder.h"


namespace fla
{
    // 渐变
    template <int N>
    class GradientBase
    {
    public:
        typedef Holder<Color4, N>       ColorT;
        typedef Holder<float, N>        FloatT;
        typedef Holder<Matrix, N>       MatrixT;
        
        GradientBase()
        {
            init(Int2Type<N>());
        }

        struct Record
        {
            Record(const ColorT& c, FloatT l) : color(c), location(l)    {}
            bool operator == (const Record& rhs) const
            {
                return color == rhs.color && location == rhs.location;
            }
            ColorT  color;
            FloatT  location;
        };
        
        void addRecord(const ColorT& color, Holder<float, N> location)
        {
            _records.push_back(Record(color, location));
        }
        
        const std::vector<Record>&      records() const      {   return _records;     }
        
		real_t radius() const          { return static_cast<real_t>(16384.0 / 20.0); }
        
        void setMatrix(const MatrixT& m)  {   _matrix = m;    }
        const MatrixT& matrix() const     {   return _matrix; }
        
        void setFocalPoint(const FloatT& point)   {   _focalPoint = point;  }
        const FloatT& focalPoint() const          {   return _focalPoint;   }
        
        bool operator == (const GradientBase& rhs) const
        {
            return
            _records == rhs._records &&
            _matrix == rhs._matrix &&
            _focalPoint == rhs._focalPoint;
        }
        
    private:
        void init(Int2Type<1>)
        {
            _focalPoint = 0;
        }
        
        void init(Int2Type<2>)
        {
            _focalPoint.start = _focalPoint.end = 0;
        }
        
    private:
        std::vector<Record>     _records;
        MatrixT                 _matrix;
        FloatT                  _focalPoint;
    };
    
    
    typedef GradientBase<1> Gradient;
    typedef GradientBase<2> MorphGradient;
};



#endif
