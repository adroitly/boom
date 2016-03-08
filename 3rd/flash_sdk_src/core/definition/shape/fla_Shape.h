//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLASHAPEWITHSTYLE__
#define __FLASHAPEWITHSTYLE__

#include <vector>
#include "fla_LineStyle.h"
#include "fla_FillStyle.h"
#include "fla_Path.h"
#include "clover/ImmutableData.h"

namespace fla
{
    template <int N>
    class ShapeBase
    {
    public:
        typedef FillStyleBase<N> FillStyleT;
        typedef LineStyleBase<N> LineStyleT;
        typedef typename PathTypeTratis<N>::PathT PathT;

        // 是否有样式
        bool hasStyle() const;

        void shrink_to_fit();
        void swap(ShapeBase& shape);

        bool isEmpty() const
        {
            return paths.empty();
        }

        bool isStyleInvisible() const;

        std::vector<FillStyleT> fillStyles;
        std::vector<LineStyleT> lineStyles;
        std::vector<PathT> paths;
    };

    template <int N>
    inline bool ShapeBase<N>::hasStyle() const
    {
        return !fillStyles.empty() || !lineStyles.empty();
    }

    template <int N>
    void ShapeBase<N>::shrink_to_fit()
    {
        fillStyles.shrink_to_fit();
        lineStyles.shrink_to_fit();
        paths.shrink_to_fit();
        for (auto& path : paths)
        {
            path.shrink_to_fit();
        }
    }

    template <int N>
    void ShapeBase<N>::swap(ShapeBase& shape)
    {
        fillStyles.swap(shape.fillStyles);
        lineStyles.swap(shape.lineStyles);
        paths.swap(shape.paths);
    }

    template <int N>
    bool ShapeBase<N>::isStyleInvisible() const
    {
        for (auto& style : fillStyles)
        {
            if (!style.isInvisible())
            {
                return false;
            }
        }

        for (auto& style : lineStyles)
        {
            if (!style.isInvisible())
            {
                return false;
            }
        }
        return true;
    }

    ////////////////////////////////////////////////////////////
    class Shape : public ShapeBase<1>
    {
    public:
        // 计算所有的边合起来的大小
        Rect computeEdgeBounds() const;
    };

    class MorphShape : public ShapeBase<2>
    {
    };

    typedef clover::ImmutableData<clover::MemCopy, clover::MemFree> RawData;
}

#endif
