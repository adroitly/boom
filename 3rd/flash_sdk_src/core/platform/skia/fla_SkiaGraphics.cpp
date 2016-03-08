//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../../base/fla_Base.h"

#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_SKIA)

#include <algorithm>
#include "fla_SkiaGraphics.h"
#include "fla_SkiaImage.h"
#include "SkGradientShader.h"
#include "SkImageDecoder.h"

namespace fla
{
    static inline SkColor s_makeColor(real_t r, real_t g, real_t b, real_t a)
    {
        return SkColorSetARGB(a * 255, r * 255, g * 255, b * 255);
    }

    inline static SkColor s_makeColor2(const Color4& color)
    {
        return s_makeColor(color.red, color.green, color.blue, color.alpha);
    }

    inline static SkRect s_makeRect(const Rect& rt)
    {
        SkRect rect;
        rect.set(rt.x, rt.y, rt.x + rt.width, rt.y + rt.height);
        return rect;
    }

    static SkMatrix s_makeMatrix(const Matrix& trans)
    {
        real_t a, b, c, d, tx, ty;
        trans.get(a, b, c, d, tx, ty);

        SkMatrix m;
        m.setAll(a, c, tx, b, d, ty, 0, 0, 1);

        return m;
    }

    static SkBitmap s_createImage(const Size& imageSize, const Image& img)
    {
        SkBitmap image;
        switch (img.getImageType())
        {
            case Image::ImageType::Bitmap:
            {
                auto& bitmap = img.getImageData();
                image.setConfig(SkBitmap::kARGB_8888_Config, imageSize.width, imageSize.height);
                image.setPixels((void*)&bitmap[0]);
            }
            break;

            case Image::ImageType::Png:
            case Image::ImageType::Jpeg:
            {
                auto& png = img.getImageData();
                SkImageDecoder::DecodeMemory(&png[0], png.size(), &image);
            }
            break;

            default:
                break;
        }
        return image;
    }

    void SkiaGraphics::drawBitmap(const Size& imageSize,
                                  const SkBitmap& bitmap,
                                  const Matrix& trans)
    {
        if (!bitmap.isNull())
        {
            SkShader* shader = SkShader::CreateBitmapShader(bitmap,
                                                            SkShader::kRepeat_TileMode,
                                                            SkShader::kRepeat_TileMode);
            drawShader(shader, trans);
            SkSafeUnref(shader);
        }
        _path.reset();
    }

    void SkiaGraphics::drawImage(const Size& imageSize, const Image& image, const Matrix& trans)
    {
        SkBitmap bitmap = s_createImage(imageSize, image);
        drawBitmap(imageSize, bitmap, trans);
    }

    void SkiaGraphics::clipToRect(const Rect& rt)
    {
        _canvas->clipRect(s_makeRect(rt));
    }

