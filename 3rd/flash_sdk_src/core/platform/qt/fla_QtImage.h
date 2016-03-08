//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_QTBITMAP__
#define __FLA_QTBITMAP__

#include "core/base/fla_Image.h"
#include "core/base/fla_BitmapData.h"
#include <memory>
#include <QtGui/QImage>

namespace fla
{
    class QtImage : public Image
    {
    public:
        static Ptr create(const BitmapData::Ptr& bitmapData);
        static Ptr create();

        virtual Size getSize() const override;
        virtual void savePng(const std::string& path) override;
        virtual bool isSupportScale() const override;
        virtual Ptr scaleImageData(float scale, const Size& oldSize, Size* newSize) override;

        static QImage createQImage(BitmapData::Ptr& bitmapData);
        static QImage createQImage(const Image& image, const Size& imageSize);
        static QByteArray saveToByteArray(QImage image, const char* format);

    private:
        QtImage(const BitmapData::Ptr& bitmapData);
        QtImage();

    private:
        fla::BitmapData::Ptr _bitmapData;
        QImage               _image;
    };
}

#endif
