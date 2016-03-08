//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_EDGELIST_H__
#define __FLA_EDGELIST_H__

#include <vector>
#include "fla_PathEdge.h"
#include "clover/Data.h"

namespace fla
{
    //! 一系列边
    class EdgeList
    {
    public:
        EdgeList() : _lastEdgePos(0)
        {
        }

        // 加入边
        void addEdge(const LineTo& edge)
        {
            pushEdge((uint8_t*)&edge, sizeof(LineTo));
        }

        void addEdge(const CurveTo& edge)
        {
            pushEdge((uint8_t*)&edge, sizeof(CurveTo));
        }

        // 如果最后一点等于path的第一个点，就可以将两路径收尾连接起来
        bool join(const EdgeList& path);

        // 将路径翻转
        void flipPath();

        // 计算各边合起来的包围框
        Rect computeEdgeBounds() const;

        // 迭代器，遍历各边
        class EdgeIter
        {
        public:
            EdgeIter(const uint8_t* cur) : _cur(cur)
            {
            }

            const Edge* operator*() const
            {
                return ((Edge*)_cur);
            }

            bool operator!=(const EdgeIter& rhs) const
            {
                return (_cur != rhs._cur);
            }

            EdgeIter& operator++()
            {
                _cur += sizeofEdge((Edge*)_cur);
                return *this;
            }

        private:
            const uint8_t* _cur;
        };

        EdgeIter begin() const
        {
            return EdgeIter(_edges.begin());
        }

        EdgeIter end() const
        {
            return EdgeIter(_edges.end());
        }

        void setFirstPt(const Point& pt)
        {
            _firstPt = pt;
        }
        const Point& firstPt() const;
        const Point& lastPoint() const;

        // 是否没有边
        bool isEdgeEmpty() const
        {
            return _edges.empty();
        }

        // 是否闭合，指首尾相连
        bool isClosed() const;

        // 边是否相等
        bool isEdgesEqualTo(const EdgeList& other) const;

        // 翻转边后，是否相等
        bool isFlipEdgesEqualTo(const EdgeList& other) const;

        // 判断是否是最后一边
        bool isLastEdge(const Edge* edge) const;

        void shrink_to_fit()
        {
            _edges.shrink_to_fit();
        }

    private:
        void pushEdge(uint8_t* bytes, size_t size);

    private:
        clover::Data         _edges;
        Point                _firstPt;
        size_t               _lastEdgePos;
    };

    inline const Point& EdgeList::firstPt() const
    {
        return _firstPt;
    }

    inline void EdgeList::pushEdge(uint8_t* bytes, size_t size)
    {
        _lastEdgePos = _edges.size();
        _edges.pushData(bytes, size);
    }
}

#endif