    void SkiaGraphics::drawBitmapImage(const Size& imageSize,
                                       const void* pixels,
                                       const Matrix& trans)
    {
        SkBitmap bitmap;
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, imageSize.width, imageSize.height);
        bitmap.setPixels((void*)pixels);
        drawBitmap(imageSize, bitmap, trans);
    }

    void SkiaGraphics::drawImage(const Size& imageSize, const Image& image, const Rect& rect)
    {
        SkBitmap bitmap = s_createImage(imageSize, image);
        if (!bitmap.isNull())
        {
            _canvas->drawBitmapRect(bitmap, s_makeRect(rect), nullptr);
        }
    }

    void SkiaGraphics::drawShader(SkShader* shader, const Matrix& trans)
    {
        shader->setLocalMatrix(s_makeMatrix(trans));
        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setFilterBitmap(true);
        paint.setShader(shader);
        _canvas->drawPath(_path, paint);
        _path.reset();
    }

    void SkiaGraphics::drawGradient(const std::vector<Color4>& colors,
                                    const std::vector<real_t>& locations,
                                    bool isLinaer,
                                    real_t radius,
                                    const Matrix& trans)
    {
        SkColor tmpColors[colors.size()];
        SkScalar tmpLocs[locations.size()];

        std::transform(colors.begin(), colors.end(), tmpColors, s_makeColor2);
        std::copy(locations.begin(), locations.end(), tmpLocs);

        if (isLinaer)
        {
            SkPoint myPts[] = {
                { -radius, 0 }, { +radius, 0 },
            };
            SkShader* shader = SkGradientShader::CreateLinear(myPts,
                                                              tmpColors,
                                                              tmpLocs,
                                                              colors.size(),
                                                              SkShader::kClamp_TileMode);
            drawShader(shader, trans);
            SkSafeUnref(shader);
        }
        else
        {
            SkShader* shader = SkGradientShader::CreateRadial(SkPoint::Make(0, 0),
                                                              radius,
                                                              tmpColors,
                                                              tmpLocs,
                                                              colors.size(),
                                                              SkShader::kClamp_TileMode);
            drawShader(shader, trans);
            SkSafeUnref(shader);
        }
    }

    SkiaBitmapGraphics::SkiaBitmapGraphics(int width, int height, PixelFormat pixelFormat)
    {

        pixelFormat = PixelFormat::RGBA8888;
        SkBitmap bitmap;
        _bitmapData = fla::BitmapData::create(width, height, pixelFormat);
        bitmap.setConfig(SkBitmap::kARGB_8888_Config,
                         _bitmapData->getWidth(),
                         _bitmapData->getHeight());
        bitmap.setPixels(_bitmapData->getPixels());
        _bitmapCanvas = new SkCanvas(bitmap);
        setCanvas(_bitmapCanvas);
    }

    SkiaBitmapGraphics::~SkiaBitmapGraphics()
    {
        SkSafeUnref(_bitmapCanvas);
    }

    fla::Image::Ptr SkiaBitmapGraphics::createImage()
    {
        return fla::SkiaImage::create();
    }

    void SkiaBitmapGraphics::flipAndScale(real_t scale)
    {
        this->scaleCTM(scale, scale);
    }

    ///////////////////////////////////////////////////////////////////
    void SkiaGraphics::moveTo(real_t x, real_t y)
    {
        _path.moveTo(x, y);
    }

    void SkiaGraphics::ellipse(const Rect& rect)
    {
        _path.addArc(s_makeRect(rect), 0, 360);
    }

    void SkiaGraphics::lineTo(real_t x, real_t y)
    {
        _path.lineTo(x, y);
    }

    void SkiaGraphics::quadCurveTo(real_t ctlx, real_t ctly, real_t x, real_t y)
    {
        _path.quadTo(ctlx, ctly, x, y);
    }

    void SkiaGraphics::beginPath()
    {
        _path.reset();
    }

    void SkiaGraphics::closePath()
    {
        _path.close();
    }

    void SkiaGraphics::drawPath(DrawingMode mode)
    {
        if (mode == PathEOFill)
        {
            auto& paint = _stateStack.top().paint;
            paint.setStyle(SkPaint::Style::kFill_Style);
            paint.setColor(_stateStack.top().fillColor);
            _canvas->drawPath(_path, paint);
        }

        else if (mode == PathStroke)
        {
            auto& paint = _stateStack.top().paint;
            paint.setStyle(SkPaint::Style::kStroke_Style);
            paint.setColor(_stateStack.top().strokeColor);
            _canvas->drawPath(_path, paint);
        }

        else if (mode == PathEOFillStroke)
        {
            auto& paint = _stateStack.top().paint;

            paint.setStyle(SkPaint::Style::kFill_Style);
            paint.setColor(_stateStack.top().fillColor);
            _canvas->drawPath(_path, _stateStack.top().paint);

            paint.setStyle(SkPaint::Style::kStroke_Style);
            paint.setColor(_stateStack.top().strokeColor);
            _canvas->drawPath(_path, paint);
        }

        _path.reset();
    }

    void SkiaGraphics::setStrokeColor(real_t r, real_t g, real_t b, real_t a)
    {
        _stateStack.top().strokeColor = s_makeColor(r, g, b, a);
    }

    void SkiaGraphics::setFillColor(real_t r, real_t g, real_t b, real_t a)
    {
        _stateStack.top().fillColor = s_makeColor(r, g, b, a);
    }

    void SkiaGraphics::scaleCTM(real_t sx, real_t sy)
    {
        _canvas->scale(sx, sy);
    }

    void SkiaGraphics::translateCTM(real_t tx, real_t ty)
    {
        _canvas->translate(tx, ty);
    }

    void SkiaGraphics::rotateCTM(real_t angle)
    {
        angle = angle * 180 / M_PI;
        _canvas->rotate(angle);
    }

    void SkiaGraphics::concatCTM(const Matrix& trans)
    {
        _canvas->concat(s_makeMatrix(trans));
    }

    void SkiaGraphics::setLineWidth(real_t lineWidth)
    {
        _stateStack.top().paint.setStrokeWidth(lineWidth);
    }

    void SkiaGraphics::saveGState()
    {
        _canvas->save();
        _stateStack.push(_stateStack.top());
    }
}

#endif
