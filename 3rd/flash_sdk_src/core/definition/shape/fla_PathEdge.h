//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef _FLA_PATHEDGE_H
#define _FLA_PATHEDGE_H

#include <stdint.h>
#include "../../base/fla_Base.h"

namespace fla
{
    //! 边的类型
    enum class EdgeType : uint32_t
    {
        None,     //! 非法
        LineTo,   //! 直线
        CurveTo,  //! 弧线
    };

    class Edge
    {
    public:
        Edge() : _type(EdgeType::None)
        {
        }
        
        EdgeType getType() const
        {
            return _type;
        }

    protected:
        EdgeType _type;
    };

    //! 直线边
    struct LineTo : public Edge
    {
        LineTo()
        {
            _type = EdgeType::LineTo;
        }
        
        LineTo(const Point& pt_) : point(pt_)
        {
            _type = EdgeType::LineTo;
        }
        
        Point point;
    };

    //! 弧线边
    struct CurveTo : public LineTo
    {
        CurveTo()
        {
            _type = EdgeType::CurveTo;
        }
        Point control;
    };

    //! 根据类型，计算出边的大小
    inline size_t sizeofEdge(const Edge* edge)
    {
        if (edge->getType() == EdgeType::LineTo)
        {
            return sizeof(LineTo);
        }
        
        if (edge->getType() == EdgeType::CurveTo)
        {
            return sizeof(CurveTo);
        }
        return 0;
    }
}

#endif
