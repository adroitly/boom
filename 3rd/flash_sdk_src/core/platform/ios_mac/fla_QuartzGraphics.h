//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_QUARTZGRAPHICS__
#define __FLA_QUARTZGRAPHICS__

#include "../../base/fla_Base.h"
#include "../../base/fla_Color4.h"
#include "../../base/fla_Image.h"
#include "../../base/fla_BitmapData.h"
#include "../../graphics/fla_Graphics.h"
#include <CoreGraphics/CoreGraphics.h>
#include <boost/noncopyable.hpp>

namespace fla
{
    // 使用Quartz实现的图形接口
    class QuartzGraphics : boost::noncopyable
    {
    public:
        explicit QuartzGraphics(CGContextRef ctx);
        
        void ellipse(const Rect& rect);
        void moveTo(real_t x, real_t y);
        void lineTo(real_t x, real_t y);
        void quadCurveTo(real_t ctlx, real_t ctly, real_t x, real_t y);

        void beginPath();
        void closePath();

        enum DrawingMode
        {
            PathEOFill = kCGPathEOFill,
            PathStroke = kCGPathStroke,
            PathEOFillStroke = kCGPathEOFillStroke,
        };

        void drawPath(DrawingMode mode);
        void setStrokeColor(real_t r, real_t g, real_t b, real_t a);
        void setFillColor(real_t r, real_t g, real_t b, real_t a);

        void scaleCTM(real_t sx, real_t sy);
        void translateCTM(real_t tx, real_t ty);
        void rotateCTM(real_t angle);
        void concatCTM(const Matrix& trans);

        void setLineWidth(real_t lineWidth);
        void saveGState();

        void restoreGState();

        enum LineCap
        {
            LineCapButt = kCGLineCapButt,
            LineCapRound = kCGLineCapRound,
            LineCapSquare = kCGLineCapSquare,
        };

        void setLineCap(LineCap lineCap);
        void setMiterLimit(real_t limit);

        enum LineJoin
        {
            LineJoinMiter = kCGLineJoinMiter,
            LineJoinRound = kCGLineJoinRound,
            LineJoinBevel = kCGLineJoinBevel,
        };

        void setLineJoin(LineJoin join);
        void clipPath();
        void drawGradient(const std::vector<Color4>& colors,
                          const std::vector<real_t>& locations,
                          bool isLinaer,
                          real_t radius,
                          const Matrix& trans);

        void drawBitmapImage(const Size& imageSize, const void* pixels, const Matrix& trans);
        void drawImage(const Size& imageSize, const Image& image, const Matrix& trans);
        void drawImage(const Size& imageSize, const Image& image, const Rect& rect);
        
        void clipToRect(const Rect& rt);
        
    protected:
        void drawImageRef(const Size& imageSize, CGImageRef image, const Matrix& trans);

        QuartzGraphics();
        void setContent(CGContextRef content, bool checkInitCTM);

    private:
        CGContextRef        _context;
        CGAffineTransform   _initInvertCTM;
        bool                _checkInitCTM;
    };

    ////////////////////////////////////////////////////////////////////////
    class QuartzBitmapGraphics : public QuartzGraphics
    {
    public:
        explicit QuartzBitmapGraphics(int width, int height, PixelFormat pixelFormat);
        ~QuartzBitmapGraphics();

        void flipAndScale(real_t scale);

        fla::Image::Ptr createImage() const;
        fla::BitmapData::Ptr getBitmapData() const;

    private:
        CGContextRef _bitmapContent;
        fla::BitmapData::Ptr _bitmapData;
    };
}

#endif
