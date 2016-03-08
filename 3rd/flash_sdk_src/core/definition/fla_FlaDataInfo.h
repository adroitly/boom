//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_FILEINFO_H__
#define __FLA_FILEINFO_H__

#include <string>
#include <map>
#include "clover/IntrusiveObject.h"

namespace fla
{
    class DefinitionImage;
    class FlaDataInfo : public clover::IntrusiveObject<FlaDataInfo>
    {
    public:
        static Ptr create();

        // 帧率
        void setFrameRate(float frameRate);
        float getFrameRate() const;

        // Md5
        void setDataMd5(const std::string& md5str, const uint8_t md5[16]);
        const std::string& getMd5String() const;

        bool isSameMd5(const FlaDataInfo& dataInfo);

    protected:
        FlaDataInfo();

    private:
        uint8_t _md5[16];
        std::string _md5str;
        float _frameRate;
    };

    class FlaDataInfoWithImages : public FlaDataInfo
    {
    public:
        typedef boost::intrusive_ptr<FlaDataInfoWithImages> Ptr;
        static Ptr create();

        boost::intrusive_ptr<DefinitionImage> findImage(int Id) const;
        void addImage(const boost::intrusive_ptr<DefinitionImage>& image);

    private:
        std::map<int, boost::intrusive_ptr<DefinitionImage>> _images;
    };
}

#endif
