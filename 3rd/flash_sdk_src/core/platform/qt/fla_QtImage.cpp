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

#include "fla_QtImage.h"
#include "clover/ScopeGuard.h"
#include "libra/libra_safe.h"
#include <assert.h>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtGui/QPainter>

namespace fla
{
    QtImage::Ptr QtImage::create(const BitmapData::Ptr& bitmapData)
    {
        return Ptr(new QtImage(bitmapData), false);
    }

    QtImage::Ptr QtImage::create()
    {
        return Ptr(new QtImage(), false);
    }

    QtImage::QtImage(const fla::BitmapData::Ptr& bitmapData)
    {
        _bitmapData = bitmapData;
    }

    QtImage::QtImage()
    {
    }

    Size QtImage::getSize() const
    {
        if (_bitmapData)
        {
            return Size(_bitmapData->getWidth(), _bitmapData->getHeight());
        }

        if (_image.isNull())
        {
            return Size();
        }

        return Size(_image.width(), _image.height());
    }

    static inline QImage::Format s_transPixelFormat(PixelFormat format)
    {
        assert(format != PixelFormat::RGBA4444);
        if (format == PixelFormat::ARGB4444)
        {
            return QImage::Format_ARGB4444_Premultiplied;
        }
        return QImage::Format_RGBA8888_Premultiplied;
    }

    QImage QtImage::createQImage(BitmapData::Ptr& bitmapData)
    {
        auto imageFormat = s_transPixelFormat(bitmapData->getPixelFormat());
        auto pixels = (uchar*)bitmapData->getPixels();
        auto bitmapWidth = bitmapData->getWidth();
        auto bitmapHeight = bitmapData->getHeight();
        return QImage(pixels, bitmapWidth, bitmapHeight, imageFormat);
    }

    QImage QtImage::createQImage(const Image& image, const Size& imageSize)
    {
        switch (image.getImageType())
        {
            case Image::ImageType::Bitmap:
            {
                auto& bitmap = image.getImageData();
                return QImage(&bitmap[0],
                              imageSize.width,
                              imageSize.height,
                              QImage::Format_RGBA8888_Premultiplied);
            }
            break;

            case Image::ImageType::Png:
            case Image::ImageType::Jpeg:
            {
                auto& pngData = image.getImageData();
                return QImage::fromData(&pngData[0], pngData.size());
            }

            default:
                break;
        }
        return QImage();
    }

    void QtImage::savePng(const std::string& path)
    {
        if (_image.isNull())
        {
            _image = createQImage(_bitmapData);
        }

#ifdef _MSC_VER
        QFile file(path.c_str());
        file.open(QIODevice::WriteOnly);
        _image.save(&file, "png");
        file.close();
#else
        // 上面的代码使用wingw编译，在xp系统输出不了png
        // 这里注意打开使用二进制方式，不能 fopen(path.c_str(), "w");
        FILE* fileHandle = fopen(path.c_str(), "wb+");
        QFile file;
        file.open(fileHandle, QIODevice::WriteOnly);
        _image.save(&file, "png");
        file.close();
        fclose(fileHandle);
#endif
    }

    bool QtImage::isSupportScale() const
    {
        return true;
    }

    QByteArray QtImage::saveToByteArray(QImage image, const char* format)
    {
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, format);
        return bytes;
    }

    QtImage::Ptr QtImage::scaleImageData(float scale, const Size& oldSize, Size* pnewSize)
    {
        QImage image = QtImage::createQImage(*this, oldSize);
        Size newSize = oldSize * scale;
        int newWidth = std::ceil(newSize.width);
        int newHeight = std::ceil(newSize.height);

        std::vector<uint8_t> pixels;
        pixels.resize(newWidth * newHeight * 4);

        image.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QImage newImage(&pixels[0], newWidth, newHeight, QImage::Format_RGBA8888_Premultiplied);
        QPainter painter(&newImage);
        painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.scale(scale, scale);
        painter.drawImage(QPoint(0, 0), image);

        QByteArray imageData;
        ImageType imageType;
        if (getImageType() == ImageType::Png || getImageType() == ImageType::Bitmap)
        {
            imageData = saveToByteArray(newImage, "png");
            imageType = ImageType::Png;
        }
        else
        {
            imageData = saveToByteArray(newImage, "jpg");
            imageType = ImageType::Jpeg;
        }

        auto result = QtImage::create();
        clover::LightData lightData(imageData.data(), imageData.size());
        result->setImageData(lightData, imageType);

        if (pnewSize != nullptr)
        {
            *pnewSize = newSize;
        }
        return result;
    }
}

#endif
