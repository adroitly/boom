//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================
#include "../../base/fla_Base.h"

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_QT)

#include "fla_QtGraphics.h"
#include "fla_QtImage.h"
#include "core/base/fla_utils.h"
#include "core/base/fla_Image.h"
#include "libra/libra_math.h"
#include <QtGui/QImage>

namespace fla
{
    static inline QColor s_makeColor(real_t r, real_t g, real_t b, real_t a)
    {
        return QColor(r * 255, g * 255, b * 255, a * 255);
    }

    static inline QColor s_makeColor(const Color4& color)
    {
        return s_makeColor(color.red, color.green, color.blue, color.alpha);
    }

    static inline QRectF s_makeRect(const Rect& rect)
    {
        return QRectF(rect.x, rect.y, rect.width, rect.height);
    }

    static inline QMatrix s_makeMatrix(const Matrix& trans)
    {
        real_t a, b, c, d, tx, ty;
        trans.get(a, b, c, d, tx, ty);
        return QMatrix(a, b, c, d, tx, ty);
    }

    ////////////////////////////////////////////////////////
    QtGraphics::QtGraphics(QPainter* painter) : _painter(painter)
    {
        _stateStack.push(State());
        if (painter)
        {
            _painter->setRenderHint(QPainter::Antialiasing, true);
        }
    }

    void QtGraphics::setPainter(QPainter* painter)
    {
        _painter = painter;
    }

    void QtGraphics::moveTo(real_t x, real_t y)
    {
        _path.moveTo(x, y);
    }

    void QtGraphics::lineTo(real_t x, real_t y)
    {
        _path.lineTo(x, y);
    }

    void QtGraphics::quadCurveTo(real_t ctlx, real_t ctly, real_t x, real_t y)
    {
        _path.quadTo(ctlx, ctly, x, y);
    }

    void QtGraphics::beginPath()
    {
        QPainterPath().swap(_path);
    }

    void QtGraphics::closePath()
    {
        _path.closeSubpath();
    }

    void QtGraphics::setStrokeColor(real_t r, real_t g, real_t b, real_t a)
    {
        _stateStack.top().pen.setColor(s_makeColor(r, g, b, a));
    }

    void QtGraphics::setFillColor(real_t r, real_t g, real_t b, real_t a)
    {
        _stateStack.top().brush.setColor(s_makeColor(r, g, b, a));
    }

    void QtGraphics::scaleCTM(real_t sx, real_t sy)
    {
        _painter->scale(sx, sy);
    }

    void QtGraphics::translateCTM(real_t tx, real_t ty)
    {
        _painter->translate(tx, ty);
    }

    void QtGraphics::rotateCTM(real_t angle)
    {
        _painter->rotate(libra_radian_to_degree(angle));
    }

    void QtGraphics::concatCTM(const Matrix& trans)
    {
        _painter->setMatrix(s_makeMatrix(trans), true);
    }

    void QtGraphics::drawPath(DrawingMode mode)
    {
        if (mode == PathEOFill)
        {
            _painter->setPen(Qt::PenStyle::NoPen);
            _painter->setBrush(_stateStack.top().brush);
        }
        else if (mode == PathStroke)
        {
            _painter->setPen(_stateStack.top().pen);
            _painter->setBrush(Qt::BrushStyle::NoBrush);
        }
        else if (mode == PathEOFillStroke)
        {
            _painter->setPen(_stateStack.top().pen);
            _painter->setBrush(_stateStack.top().brush);
        }
        _painter->drawPath(_path);
        clearPath();
    }

    void QtGraphics::setLineWidth(real_t lineWidth)
    {
        _stateStack.top().pen.setWidth(lineWidth);
    }

    void QtGraphics::saveGState()
    {
        _painter->save();
        _stateStack.push(_stateStack.top());
    }

    void QtGraphics::restoreGState()
    {
        _painter->restore();
        if (_stateStack.size() > 1)
        {
            _stateStack.pop();
        }
    }

    void QtGraphics::setLineCap(LineCap lineCap)
    {
        _stateStack.top().pen.setCapStyle((Qt::PenCapStyle)lineCap);
    }

    void QtGraphics::setMiterLimit(real_t limit)
    {
        _stateStack.top().pen.setMiterLimit(limit);
    }

    void QtGraphics::setLineJoin(LineJoin join)
    {
        _stateStack.top().pen.setJoinStyle((Qt::PenJoinStyle)join);
    }

    void QtGraphics::clearPath()
    {
        QPainterPath().swap(_path);
    }

    void QtGraphics::clipToRect(const Rect& rt)
    {
        _painter->setClipRect(s_makeRect(rt));
    }

    void QtGraphics::drawGradient(const QGradient& gradient, const Matrix& trans)
    {
        QBrush brush(gradient);
        brush.setMatrix(s_makeMatrix(trans));
        _painter->setBrush(brush);
        _painter->setPen(Qt::PenStyle::NoPen);
        _painter->drawPath(_path);
        clearPath();
    }

    static void s_setupGradient(QGradient& gradient,
                                const std::vector<Color4>& colors,
                                const std::vector<real_t>& locations)
    {
        gradient.setInterpolationMode(QGradient::ComponentInterpolation);
        for (size_t i = 0; i < locations.size(); i++)
        {
            gradient.setColorAt(locations[i], s_makeColor(colors[i]));
        }
    }

    void QtGraphics::drawGradient(const std::vector<Color4>& colors,
                                  const std::vector<real_t>& locations,
                                  bool isLinaer,
                                  real_t radius,
                                  const Matrix& trans)
    {
        if (isLinaer)
        {
            QLinearGradient gradient(-radius, 0, +radius, 0);
            s_setupGradient(gradient, colors, locations);
            drawGradient(gradient, trans);
        }
        else
        {
            QRadialGradient gradient(0, 0, radius);
            s_setupGradient(gradient, colors, locations);
            drawGradient(gradient, trans);
        }
    }

    void QtGraphics::drawImage(const Size& imageSize, const Image& rawImage, const Matrix& trans)
    {
        QImage image = QtImage::createQImage(rawImage, imageSize);
        QBrush brush(image);
        auto kk = s_makeMatrix(trans);

        brush.setMatrix(kk);
        _painter->setBrush(brush);
        _painter->setPen(Qt::PenStyle::NoPen);
        _painter->drawPath(_path);
        clearPath();
    }

    void QtGraphics::drawImage(const Size& imageSize, const Image& rawImage, const Rect& rect)
    {
        QImage image = QtImage::createQImage(rawImage, imageSize);
        _painter->drawImage(s_makeRect(rect), image);
    }

    ///////////////////////////////////////////////////////////////////////
    QtBitmapGraphics::QtBitmapGraphics(int width, int height, PixelFormat pixelFormat)
        : QtGraphics(nullptr)
    {
        if (pixelFormat == PixelFormat::RGBA4444)
        {
            pixelFormat = PixelFormat::ARGB4444;
        }
        _bitmapData = fla::BitmapData::create(width, height, pixelFormat);
        _image = fla::QtImage::createQImage(_bitmapData);
        _painter.reset(new QPainter(&_image));
        _painter->setRenderHint(QPainter::Antialiasing, true);
        _painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
        setPainter(_painter.get());
    }

    void QtBitmapGraphics::flipAndScale(real_t scale)
    {
        this->scaleCTM(scale, scale);
    }

    fla::Image::Ptr QtBitmapGraphics::createImage() const
    {
        return QtImage::create(_bitmapData);
    }

    fla::BitmapData::Ptr QtBitmapGraphics::getBitmapData() const
    {
        return _bitmapData;
    }
}

#endif
