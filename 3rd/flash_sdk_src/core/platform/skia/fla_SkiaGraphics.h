//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_SKIAGRAPHICS_H__
#define __FLA_SKIAGRAPHICS_H__

#include <vector>
#include <stack>
#include "core/base/fla_Base.h"
#include "core/graphics/fla_Graphics.h"
#include "core/base/fla_Color4.h"
#include "SkCanvas.h"
#include "core/base/fla_BitmapData.h"

namespace fla
{
    // 使用Quartz实现的图形接口
    class SkiaGraphics : public fla::Graphics
    {
    public:
        explicit SkiaGraphics(SkCanvas* cav) : _canvas(cav)
        {
        }
        SkiaGraphics(const SkiaGraphics& rhs) = delete;
        SkiaGraphics& operator=(const SkiaGraphics& rhs) = delete;

        void ellipse(const Rect& rect);
        void moveTo(real_t x, real_t y);
        void lineTo(real_t x, real_t y);
        void quadCurveTo(real_t ctlx, real_t ctly, real_t x, real_t y);

        void beginPath();
        void closePath();

        enum DrawingMode
        {
            PathEOFill,
            PathStroke,
            PathEOFillStroke,
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

        void restoreGState()
        {
            _canvas->restore();
            if (_stateStack.size() > 1)
            {
                _stateStack.pop();
            }
        }

        enum LineCap
        {
            LineCapButt,
            LineCapRound,
            LineCapSquare,
        };

        void setLineCap(LineCap lineCap)
        {
            _stateStack.top().paint.setStrokeCap((SkPaint::Cap)lineCap);
        }

        void setMiterLimit(real_t limit)
        {
            _stateStack.top().paint.setStrokeMiter(limit);
        }

        enum LineJoin
        {
            LineJoinMiter = SkPaint::Join::kMiter_Join,
            LineJoinRound = SkPaint::Join::kRound_Join,
            LineJoinBevel = SkPaint::Join::kBevel_Join,
        };

        void setLineJoin(LineJoin join)
        {
            _stateStack.top().paint.setStrokeJoin((SkPaint::Join)join);
        }
        
        void clipToRect(const Rect& rt);

        void clipPath()
        {
            _canvas->clipPath(_path);
        }

        void drawGradient(const std::vector<Color4>& colors,
                          const std::vector<real_t>& locations,
                          bool isLinaer,
                          real_t radius,
                          const Matrix& trans);

        void drawImage(const Size& imageSize, const Image& image, const Matrix& trans);

        void drawImage(const Size& imageSize, const Image& image, const Rect& rect);

        void drawBitmapImage(const Size& imageSize,
                             const void* pixels,
                             const Matrix& trans);

    protected:
        SkiaGraphics() : _canvas(NULL)
        {
            _stateStack.push(State());
            _path.setFillType(SkPath::FillType::kEvenOdd_FillType);
            _stateStack.top().paint.setAntiAlias(true);
            _stateStack.top().paint.setFilterBitmap(true);
        }

        void setCanvas(SkCanvas* cav)
        {
            _canvas = cav;
        }

    private:
        struct State
        {
            State()
            {
                strokeColor = SkColorSetARGB(255, 0, 0, 0);
                fillColor = SkColorSetARGB(255, 0, 0, 0);
            }
            SkPaint paint;
            SkColor strokeColor;
            SkColor fillColor;
        };
        void drawShader(SkShader* shader, const Matrix& trans);
        void drawBitmap(const Size& imageSize,
                        const SkBitmap& bitmap,
                        const Matrix& trans);

    private:
        SkPath _path;
        SkCanvas* _canvas;
        std::stack<State> _stateStack;
    };

    ///////////////////////////////////////////////////////
    class SkiaBitmapGraphics : public SkiaGraphics
    {
    public:
        explicit SkiaBitmapGraphics(int width, int height, PixelFormat pixelFormat);
        ~SkiaBitmapGraphics();

        fla::Image::Ptr createImage();
        fla::BitmapData::Ptr getBitmapData() const
        {
            return _bitmapData;
        }
        void flipAndScale(real_t scale);

    private:
        SkCanvas* _bitmapCanvas;
        fla::BitmapData::Ptr _bitmapData;
    };
}

#endif
