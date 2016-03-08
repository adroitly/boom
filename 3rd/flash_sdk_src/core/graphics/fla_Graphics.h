//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_GRAPHICS__
#define __FLA_GRAPHICS__

#include "../base/fla_Base.h"
#include "../base/fla_Color4.h"
#include "../base/fla_Image.h"
#include <vector>

namespace fla
{
    // 需要完成这些的接口，才能完成最基本的渲染
    class Graphics
    {
    public:
        // 路径操作
        void beginPath()
        {
        }

        void closePath()
        {
        }

        void moveTo(real_t x, real_t y)
        {
            FLA_UNUSED(x);
            FLA_UNUSED(y);
        }

        void lineTo(real_t x, real_t y)
        {
            FLA_UNUSED(x);
            FLA_UNUSED(y);
        }

        void quadCurveTo(real_t ctlx, real_t ctly, real_t x, real_t y)
        {
            FLA_UNUSED(ctlx);
            FLA_UNUSED(ctly);
            FLA_UNUSED(x);
            FLA_UNUSED(y);
        }

        // 绘画参数
        void setStrokeColor(real_t r, real_t g, real_t b, real_t a)
        {
            FLA_UNUSED(r);
            FLA_UNUSED(g);
            FLA_UNUSED(b);
            FLA_UNUSED(a);
        }

        void setFillColor(real_t r, real_t g, real_t b, real_t a)
        {
            FLA_UNUSED(r);
            FLA_UNUSED(g);
            FLA_UNUSED(b);
            FLA_UNUSED(a);
        }

        void setLineWidth(real_t lineWidth)
        {
            FLA_UNUSED(lineWidth);
        }

        // 绘画
        enum DrawingMode
        {
            PathEOFill,
            PathStroke,
            PathEOFillStroke,
        };

        void drawPath(DrawingMode mode)
        {
            FLA_UNUSED(mode);
        }

        void drawImage(const fla::Rect& rt, const fla::Image&)
        {
            FLA_UNUSED(rt);
        }

        // 变换
        void scaleCTM(real_t sx, real_t sy)
        {
            FLA_UNUSED(sx);
            FLA_UNUSED(sy);
        }

        void translateCTM(real_t tx, real_t ty)
        {
            FLA_UNUSED(tx);
            FLA_UNUSED(ty);
        }

        void rotateCTM(real_t angle)
        {
            FLA_UNUSED(angle);
        }

        void concatCTM(const Matrix& trans)
        {
            FLA_UNUSED(trans);
        }

        // 状态保存
        void saveGState()
        {
        }

        void restoreGState()
        {
        }

        enum LineCap
        {
            LineCapButt,
            LineCapRound,
            LineCapSquare,
        };

        enum LineJoin
        {
            LineJoinMiter,
            LineJoinRound,
            LineJoinBevel,
        };

        void setLineCap(LineCap lineCap)
        {
            FLA_UNUSED(lineCap);
        }

        void setMiterLimit(real_t limit)
        {
            FLA_UNUSED(limit);
        }

        void setLineJoin(LineJoin join)
        {
            FLA_UNUSED(join);
        }

        // 绘画渐变
        void drawGradient(const std::vector<Color4>& colors,
                          const std::vector<real_t>& locations,
                          bool isLinaer,
                          real_t radius,
                          const Matrix& trans)
        {
            FLA_UNUSED(colors);
            FLA_UNUSED(locations);
            FLA_UNUSED(isLinaer);
            FLA_UNUSED(radius);
            FLA_UNUSED(trans);
        }
    };
}

#endif
