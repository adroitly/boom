//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../../base/fla_Base.h"
#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_MAC) || (FLA_TARGET_PLATFORM == FLA_PLATFORM_IOS)

#include "fla_QuartzGraphics.h"
#include "fla_QuartzImage.h"
#include "clover/ScopeGuard.h"
#include "fla_CFScopeRelease.h"

namespace fla
{
    namespace
    {
        template <bool SameFloat>
        struct CreateGradient
        {
            static CGGradientRef action(CGColorSpaceRef space,
                                        const std::vector<Color4>& colors,
                                        const std::vector<real_t>& locations)
            {
                assert(colors.size() == locations.size());
                CGFloat tmpColors[colors.size() * 4];
                CGFloat tmpLocations[locations.size()];
                for (auto i = 0; i < colors.size(); i++)
                {
                    CGFloat* ptr = tmpColors + i * 4;
                    ptr[0] = colors[i].red;
                    ptr[1] = colors[i].green;
                    ptr[2] = colors[i].blue;
                    ptr[3] = colors[i].alpha;
                    tmpLocations[i] = locations[i];
                }
                return CGGradientCreateWithColorComponents(
                    space, tmpColors, tmpLocations, colors.size());
            }
        };

        template <>
        struct CreateGradient<true>
        {
            static CGGradientRef action(CGColorSpaceRef space,
                                        const std::vector<ColorBase<CGFloat>>& colors,
                                        const std::vector<CGFloat>& locations)
            {
                assert(colors.size() == locations.size());
                return CGGradientCreateWithColorComponents(
                    space, &colors[0].red, &locations[0], colors.size());
            }
        };
    }

    inline CGAffineTransform s_makeTransform(const Matrix& trans)
    {
        CGAffineTransform m;
        trans.get(m.a, m.b, m.c, m.d, m.tx, m.ty);
        return m;
    }

    inline CGRect s_makeRect(const Rect& rect)
    {
        return CGRectMake(rect.x, rect.y, rect.width, rect.height);
    }

    inline CGRect s_getImageBounds(CGImageRef image)
    {
        size_t width = CGImageGetWidth(image);
        size_t height = CGImageGetHeight(image);
        return CGRectMake(0, 0, width, height);
    }

    static void s_drawImagePattern(void* info, CGContextRef context)
    {
        CGImageRef patternImage = (CGImageRef)info;
        CGRect bounds = s_getImageBounds(patternImage);
        CGContextTranslateCTM(context, 0, bounds.size.height);
        CGContextScaleCTM(context, 1, -1);
        CGContextDrawImage(context, bounds, patternImage);
    }

    static CGPatternRef s_createPattern(CGImageRef patternImage,
                                        const CGAffineTransform& transform)
    {
        static CGPatternCallbacks callbacks = { 0, &s_drawImagePattern, NULL };
        auto imageBounds = s_getImageBounds(patternImage);
        return CGPatternCreate(patternImage,
                               imageBounds,
                               transform,
                               CGImageGetWidth(patternImage),
                               CGImageGetHeight(patternImage),
                               kCGPatternTilingNoDistortion,
                               true,
                               &callbacks);
    }

    static CGDataProviderRef s_createDataProvider(const std::vector<uint8_t>& v)
    {
        CFDataRef data =
            CFDataCreateWithBytesNoCopy(nullptr, &v[0], v.size(), kCFAllocatorNull);
        CF_SCOPE_RELEASE(data);
        CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData(data);
        return dataProvider;
    }

    inline CGImageRef s_createJPEGImage(const std::vector<uint8_t>& jpeg)
    {
        CGDataProviderRef dataProvider = s_createDataProvider(jpeg);
        CF_SCOPE_RELEASE(dataProvider);
        CGImageRef image = CGImageCreateWithJPEGDataProvider(
            dataProvider, NULL, true, kCGRenderingIntentDefault);
        return image;
    }

    inline CGImageRef s_createPNGImage(const std::vector<uint8_t>& png)
    {
        CGDataProviderRef dataProvider = s_createDataProvider(png);
        CF_SCOPE_RELEASE(dataProvider);
        CGImageRef image = CGImageCreateWithPNGDataProvider(
            dataProvider, NULL, true, kCGRenderingIntentDefault);
        return image;
    }

