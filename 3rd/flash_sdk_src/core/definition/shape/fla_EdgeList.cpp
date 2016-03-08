//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_EdgeList.h"
#include <stack>
#include <memory>
#include "../../base/fla_Base.h"

namespace fla
{
	const real_t kEdgeListPointEpsilon = static_cast<real_t>(0.00001);

    bool EdgeList::join(const EdgeList& other)
    {
        if (lastPoint().equals(other._firstPt, kEdgeListPointEpsilon))
        {
            _lastEdgePos = other._lastEdgePos + _edges.size();
            _edges.pushData(other._edges.begin(), other._edges.size());
            return true;
        }
        return false;
    }

    bool EdgeList::isEdgesEqualTo(const EdgeList& other) const
    {
        return _firstPt.equals(other._firstPt, kEdgeListPointEpsilon) && _edges == other._edges;
    }

    bool EdgeList::isClosed() const
    {
        return _firstPt.equals(lastPoint(), kEdgeListPointEpsilon);
    }

    void EdgeList::flipPath()
    {
        if (isEdgeEmpty())
        {
            return;
        }

        CurveTo edgeData;
        std::stack<CurveTo> stack;
        auto edgeSize = sizeofEdge((Edge*)&_edges[0]);
        _lastEdgePos = _edges.size() - edgeSize;

        for (auto edge : *this)
        {
            memcpy(&edgeData, edge, sizeofEdge(edge));
            std::swap(edgeData.point, _firstPt);
            stack.push(edgeData);
        }

        _edges.clear();
        while (!stack.empty())
        {
            auto& top = stack.top();
            pushEdge((uint8_t*)&top, sizeofEdge(&top));
            stack.pop();
        }
    }

    static void unionPoint(Point& minPt, Point& maxPt, const Point& pt)
    {
        minPt.x = std::min(minPt.x, pt.x);
        minPt.y = std::min(minPt.y, pt.y);
        maxPt.x = std::max(maxPt.x, pt.x);
        maxPt.y = std::max(maxPt.y, pt.y);
    }

    Rect EdgeList::computeEdgeBounds() const
    {
        Point minPt = _firstPt;
        Point maxPt = _firstPt;

        for (auto edge : *this)
        {
            if (edge->getType() == EdgeType::LineTo)
            {
                auto line = static_cast<const LineTo*>(edge);
                unionPoint(minPt, maxPt, line->point);
            }
            else if (edge->getType() == EdgeType::CurveTo)
            {
                auto curve = static_cast<const CurveTo*>(edge);
                unionPoint(minPt, maxPt, curve->point);
                unionPoint(minPt, maxPt, curve->control);
            }
        }

        auto width = maxPt.x - minPt.x;
        auto height = maxPt.y - minPt.y;
        return Rect(minPt.x, minPt.y, width, height);
    }

    bool EdgeList::isFlipEdgesEqualTo(const EdgeList& other) const
    {
        if (_edges.size() != other._edges.size())
        {
            return false;
        }
        EdgeList flipPath = other;
        flipPath.flipPath();
        return isEdgesEqualTo(flipPath);
    }

    const Point& EdgeList::lastPoint() const
    {
        if (isEdgeEmpty())
        {
            return _firstPt;
        }
        auto edge = reinterpret_cast<const LineTo*>(&_edges[_lastEdgePos]);
        return edge->point;
    }

    bool EdgeList::isLastEdge(const Edge* edge) const
    {
        auto lastEdge = &_edges[_lastEdgePos];
        return (uint8_t*)edge >= lastEdge;
    }
}
