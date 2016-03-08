//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_SHAPEGRAPHICSUTILS__
#define __FLA_SHAPEGRAPHICSUTILS__

#include "fla_Shape.h"
#include "../../base/fla_Lerp.h"

namespace fla
{
    namespace shape
    {
        template <typename Graphics>
        void GenPath(Graphics& graphics, const Path& path, bool includeHole)
        {
            graphics.moveTo(path.edges<0>().firstPt().x, path.edges<0>().firstPt().y);

            for (auto edge : path.edges<0>())
            {
                if (edge->getType() == EdgeType::LineTo)
                {
                    auto& line = static_cast<const LineTo&>(*edge);
                    graphics.lineTo(line.point.x, line.point.y);
                }
                else if (edge->getType() == EdgeType::CurveTo)
                {
                    auto& curve = static_cast<const CurveTo&>(*edge);
                    graphics.quadCurveTo(curve.control.x, curve.control.y, curve.point.x, curve.point.y);
                }
            }

            if (path.hasFillStyle())
            {
                graphics.closePath();
                if (includeHole)
                {
                    for (auto& holePath : path.subPaths())
                    {
                        GenPath(graphics, holePath, includeHole);
                    }
                }
            }
        }

        template <typename Graphics>
        void GenEdge(Graphics& graphics, Point& startPt, Point& endPt, float ratio, const Edge& edge0, const Edge& edge1)
        {
            auto startType = edge0.getType();
            auto endType = edge1.getType();

            // line, line
            if (startType == EdgeType::LineTo && endType == EdgeType::LineTo)
            {
                auto& line0 = static_cast<const LineTo&>(edge0);
                auto& line1 = static_cast<const LineTo&>(edge1);
                startPt = line0.point;
                endPt = line1.point;
                auto pt = lerp(line0.point, line1.point, ratio);
                graphics.lineTo(pt.x, pt.y);
            }
            // curve, curve
            else if (startType == EdgeType::CurveTo && endType == EdgeType::CurveTo)
            {
                auto& curve0 = static_cast<const CurveTo&>(edge0);
                auto& curve1 = static_cast<const CurveTo&>(edge1);
                startPt = curve0.point;
                endPt = curve1.point;
                auto ctl = lerp(curve0.control, curve1.control, ratio);
                auto pt = lerp(curve0.point, curve1.point, ratio);
                graphics.quadCurveTo(ctl.x, ctl.y, pt.x, pt.y);
            }
            // line, curve
            else if (startType == EdgeType::LineTo && endType == EdgeType::CurveTo)
            {
                auto& line0 = static_cast<const LineTo&>(edge0);
                auto& curve1 = static_cast<const CurveTo&>(edge1);

                auto ctl0 = (startPt + line0.point) * 0.5;
                startPt = line0.point;
                endPt = curve1.point;

                auto ctl = lerp(ctl0, curve1.control, ratio);
                auto pt = lerp(line0.point, curve1.point, ratio);
                graphics.quadCurveTo(ctl.x, ctl.y, pt.x, pt.y);
            }
            // curve, line
            else if (startType == EdgeType::CurveTo && endType == EdgeType::LineTo)
            {
                auto& curve0 = static_cast<const CurveTo&>(edge0);
                auto& line1 = static_cast<const LineTo&>(edge1);

                auto crl1 = (endPt + line1.point) * 0.5;
                startPt = curve0.point;
                endPt = line1.point;

                auto ctl = lerp(curve0.control, crl1, ratio);
                auto pt = lerp(curve0.point, line1.point, ratio);
                graphics.quadCurveTo(ctl.x, ctl.y, pt.x, pt.y);
            }
        }

        template <typename Graphics>
        void GenMorphPath(Graphics& graphics, const MorphPath& path, float ratio, bool includeHold)
        {
            auto& startEdge = path.edges<0>();
            auto& endEdge = path.edges<1>();

            auto start = startEdge.firstPt();
            auto end = endEdge.firstPt();
            auto pt = lerp(start, end, ratio);
            graphics.moveTo(pt.x, pt.y);

            for (auto sIter = startEdge.begin(), eIter = endEdge.begin(); sIter != startEdge.end() && eIter != endEdge.end();
                 ++sIter, ++eIter)
            {
                auto sEdge = *sIter;
                auto eEdge = *eIter;
                GenEdge(graphics, start, end, ratio, *sEdge, *eEdge);
            }

            if (path.hasFillStyle())
            {
                graphics.closePath();
                if (includeHold)
                {
                    for (auto& subPath : path.subPaths())
                    {
                        GenMorphPath(graphics, subPath, ratio, includeHold);
                    }
                }
            }
        }

        template <typename Graphics>
        inline typename Graphics::LineCap _lineCap(LineCapStyle cap)
        {
            if (cap == LineCapStyle::Round)
            {
                return Graphics::LineCapRound;
            }
            else if (cap == LineCapStyle::Square)
            {
                return Graphics::LineCapSquare;
            }
            return Graphics::LineCapRound;
        }

        template <typename Graphics>
        inline typename Graphics::LineJoin _lineJoint(LineJoinStyle joint)
        {
            if (joint == LineJoinStyle::Miter)
            {
                return Graphics::LineJoinMiter;
            }
            else if (joint == LineJoinStyle::Bevel)
            {
                return Graphics::LineJoinBevel;
            }
            return Graphics::LineJoinRound;
        }
    }
};

#endif
