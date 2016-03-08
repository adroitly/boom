//
//  FlaPreloader.h
//  WeAreHeros
//
//  Created by HJC on 14/12/9.
//
//

#ifndef __FLA_EX_PRELOADER_H__
#define __FLA_EX_PRELOADER_H__

#include "FlaSDK.h"

namespace fla_ex
{
    struct PreloadItem
    {
        PreloadItem()
        {
            format = FlaPixelFormat::RGBA4444;
            scale = 1.0;
        }

        bool operator<(const PreloadItem& rhs) const
        {
            return std::tie(definition, scale) < std::tie(rhs.definition, rhs.scale);
        }

        bool operator==(const PreloadItem& rhs) const
        {
            return definition == rhs.definition && scale == rhs.scale;
        }

        FlaDefinition definition;
        FlaPixelFormat format;
        float scale;
    };

    class Preloader : public cocos2d::Ref
    {
    public:
        std::function<void()> onFinish;
        std::function<void(int total, int current)> onProgress;

        void preload(const std::vector<PreloadItem>& roleItems, const std::vector<PreloadItem>& effectItems);

    private:
        int _totalLoadSize;
        int _currentLoadSize;
    };
}

#endif