    static CGImageRef s_createImage(const Image& image, const Size& imageSize)
    {
        switch (image.getImageType())
        {
            case Image::ImageType::Bitmap:
            {
                auto& bitmap = image.getImageData();
                return createRefWithNoCopyPixels(
                    &bitmap[0], imageSize.width, imageSize.height);
            }
            break;

            case Image::ImageType::Jpeg:
                return s_createJPEGImage(image.getImageData());
                break;

            case Image::ImageType::Png:
                return s_createPNGImage(image.getImageData());
                break;

            default:
                break;
        }
        return NULL;
    }
    
    QuartzGraphics::QuartzGraphics(CGContextRef ctx)
    {
        setContent(ctx, true);
    }
    
    QuartzGraphics::QuartzGraphics()
    {
        setContent(nullptr, false);
    }
    
    void QuartzGraphics::setContent(CGContextRef content, bool checkInitCTM)
    {
        _context = content;
        _checkInitCTM = checkInitCTM;
        if (_checkInitCTM)
        {
            assert(_context);
            _initInvertCTM = CGContextGetCTM(_context);
            _initInvertCTM = CGAffineTransformInvert(_initInvertCTM);
        }
        else
        {
            _initInvertCTM = CGAffineTransformIdentity;
        }
    }

    void QuartzGraphics::drawGradient(const std::vector<Color4>& colors,
                                      const std::vector<real_t>& locations,
                                      bool isLinaer,
                                      real_t radius,
                                      const Matrix& trans)
    {
        saveGState();
        CLOVER_SCOPE_EXIT
        {
            restoreGState();
        };

        clipPath();
        concatCTM(trans);

        CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
        CF_SCOPE_RELEASE(space);

        CGGradientRef gradient =
            CreateGradient<std::is_same<CGFloat, real_t>::value>::action(
                space, colors, locations);
        CF_SCOPE_RELEASE(gradient);
        
        if (isLinaer)
        {
            CGPoint start = CGPointMake(-radius, 0);
            CGPoint end = CGPointMake(radius, 0);
            CGContextDrawLinearGradient(_context,
                                        gradient,
                                        start,
                                        end,
                                        kCGGradientDrawsBeforeStartLocation |
                                            kCGGradientDrawsAfterEndLocation);
        }
        else
        {
            CGContextDrawRadialGradient(_context,
                                        gradient,
                                        CGPointMake(0, 0),
                                        0,
                                        CGPointMake(0, 0),
                                        radius,
                                        kCGGradientDrawsBeforeStartLocation |
                                            kCGGradientDrawsAfterEndLocation);
        }
    }

    static CGContextRef s_newBitmapContext(void* data, int imgWith, int imgHeight)
    {
        CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
        CF_SCOPE_RELEASE(colorSpaceRef);
        size_t bytesPerRow = imgWith * 4;
        CGContextRef context = CGBitmapContextCreate(
            data,
            imgWith,
            imgHeight,
            8,
            bytesPerRow,
            colorSpaceRef,
            (kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big));
        return context;
    }
    
    
    void QuartzGraphics::drawImageRef(const Size& imageSize,
                                      CGImageRef image,
                                      const Matrix& trans)
    {
        if (image)
        {
            CGAffineTransform transform = CGContextGetCTM(_context);
            if (_checkInitCTM)
            {
                transform = CGAffineTransformConcat(transform, _initInvertCTM);
            }
            transform = CGAffineTransformConcat(s_makeTransform(trans), transform);

            CGColorSpaceRef patternSpace = CGColorSpaceCreatePattern(NULL);
            CF_SCOPE_RELEASE(patternSpace);
            CGContextSetFillColorSpace(_context, patternSpace);

            auto pattern = s_createPattern(image, transform);
            CF_SCOPE_RELEASE(pattern);

            CGFloat components[] = { 1, 1, 1, 1 };
            CGContextSetFillPattern(_context, pattern, components);
            CGContextFillPath(_context);
        }
        else
        {
            CGContextSetRGBFillColor(_context, 1.0, 0.0, 0.0, 1.0);
            CGContextFillPath(_context);
        }
    }

    void QuartzGraphics::drawBitmapImage(const Size& imageSize,
                                         const void* pixels,
                                         const Matrix& trans)
    {
        CGImageRef image =
            createRefWithNoCopyPixels(pixels, imageSize.width, imageSize.height);
        CF_SCOPE_RELEASE(image);
        drawImageRef(imageSize, image, trans);
    }

    void QuartzGraphics::drawImage(const Size& imageSize,
                                   const Image& img,
                                   const Matrix& trans)
    {
        CGImageRef image = s_createImage(img, imageSize);
        CF_SCOPE_RELEASE(image);
        drawImageRef(imageSize, image, trans);
    }

