//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_QTGRAPHICS__
#define __FLA_QTGRAPHICS__

#include <QtGui/QPainter>
#include <stack>
#include "core/Graphics/fla_Graphics.h"
#include "core/base/fla_BitmapData.h"

namespace fla
{
    class Image;
    class QtGraphics  //: public fla::Graphics
    {
    public:
        QtGraphics(QPainter* painter);
        QtGraphics(const QtGraphics&) = delete;
        QtGraphics& operator=(const QtGraphics&) = delete;

        void setPainter(QPainter* painter);

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
        void restoreGState();

        enum LineCap
        {
            LineCapButt = Qt::PenCapStyle::FlatCap,
            LineCapRound = Qt::PenCapStyle::RoundCap,
            LineCapSquare = Qt::PenCapStyle::SquareCap,
        };

        void setLineCap(LineCap lineCap);
        void setMiterLimit(real_t limit);

        enum LineJoin
        {
            LineJoinMiter = Qt::PenJoinStyle::MiterJoin,
            LineJoinRound = Qt::PenJoinStyle::RoundJoin,
            LineJoinBevel = Qt::PenJoinStyle::BevelJoin,
        };

        void setLineJoin(LineJoin join);

        void drawGradient(const std::vector<Color4>& colors,
                          const std::vector<real_t>& locations,
                          bool isLinaer,
                          real_t radius,
                          const Matrix& trans);

        void drawImage(const Size& imageSize,
                       const Image& image,
                       const Matrix& trans);

        void drawImage(const Size& imageSize,
                       const Image& image,
                       const Rect& rect);
        
        void clipToRect(const Rect& rt);

    private:
        struct State
        {
            State() : brush(Qt::SolidPattern), pen(Qt::SolidLine)
            {
            }
            QBrush brush;
            QPen pen;
        };
        void clearPath();
        void drawGradient(const QGradient& gradient, const Matrix& trans);

    private:
        QPainter* _painter;
        QPainterPath _path;
        std::stack<State> _stateStack;
    };

    ///////////////////////////////////////////////////
    class QtBitmapGraphics : public QtGraphics
    {
    public:
        QtBitmapGraphics(int width, int height, PixelFormat pixelFormat);
        void flipAndScale(real_t scale);

        fla::Image::Ptr createImage() const;
        fla::BitmapData::Ptr getBitmapData() const;

    private:
        fla::BitmapData::Ptr _bitmapData;
        QImage _image;
        std::unique_ptr<QPainter> _painter;
    };
}

#endif