    void QuartzGraphics::drawImage(const Size& imageSize,
                                   const Image& img,
                                   const Rect& rect)
    {
        CGImageRef image = s_createImage(img, imageSize);
        CF_SCOPE_RELEASE(image);
        if (image)
        {
            CGContextDrawImage(_context, s_makeRect(rect), image);
        }
    }

    QuartzBitmapGraphics::QuartzBitmapGraphics(int width,
                                               int height,
                                               PixelFormat pixelFormat)
    {
        // 不支持RGBA4444
        pixelFormat = PixelFormat::RGBA8888;
        _bitmapData = BitmapData::create(width, height, pixelFormat);
        _bitmapContent = s_newBitmapContext(_bitmapData->getPixels(), width, height);
        setContent(_bitmapContent, false);
    }

    QuartzBitmapGraphics::~QuartzBitmapGraphics()
    {
        CGContextRelease(_bitmapContent);
        _bitmapContent = NULL;
    }

    Image::Ptr QuartzBitmapGraphics::createImage() const
    {
        CGImageRef image = CGBitmapContextCreateImage(_bitmapContent);
        CF_SCOPE_RELEASE(image);
        return QuartzImage::create(image);
    }

    void QuartzGraphics::ellipse(const Rect& rect)
    {
        CGContextAddEllipseInRect(_context, s_makeRect(rect));
    }

    void QuartzGraphics::moveTo(real_t x, real_t y)
    {
        CGContextMoveToPoint(_context, x, y);
    }

    void QuartzGraphics::lineTo(real_t x, real_t y)
    {
        CGContextAddLineToPoint(_context, x, y);
    }

    void QuartzGraphics::quadCurveTo(real_t ctlx, real_t ctly, real_t x, real_t y)
    {
        CGContextAddQuadCurveToPoint(_context, ctlx, ctly, x, y);
    }

    void QuartzGraphics::beginPath()
    {
        CGContextBeginPath(_context);
    }

    void QuartzGraphics::closePath()
    {
        CGContextClosePath(_context);
    }

    void QuartzGraphics::drawPath(DrawingMode mode)
    {
        CGContextDrawPath(_context, (CGPathDrawingMode)mode);
    }

    void QuartzGraphics::setStrokeColor(real_t r, real_t g, real_t b, real_t a)
    {
        CGContextSetRGBStrokeColor(_context, r, g, b, a);
    }

    void QuartzGraphics::setFillColor(real_t r, real_t g, real_t b, real_t a)
    {
        CGContextSetRGBFillColor(_context, r, g, b, a);
    }

    void QuartzGraphics::scaleCTM(real_t sx, real_t sy)
    {
        CGContextScaleCTM(_context, sx, sy);
    }

    void QuartzGraphics::translateCTM(real_t tx, real_t ty)
    {
        CGContextTranslateCTM(_context, tx, ty);
    }

    void QuartzGraphics::rotateCTM(real_t angle)
    {
        CGContextRotateCTM(_context, angle);
    }

    void QuartzGraphics::concatCTM(const Matrix& trans)
    {
        CGAffineTransform m = s_makeTransform(trans);
        CGContextConcatCTM(_context, m);
    }

    void QuartzGraphics::setLineWidth(real_t lineWidth)
    {
        CGContextSetLineWidth(_context, lineWidth);
    }

    void QuartzGraphics::saveGState()
    {
        CGContextSaveGState(_context);
    }

    void QuartzGraphics::restoreGState()
    {
        CGContextRestoreGState(_context);
    }

    void QuartzGraphics::setLineCap(LineCap lineCap)
    {
        CGContextSetLineCap(_context, (CGLineCap)lineCap);
    }

    void QuartzGraphics::setMiterLimit(real_t limit)
    {
        CGContextSetMiterLimit(_context, limit);
    }

    void QuartzGraphics::setLineJoin(LineJoin join)
    {
        CGContextSetLineJoin(_context, (CGLineJoin)join);
    }

    void QuartzGraphics::clipPath()
    {
        CGContextEOClip(_context);
    }

    void QuartzGraphics::clipToRect(const Rect& rt)
    {
        CGContextClipToRect(_context, s_makeRect(rt));
    }

    BitmapData::Ptr QuartzBitmapGraphics::getBitmapData() const
    {
        return _bitmapData;
    }

    void QuartzBitmapGraphics::flipAndScale(real_t scale)
    {
        translateCTM(0, _bitmapData->getHeight());
        scaleCTM(scale, -scale);
    }
}

#endif
